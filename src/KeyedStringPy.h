#pragma once
#include <pybind11/pybind11.h>
#include <string>
#include "ZRBuiltinTypes.h" 

namespace py = pybind11;

class KeyedStringPy {
public:
    // 构造 & 析构
    KeyedStringPy(const std::string &key, const std::string &value);
    KeyedStringPy(const DDS_KeyedString& ks);
    ~KeyedStringPy();

    // Get函数
    std::string get_key() const;
    std::string get_value() const;

    // Set函数
    void set_key(const std::string &k);
    void set_value(const std::string &v);

    // 转换为 DDS_KeyedString（传给底层 C++ DDS 用）
    DDS_KeyedString to_dds() const;

    static char* string_dup(const std::string& src);
    static void string_free(char*& s);

private:
    std::string key_;
    std::string value_;
};
void init_KeyedString(py::module_ &m);