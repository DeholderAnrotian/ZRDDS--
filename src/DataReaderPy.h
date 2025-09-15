#pragma once
#include <pybind11/pybind11.h>
#include "DataReader.h"
#include "ZRDDSDataReader.h"
#include "ReturnCode_t.h"
#include "SampleStateMaskEnum.h"
#include "ViewStateMaskEnum.h"
#include "InstanceStateMaskEnum.h"
#include "SampleInfoPy.h"
#include "ReturnCode_t.h"
#include <tuple>
#include "SampleInfo.h"
#include <ZRBuiltinTypesDataReader.h>
#include <iostream>
#include "ViewStateMaskEnum.h"
#include "SampleStateMaskEnum.h"
#include "InstanceStateMaskEnum.h"
namespace py = pybind11;

class DataReaderPy
{
public:
  DataReaderPy(DDS::DataReader *inputDataReader);

  ~DataReaderPy();

  DDS::DataReader *raw() const;

  std::tuple<py::object, SampleInfoPy, DDS::ReturnCode_t> take_next_sample();
  std::tuple<py::object, SampleInfoPy, DDS::ReturnCode_t> read_next_sample();
  std::tuple<py::list, py::list, DDS::ReturnCode_t> take(
      int max_samples,
      SampleStateMaskEnum sample_mask_enum,
      ViewStateMaskEnum view_mask_enum,
      InstanceStateMaskEnum instance_mask_enum);

  std::tuple<py::list, py::list, DDS::ReturnCode_t> read(
    int max_samples, 
    SampleStateMaskEnum sample_mask_enum, 
    ViewStateMaskEnum view_mask_enum, 
    InstanceStateMaskEnum instance_mask_enum);

  // inline bool string_equal(const char *a, const char *b);

  // DDS::ReturnCode_t read(StringSeqPy &data_values,
  //                        SampleInfoSeqPy &sample_infos,
  //                        int max_samples,
  //                        SampleStateMaskEnum sample_mask,
  //                        ViewStateMaskEnum view_mask,
  //                        InstanceStateMaskEnum instance_mask);

  // DDS::ReturnCode_t take(StringSeqPy &data_values,
  //                        SampleInfoSeqPy &sample_infos,
  //                        int max_samples,
  //                        SampleStateMaskEnum sample_mask,
  //                        ViewStateMaskEnum view_mask,
  //                        InstanceStateMaskEnum instance_mask);

private:
  DDS::DataReader *it;
  std::string type_name;
};

void init_DataReader(py::module_ &m);