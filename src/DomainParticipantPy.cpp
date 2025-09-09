#include "Aliases.h"
#include "DomainParticipantPy.h"

DPPy::DomainParticipantPy(DDS::DomainParticipant *intputDomainParticipant)
    : it(intputDomainParticipant) {}

DPPy::~DomainParticipantPy() {}

DDS::DomainParticipant *DPPy::raw() const { return it; }

TopicPy *DPPy::create_topic(const char *topic_name,
                            const char *type_name,
                            const TQPy &qoslist,
                            // DDS::TopicListener *a_listener,
                            const StatusKindMaskEnum &mask)
{
  DDS::Topic *tp = it->create_topic(topic_name, type_name, *qoslist.raw(), nullptr, getMask(mask));
  TopicPy *newTopicPy = new TopicPy(tp);
  Topics.insert(newTopicPy);
  return newTopicPy;
}

SubscriberPy *DPPy::create_subscriber(const SubscriberQosPy &qoslist,
                                      // SubscriberListener *a_listener,
                                      const StatusKindMaskEnum &mask)
{
  DDS::Subscriber *sub = it->create_subscriber(*qoslist.raw(), nullptr, getMask(mask));
  SubscriberPy *newSubscriberPy = new SubscriberPy(sub);
  Subscribers.insert(newSubscriberPy);
  return newSubscriberPy;
}
PublisherPy *DPPy::create_publisher(const PublisherQosPy &qoslist,
                                    // PublisherListener *a_listener,
                                    const StatusKindMaskEnum &mask)
{
  DDS::Publisher *pub = it->create_publisher(*qoslist.raw(), nullptr, getMask(mask));
  PublisherPy *newPublisherPy = new PublisherPy(pub);
  Publishers.insert(newPublisherPy);
  return newPublisherPy;
}

DDS::ReturnCode_t DPPy::delete_contained_entities()
{
  for (auto topic : Topics)
  {
    delete topic;
  }
  for (auto sub : Subscribers)
  {
    delete sub;
  }
  Topics.clear();
  Subscribers.clear();
  return it->delete_contained_entities();
}

void init_DomainParticipant(py::module_ &m)
{
  py::class_<DPPy>(m, "DomainParticipant")
      .def(py::init<DDS::DomainParticipant *>(), py::arg("intputDomainParticipant"))
      .def("create_topic",
           &DPPy::create_topic,
           py::arg("topic_name"),
           py::arg("type_name"),
           py::arg("qos"),
           // py::arg("a_listener") = py::none(),
           py::arg("mask"),
           "Create a Topic")
      .def("create_subscriber", &DPPy::create_subscriber, "Create a Subscriber")
      .def("create_publisher", &DPPy::create_publisher, "Create a Publisher")
      .def("delete_contained_entities", &DPPy::delete_contained_entities, "Delete all contained entities");
}