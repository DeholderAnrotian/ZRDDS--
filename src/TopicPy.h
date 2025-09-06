#pragma once
#include <pybind11/pybind11.h>
#include "Topic.h"

namespace py = pybind11;

class TopicPy
{
public:
  TopicPy(DDS::Topic *intputTopic);
  ~TopicPy();
  DDS::Topic *raw() const;

private:
  DDS::Topic *topic;
};

void init_Topic(py::module_ &m);