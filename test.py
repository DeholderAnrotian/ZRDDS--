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

participant= factory.create_participant(0,zrpy.DomainParticipantQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(participant)

# time.sleep(3)
# while True:
#   pass
topic= participant.create_topic("Hello",'DDS_String',zrpy.TopicQos.getDefault(),zrpy.StatusKindMask.STATUS_MASK_NONE)
print(topic)
time.sleep(3)
participant.delete_contained_entities()
print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())