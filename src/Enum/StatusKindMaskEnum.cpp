#include "StatusKindMaskEnum.h"

DDS::StatusKindMask getMask(StatusKindMaskEnum mask)
{
  return static_cast<DDS::StatusKindMask>(mask);
}

void init_StatusKindMaskEnum(py::module_ &m)
{
  py::enum_<StatusKindMaskEnum>(m, "StatusKindMask", py::arithmetic())
      .value("STATUS_MASK_NONE", StatusKindMaskEnum::STATUS_MASK_NONE_ENUM)
      .value("STATUS_MASK_ALL", StatusKindMaskEnum::STATUS_MASK_ALL_ENUM)
      .value("INCONSISTENT_TOPIC_STATUS", StatusKindMaskEnum::INCONSISTENT_TOPIC_STATUS_ENUM)
      .value("OFFERED_DEADLINE_MISSED_STATUS", StatusKindMaskEnum::OFFERED_DEADLINE_MISSED_STATUS_ENUM)
      .value("REQUESTED_DEADLINE_MISSED_STATUS", StatusKindMaskEnum::REQUESTED_DEADLINE_MISSED_STATUS_ENUM)
      .value("OFFERED_INCOMPATIBLE_QOS_STATUS", StatusKindMaskEnum::OFFERED_INCOMPATIBLE_QOS_STATUS_ENUM)
      .value("REQUESTED_INCOMPATIBLE_QOS_STATUS", StatusKindMaskEnum::REQUESTED_INCOMPATIBLE_QOS_STATUS_ENUM)
      .value("SAMPLE_LOST_STATUS", StatusKindMaskEnum::SAMPLE_LOST_STATUS_ENUM)
      .value("SAMPLE_REJECTED_STATUS", StatusKindMaskEnum::SAMPLE_REJECTED_STATUS_ENUM)
      .value("DATA_ON_READERS_STATUS", StatusKindMaskEnum::DATA_ON_READERS_STATUS_ENUM)
      .value("DATA_AVAILABLE_STATUS", StatusKindMaskEnum::DATA_AVAILABLE_STATUS_ENUM)
      .value("LIVELINESS_LOST_STATUS", StatusKindMaskEnum::LIVELINESS_LOST_STATUS_ENUM)
      .value("LIVELINESS_CHANGED_STATUS", StatusKindMaskEnum::LIVELINESS_CHANGED_STATUS_ENUM)
      .value("PUBLICATION_MATCHED_STATUS", StatusKindMaskEnum::PUBLICATION_MATCHED_STATUS_ENUM)
      .value("SUBSCRIPTION_MATCHED_STATUS", StatusKindMaskEnum::SUBSCRIPTION_MATCHED_STATUS_ENUM)
      .export_values();
}