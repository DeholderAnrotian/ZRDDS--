#include "DataWriterListenerPy.h"

void DataWriterListenerPy::on_liveliness_lost(DataWriter *the_writer, const LivelinessLostStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataWriterListener, on_liveliness_lost, the_writer, status);
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
void DataWriterListenerPy::on_offered_deadline_missed(DataWriter *the_writer, const OfferedDeadlineMissedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataWriterListener, on_offered_deadline_missed, the_writer, status);
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
void DataWriterListenerPy::on_offered_incompatible_qos(DataWriter *the_writer, const OfferedIncompatibleQosStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataWriterListener, on_offered_incompatible_qos, the_writer, status);
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
void DataWriterListenerPy::on_publication_matched(DataWriter *the_writer, const PublicationMatchedStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DataWriterListener, on_publication_matched, the_writer, status);
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

void init_DataWriterListener(py::module_ &m)
{
  py::class_<DDS::DataWriterListener, DataWriterListenerPy, py::smart_holder>(m, "DataWriterListener")
      .def(py::init<>());
}