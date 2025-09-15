import sys
import time
import re
import json
from build.Release import zrdds_python as zrpy
from PySide6.QtCore import Qt, QTimer, QPointF
from PySide6.QtGui import QMouseEvent, QColor, QPen, QPalette
from PySide6.QtWidgets import (
    QApplication, QGraphicsScene, QGraphicsView, QGraphicsLineItem, QWidget,
    QVBoxLayout, QHBoxLayout, QPushButton, QSlider, QLabel, QColorDialog
)
from queue import Queue
from PySide6.QtWidgets import (
    QApplication, QGraphicsView, QGraphicsScene, QMainWindow,
    QVBoxLayout, QWidget, QPushButton, QColorDialog, QSlider, QLabel, QHBoxLayout
)



# ========== 工具函数 ==========
def get_event_pos(event: QMouseEvent):
    return event.position().toPoint()

def get_default_pen_color():
    palette = QApplication.instance().palette()
    bg_color = palette.color(QPalette.Window)
    # 判断背景亮度
    brightness = 0.299*bg_color.red() + 0.587*bg_color.green() + 0.114*bg_color.blue()
    # 亮度 < 128 认为深色模式，亮度 >= 128 认为浅色模式
    return QColor("#FFFFFF") if brightness < 128 else QColor("#000000")

