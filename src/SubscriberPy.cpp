#include "Aliases.h"
#include "SubscriberPy.h"

SubscriberPy::SubscriberPy(DDS::Subscriber *intputSubscriber)
    : it(intputSubscriber) {}

SubscriberPy::~SubscriberPy() {}

DDS::Subscriber *SubscriberPy::raw() const { return it; }

DRPy *SubscriberPy::create_datareader(TDPy *a_topic,
                                      const DRQPy &qoslist,
                                      // DataReaderListener *a_listener,
                                      const StatusKindMaskEnum &mask)
{
  DDS::DataReader *dr = it->create_datareader(a_topic->raw(), *qoslist.raw(), nullptr, getMask(mask));
  DRPy *newDRPy = new DRPy(dr);
  DataReaders.insert(newDRPy);
  return newDRPy;
}

void init_Subscriber(py::module_ &m)
{
  py::class_<SubscriberPy>(m, "Subscriber")
      .def("create_datareader",
           &SubscriberPy::create_datareader,
           py::arg("a_topic"),
           py::arg("qos"),
           // py::arg("a_listener") = py::none(),
           py::arg("mask"),
           "Create a DataReader");
}