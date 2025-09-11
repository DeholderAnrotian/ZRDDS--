from build.Release import zrdds_python as zrpy
import time
# if(zrpy.DomainParticipantFactory.get_instance() == None):
#   print("get instance failed\n")
# else:
#   print("get instance success\n")

# print(zrpy.DomainParticipantFactory.get_instance())
# print(zrpy.DomainParticipantFactory.finalize_instance())

class tListener (zrpy.DataReaderListener):
  def on_data_available(self):
        print("Data available!")


factory = zrpy.DomainParticipantFactory.get_instance()
print(factory)
# print(zrpy.Qos.DOMAINPARTICIPANT_QOS_DEFAULT)
# help(factory.create_participant)

participant= factory.create_participant(80,zrpy.DomainParticipantQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(participant)

topic= participant.create_topic("DATARECEIVEBYLISTENER",'DDS_LongLong',zrpy.TopicQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(topic)

subscriber= participant.create_subscriber(zrpy.SubscriberQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)

listener= tListener()
print(listener)
dataReader= subscriber.create_datareader(topic,zrpy.DataReaderQos.getDefault(),None,zrpy.StatusKindMask.STATUS_MASK_ALL)
print(dataReader)

# while True:
#   time.sleep(1)
#   print("等待数据中...")

while True:
  LongLongData,SampleInfo,retcode = dataReader.take_next_sample()
  if retcode == zrpy.ReturnCode_t.RETCODE_OK and SampleInfo.valid_data():
    print("收到:", LongLongData)
  elif retcode == zrpy.ReturnCode_t.RETCODE_NO_DATA:
    print("暂时没有数据")
    time.sleep(0.5)
  else:
    print(retcode)
    print("其他错误:", retcode)
    time.sleep(0.5)

participant.delete_contained_entities()
print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())