#include "SampleStateMaskEnum.h"

DDS::SampleStateMask getMask(SampleStateMaskEnum mask)
{
  return static_cast<DDS::SampleStateMask>(mask);
}

void init_SampleStateMaskEnum(py::module_ &m)
{
  py::enum_<SampleStateMaskEnum>(m, "SampleStateMask", py::arithmetic())
      .value("READ_SAMPLE_STATE", SampleStateMaskEnum::READ_SAMPLE_STATE_ENUM)
      .value("NOT_READ_SAMPLE_STATE", SampleStateMaskEnum::NOT_READ_SAMPLE_STATE_ENUM)
      .value("ANY_SAMPLE_STATE", SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM)
      .export_values();
}