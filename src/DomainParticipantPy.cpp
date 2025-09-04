#include "Aliases.h"
#include "DomainParticipantPy.h"

DPPy::DomainParticipantPy(DDS::DomainParticipant *intputDomainParticipant)
    : dp(intputDomainParticipant){}

DPPy::~DomainParticipantPy() {}

DDS::DomainParticipant *DPPy::raw() const { return dp; }

void init_DomainParticipant(py::module_ &m)
{
  py::class_<DPPy>(m, "DomainParticipant")
      .def(py::init<DDS::DomainParticipant *>(), py::arg("intputDomainParticipant"));
}