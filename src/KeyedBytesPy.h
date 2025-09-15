#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>   
#include <ZRBuiltinTypes.h>    
#include <iostream>
#include <cstring>

namespace py = pybind11;

class KeyedBytesPy {
public:
    // 构造函数
    KeyedBytesPy(const std::string& key, const py::bytes& value);
    KeyedBytesPy(const DDS_KeyedBytes& data);

    // 析构函数
    ~KeyedBytesPy();

    std::string get_key() const;
    py::bytes get_value() const;

    void set_key(const std::string& k);
    void set_value(const py::bytes& v);

    DDS_KeyedBytes to_dds() const;
private:
    std::string key_;
    py::bytes value_;
    // DDS_KeyedBytes data;           // 底层 DDS 数据
    // std::string value_holder;  // 保存 value 内存，保证 loan_contiguous 安全
};

// pybind11 绑定函数
void init_KeyedBytes(py::module_ &m);
