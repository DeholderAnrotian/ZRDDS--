from build.Release import zrdds_python as zrpy
import time

def main():
    factory = zrpy.DomainParticipantFactory.get_instance()
    participant = factory.create_participant(
        80,
        zrpy.DomainParticipantQos.getDefault(),
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )
    subscriber = participant.create_subscriber(
        zrpy.SubscriberQos.getDefault(),
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )

    # 列出要测试的所有数据类型
    data_types = [
        "DDS_Octet", "DDS_Boolean", "DDS_Short", "DDS_UShort",
        "DDS_Long", "DDS_ULong", "DDS_LongLong", "DDS_ULongLong",
        "DDS_Float", "DDS_Double", "DDS_String", "DDS_Bytes"
    ]

    readers = {}
    for dtype in data_types:
        topic_name = f"TOPIC_{dtype.upper()}"
        topic = participant.create_topic(
            topic_name,
            dtype,
            zrpy.TopicQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        reader = subscriber.create_datareader(
            topic,
            zrpy.DataReaderQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        readers[dtype] = reader
        print(f"✅ Created reader for {dtype}")

    print("⏳ Start taking samples...")

    while True:
        for dtype, reader in readers.items():
            try:
                values, infos, ret = reader.take(max_samples=10)
                if len(values) > 0:
                    print(f"\n📥 {dtype}: Took {len(values)} samples")
                    for idx, value in enumerate(values):
                        # DDS_Bytes 类型是 bytes，需要显示长度
                        if dtype == "DDS_Bytes":
                            print(f"  Sample {idx}: {len(value)} bytes -> {value}")
                        else:
                            print(f"  Sample {idx}: {value}")
                    # 打印 SampleInfo
                    for idx, info in enumerate(infos):
                        print(f"  Info {idx}: valid_data={info.valid_data}")
                else:
                    print(f"\n⏳ {dtype}: No new data")
            except Exception as e:
                print(f"❌ Exception reading {dtype}: {e}")

        time.sleep(1)

if __name__ == "__main__":
    main()
