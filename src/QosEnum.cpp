#pragma once
#include <pybind11/pybind11.h>
#include "QosEnum.h"
namespace py = pybind11;

DDS::DomainParticipantQos getQos(QosEnum qos)
{
  switch (qos)
  {
  case QosEnum::DDS_DOMAINPARTICIPANT_QOS_DEFAULT_ENUM:
    return DDS::DOMAINPARTICIPANT_QOS_DEFAULT;
  default:
    throw std::invalid_argument("Invalid QosEnum value");
  }
}
void init_QosEnum(py::module_ &m)
{
  py::enum_<QosEnum>(m, "Qos")
      .value("DOMAINPARTICIPANT_QOS_DEFAULT", QosEnum::DDS_DOMAINPARTICIPANT_QOS_DEFAULT_ENUM, "Default DomainParticipantQos")
      .export_values();
}