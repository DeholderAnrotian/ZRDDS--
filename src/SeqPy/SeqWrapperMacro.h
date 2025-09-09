#pragma once
#include <pybind11/pybind11.h>
#include <vector>

namespace py = pybind11;

#define DECLARE_SEQ_WRAPPER(SEQNAME, DDS_SEQ_TYPE, ELEM_TYPE)               \
  class SEQNAME##Py                                                         \
  {                                                                         \
  public:                                                                   \
    SEQNAME##Py() { DDS_SEQ_TYPE##_initialize(it); }                        \
                                                                            \
    explicit SEQNAME##Py(DDS_SEQ_TYPE *input) : it(input) {}                \
                                                                            \
    ~SEQNAME##Py() {}                                                       \
                                                                            \
    DDS_SEQ_TYPE *raw() const { return it; }                                \
                                                                            \
    std::vector<ELEM_TYPE> to_list() const                                  \
    {                                                                       \
      std::vector<ELEM_TYPE> result;                                        \
      if (!it)                                                              \
        return result;                                                      \
      auto n = DDS_SEQ_TYPE##_get_length(it);                               \
      result.resize(n);                                                     \
      DDS_SEQ_TYPE##_to_array(it, result.data(), n);                        \
      return result;                                                        \
    }                                                                       \
                                                                            \
  private:                                                                  \
    DDS_SEQ_TYPE *it;                                                       \
  };                                                                        \
                                                                            \
  inline void init_##SEQNAME(py::module_ &m)                                \
  {                                                                         \
    py::class_<SEQNAME##Py>(m, #SEQNAME)                                    \
        .def(py::init<>())                                                  \
        .def("to_list", &SEQNAME##Py::to_list, "Convert to a Python list"); \
  }
