#pragma once
#include <pybind11/pybind11.h>
#include "DataReader.h"
#include "ZRDDSDataReader.h"
#include "ReturnCode_t.h"
#include "SeqPy.h"
#include "SampleStateMaskEnum.h"
#include "ViewStateMaskEnum.h"
#include "InstanceStateMaskEnum.h"

namespace py = pybind11;

class DataReaderPy
{
public:
  DataReaderPy(DDS::DataReader *inputDataReader);

  ~DataReaderPy();

  DDS::DataReader *raw() const;

  DDS::ReturnCode_t read(LongLongSeqPy &data_values,
                         SampleInfoSeqPy &sample_infos,
                         int max_samples,
                         SampleStateMaskEnum sample_mask,
                         ViewStateMaskEnum view_mask,
                         InstanceStateMaskEnum instance_mask);

  DDS::ReturnCode_t take(LongLongSeqPy &data_values,
                         SampleInfoSeqPy &sample_infos,
                         int max_samples,
                         SampleStateMaskEnum sample_mask,
                         ViewStateMaskEnum view_mask,
                         InstanceStateMaskEnum instance_mask);

private:
  DDS::DataReader *it;
};

void init_DataReader(py::module_ &m);