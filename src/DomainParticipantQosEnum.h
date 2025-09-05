#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <stdexcept>
namespace py = pybind11;

// 枚举声明
enum class DomainParticipantQosEnum : unsigned int
{
  DOMAINPARTICIPANT_QOS_DEFAULT_ENUM = 0
};

// 函数声明
DDS::DomainParticipantQos getDomainParticipantQos(DomainParticipantQosEnum qos);

void init_DomainParticipantQosEnum(py::module_ &m);
