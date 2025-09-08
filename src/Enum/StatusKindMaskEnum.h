#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>

namespace py = pybind11;

enum class StatusKindMaskEnum : unsigned int
{
  STATUS_MASK_NONE_ENUM = 0x0000,
  /** @brief 主题不匹配状态。 @ingroup CoreStatusStruct */
  INCONSISTENT_TOPIC_STATUS_ENUM = 0x0001 << 0,
  /** @brief 数据写者截止时间未满足状态类型。 @ingroup CoreStatusStruct */
  OFFERED_DEADLINE_MISSED_STATUS_ENUM = 0x0001 << 1,
  /** @brief 数据读者截止时间未满足状态类型。 @ingroup CoreStatusStruct */
  REQUESTED_DEADLINE_MISSED_STATUS_ENUM = 0x0001 << 2,
  /** @brief 数据写者端QoS不匹配状态类型。 @ingroup CoreStatusStruct */
  OFFERED_INCOMPATIBLE_QOS_STATUS_ENUM = 0x0001 << 5,
  /** @brief 数据读者端QoS不匹配状态类型。 @ingroup CoreStatusStruct */
  REQUESTED_INCOMPATIBLE_QOS_STATUS_ENUM = 0x0001 << 6,
  /** @brief 数据样本丢失状态类型。 @ingroup CoreStatusStruct */
  SAMPLE_LOST_STATUS_ENUM = 0x0001 << 7,
  /** @brief 数据样本拒绝状态类型。 @ingroup CoreStatusStruct */
  SAMPLE_REJECTED_STATUS_ENUM = 0x0001 << 8,
  /** @brief 订阅者数据到达状态类型。 @ingroup CoreStatusStruct */
  DATA_ON_READERS_STATUS_ENUM = 0x0001 << 9,
  /** @brief 数据读者数据到达状态类型。 @ingroup CoreStatusStruct */
  DATA_AVAILABLE_STATUS_ENUM = 0x0001 << 10,
  /** @brief 数据写者存活性状态丢失状态。 @ingroup CoreStatusStruct */
  LIVELINESS_LOST_STATUS_ENUM = 0x0001 << 11,
  /** @brief 数据写者存活性改变状态类型。 @ingroup CoreStatusStruct */
  LIVELINESS_CHANGED_STATUS_ENUM = 0x0001 << 12,
  /** @brief 数据写者匹配状态类型。 @ingroup CoreStatusStruct */
  PUBLICATION_MATCHED_STATUS_ENUM = 0x0001 << 13,
  /** @brief 数据读者匹配状态类型。 @ingroup CoreStatusStruct */
  SUBSCRIPTION_MATCHED_STATUS_ENUM = 0x0001 << 14,
  STATUS_MASK_ALL_ENUM = INCONSISTENT_TOPIC_STATUS_ENUM |
                         OFFERED_DEADLINE_MISSED_STATUS_ENUM |
                         REQUESTED_DEADLINE_MISSED_STATUS_ENUM |
                         OFFERED_INCOMPATIBLE_QOS_STATUS_ENUM |
                         REQUESTED_INCOMPATIBLE_QOS_STATUS_ENUM |
                         SAMPLE_LOST_STATUS_ENUM |
                         SAMPLE_REJECTED_STATUS_ENUM |
                         DATA_ON_READERS_STATUS_ENUM |
                         DATA_AVAILABLE_STATUS_ENUM |
                         LIVELINESS_LOST_STATUS_ENUM |
                         LIVELINESS_CHANGED_STATUS_ENUM |
                         PUBLICATION_MATCHED_STATUS_ENUM |
                         SUBSCRIPTION_MATCHED_STATUS_ENUM
};

DDS_StatusKindMask getMask(StatusKindMaskEnum mask);

void init_StatusKindMaskEnum(py::module_ &m);