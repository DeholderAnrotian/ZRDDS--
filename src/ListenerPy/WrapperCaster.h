#pragma once
#include <pybind11/pybind11.h>
#include "DataReaderListener.h"
#include "DataReaderListenerPy.h"
namespace py = pybind11;

namespace pybind11
{
  namespace detail
  {
    // 泛型封装类 type_caster
    // TWrapper: 封装类，如 DataReaderPy
    // TRaw: 裸指针类型，如 DDS::DataReader*
    template <typename TWrapper, typename TRaw>
    struct pointer_wrapper_caster
    {
      PYBIND11_TYPE_CASTER(TRaw *, _("WrappedPointer"));

      // Python -> C++ 裸指针
      bool load(handle src, bool)
      {
        // Python 端是封装类，取裸指针
        value = src.cast<TWrapper>().raw();
        return true;
      }

      // C++ 裸指针 -> Python 封装类
      static handle cast(TRaw *src, return_value_policy /*policy*/, handle /*parent*/)
      {
        return py::cast(TWrapper(src)).release();
      }
    };

  }
} // namespace pybind11::detail
