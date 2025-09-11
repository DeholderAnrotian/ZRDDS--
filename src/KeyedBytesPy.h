#pragma once
#include <string.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>   
#include <ZRBuiltinTypes.h>    

namespace py = pybind11;

class KeyedBytesPy {
public:
    // 构造函数
    KeyedBytesPy(const std::string& key, const py::bytes& value);

    // 析构函数
    ~KeyedBytesPy();

    // 获取 key
    std::string get_key() const;

    // 获取 value
    py::bytes get_value() const;

    // 获取底层 DDS 数据对象
    DDS_KeyedBytes* get_dds_data();

private:
    DDS_KeyedBytes data;           // 底层 DDS 数据
    std::string value_holder;  // 保存 value 内存，保证 loan_contiguous 安全
};

// pybind11 绑定函数
void init_KeyedBytes(py::module_ &m);
