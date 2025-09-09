#include "DataWriterPy.h"

DataWriterPy::DataWriterPy(DDS::DataWriter *writer)
    : it(writer) {}

DataWriterPy::~DataWriterPy()
{
  // DataWriter 的生命周期一般由 Publisher 管理?
}

DDS::DataWriter *DataWriterPy::raw() const
{
  return it;
}

inline bool DataWriterPy::str_equal(const char *a, const char *b)
{
  if (a == nullptr || b == nullptr)
    return false;
  return std::strcmp(a, b) == 0;
}

DDS::ReturnCode_t DataWriterPy::write(DDS_LongLong data)
{
  return static_cast<DDS::ZRDDSDataWriter<DDS_LongLong> *>(it)->write(data, DDS::HANDLE_NIL_NATIVE);

  // 结构体的内置数据类型没有实现
  // DDS::Topic *topic = writer->get_topic();
  // const char *type_name = topic->get_type_name();

  // if (str_equal(type_name, "DDS::Octet"))
  // {
  //   auto typed = dynamic_cast<DDS::OctetDataWriter *>(writer);
  //   DDS::Octet value = obj.cast<uint8_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::Boolean"))
  // {
  //   auto typed = dynamic_cast<DDS::BooleanDataWriter *>(writer);
  //   if (!typed)
  //     throw std::runtime_error("Writer type mismatch");
  //   DDS::Boolean value = obj.cast<bool>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::Short"))
  // {
  //   auto typed = dynamic_cast<DDS::ShortDataWriter *>(writer);
  //   DDS::Short value = obj.cast<int16_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::UShort"))
  // {
  //   auto typed = dynamic_cast<DDS::UShortDataWriter *>(writer);
  //   if (!typed)
  //     throw std::runtime_error("Writer type mismatch");
  //   DDS::UShort value = obj.cast<uint16_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::Long"))
  // {
  //   auto typed = dynamic_cast<DDS::LongDataWriter *>(writer);
  //   DDS::Long value = obj.cast<int32_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::ULong"))
  // {
  //   auto typed = dynamic_cast<DDS::ULongDataWriter *>(writer);
  //   DDS::ULong value = obj.cast<uint32_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::LongLong"))
  // {
  //   auto typed = dynamic_cast<DDS::LongLongDataWriter *>(writer);
  //   DDS::LongLong value = obj.cast<int64_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::ULongLong"))
  // {
  //   auto typed = dynamic_cast<DDS::ULongLongDataWriter *>(writer);
  //   DDS::ULongLong value = obj.cast<uint64_t>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::Float"))
  // {
  //   auto typed = dynamic_cast<DDS::FloatDataWriter *>(writer);
  //   DDS::Float value = obj.cast<float>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::Double"))
  // {
  //   auto typed = dynamic_cast<DDS::DoubleDataWriter *>(writer);
  //   DDS::Double value = obj.cast<double>();
  //   return typed->write(value, DDS::HANDLE_NIL_NATIVE);
  // }
  // else if (str_equal(type_name, "DDS::String"))
  // {
  //   auto typed = dynamic_cast<DDS::StringDataWriter *>(writer);
  //   std::string value = obj.cast<std::string>();
  //   // 分配可写 DDS::String
  //   char *dds_str = static_cast<char *>(std::malloc(value.size() + 1));
  //   std::memcpy(dds_str, value.c_str(), value.size() + 1); // 拷贝字符串 + '\0'
  //   // 写入
  //   DDS::ReturnCode_t ret = typed->write(dds_str, DDS::HANDLE_NIL_NATIVE);
  //   // 释放内存
  //   std::free(dds_str);
  //   return ret;
  // }
  // else
  // {
  //   throw std::runtime_error(std::string("Unsupported type: ") + type_name);
  // }
}

void init_DataWriter(py::module_ &m)
{
  py::class_<DataWriterPy>(m, "DataWriter")
      .def(py::init<DDS::DataWriter *>(), py::arg("data_writer"))
      .def("write", &DataWriterPy::write, py::arg("data"), "Write data to the topic");
}
