#include "KeyedBytesPy.h"


KeyedBytesPy::KeyedBytesPy(const std::string& key, const py::bytes& value)
    : key_(key), value_(value)
{
    std::cout << "[KeyedBytesPy] Constructor called (key=" << key_ << ")" << std::endl;
}

KeyedBytesPy::KeyedBytesPy(const DDS_KeyedBytes& data) {
    if (data.key)
        key_ = std::string(data.key);
    else
        key_ = "";

    if (DDS_OctetSeq_get_length(&data.value) > 0) {
        int len = DDS_OctetSeq_get_length(&data.value);
        DDS_Octet* buf = DDS_OctetSeq_get_contiguous_buffer(&data.value);
        value_ = py::bytes(reinterpret_cast<const char*>(buf), len);
    } else {
        value_ = py::bytes("");
    }

    std::cout << "[KeyedBytesPy] Constructed from DDS_KeyedBytes" << std::endl;
}

KeyedBytesPy::~KeyedBytesPy() {
    std::cout << "[KeyedBytesPy] Destructor called" << std::endl;
}

std::string KeyedBytesPy::get_key() const { return key_; }
py::bytes KeyedBytesPy::get_value() const { return value_; }

void KeyedBytesPy::set_key(const std::string& k) { key_ = k; }
void KeyedBytesPy::set_value(const py::bytes& v) { value_ = v; }

DDS_KeyedBytes KeyedBytesPy::to_dds() const {
    DDS_KeyedBytes data;

    // key
    char* kbuf = new char[key_.size() + 1];
    std::memcpy(kbuf, key_.c_str(), key_.size() + 1);
    data.key = kbuf;

    // value
    std::string val_str = static_cast<std::string>(value_);
    DDS_OctetSeq_initialize(&data.value);
    DDS_Octet* buf = reinterpret_cast<DDS_Octet*>(const_cast<char*>(val_str.data()));
    DDS_OctetSeq_loan_contiguous(&data.value, buf, (int)val_str.size(), (int)val_str.size());

    return data;
}
// -------------------- pybind11 绑定 --------------------
void init_KeyedBytes(py::module_ &m) {
    py::class_<KeyedBytesPy>(m, "KeyedBytes")
        .def(py::init<const std::string&, const py::bytes&>(),
             py::arg("key"), py::arg("value"))
        .def("get_key", &KeyedBytesPy::get_key)
        .def("get_value", &KeyedBytesPy::get_value)
        .def("set_key", &KeyedBytesPy::set_key)
        .def("set_value", &KeyedBytesPy::set_value)
        .def("to_dds", &KeyedBytesPy::to_dds);
}
