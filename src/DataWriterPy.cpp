#include "DataWriterPy.h"

DataWriterPy::DataWriterPy(DDS::DataWriter *writer)
    : it(writer)
{
  type_name = it->get_topic()->get_type_name();
}

DataWriterPy::~DataWriterPy()
{
  // DataWriter 的生命周期一般由 Publisher 管理?
}

DDS::DataWriter *DataWriterPy::raw() const
{
  return it;
}

DDS::ReturnCode_t DataWriterPy::write(py::object obj)
{
  // return static_cast<DDS::ZRDDSDataWriter<DDS_LongLong> *>(it)->write(data, DDS::HANDLE_NIL_NATIVE);

  try
  {
    if (type_name == "DDS_Octet")
    {
      auto typed = dynamic_cast<DDS::OctetDataWriter *>(it);
      DDS::Octet value = obj.cast<uint8_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_Boolean")
    {
      auto typed = dynamic_cast<DDS::BooleanDataWriter *>(it);
      DDS::Boolean value = obj.cast<bool>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_Short")
    {
      auto typed = dynamic_cast<DDS::ShortDataWriter *>(it);
      DDS::Short value = obj.cast<int16_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_UShort")
    {
      auto typed = dynamic_cast<DDS::UShortDataWriter *>(it);
      DDS::UShort value = obj.cast<uint16_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_Long")
    {
      auto typed = dynamic_cast<DDS::LongDataWriter *>(it);
      DDS::Long value = obj.cast<int32_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_ULong")
    {
      auto typed = dynamic_cast<DDS::ULongDataWriter *>(it);
      DDS::ULong value = obj.cast<uint32_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_LongLong")
    {
      auto typed = dynamic_cast<DDS::LongLongDataWriter *>(it);
      DDS::LongLong value = obj.cast<int64_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_ULongLong")
    {
      auto typed = dynamic_cast<DDS::ULongLongDataWriter *>(it);
      DDS::ULongLong value = obj.cast<uint64_t>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_Float")
    {
      auto typed = dynamic_cast<DDS::FloatDataWriter *>(it);
      DDS::Float value = obj.cast<float>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_Double")
    {
      auto typed = dynamic_cast<DDS::DoubleDataWriter *>(it);
      DDS::Double value = obj.cast<double>();
      return typed->write(value, DDS::HANDLE_NIL_NATIVE);
    }
    else if (type_name == "DDS_String")
    {
      auto typed = dynamic_cast<DDS::StringDataWriter *>(it);
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
    else if (type_name == "DDS_Bytes")
    {
      auto typed = dynamic_cast<DDS::BytesDataWriter *>(it);
      DDS_Bytes data;
      py::bytes py_bytes = obj.cast<py::bytes>();
      std::string bytes_str = static_cast<std::string>(py_bytes);

      DDS_Octet *buffer = reinterpret_cast<DDS_Octet *>(const_cast<char *>(bytes_str.data()));
      int length = static_cast<int>(bytes_str.size());

      DDS_OctetSeq_initialize(&data.value);
      DDS_OctetSeq_loan_contiguous(&data.value, buffer, length, length);

      DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);
      return ret;
    }
    else
    {
      return DDS::RETCODE_UNSUPPORTED;
    }
  }

  else if (str_equal(type_name, "DDS_KeyedString"))
  {
      auto typed = dynamic_cast<DDS::KeyedStringDataWriter *>(writer);
      if (!typed)
          throw std::runtime_error("Writer type mismatch for KeyedString");

      KeyedStringPy &ks = obj.cast<KeyedStringPy&>();
      DDS_KeyedString data = ks.to_dds();

      DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);

        // 释放动态分配的内存
      KeyedStringPy::string_free(data.key);
      KeyedStringPy::string_free(data.value);

      return ret;
  }


  else if (str_equal(type_name, "DDS_KeyedBytes"))
  {
      auto typed = dynamic_cast<DDS::KeyedBytesDataWriter *>(writer);
      if (!typed)
          throw std::runtime_error("Writer type mismatch for KeyedBytes");

      // 从 Python 对象获取 KeyedBytesPy
      KeyedBytesPy &kb = obj.cast<KeyedBytesPy&>();

      // 转换成 DDS_KeyedBytes
      DDS_KeyedBytes data = kb.to_dds();

      // 写入
      DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);

      // 释放 key
      delete[] data.key;

      // 释放 value
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

// else if (type_name == "DDS_KeyedBytes")
// {
//   auto typed = dynamic_cast<DDS::KeyedBytesDataWriter *>(it);
//   DDS_KeyedBytes data = *py::cast<KeyedBytesPy>(obj).to_dds_data();
//   DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);
//   return ret;
// }
// else
// {
//   py::module_ pickle = py::module_::import("pickle");

//   // pickle.dumps(obj) 返回 bytes
//   py::object dumps = pickle.attr("dumps");
//   py::bytes serialized = dumps(obj);

//   auto typed = dynamic_cast<DDS::BytesDataWriter *>(it);
//   DDS_Bytes data;

//   std::string bytes_str = static_cast<std::string>(serialized);

//   DDS_Octet *buffer = reinterpret_cast<DDS_Octet *>(const_cast<char *>(bytes_str.data()));
//   int length = static_cast<int>(bytes_str.size());

//   DDS_OctetSeq_initialize(&data.value);
//   DDS_OctetSeq_loan_contiguous(&data.value, buffer, length, length);

//   DDS::ReturnCode_t ret = typed->write(data, DDS::HANDLE_NIL_NATIVE);
//   return ret;
// }

// inline bool DataWriterPy::str_equal(const std::string a, const std::string b)
// {
//   // if (a == nullptr || b == nullptr)
//   //   return false;
//   // return std::strcmp(a, b) == 0;
//   return a == b;
// }