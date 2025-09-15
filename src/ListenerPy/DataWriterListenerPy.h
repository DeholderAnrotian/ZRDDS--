#pragma once
#include <pybind11/pybind11.h>
#include "DataWriterListener.h"
#include "DataWriter.h"
#include "WrapperCaster.h"

namespace py = pybind11;
using namespace DDS;

class DataWriterListenerPy : public DataWriterListener, public py::trampoline_self_life_support
{
public:
  using DataWriterListener::DataWriterListener;
  ~DataWriterListenerPy() override = default;

  void on_liveliness_lost(DataWriter *the_writer, const LivelinessLostStatus &status) override;

  void on_offered_deadline_missed(DataWriter *the_writer, const OfferedDeadlineMissedStatus &status) override;

  void on_offered_incompatible_qos(DataWriter *the_writer, const OfferedIncompatibleQosStatus &status) override;

  void on_publication_matched(DataWriter *the_writer, const PublicationMatchedStatus &status) override;
};

void init_DataWriterListener(py::module_ &m);
