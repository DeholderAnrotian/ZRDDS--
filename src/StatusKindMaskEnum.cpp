#include "StatusKindMaskEnum.h"

DDS::StatusKindMask getMask(StatusKindMaskEnum mask)
{
  switch (mask)
  {
  case StatusKindMaskEnum::DDS_STATUS_MASK_NONE_ENUM:
    return DDS::STATUS_MASK_NONE;
  case StatusKindMaskEnum::DDS_STATUS_MASK_ALL_ENUM:
    return DDS::STATUS_MASK_ALL;
  default:
    throw std::invalid_argument("Invalid StatusKingMaskEnum value");
  }
}

void init_StatusKindMaskEnum(py::module_ &m)
{
  py::enum_<StatusKindMaskEnum>(m, "StatusKindMaskEnum")
      .value("STATUS_MASK_NONE", StatusKindMaskEnum::DDS_STATUS_MASK_NONE_ENUM)
      .value("STATUS_MASK_ALL", StatusKindMaskEnum::DDS_STATUS_MASK_ALL_ENUM)
      .export_values();
}