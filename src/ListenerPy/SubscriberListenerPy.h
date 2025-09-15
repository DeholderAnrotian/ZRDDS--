#pragma once
#include <pybind11/pybind11.h>
#include "SubscriberListener.h"
#include "Subscriber.h"
#include "WrapperCaster.h"

namespace py = pybind11;
using namespace DDS;

class SubscriberListenerPy : public SubscriberListener, public py::trampoline_self_life_support
{
public:
  using SubscriberListener::SubscriberListener;
  ~SubscriberListenerPy() override = default;
  virtual void on_data_on_readers(Subscriber *the_subscriber) override;
};

void init_SubscriberListener(py::module_ &m);