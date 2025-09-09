#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>  
#include "ReturnCode_t.h"
#include <DataWriter.h>
#include <ZRDDSDataWriter.h>
#include <ZRBuiltinTypesDataWriter.h>

namespace py = pybind11;

class DataWriterPy {
public:
    DataWriterPy(DDS::DataWriter* it);
    ~DataWriterPy();

    DDS::DataWriter* raw() const;

    DDS::ReturnCode_t write(DDS_LongLong data); 

    inline bool str_equal(const char* a, const char* b);
    
private:
    DDS::DataWriter* it;
};

void init_DataWriter(py::module_ &m);
