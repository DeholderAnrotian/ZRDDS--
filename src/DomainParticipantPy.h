#pragma once
#include <pybind11/pybind11.h>
#include "DomainParticipant.h"

namespace py = pybind11;

class DomainParticipantPy
{
public:
  DomainParticipantPy(DDS::DomainParticipant *intputDomainParticipant);
  ~DomainParticipantPy();
  DDS::DomainParticipant *raw() const;

private:
  DDS::DomainParticipant *dp;
};

void init_DomainParticipant(py::module_ &m);