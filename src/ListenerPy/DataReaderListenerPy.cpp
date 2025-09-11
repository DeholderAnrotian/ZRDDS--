#include "Aliases.h"
#include "DataReaderListenerPy.h"

namespace py = pybind11;

void DataReaderListenerPy::on_data_available(DataReader *reader)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_data_available, reader);
}
void DataReaderListenerPy::on_requested_deadline_missed(DataReader *reader, const RequestedDeadlineMissedStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_requested_deadline_missed, reader, status);
}
void DataReaderListenerPy::on_data_arrived(DataReader *reader, void *sample, const SampleInfo &info)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_data_arrived, reader, sample, info);
}

void DataReaderListenerPy::on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_sample_rejected, reader, status);
}

void DataReaderListenerPy::on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_liveliness_changed, reader, status);
}

void DataReaderListenerPy::on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_requested_incompatible_qos, reader, status);
}

void DataReaderListenerPy::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_subscription_matched, reader, status);
}

void DataReaderListenerPy::on_sample_lost(DataReader *reader, const SampleLostStatus &status)
{
  PYBIND11_OVERLOAD(void, DataReaderListener, on_sample_lost, reader, status);
}
void init_DataReaderListener(py::module_ &m)
{
  py::class_<DDS::DataReaderListener, DataReaderListenerPy, py::smart_holder>(m, "DataReaderListener")
      .def(py::init<>());
}




