#include "PublisherPy.h"
#include "StatusKindMaskEnum.h"

PublisherPy::PublisherPy(DDS::Publisher *publisher)
    : publisher(publisher) {}

PublisherPy::~PublisherPy()
{
  // Publisher 的生命周期通常由 DomainParticipant 管理?
}

DDS::Publisher *PublisherPy::raw() const
{
  return publisher;
}

DataWriterPy *PublisherPy::create_datawriter(
    DDS::Topic *the_topic,
    const PublisherQosPy &qos,
    // DDS::DataWriterListener* a_listener,
    const StatusKindMaskEnum &mask)
{
  DDS::DataWriter *writer = publisher->create_datawriter(
      the_topic,
      *qos->raw(), // getPublisherQos(qos),
      nullptr,
      getMask(mask));
  if (!writer)
  {
    throw std::runtime_error("Failed to create DataWriter");
  }
  return new DataWriterPy(writer);
}

DDS::ReturnCode_t PublisherPy::delete_datawriter(DataWriterPy *writer)
{
  DDS::ReturnCode_t ret = publisher->delete_datawriter(writer->raw());
  delete writer;
  return ret;
}

void init_Publisher(py::module_ &m)
{
  py::class_<PublisherPy>(m, "Publisher")
      .def("create_datawriter",
           &PublisherPy::create_datawriter,
           py::arg("topic"),
           py::arg("qos") = py::cast(PublisherQosEnum::PUBLISHER_QOS_DEFAULT_ENUM),
           py::arg("a_listener") = py::none(),
           py::arg("mask") = py::cast(StatusKindMaskEnum::STATUS_MASK_NONE_ENUM),
           "Create a DataWriter with the given parameters")
      .def("delete_datawriter",
           &PublisherPy::delete_datawriter,
           py::arg("writer"),
           "Delete a DataWriter");
}
