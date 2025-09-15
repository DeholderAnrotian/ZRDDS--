#include "DataReaderListenerPy.h"

namespace py = pybind11;

void DataReaderListenerPy::on_data_available(DataReader *reader)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(      // 基类有默认实现 -> 用 PYBIND11_OVERLOAD
        void,               // 返回类型
        DataReaderListener, // 父类
        on_data_available,  // 方法名
        reader              // 参数
    );
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
void DataReaderListenerPy::on_requested_deadline_missed(DataReader *reader, const RequestedDeadlineMissedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_requested_deadline_missed, reader, status);
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
void DataReaderListenerPy::on_data_arrived(DataReader *reader, void *sample, const SampleInfo &info)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_data_arrived, reader, sample, info);
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
void DataReaderListenerPy::on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_sample_rejected, reader, status);
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
void DataReaderListenerPy::on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_liveliness_changed, reader, status);
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
void DataReaderListenerPy::on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_requested_incompatible_qos, reader, status);
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
void DataReaderListenerPy::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_subscription_matched, reader, status);
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
void DataReaderListenerPy::on_sample_lost(DataReader *reader, const SampleLostStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataReaderListener, on_sample_lost, reader, status);
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

void init_DataReaderListener(py::module_ &m)
{
  py::class_<DDS::DataReaderListener, DataReaderListenerPy, py::smart_holder>(m, "DataReaderListener")
      .def(py::init<>());
}
