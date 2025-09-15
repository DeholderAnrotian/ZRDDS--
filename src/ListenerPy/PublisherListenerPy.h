#pragma once
#include <pybind11/pybind11.h>
#include "PublisherListener.h"
#include "Publisher.h"
#include "WrapperCaster.h"

namespace py = pybind11;
using namespace DDS;

class PublisherListenerPy : public PublisherListener, public py::trampoline_self_life_support
{
public:
  using PublisherListener::PublisherListener;
  ~PublisherListenerPy() override = default;
};

void init_PublisherListener(py::module_ &m);