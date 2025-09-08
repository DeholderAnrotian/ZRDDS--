#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>

namespace py = pybind11;

enum class SampleStateMaskEnum : unsigned int
{
  READ_SAMPLE_STATE_ENUM = 0x0001 << 0,
  NOT_READ_SAMPLE_STATE_ENUM = 0x0001 << 1,
  ANY_SAMPLE_STATE_ENUM = READ_SAMPLE_STATE_ENUM | NOT_READ_SAMPLE_STATE_ENUM
};

DDS_SampleStateMask getMask(SampleStateMaskEnum mask);

void init_SampleStateMaskEnum(py::module_ &m);
