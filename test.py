import zrpy.zrdds_python as zrpy

# if(zrpy.DomainParticipantFactory.get_instance() == None):
#   print("get instance failed\n")
# else:
#   print("get instance success\n")

# print(zrpy.DomainParticipantFactory.get_instance())
# print(zrpy.DomainParticipantFactory.finalize_instance())

factory = zrpy.DomainParticipantFactory.get_instance()
print(factory)

participant= factory.create_participant(0)
print(participant)

print(factory.delete_participant(participant))
print(zrpy.DomainParticipantFactory.finalize_instance())