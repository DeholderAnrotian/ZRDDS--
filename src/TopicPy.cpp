#include "Aliases.h"
#include "TopicPy.h"

TopicPy::TopicPy(DDS::Topic *intputTopic)
    : topic(intputTopic) {}

TopicPy::~TopicPy() {}

DDS::Topic *TopicPy::raw() const { return topic; }

void init_Topic(py::module_ &m)
{
  py::class_<TopicPy>(m, "Topic")
      .def(py::init<DDS::Topic *>(), py::arg("intputTopic"));
}