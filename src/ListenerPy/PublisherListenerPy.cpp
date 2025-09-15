#include "PublisherListenerPy.h "

void init_PublisherListener(py::module_ &m)
{
  py::class_<DDS::PublisherListener, DDS::DataWriterListener, PublisherListenerPy, py::smart_holder>(m, "PublisherListener")
      .def(py::init<>());
}