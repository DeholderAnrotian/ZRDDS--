#include "DomainParticipantListenerPy.h "

void DomainParticipantListenerPy::on_domain_received(ULong domainId)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, DomainParticipantListener, on_domain_received, domainId);
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

void init_DomainParticipantListener(py::module_ &m)
{
  py::class_<DDS::DomainParticipantListener, DDS::SubscriberListener, DDS::PublisherListener, DDS::TopicListener, DomainParticipantListenerPy, py::smart_holder>(m, "DomainParticipantListener")
      .def(py::init<>());
}