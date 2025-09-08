#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>

namespace py = pybind11;

// 定义枚举
enum class InstanceStateMaskEnum : unsigned int
{
  ALIVE_INSTANCE_STATE_ENUM = 0x0001 << 0,
  NOT_ALIVE_DISPOSED_INSTANCE_STATE_ENUM = 0x0001 << 1,
  NOT_ALIVE_NO_WRITERS_INSTANCE_STATE_ENUM = 0x0001 << 2,
  ANY_INSTANCE_STATE_ENUM = ALIVE_INSTANCE_STATE_ENUM | NOT_ALIVE_DISPOSED_INSTANCE_STATE_ENUM | NOT_ALIVE_NO_WRITERS_INSTANCE_STATE_ENUM
};
// 转换函数，返回 DDS 内部类型
DDS::InstanceStateMask getMask(InstanceStateMaskEnum mask);
// Python 绑定函数
void init_InstanceStateMaskEnum(py::module_ &m);
