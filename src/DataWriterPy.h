#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include "ReturnCode_t.h"
#include <DataWriter.h>
#include <ZRDDSDataWriter.h>
#include <ZRBuiltinTypes.h>
#include <ZRBuiltinTypesDataWriter.h>
#include <ZRBuiltinTypes.h> 
#include "KeyedBytesPy.h"
#include "KeyedStringPy.h"
namespace py = pybind11;

class DataWriterPy
{
public:
  DataWriterPy(DDS::DataWriter *writer);
  ~DataWriterPy();

  DDS::DataWriter *raw() const;

  DDS::ReturnCode_t write(py::object obj);

  // inline bool str_equal(const std::string a, const std::string b);

private:
  DDS::DataWriter *it;
  std::string type_name;
};

void init_DataWriter(py::module_ &m);
