#pragma once
#include <pybind11/pybind11.h>
#include "DomainParticipantListener.h"
#include "DomainParticipant.h"
#include "WrapperCaster.h"

namespace py = pybind11;
using namespace DDS;

class DomainParticipantListenerPy : public DomainParticipantListener, public py::trampoline_self_life_support
{
public:
  using DomainParticipantListener::DomainParticipantListener;
  ~DomainParticipantListenerPy() override = default;
  void on_domain_received(ULong domainId) override;
};

void init_DomainParticipantListener(py::module_ &m);