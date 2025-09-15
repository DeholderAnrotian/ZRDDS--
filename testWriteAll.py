from build.Release import zrdds_python as zrpy
import time


def main():
    factory = zrpy.DomainParticipantFactory.get_instance()
    participant = factory.create_participant(
        80,
        zrpy.DomainParticipantQos.getDefault(),
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )
    publisher = participant.create_publisher(
        zrpy.PublisherQos.getDefault(),
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )

    # 定义所有要测试的类型
    type_list = [
         ("TOPIC_OCTET", "DDS_Octet", 0x12),
        ("TOPIC_BOOLEAN", "DDS_Boolean", True),
        ("TOPIC_SHORT", "DDS_Short", -123),
        ("TOPIC_USHORT", "DDS_UShort", 456),
        ("TOPIC_LONG", "DDS_Long", -7890),
        ("TOPIC_ULONG", "DDS_ULong", 12345),
        ("TOPIC_LONGLONG", "DDS_LongLong", -9876543210),
        ("TOPIC_ULONGLONG", "DDS_ULongLong", 9876543210),
        ("TOPIC_FLOAT", "DDS_Float", 3.14),
        ("TOPIC_DOUBLE", "DDS_Double", 2.718281828),
        ("TOPIC_STRING", "DDS_String", "a"*10),
        ("TOPIC_BYTES", "DDS_Bytes", b"\x01\x02\x03\x04HelloDDS"),
        # ("TOPIC_KEYEDSTRING", "DDS_KeyedString", zrpy.KeyedString("myKey", "Hello KeyedString")),
        # ("TOPIC_KEYEDBYTES", "DDS_KeyedBytes", zrpy.KeyedBytes("myKey", b"\x01\x02\x03\x04HelloDDS")),
    ]

    writers = {}
    for topic_name, type_name, init_val in type_list:
        topic = participant.create_topic(
            topic_name,
            type_name,
            zrpy.TopicQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        writer = publisher.create_datawriter(
            topic,
            zrpy.DataWriterQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        writers[type_name] = (writer, init_val)
        print(f"✅ Created DataWriter for {type_name}")

    # 写入数据
    i = 0  # 初始化计数器
    while True:
        print(f"\n--- Round {i} ---")
        for type_name, (writer, value) in writers.items():
            # 针对不同类型动态修改数据
            if isinstance(value, bool):
                data = not value if i % 2 else value
            elif isinstance(value, int):
                data = value + i
            elif isinstance(value, float):
                data = value * (1 + 0.1 * i)
            elif isinstance(value, str):
                data = f"{value} #{i}"
            else:
                data = value

            ret = writer.write(data)
            if ret == zrpy.ReturnCode_t.RETCODE_OK:
                if type_name == "DDS_KeyedBytes":
                    print(f"Write {type_name}: key={data.get_key()}, value={data.get_value()}")
                if(type_name == "DDS_KeyedString"):
                    print(f"Write {type_name}: key={data.get_key()}, value={data.get_value()}")
                else:
                    print(f"Write {type_name}: {data}")
            else:
                print(f"❌ Write {type_name} failed, ret={ret}")


        i += 1  # 自增计数器
        time.sleep(1)  # 每轮写入间隔，可调整



if __name__ == "__main__":
    main()
