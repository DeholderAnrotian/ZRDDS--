#pragma once
#include <pybind11/pybind11.h>
#include "Topic.h"
#include "TopicDescriptionPy.h"

namespace py = pybind11;

class TopicPy :public TopicDescriptionPy
{
public:
  TopicPy(DDS::Topic *intputTopic);

  ~TopicPy();
  
  DDS::Topic *raw() const;
};

void init_Topic(py::module_ &m);