#include "KeyedStringPy.h"
#include <iostream>

// 构造函数
KeyedStringPy::KeyedStringPy(const std::string &key, const std::string &value)
    : key_(key), value_(value) {
    std::cout << "[KeyedStringPy] Constructor called (key=" 
              << key_ << ", value=" << value_ << ")" << std::endl;
}
KeyedStringPy::KeyedStringPy(const DDS_KeyedString& ks) {
    if (ks.key) {
        key_ = std::string(ks.key); // 拷贝
    } else {
        key_ = "";
    }

    if (ks.value) {
        value_ = std::string(ks.value); // 拷贝
    } else {
        value_ = "";
    }
}

// 析构函数
KeyedStringPy::~KeyedStringPy() {
    std::cout << "[KeyedStringPy] Destructor called" << std::endl;
}

// Getter
std::string KeyedStringPy::get_key() const { return key_; }
std::string KeyedStringPy::get_value() const { return value_; }

// Setter
void KeyedStringPy::set_key(const std::string &k) { key_ = k; }
void KeyedStringPy::set_value(const std::string &v) { value_ = v; }

char* KeyedStringPy::string_dup(const std::string& src) {
    char* buf = new char[src.size() + 1];
    std::memcpy(buf, src.c_str(), src.size() + 1);
    return buf;
}
void KeyedStringPy::string_free(char*& s) {
    if (s) delete[] s;
    s = nullptr;
}


DDS_KeyedString KeyedStringPy::to_dds() const {
    DDS_KeyedString ks;
    ks.key = string_dup(key_);
    ks.value = string_dup(value_);
    return ks;
}


// pybind11 绑定函数
void init_KeyedString(py::module_ &m) {
    py::class_<KeyedStringPy>(m, "KeyedString")
        .def(py::init<const std::string&, const std::string&>(),
             py::arg("key"), py::arg("value"))
        .def("get_key", &KeyedStringPy::get_key)
        .def("get_value", &KeyedStringPy::get_value)
        .def("set_value", &KeyedStringPy::set_value)
        .def("set_key", &KeyedStringPy::set_key);
}