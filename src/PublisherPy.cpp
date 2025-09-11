#include "Aliases.h"
#include "PublisherPy.h"

PublisherPy::PublisherPy(DDS::Publisher *inputPublisher)
    : it(inputPublisher) {}

PublisherPy::~PublisherPy() {}

DDS::Publisher *PublisherPy::raw() const { return it; }

DWPy *PublisherPy::create_datawriter(TopicPy *a_topic,
                                     const DWQPy &qoslist,
                                     // DDS::DataWriterListener* a_listener,
                                     const StatusKindMaskEnum &mask)
{
  DDS::DataWriter *dw = it->create_datawriter(a_topic->raw(), *qoslist.raw(), nullptr, getMask(mask));
  DWPy *newDWPy = new DWPy(dw);
  DataWriters.insert(newDWPy);
  return newDWPy;
}

DDS::ReturnCode_t PublisherPy::delete_datawriter(DataWriterPy *writer)
{
  DDS::ReturnCode_t ret = it->delete_datawriter(writer->raw());
  DataWriters.erase(writer);
  return ret;
}

void init_Publisher(py::module_ &m)
{
  py::class_<PublisherPy>(m, "Publisher")
      // .def(py::init<DDS::Publisher *>(), py::arg("publisher"))
      .def("create_datawriter",
           &PublisherPy::create_datawriter,
           py::arg("a_topic"),
           py::arg("qoslist"),
           //py::arg("a_listener") = py::none(),
           py::arg("mask"),
           "Create a DataWriter with the given parameters")
      .def("delete_datawriter",
           &PublisherPy::delete_datawriter,
           py::arg("writer"),
           "Delete a DataWriter");
}
