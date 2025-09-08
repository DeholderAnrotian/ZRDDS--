#pragma once
#include <pybind11/pybind11.h>
#include "TopicDescription.h"

namespace py = pybind11;

class TopicDescriptionPy
{
public:
  TopicDescriptionPy(DDS::TopicDescription *intputTopicDescription);

  ~TopicDescriptionPy();

  DDS::TopicDescription *raw() const;

protected:
  DDS::TopicDescription *it;
};

void init_TopicDescription(py::module_ &m);