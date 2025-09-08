#include "Aliases.h"
#include "TopicPy.h"

TopicPy::TopicPy(DDS::Topic *intputTopic)
    : TopicDescriptionPy(intputTopic) {}

TopicPy::~TopicPy() {}

DDS::Topic *TopicPy::raw() const { return dynamic_cast<DDS::Topic *>(it); }

void init_Topic(py::module_ &m)
{
  py::class_<TopicPy, TopicDescriptionPy>(m, "Topic");
}