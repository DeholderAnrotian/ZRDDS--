#include "SubscriberListenerPy.h"

void SubscriberListenerPy::on_data_on_readers(Subscriber *the_subscriber)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, SubscriberListener, on_data_on_readers, the_subscriber);
  }
  catch (const py::error_already_set &e)
  {
    // 打印 Python 异常到 stderr，防止异常穿越回调线程导致崩溃
    PyErr_Print();
    PyErr_Clear();
  }
  catch (const std::exception &e)
  {
    // 捕获其他 C++ 异常
    fprintf(stderr, "C++ exception in on_data_available trampoline: %s\n", e.what());
  }
  catch (...)
  {
    fprintf(stderr, "Unknown exception in on_data_available trampoline.\n");
  }
}

void init_SubscriberListener(py::module_ &m)
{
  py::class_<DDS::SubscriberListener, DDS::DataReaderListener, SubscriberListenerPy, py::smart_holder>(m, "SubscriberListener")
      .def(py::init<>());
}