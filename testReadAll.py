from build.Release import zrdds_python as zrpy
import time
import atexit



def main():
    factory = zrpy.DomainParticipantFactory.get_instance()
    print("factory:", factory)

    participant = factory.create_participant(
        80,
        zrpy.DomainParticipantQos.getDefault(),
        zrpy.StatusKindMask.STATUS_MASK_NONE
    )
    print("participant:", participant)

    subscriber = participant.create_subscriber(
        zrpy.SubscriberQos.getDefault(),
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
        # ("TOPIC_KEYEDSTRING", "DDS_KeyedString"),
        # ("TOPIC_KEYEDBYTES", "DDS_KeyedBytes"),
    ]

    # 创建 Topics 和 DataReaders
    readers = {}
    for topic_name, type_name in type_list:
        topic = participant.create_topic(
            topic_name,
            type_name,
            zrpy.TopicQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        reader = subscriber.create_datareader(
            topic,
            zrpy.DataReaderQos.getDefault(),
            zrpy.StatusKindMask.STATUS_MASK_NONE
        )
        readers[type_name] = reader
        print(f"✅ Created DataReader for {type_name}")

    while True:
        for type_name, reader in readers.items():
            try:
                data, sample_info, retcode = reader.read_next_sample()
                if retcode == zrpy.ReturnCode_t.RETCODE_OK and sample_info.valid_data():
                    if type_name == "DDS_KeyedBytes":
                        try:
                            print(f"[{type_name}] 收到: key={data.get_key()}, value={data.get_value()}")
                        except Exception as e:
                            print(f"[{type_name}] KeyedBytes 打印异常: {e}")
                    elif type_name == "DDS_KeyedString":
                        try:
                            print(f"[{type_name}] 收到: key={data.get_key()}, value={data.get_value()}", data, retcode)
                        except Exception as e:
                            print(f"[{type_name}] KeyedString 打印异常: {e}")
                    else:
                        print(f"[{type_name}] 收到: {data}", data, retcode)
                elif retcode == zrpy.ReturnCode_t.RETCODE_NO_DATA:
                    print(f"[{type_name}] 暂时没有数据")
                else:
                    print(f"[{type_name}] 读取错误: {retcode}")
            except Exception as e:
                print(f"[Reader Exception] {type_name}: {e}")

        time.sleep(0.5)


    def on_exit():
        print(">>> Reader exiting <<<")

    atexit.register(on_exit)

if __name__ == "__main__":
    main()
