#pragma once
#include "TopicListener.h"
#include "Topic.h"
#include <pybind11/pybind11.h>
#include "WrapperCaster.h"

namespace py = pybind11;
using namespace DDS;

class TopicListenerPy : public TopicListener, public py::trampoline_self_life_support
{
public:
  using TopicListener::TopicListener;
  ~TopicListenerPy() override = default;
  virtual void on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status) override;
};

void init_TopicListener(py::module_ &m);