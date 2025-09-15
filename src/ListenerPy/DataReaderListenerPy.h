#pragma once
#include "DataReaderListener.h"
#include "DataReader.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace DDS;

class DataReaderListenerPy : public DataReaderListener, public py::trampoline_self_life_support
{
public:
  using DataReaderListener::DataReaderListener;
  ~DataReaderListenerPy() override = default;

  void on_data_available(DataReader *reader) override;

  void on_requested_deadline_missed(DataReader *reader, const RequestedDeadlineMissedStatus &status) override;

  void on_data_arrived(DataReader *reader, void *sample, const SampleInfo &info) override;

  void on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status) override;

  void on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status) override;

  void on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status) override;

  void on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status) override;

  void on_sample_lost(DataReader *reader, const SampleLostStatus &status) override;
};

void init_DataReaderListener(py::module_ &m);


