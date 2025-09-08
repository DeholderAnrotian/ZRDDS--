#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <Publisher.h>
#include "ReturnCode_t.h"
#include "DataWriterPy.h"
#include "StatusKindMaskEnum.h"
#include "QosPy.h"

namespace py = pybind11;

class PublisherPy {
public:
    PublisherPy(DDS::Publisher* publisher);
    ~PublisherPy();

    // 返回底层原生指针
    DDS::Publisher* raw() const;

    // 封装常用方法
    virtual DataWriterPy* create_datawriter(
        DDS::Topic* the_topic,
        const PublisherQosPy& qos,
        //DDS::DataWriterListener* a_listener,
        const StatusKindMaskEnum& mask);

    DDS::ReturnCode_t delete_datawriter(DataWriterPy* writer);


private:
    DDS::Publisher* publisher;
};

// pybind11 绑定函数
void init_Publisher(py::module_& m);
