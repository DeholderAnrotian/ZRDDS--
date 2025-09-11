#include "KeyedBytesPy.h"


KeyedBytesPy::KeyedBytesPy(const std::string& key, const py::bytes& py_value) {
    // 复制 key(直接赋值会报错)
    char* buf = new char[key.size() + 1];  // +1 终止符
    std::memcpy(buf, key.c_str(), key.size() + 1);
    data.key = buf;
    DDS_OctetSeq_from_array(&data.value, buffer, length);

    // 初始化 value
    DDS_OctetSeq_initialize(&data.value);

    // 保存 Python bytes 数据
    value_holder = static_cast<std::string>(py_value);

    // 借用内存
    DDS_Octet* buffer = reinterpret_cast<DDS_Octet*>(const_cast<char*>(value_holder.data()));
    DDS_OctetSeq_loan_contiguous(&data.value, buffer, value_holder.size(), value_holder.size());
}

KeyedBytesPy::~KeyedBytesPy() {
    if (data.key) {
        delete[] data.key;
    }
    DDS_OctetSeq_finalize(&data.value);
}

std::string KeyedBytesPy::get_key() const {
    return data.key ? std::string(data.key) : "";
}

py::bytes KeyedBytesPy::get_value() const {
    return py::bytes(value_holder);
}

DDS_KeyedBytes* KeyedBytesPy::get_dds_data() {
    return &data;
}

// -------------------- pybind11 绑定 --------------------
void init_KeyedBytes(py::module_ &m) {
    py::class_<KeyedBytesPy>(m, "KeyedBytes")
        .def(py::init<const std::string&, const py::bytes&>(),
             py::arg("key"), py::arg("value"))
        .def("get_key", &KeyedBytesPy::get_key)
        .def("get_value", &KeyedBytesPy::get_value);
}
