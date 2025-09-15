#include "TopicListenerPy.h"

void TopicListenerPy::on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status)
{
  py::gil_scoped_acquire gil;
  try
  {
    PYBIND11_OVERLOAD(void, TopicListener, on_inconsistent_topic, the_topic, status);
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
void init_TopicListener(py::module_ &m)
{
  py::class_<DDS::TopicListener, TopicListenerPy, py::smart_holder>(m, "TopicListener")
      .def(py::init<>());
}