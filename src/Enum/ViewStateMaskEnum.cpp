#include "ViewStateMaskEnum.h"

DDS::ViewStateMask getMask(ViewStateMaskEnum mask)
{
  return static_cast<DDS::ViewStateMask>(mask);
}

void init_ViewStateMaskEnum(py::module_ &m)
{
  py::enum_<ViewStateMaskEnum>(m, "ViewStateMask", py::arithmetic())
      .value("NEW_VIEW_STATE", ViewStateMaskEnum::NEW_VIEW_STATE_ENUM)
      .value("NOT_NEW_VIEW_STATE", ViewStateMaskEnum::NOT_NEW_VIEW_STATE_ENUM)
      .value("ANY_VIEW_STATE", ViewStateMaskEnum::ANY_VIEW_STATE_ENUM)
      .export_values();
}