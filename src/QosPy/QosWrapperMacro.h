#pragma once
#include <pybind11/pybind11.h>

namespace py = pybind11;

#define DECLARE_QOS_WRAPPER(QOSNAME, DDS_QOS_TYPE, DDS_QOS_DEFAULT) \
  class QOSNAME##Py                                                 \
  {                                                                 \
  public:                                                           \
    explicit QOSNAME##Py(DDS_QOS_TYPE *inputQos) : it(inputQos) {}  \
    ~QOSNAME##Py() = default;                                       \
                                                                    \
    DDS_QOS_TYPE *raw() const { return it; }                        \
                                                                    \
    static QOSNAME##Py getDefault()                                 \
    {                                                               \
      return QOSNAME##Py(&DDS_QOS_DEFAULT);                         \
    }                                                               \
                                                                    \
  private:                                                          \
    DDS_QOS_TYPE *it;                                               \
  };                                                                \
                                                                    \
  inline void init_##QOSNAME(py::module_ &m)                        \
  {                                                                 \
    py::class_<QOSNAME##Py>(m, #QOSNAME)                            \
        .def_static("getDefault", &QOSNAME##Py::getDefault,         \
                    "Get the default " #QOSNAME);                   \
  }