# ========== DDS 客户端 ==========
class DDSClient:
    def __init__(self, username):
        self.username = username

        # 创建 DomainParticipant
        factory = zrpy.DomainParticipantFactory.get_instance()
        self.participant = factory.create_participant(
            80,
            zrpy.DomainParticipantQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )

        # Publisher / Subscriber
        self.publisher = self.participant.create_publisher(
            zrpy.PublisherQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        self.subscriber = self.participant.create_subscriber(
            zrpy.SubscriberQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )

        # Topic
        self.topic = self.participant.create_topic(
            "PaintTopic",
            "DDS_Bytes",  # 用字符串消息传递 JSON
            zrpy.TopicQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )

        # Writer / Reader
        self.writer = self.publisher.create_datawriter(
            self.topic,
            zrpy.DataWriterQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )

        self.reader = self.subscriber.create_datareader(
            self.topic,
            zrpy.DataReaderQos.getDefault(),
            None,
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )

    def send(self, msg: dict):
        """发送 JSON 消息"""
        data = json.dumps(msg)
        ret = self.writer.write(data.encode("utf-8"))
        if ret == zrpy.ReturnCode_t.RETCODE_OK:
            print("[调试] 数据发送成功:", data)
        else:
            print("[错误] 数据发送失败:", ret)

    def receive(self):
        """接收消息（非阻塞）"""
        try:
            sample, info, ret = self.reader.take_next_sample()
            if ret == zrpy.ReturnCode_t.RETCODE_OK and info.valid_data:
                return json.loads(sample.decode("utf-8"))
        except Exception as e:
            print("[错误] 接收数据失败:", e)
        return None


# ========== 画板 ==========
class PaintView(QGraphicsView):
    def __init__(self, scene, dds_client):
        super().__init__(scene)
        self.scene = scene
        self.dds = dds_client
        self.pen_color = get_default_pen_color()
        self.pen_width = 2
        self.path_points = []
        self.last_pos = None

        # 定时发送路径（延迟保证连续）
        self.timer = QTimer()
        self.timer.timeout.connect(self.flush_points)
        self.timer.start(95)  # 每80ms发送一次

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            pos = self.mapToScene(event.position().toPoint())
            self.path_points = [(pos.x(), pos.y())]
            self.last_pos = pos

    def mouseMoveEvent(self, event):
        if event.buttons() & Qt.LeftButton and self.last_pos:
            pos = self.mapToScene(event.position().toPoint())
            # 本地画
            self.scene.addLine(self.last_pos.x(), self.last_pos.y(),
                               pos.x(), pos.y(),
                               QPen(self.pen_color, self.pen_width))
            self.path_points.append((pos.x(), pos.y()))
            self.last_pos = pos

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.flush_points(force=True)
            self.last_pos = None
            self.path_points = []

    def flush_points(self, force=False):
        """发送当前路径"""
        if len(self.path_points) > 1:
            msg = {
                "points": [{"x": x, "y": y} for x, y in self.path_points],
                "color": self.pen_color.name(),
                "width": self.pen_width,
                "tool": "pen",
                "username": self.dds.username
            }
            self.dds.send(msg)
            if force:
                self.path_points = []
            else:
                # 保留最后一个点继续画
                self.path_points = [self.path_points[-1]]



# ========== 主窗口 ==========
class PaintWindow(QMainWindow):
    def __init__(self, username):
        super().__init__()
        self.setWindowTitle(f"共享画板 - {username}")
        self.setGeometry(200, 200, 900, 700)

        self.dds = DDSClient(username)
        self.scene = QGraphicsScene()
        self.view = PaintView(self.scene, self.dds)

        # 工具栏
        self.color_btn = QPushButton("颜色")
        self.color_btn.clicked.connect(self.choose_color)

        self.width_slider = QSlider(Qt.Horizontal)
        self.width_slider.setMinimum(1)
        self.width_slider.setMaximum(20)
        self.width_slider.setValue(2)
        self.width_slider.valueChanged.connect(self.change_width)

        self.width_label = QLabel("粗细: 2")

        self.clear_btn = QPushButton("清屏")
        self.clear_btn.clicked.connect(lambda: self.scene.clear())

        tool_layout = QHBoxLayout()
        tool_layout.addWidget(self.color_btn)
        tool_layout.addWidget(self.width_label)
        tool_layout.addWidget(self.width_slider)
        tool_layout.addWidget(self.clear_btn)

        layout = QVBoxLayout()
        layout.addWidget(self.view)
        layout.addLayout(tool_layout)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

        # 定时轮询 DDS 消息
        self.timer = QTimer()
        self.timer.timeout.connect(self.check_messages)
        self.timer.start(100)

    def choose_color(self):
        color = QColorDialog.getColor(self.view.pen_color, self, "选择颜色")
        if color.isValid():
            self.view.pen_color = color

    def change_width(self, value):
        self.view.pen_width = value
        self.width_label.setText(f"粗细: {value}")

    def check_messages(self):
        msg = self.dds.receive()
        if msg:
            try:
                self.draw_remote_line(msg)
            except Exception as e:
                print("[错误] 解析消息失败:", e)

    def draw_remote_line(self, data):
        points = [QPointF(p["x"], p["y"]) for p in data["points"]]
        color = QColor(data["color"])
        width = data["width"]
        username = data.get("username", "未知用户")
        if username == self.dds.username:
          username = None
        # 绘制线条
        for i in range(1, len(points)):
            self.scene.addLine(points[i-1].x(), points[i-1].y(),
                              points[i].x(), points[i].y(),
                              QPen(color, width))

        # 显示名字跟随最后一个点
        if username and points:
          if not hasattr(self, "user_labels"):
              self.user_labels = {}
          text_item = self.user_labels.get(username)
          if not text_item:
              text_item = self.scene.addText(username)
              text_item.setDefaultTextColor(color)  # 颜色跟随笔迹
              font = text_item.font()
              font.setPointSize(14)               # 字体放大
              text_item.setFont(font)
              text_item.setZValue(10)
              self.user_labels[username] = text_item

          # 始终更新颜色，以防对方换颜色
          text_item.setDefaultTextColor(color)
          text_item.setPos(points[-1].x() + 5, points[-1].y() - 5)




# ========== 主程序入口 ==========
if __name__ == "__main__":
    username1 = 'asd'
    username2 ='jkl' 

    app = QApplication(sys.argv)
    win1 = PaintWindow(username1)
    win1.show()
    win2 = PaintWindow(username2)
    win2.show()
    sys.exit(app.exec())
