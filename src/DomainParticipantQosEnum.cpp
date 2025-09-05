#pragma once
#include "Aliases.h"
#include <pybind11/pybind11.h>
#include "DomainParticipantQosEnum.h"
namespace py = pybind11;

DDS::DomainParticipantQos getDomainParticipantQos(DPQE qos)
{
  switch (qos)
  {
  case DPQE::DOMAINPARTICIPANT_QOS_DEFAULT_ENUM:
  {
    return DDS::DOMAINPARTICIPANT_QOS_DEFAULT;
  }
  default:
    throw std::invalid_argument("Invalid QosEnum value");
  }
}
void init_DomainParticipantQosEnum(py::module_ &m)
{
  py::enum_<DPQE>(m, "DomainParticipantQos")
      .value("DOMAINPARTICIPANT_QOS_DEFAULT", DPQE::DOMAINPARTICIPANT_QOS_DEFAULT_ENUM, "Default DomainParticipantQos")
      .export_values();
}