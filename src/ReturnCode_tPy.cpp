#pragma once
#include <pybind11/pybind11.h>
#include "ReturnCode_t.h"

namespace py = pybind11;

void init_ReturnCode_t(py::module_ &m)
{
  py::enum_<DDS_ReturnCode_t>(m, "ReturnCode_t", R"pbdoc(
        DDS interface return type enum

        member:
        - RETCODE_OK: exeute successfully
        - RETCODE_ERROR: execute error
        - RETCODE_UNSUPPORTED: unsupported operation
        - RETCODE_BAD_PARAMETER: incorrect parameter
        - RETCODE_PRECONDITION_NOT_MET: condition not met
        - RETCODE_OUT_OF_RESOURCES: resource insufficient
        - RETCODE_NOT_ENABLED: entity not enabled
        - RETCODE_IMMUTABLE_POLICY: Qos is immutable
        - RETCODE_INCONSISTENT: Qos is inconsistent
        - RETCODE_ALREADY_DELETED: entity already deleted
        - RETCODE_TIMEOUT: operation timeout
        - RETCODE_NO_DATA: no valid data
        - RETCODE_ILLEGAL_OPERATION: illegal operation
        - RETCODE_NOT_ALLOWED_BY_SEC: rejected by security reason
    )pbdoc")
      .value("RETCODE_OK", DDS_RETCODE_OK, "exeute successfully")
      .value("RETCODE_ERROR", DDS_RETCODE_ERROR, "execute error")
      .value("RETCODE_UNSUPPORTED", DDS_RETCODE_UNSUPPORTED, "unsupported operation")
      .value("RETCODE_BAD_PARAMETER", DDS_RETCODE_BAD_PARAMETER, "incorrect parameter")
      .value("RETCODE_PRECONDITION_NOT_MET", DDS_RETCODE_PRECONDITION_NOT_MET, "condition not met")
      .value("RETCODE_OUT_OF_RESOURCES", DDS_RETCODE_OUT_OF_RESOURCES, "resource insufficient")
      .value("RETCODE_NOT_ENABLED", DDS_RETCODE_NOT_ENABLED, "entity not enabled")
      .value("RETCODE_IMMUTABLE_POLICY", DDS_RETCODE_IMMUTABLE_POLICY, "Qos is immutable")
      .value("RETCODE_INCONSISTENT", DDS_RETCODE_INCONSISTENT, "Qos is inconsistent")
      .value("RETCODE_ALREADY_DELETED", DDS_RETCODE_ALREADY_DELETED, "entity already deleted")
      .value("RETCODE_TIMEOUT", DDS_RETCODE_TIMEOUT, "operation timeout")
      .value("RETCODE_NO_DATA", DDS_RETCODE_NO_DATA, "no valid data")
      .value("RETCODE_ILLEGAL_OPERATION", DDS_RETCODE_ILLEGAL_OPERATION, "illegal operation")
      .value("RETCODE_NOT_ALLOWED_BY_SEC", DDS_RETCODE_NOT_ALLOWED_BY_SEC, "rejected by security reason")
      .export_values();
}
