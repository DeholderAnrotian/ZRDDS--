#include "DataWriterPy.h"

DataWriterPy::DataWriterPy(DDS::DataWriter *writer)
    : writer(writer) {}

DataWriterPy::~DataWriterPy()
{
  // DataWriter 的生命周期一般由 Publisher 管理?
}

DDS::DataWriter *DataWriterPy::raw() const
{
  return writer;
}

inline bool DataWriterPy::str_equal(const char *a, const char *b)
{
  if (a == nullptr || b == nullptr)
    return false;
  return std::strcmp(a, b) == 0;
}

DDS::ReturnCode_t DataWriterPy::write(py::object obj)
{
  // return static_cast<DDS::ZRDDSDataWriter<DDS_LongLong> *>(it)->write(data, DDS::HANDLE_NIL_NATIVE);

  //结构体的内置数据类型没有实现
  DDS::Topic *topic = writer->get_topic();
  const char *type_name = topic->get_type_name();

  if (str_equal(type_name, "DDS_Octet"))
  {
    auto typed = dynamic_cast<DDS::OctetDataWriter *>(writer);
    DDS::Octet value = obj.cast<uint8_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_Boolean"))
  {
    auto typed = dynamic_cast<DDS::BooleanDataWriter *>(writer);
    if (!typed)
      throw std::runtime_error("Writer type mismatch");
    DDS::Boolean value = obj.cast<bool>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_Short"))
  {
    auto typed = dynamic_cast<DDS::ShortDataWriter *>(writer);
    DDS::Short value = obj.cast<int16_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_UShort"))
  {
    auto typed = dynamic_cast<DDS::UShortDataWriter *>(writer);
    if (!typed)
      throw std::runtime_error("Writer type mismatch");
    DDS::UShort value = obj.cast<uint16_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_Long"))
  {
    auto typed = dynamic_cast<DDS::LongDataWriter *>(writer);
    DDS::Long value = obj.cast<int32_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_ULong"))
  {
    auto typed = dynamic_cast<DDS::ULongDataWriter *>(writer);
    DDS::ULong value = obj.cast<uint32_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_LongLong"))
  {
    auto typed = dynamic_cast<DDS::LongLongDataWriter *>(writer);
    DDS::LongLong value = obj.cast<int64_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_ULongLong"))
  {
    auto typed = dynamic_cast<DDS::ULongLongDataWriter *>(writer);
    DDS::ULongLong value = obj.cast<uint64_t>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_Float"))
  {
    auto typed = dynamic_cast<DDS::FloatDataWriter *>(writer);
    DDS::Float value = obj.cast<float>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_Double"))
  {
    auto typed = dynamic_cast<DDS::DoubleDataWriter *>(writer);
    DDS::Double value = obj.cast<double>();
    return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  }
  else if (str_equal(type_name, "DDS_String"))
  {
    auto typed = dynamic_cast<DDS::StringDataWriter *>(writer);
    std::string value = obj.cast<std::string>();
    // 分配可写 DDS::String
    char *dds_str = static_cast<char *>(std::malloc(value.size() + 1));
    std::memcpy(dds_str, value.c_str(), value.size() + 1); // 拷贝字符串 + '\0'
    // 写入
    DDS::ReturnCode_t ret = typed->write(dds_str, DDS::HANDLE_NIL_NATIVE);
    // 释放内存
    std::free(dds_str);
    return ret;
  }
  //结构体数据类型
  else if (str_equal(type_name, "DDS_Bytes"))
  {
    auto typed = dynamic_cast<DDS::BytesDataWriter *>(writer);
    if (!typed)
      throw std::runtime_error("Writer type mismatch for DDS_Bytes");
    DDS_Bytes data;
    py::bytes py_bytes = obj.cast<py::bytes>();
    std::string bytes_str = static_cast<std::string>(py_bytes);
    // 构造DDS::Bytes
    DDS_Octet* buffer = reinterpret_cast<DDS_Octet*>(const_cast<char*>(bytes_str.data()));
    int length = static_cast<int>(bytes_str.size());
    // 初始化内部缓冲区并填充
    //DDS_OctetSeq_from_array(&data.value, buffer, length);
    DDS_OctetSeq_initialize(&data.value);
    DDS_OctetSeq_loan_contiguous(&data.value, buffer, length, length);
    // 写入
    DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);
    return ret;

  }
  else if(str_equal(type_name, "DDS_KeyedBytes"))
  {
    auto typed = dynamic_cast<DDS::KeyedBytesDataWriter *>(writer);
    if (!typed)
      throw std::runtime_error("Writer type mismatch for KeyedBytes");

    // 构造 DDS_KeyedBytes
    DDS_KeyedBytes data;

    // 从 Python 对象取出 KeyedBytesPy
    KeyedBytesPy &kb = obj.cast<KeyedBytesPy&>();

    // --- 处理 key ---
    const std::string key_str = kb.get_key();
    char* key_buf = new char[key_str.size() + 1];
    std::memcpy(key_buf, key_str.c_str(), key_str.size() + 1);
    data.key = key_buf;

   // --- 处理 value ---
    py::bytes py_bytes = kb.get_value();
    std::string value_str = static_cast<std::string>(py_bytes);

    DDS_Octet* buffer = reinterpret_cast<DDS_Octet*>(const_cast<char*>(value_str.data()));
    int length = static_cast<int>(value_str.size());
    DDS_OctetSeq_initialize(&data.value);
    DDS_OctetSeq_loan_contiguous(&data.value, buffer, length, length);

    // 写入
    DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);

    delete[] data.key;
    DDS_OctetSeq_finalize(&data.value);

    return ret;
  }
  else
  {
    throw std::runtime_error(std::string("Unsupported type: ") + type_name);
  }
}

void init_DataWriter(py::module_ &m)
{
  py::class_<DataWriterPy>(m, "DataWriter")
      .def(py::init<DDS::DataWriter *>(), py::arg("data_writer"))
      .def("write", &DataWriterPy::write, py::arg("data"), "Write data to the topic");
}
