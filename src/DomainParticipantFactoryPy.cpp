#include "Aliases.h"
#include "DomainParticipantFactoryPy.h"
#include "ZRBuiltinTypesTypeSupport.h"

DDS::DomainParticipantFactory *DPFPy::it = nullptr;

std::set<DPPy *> DPFPy::DomainParticipants;

DPFPy::DomainParticipantFactoryPy()
{
  it = DDS::DomainParticipantFactory::get_instance();
}

DPFPy::~DPFPy() {}

DPFPy *DPFPy::get_instance()
{
  static DPFPy instance;
  return &instance;
}

DDS::ReturnCode_t DPFPy::finalize_instance()
{
  return it->finalize_instance();
}

DPPy *DPFPy::create_participant(const unsigned int &domain_id,
                                const DPQPy &qoslist,
                                DDS::DomainParticipantListener *a_listener,
                                const StatusKindMaskEnum &mask)
{
  DDS::DomainParticipant *dp = it->create_participant(domain_id, *qoslist.raw(), nullptr, getMask(mask));
  DPPy *newDPPy = new DPPy(dp);
  DomainParticipants.insert(newDPPy);
  // 数据类型注册
  DDS::BooleanTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::OctetTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::CharTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::ShortTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::UShortTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::LongTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::ULongTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::LongLongTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::ULongLongTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::FloatTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::DoubleTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::StringTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::KeyedStringTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::BytesTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::KeyedBytesTypeSupport::get_instance()->register_type(dp, NULL);
  DDS::ZeroCopyBytesTypeSupport::get_instance()->register_type(dp, NULL);
  return newDPPy;
}

DDS::ReturnCode_t DPFPy::delete_participant(DPPy *a_dp)
{
  DDS::ReturnCode_t returnCode = it->delete_participant(a_dp->raw());
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
           py::arg("qos"),
           py::arg("a_listener"),
           py::arg("mask"),
           "Create a DomainParticipant with the given parameters")
      .def("delete_participant",
           &DPFPy::delete_participant,
           py::arg("a_dp"),
           "Delete the specified DomainParticipant");
}