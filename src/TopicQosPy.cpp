#pragma once
#include "Aliases.h"
#include <pybind11/pybind11.h>
#include "TopicQosPy.h"

namespace py = pybind11;

TopicQosPy::TopicQosPy(DDS_TopicQos *intputTopicQos)
    : tq(intputTopicQos) {}

TopicQosPy::~TopicQosPy() {}

DDS::TopicQos *TopicQosPy::raw() const { return tq; }

TopicQosPy TopicQosPy::getDefault()
{
  return TopicQosPy(&DDS_TOPIC_QOS_DEFAULT);
}

void init_TopicQos(py::module_ &m)
{
  py::class_<TopicQosPy>(m, "TopicQos")
      .def(py::init<DDS::TopicQos *>(), py::arg("intputTopicQos"))
      .def_static("getDefault", &TopicQosPy::getDefault, "Get the default TopicQos");
}
