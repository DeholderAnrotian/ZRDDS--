#pragma once
#include "Aliases.h"
#include <pybind11/pybind11.h>
#include "DomainParticipantQosPy.h"

namespace py = pybind11;

DPQPy::DomainParticipantQosPy(DDS_DomainParticipantQos *intputDomainParticipantQos)
    : dpq(intputDomainParticipantQos) {}

DPQPy::~DomainParticipantQosPy() {}

DDS::DomainParticipantQos *DPQPy::raw() const { return dpq; }

DPQPy DPQPy::getDefault()
{
  return DPQPy(&DDS_DOMAINPARTICIPANT_QOS_DEFAULT);
}

void init_DomainParticipantQos(py::module_ &m)
{
  py::class_<DPQPy>(m, "DomainParticipantQos")
      .def(py::init<DDS::DomainParticipantQos *>(), py::arg("intputDomainParticipantQos"))
      .def_static("getDefault", &DPQPy::getDefault, "Get the default DomainParticipantQos");
}