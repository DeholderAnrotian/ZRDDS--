#include "Aliases.h"
#include "TopicDescriptionPy.h"

TopicDescriptionPy::TopicDescriptionPy(DDS::TopicDescription *intputTopicDescription)
    : it(intputTopicDescription) {}

TopicDescriptionPy::~TopicDescriptionPy() {}

DDS::TopicDescription *TopicDescriptionPy::raw() const { return it; }

void init_TopicDescription(py::module_ &m)
{
  py::class_<TopicDescriptionPy>(m, "TopicDescription");
}