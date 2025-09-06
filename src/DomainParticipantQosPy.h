#pragma once
#include <pybind11/pybind11.h>
#include "DefaultQos.h"
#include <stdexcept>
namespace py = pybind11;

class DomainParticipantQosPy
{
public:
  DomainParticipantQosPy(DDS::DomainParticipantQos *intputDomainParticipantQos);
  ~DomainParticipantQosPy();
  DDS::DomainParticipantQos *raw() const;

  static DomainParticipantQosPy getDefault();

private:
  DDS::DomainParticipantQos *dpq;
};

void init_DomainParticipantQos(py::module_ &m);
