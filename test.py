from build.Release import zrdds_python as zrpy

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

participant= factory.create_participant(0,zrpy.DomainParticipantQos.DOMAINPARTICIPANT_QOS_DEFAULT,zrpy.StatusKindMask.STATUS_MASK_NONE)
print(participant)

print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())