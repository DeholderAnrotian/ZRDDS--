from build.Release import zrdds_python as zrpy
import time
import atexit



def main():
    factory = zrpy.DomainParticipantFactory.get_instance()
    print("factory:", factory)

    participant = factory.create_participant(
        80,
        zrpy.DomainParticipantQos.getDefault(),
        None,
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )
    print("participant:", participant)

    subscriber = participant.create_subscriber(
        zrpy.SubscriberQos.getDefault(),
        None,
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )
    print("subscriber:", subscriber)

    # 所有测试类型
    type_list = [
        ("TOPIC_OCTET", "DDS_Octet"),
        ("TOPIC_BOOLEAN", "DDS_Boolean"),
        ("TOPIC_SHORT", "DDS_Short"),
        ("TOPIC_USHORT", "DDS_UShort"),
        ("TOPIC_LONG", "DDS_Long"),
        ("TOPIC_ULONG", "DDS_ULong"),
        ("TOPIC_LONGLONG", "DDS_LongLong"),
        ("TOPIC_ULONGLONG", "DDS_ULongLong"),
        ("TOPIC_FLOAT", "DDS_Float"),
        ("TOPIC_DOUBLE", "DDS_Double"),
        ("TOPIC_STRING", "DDS_String"),
        ("TOPIC_BYTES", "DDS_Bytes"),
        # ("TOPIC_KEYEDBYTES", "DDS_KeyedBytes"),
    ]

    # 创建 Topics 和 DataReaders
    readers = {}
    for topic_name, type_name in type_list:
        topic = participant.create_topic(
            topic_name,
            type_name,
            zrpy.TopicQos.getDefault(),
            None,
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        reader = subscriber.create_datareader(
            topic,
            zrpy.DataReaderQos.getDefault(),
            None,
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        readers[type_name] = reader
        print(f"✅ Created DataReader for {type_name}")

    # 循环读取数据
    while True:
        for type_name, reader in readers.items():
            data, sample_info, retcode = reader.take_next_sample()
            if retcode == zrpy.ReturnCode_t.RETCODE_OK and sample_info.valid_data():
                if type_name == "DDS_KeyedBytes":
                    print(f"[{type_name}] 收到: key={data.get_key()}, value={data.get_value()}")
                else:
                    print(f"[{type_name}] 收到: {data}")
            elif retcode == zrpy.ReturnCode_t.RETCODE_NO_DATA:
                print("暂时没有数据")
            else:
                print(f"[{type_name}] 读取错误: {retcode}")

        time.sleep(0.5)

    # # 清理资源（实际循环里可能不会到这里，可手动中断）
    # participant.delete_contained_entities()
    # factory.delete_participant(participant)
    # zrpy.DomainParticipantFactory.finalize_instance()
    

if __name__ == "__main__":
    main()
