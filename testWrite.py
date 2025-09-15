from build.Release import zrdds_python as zrpy
import time

factory = zrpy.DomainParticipantFactory.get_instance()
print(factory)
# print(zrpy.Qos.DOMAINPARTICIPANT_QOS_DEFAULT)
# help(factory.create_participant)

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
