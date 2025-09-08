#include "Aliases.h"
#include "DataReaderPy.h"

DRPy::DataReaderPy(DDS::DataReader *inputDataReader)
    : it(inputDataReader) {}

DRPy::~DataReaderPy() {}

DDS::DataReader *DRPy::raw() const { return it; }

DDS::ReturnCode_t DRPy::read(LongLongSeqPy &data_values,
                             SampleInfoSeqPy &sample_infos,
                             int max_samples,
                             SampleStateMaskEnum sample_mask,
                             ViewStateMaskEnum view_mask,
                             InstanceStateMaskEnum instance_mask)
{
  return static_cast<DDS::ZRDDSDataReader<DDS_LongLong, DDS_LongLongSeq> *>(it)->read(*data_values.raw(), *sample_infos.raw(), max_samples,
                                                                                      getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
}

DDS::ReturnCode_t DRPy::take(LongLongSeqPy &data_values,
                             SampleInfoSeqPy &sample_infos,
                             int max_samples,
                             SampleStateMaskEnum sample_mask,
                             ViewStateMaskEnum view_mask,
                             InstanceStateMaskEnum instance_mask)
{
  return static_cast<DDS::ZRDDSDataReader<DDS_LongLong, DDS_LongLongSeq> *>(it)->take(*data_values.raw(), *sample_infos.raw(), max_samples,
                                                                                      getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
}

void init_DataReader(py::module_ &m)
{
  py::class_<DRPy>(m, "DataReader")
      .def("read", &DRPy::read, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
           py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
           py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
           py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
           "Read data from the topic")
      .def("take", &DRPy::take, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
           py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
           py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
           py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
           "Take data from the topic");
}