from build.Release import zrdds_python as zrpy
import time
# if(zrpy.DomainParticipantFactory.get_instance() == None):
#   print("get instance failed\n")
# else:
#   print("get instance success\n")

# print(zrpy.DomainParticipantFactory.get_instance())
# print(zrpy.DomainParticipantFactory.finalize_instance())

factory = zrpy.DomainParticipantFactory.get_instance()
print(factory)
# print(zrpy.Qos.DOMAINPARTICIPANT_QOS_DEFAULT)
# help(factory.create_participant)

participant= factory.create_participant(80,zrpy.DomainParticipantQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(participant)

topic= participant.create_topic("DATARECEIVEBYLISTENER",'DDS_LongLong',zrpy.TopicQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(topic)

publisher= participant.create_publisher(zrpy.PublisherQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)

dataWriter= publisher.create_datawriter(topic,zrpy.DataWriterQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(dataWriter)

LongLongData=1000
SampleInfo=zrpy.SampleInfo()
while True:
  time.sleep(1)
  rtn=dataWriter.write(LongLongData)
  if rtn==zrpy.ReturnCode_t.RETCODE_OK:
    print("write data:",LongLongData)
    LongLongData+=1
  else:
    print("write error:",rtn)
    break

participant.delete_contained_entities()
print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())