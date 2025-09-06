#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <stdexcept>
#include "DefaultQos.h"
namespace py = pybind11;

class TopicQosPy
{
public:
  TopicQosPy(DDS_TopicQos *intputTopicQos);
  ~TopicQosPy();
  DDS_TopicQos *raw() const;

  static TopicQosPy getDefault();

private:
  DDS_TopicQos *tq;
};

void init_TopicQos(py::module_ &m);
