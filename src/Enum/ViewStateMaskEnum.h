#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>

namespace py = pybind11;

enum class ViewStateMaskEnum : unsigned int
{
  NEW_VIEW_STATE_ENUM = 0x0001 << 0,
  NOT_NEW_VIEW_STATE_ENUM = 0x0001 << 1,
  ANY_VIEW_STATE_ENUM = NEW_VIEW_STATE_ENUM | NOT_NEW_VIEW_STATE_ENUM
};

DDS::ViewStateMask getMask(ViewStateMaskEnum mask);

void init_ViewStateMaskEnum(py::module_ &m);
