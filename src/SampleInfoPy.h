#pragma once
#include <pybind11/pybind11.h>
#include "SampleInfoPy.h"

namespace py = pybind11;

class SampleInfoPy
{
public:
  SampleInfoPy();
  SampleInfoPy(DDS::SampleInfo *intputSampleInfo);
  SampleInfoPy(const SampleInfoPy &other) noexcept;
  ~SampleInfoPy();

  DDS::SampleInfo *raw() const;
  DDS_Boolean valid_data();

protected:
  DDS::SampleInfo *it;
};

void init_SampleInfo(py::module_ &m);