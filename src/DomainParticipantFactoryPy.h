#pragma once
#include <pybind11/pybind11.h>
#include "DomainParticipantFactory.h"
#include "DomainParticipantPy.h"
#include "ReturnCode_t.h"
#include "QosEnum.h"
#include "StatusKindMaskEnum.h"
#include <set>
namespace py = pybind11;

class DomainParticipantFactoryPy
{
public:
  ~DomainParticipantFactoryPy();
  // 获取包装器单例
  static DomainParticipantFactoryPy *get_instance();

  // 释放底层 DDS 工厂实例
  static DDS::ReturnCode_t finalize_instance();
  // virtual DomainParticipantPy *create_participant(const unsigned int &domain_id);
  virtual DomainParticipantPy *create_participant(const unsigned int &domain_id,
                                                  const QosEnum &qos,
                                                  DDS::DomainParticipantListener *a_listener,
                                                  const StatusKindMaskEnum &mask);

  virtual DDS::ReturnCode_t delete_participant(DomainParticipantPy *a_dp);

private:
  // 底层 DDS 工厂实例
  static DDS::DomainParticipantFactory *dpf;
  static std::set<DomainParticipantPy *> DomainParticipants;
  // 构造函数私有化，保证单例
  DomainParticipantFactoryPy();
};

// 声明 pybind11 绑定函数
void init_DomainParticipantFactory(py::module_ &m);
