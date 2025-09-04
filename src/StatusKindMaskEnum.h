#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <stdexcept>

namespace py = pybind11;

enum class StatusKindMaskEnum : unsigned int
{
  DDS_STATUS_MASK_NONE_ENUM = 0,
  DDS_STATUS_MASK_ALL_ENUM = 1
};

DDS::StatusKindMask getMask(StatusKindMaskEnum mask);

void init_StatusKindMaskEnum(py::module_ &m);