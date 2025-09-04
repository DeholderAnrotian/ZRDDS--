#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <stdexcept>
namespace py = pybind11;

// 枚举声明
enum class QosEnum : unsigned int
{
  DDS_DOMAINPARTICIPANT_QOS_DEFAULT_ENUM = 0
};

// 函数声明
DDS::DomainParticipantQos getQos(QosEnum qos);

void init_QosEnum(py::module_ &m);
