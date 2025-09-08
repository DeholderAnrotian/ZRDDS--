#pragma once
#include <pybind11/pybind11.h>
#include "Subscriber.h"
#include "DataReaderPy.h"
#include "TopicDescriptionPy.h"
#include "QosPy.h"
#include "StatusKindMaskEnum.h"
#include <set>

namespace py = pybind11;

class SubscriberPy
{
public:
  SubscriberPy(DDS::Subscriber *intputSubscriber);

  ~SubscriberPy();

  DDS::Subscriber *raw() const;
  
  DataReaderPy *create_datareader(TopicDescriptionPy *a_topic,
                                  const DataReaderQosPy &qoslist,
                                  // DataReaderListener *a_listener,
                                  const StatusKindMaskEnum &mask);

private:
  DDS::Subscriber *it;

  std::set<DataReaderPy *> DataReaders;
};

void init_Subscriber(py::module_ &m);