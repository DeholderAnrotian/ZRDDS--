#include "Aliases.h"
#include "DomainParticipantPy.h"

DPPy::DomainParticipantPy(DDS::DomainParticipant *intputDomainParticipant)
    : dp(intputDomainParticipant) {}

DPPy::~DomainParticipantPy() {}

DDS::DomainParticipant *DPPy::raw() const { return dp; }

TopicPy *DPPy::create_topic(const char *topic_name,
                            const char *type_name,
                            const TopicQosPy &qoslist,
                            // DDS::TopicListener *a_listener,
                            const StatusKindMaskEnum &mask)
{
  DDS::Topic *tp = dp->create_topic(topic_name, type_name, *qoslist.raw(), nullptr, getMask(mask));
  TopicPy *newTopicPy = new TopicPy(tp);
  Topics.insert(newTopicPy);
  return newTopicPy;
}

DDS::ReturnCode_t DPPy::delete_contained_entities()
{
  for (auto topic : Topics)
  {
    delete topic;
  }
  Topics.clear();
  return dp->delete_contained_entities();
}

void init_DomainParticipant(py::module_ &m)
{
  py::class_<DPPy>(m, "DomainParticipant")
      .def(py::init<DDS::DomainParticipant *>(), py::arg("intputDomainParticipant"))
      .def("create_topic",
           &DPPy::create_topic,
           py::arg("topic_name"),
           py::arg("type_name"),
           py::arg("qos") = TopicQosPy::getDefault(),
           // py::arg("a_listener") = py::none(),
           py::arg("mask") = StatusKindMaskEnum::STATUS_MASK_NONE_ENUM,
           "Create a Topic")
      .def("delete_contained_entities", &DPPy::delete_contained_entities, "Delete all contained entities");
}