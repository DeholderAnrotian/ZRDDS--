#include "InstanceStateMaskEnum.h"
// 将枚举转换为 DDS 内部掩码
DDS::InstanceStateMask getMask(InstanceStateMaskEnum mask)
{
  return static_cast<DDS::InstanceStateMask>(mask);
}

// 绑定到 Python
void init_InstanceStateMaskEnum(py::module_ &m)
{
  py::enum_<InstanceStateMaskEnum>(m, "InstanceStateMask", py::arithmetic())
      .value("ALIVE_INSTANCE_STATE", InstanceStateMaskEnum::ALIVE_INSTANCE_STATE_ENUM)
      .value("NOT_ALIVE_DISPOSED_INSTANCE_STATE", InstanceStateMaskEnum::NOT_ALIVE_DISPOSED_INSTANCE_STATE_ENUM)
      .value("NOT_ALIVE_NO_WRITERS_INSTANCE_STATE", InstanceStateMaskEnum::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE_ENUM)
      .export_values();
}
