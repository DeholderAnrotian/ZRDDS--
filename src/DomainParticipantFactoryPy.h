#pragma once
#include <pybind11/pybind11.h>
#include "DomainParticipantFactory.h"
#include "DomainParticipantPy.h"
#include "ReturnCode_t.h"
#include "QosPy.h"
#include "StatusKindMaskEnum.h"
#include <set>

namespace py = pybind11;

class DomainParticipantFactoryPy
{
public:
  DomainParticipantFactoryPy();

  ~DomainParticipantFactoryPy();
  // 获取包装器单例
  static DomainParticipantFactoryPy *get_instance();
  // 释放底层 DDS 工厂实例
  static DDS::ReturnCode_t finalize_instance();

  DomainParticipantPy *create_participant(const unsigned int &domain_id,
                                                  const DomainParticipantQosPy &qos,
                                                  // DDS::DomainParticipantListener *a_listener,
                                                  const StatusKindMaskEnum &mask);

  DDS::ReturnCode_t delete_participant(DomainParticipantPy *a_dp);

private:
  // 底层 DDS 工厂实例
  static DDS::DomainParticipantFactory *it;
  // 已创建的 DomainParticipantPy 实例集合
  static std::set<DomainParticipantPy *> DomainParticipants;
  // 构造函数私有化，保证单例
};

// 声明 pybind11 绑定函数
void init_DomainParticipantFactory(py::module_ &m);
