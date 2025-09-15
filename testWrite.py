from build.Release import zrdds_python as zrpy
import time
import random

def write_samples(writer, dtype, count=10):
    """根据数据类型批量写入示例数据"""
    for i in range(count):
        if dtype == "DDS_Octet":
            writer.write(i % 256)
        elif dtype == "DDS_Boolean":
            writer.write(i % 2 == 0)
        elif dtype == "DDS_Short":
            writer.write(i)
        elif dtype == "DDS_UShort":
            writer.write(i)
        elif dtype == "DDS_Long":
            writer.write(i)
        elif dtype == "DDS_ULong":
            writer.write(i)
        elif dtype == "DDS_LongLong":
            writer.write(i)
        elif dtype == "DDS_ULongLong":
            writer.write(i)
        elif dtype == "DDS_Float":
            writer.write(float(i) + 0.1)
        elif dtype == "DDS_Double":
            writer.write(float(i) + 0.123456)
        elif dtype == "DDS_String":
            writer.write(f"msg_{i}")
        elif dtype == "DDS_Bytes":
            # DDS_Bytes 封装成 bytes 对象
            writer.write(bytes([i % 256 for _ in range(5)]))
        else:
            raise ValueError(f"Unsupported type {dtype}")
        print(f"📤 Wrote {dtype} sample {i}")
        # 保持快速连续写，不要太慢
        time.sleep(0.01)

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

participant= factory.create_participant(80,zrpy.DomainParticipantQos.getDefault(),None,zrpy.StatusKindMask.STATUS_MASK_NONE)
print(participant)

topic= participant.create_topic("DATARECEIVEBYLISTENER",'DDS_LongLong',zrpy.TopicQos.getDefault(),None,zrpy.StatusKindMask.STATUS_MASK_NONE)
print(topic)

publisher= participant.create_publisher(zrpy.PublisherQos.getDefault(),None,zrpy.StatusKindMask.STATUS_MASK_NONE)

dataWriter= publisher.create_datawriter(topic,zrpy.DataWriterQos.getDefault(),None,zrpy.StatusKindMask.STATUS_MASK_NONE)
print(dataWriter)

data=1245
while True:
  time.sleep(1)
  rtn=dataWriter.write(data)
  if rtn==zrpy.ReturnCode_t.RETCODE_OK:
    print("write data:",data)
  else:
    print("write error:",rtn)
    break

participant.delete_contained_entities()
print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())
    # 列出要测试的所有数据类型
    data_types = [
        "DDS_Octet", "DDS_Boolean", "DDS_Short", "DDS_UShort",
        "DDS_Long", "DDS_ULong", "DDS_LongLong", "DDS_ULongLong",
        "DDS_Float", "DDS_Double", "DDS_String", "DDS_Bytes"
    ]

    writers = {}
    for dtype in data_types:
        topic_name = f"TOPIC_{dtype.upper()}"
        topic = participant.create_topic(
            topic_name,
            dtype,
            zrpy.TopicQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        writer = publisher.create_datawriter(
            topic,
            zrpy.DataWriterQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        writers[dtype] = writer
        print(f"✅ Created writer for {dtype}")

    # 循环写每种数据类型
    for dtype, writer in writers.items():
        write_samples(writer, dtype, count=10)

    print("✅ Finished publishing all types")

if __name__ == "__main__":
    main()
