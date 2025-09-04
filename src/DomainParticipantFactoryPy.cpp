#pragma once
#include "Aliases.h"
#include "DomainParticipantFactoryPy.h"

namespace py = pybind11;

DDS::DomainParticipantFactory *DPFPy::dpf = nullptr;
std::set<DomainParticipantPy *> DPFPy::DomainParticipants;
DPFPy::DomainParticipantFactoryPy()
{
  dpf = DDS::DomainParticipantFactory::get_instance();
}

DPFPy::~DomainParticipantFactoryPy() {}

DPFPy *DPFPy::get_instance()
{
  static DPFPy instance;
  return &instance;
}

DDS::ReturnCode_t DPFPy::finalize_instance()
{
  return dpf->finalize_instance();
}

DPPy *DPFPy::create_participant(
    const unsigned int &domain_id,
    const QosEnum &qos,
    DDS::DomainParticipantListener *a_listener,
    const StatusKindMaskEnum &mask)
{
  DDS::DomainParticipant *dp = dpf->create_participant(domain_id, getQos(qos), a_listener, getMask(mask));
  DPPy *newDPPy = new DPPy(dp);
  DomainParticipants.insert(newDPPy);
  return newDPPy;
}

DDS::ReturnCode_t DPFPy::delete_participant(DPPy *a_dp)
{
  DDS::ReturnCode_t returnCode = dpf->delete_participant(a_dp->raw());
  DomainParticipants.erase(a_dp);
  delete a_dp;
  return returnCode;
}

void init_DomainParticipantFactory(py::module_ &m)
{
  py::class_<DPFPy>(m, "DomainParticipantFactory")
      .def_static("get_instance",
                  &DPFPy::get_instance,
                  py::return_value_policy::reference,
                  "Get the singleton instance of DomainParticipantFactory")
      .def_static("finalize_instance",
                  &DPFPy::finalize_instance,
                  "Finalize the singleton instance of DomainParticipantFactory")
      .def("create_participant",
           &DPFPy::create_participant,
           py::arg("domain_id"),
           py::arg("qos") = py::cast(QosEnum::DDS_DOMAINPARTICIPANT_QOS_DEFAULT_ENUM),
           py::arg("a_listener") = py::none(),
           py::arg("mask") = py::cast(StatusKindMaskEnum::DDS_STATUS_MASK_NONE_ENUM),
           "Create a DomainParticipant with the given parameters")
      .def("delete_participant",
           &DPFPy::delete_participant,
           py::arg("a_dp"),
           "Delete the specified DomainParticipant");
}