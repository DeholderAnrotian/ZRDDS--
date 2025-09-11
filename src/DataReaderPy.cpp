#include "Aliases.h"
#include "DataReaderPy.h"

DRPy::DataReaderPy(DDS::DataReader *inputDataReader)
    : it(inputDataReader) {}

DRPy::~DataReaderPy() {}

std::tuple<DDS_LongLong, SampleInfoPy, DDS::ReturnCode_t> DataReaderPy::take_next_sample()
{
  DDS_LongLong data_value;
  SampleInfoPy sample_info;
  DDS::ReturnCode_t rtn = static_cast<DDS::ZRDDSDataReader<DDS_LongLong, DDS_LongLongSeq> *>(it)->take_next_sample(data_value, *sample_info.raw());
  return std::make_tuple(data_value, sample_info, rtn);
}

DDS::DataReader *DRPy::raw() const { return it; }

// DDS::ReturnCode_t DRPy::read(StringSeqPy &data_values,
//                              SampleInfoSeqPy &sample_infos,
//                              int max_samples,
//                              SampleStateMaskEnum sample_mask,
//                              ViewStateMaskEnum view_mask,
//                              InstanceStateMaskEnum instance_mask)
// {
//   return static_cast<DDS::ZRDDSDataReader<DDS_String, DDS_StringSeq> *>(it)->read(*data_values.raw(), *sample_infos.raw(), max_samples,
//                                                                                   getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
// }

// DDS::ReturnCode_t DRPy::take(StringSeqPy &data_values,
//                              SampleInfoSeqPy &sample_infos,
//                              int max_samples,
//                              SampleStateMaskEnum sample_mask,
//                              ViewStateMaskEnum view_mask,
//                              InstanceStateMaskEnum instance_mask)
// {
//   return static_cast<DDS::ZRDDSDataReader<DDS_String, DDS_StringSeq> *>(it)->take(*data_values.raw(), *sample_infos.raw(), max_samples,
//                                                                                   getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
// }

void init_DataReader(py::module_ &m)
{
  py::class_<DRPy>(m, "DataReader")
      .def(py::init<DDS::DataReader *>(), py::arg("data_reader"))
      .def("take_next_sample", &DRPy::take_next_sample, "take the next sample from the topic");
  // .def("read", &DRPy::read, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
  //      py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
  //      py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
  //      py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
  //      "Read data from the topic")
  // .def("take", &DRPy::take, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
  //      py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
  //      py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
  //      py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
  //      "Take data from the topic");
}