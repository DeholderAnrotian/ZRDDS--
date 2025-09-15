#include "Aliases.h"
#include "DataReaderPy.h"
#include <iostream>

DRPy::DataReaderPy(DDS::DataReader *inputDataReader)
    : it(inputDataReader)
{
  type_name = it->get_topicdescription()->get_type_name();
}

DRPy::~DataReaderPy() {}

// inline bool DataReaderPy::string_equal(const char *a, const char *b)
// {
//   if (a == nullptr || b == nullptr)
//     return false;
//   return std::strcmp(a, b) == 0;
// }

std::tuple<py::object, SampleInfoPy, DDS::ReturnCode_t> DataReaderPy::take_next_sample()
{
  SampleInfoPy sample_info;
  DDS::ReturnCode_t rtn;
  try
  {
    if (type_name == "DDS_Octet")
    {
      auto typed = dynamic_cast<DDS::OctetDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Octet");
      DDS::Octet value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_Boolean")
    {
      auto typed = dynamic_cast<DDS::BooleanDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Boolean");
      DDS::Boolean value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_Short")
    {
      auto typed = dynamic_cast<DDS::ShortDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Short");
      DDS::Short value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_UShort")
    {
      auto typed = dynamic_cast<DDS::UShortDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_UShort");
      DDS::UShort value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_Long")
    {
      auto typed = dynamic_cast<DDS::LongDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Long");
      DDS::Long value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_ULong")
    {
      auto typed = dynamic_cast<DDS::ULongDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_ULong");
      DDS::ULong value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_LongLong")
    {
      auto typed = dynamic_cast<DDS::LongLongDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_LongLong");
      DDS::LongLong value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_ULongLong")
    {
      auto typed = dynamic_cast<DDS::ULongLongDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_ULongLong");
      DDS::ULongLong value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_Float")
    {
      auto typed = dynamic_cast<DDS::FloatDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Float");
      DDS::Float value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_Double")
    {
      auto typed = dynamic_cast<DDS::DoubleDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Double");
      DDS::Double value;
      rtn = typed->take_next_sample(value, *sample_info.raw());
      return std::make_tuple(py::cast(value), sample_info, rtn);
    }
    else if (type_name == "DDS_String")
    {
      auto typed = dynamic_cast<DDS::StringDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_String");

      DDS::String value = nullptr;
      rtn = typed->take_next_sample(value, *sample_info.raw());

      std::string py_str;
      if (value)
        py_str = std::string(value);
      else
        py_str = ""; // 空字符串安全处理

      return std::make_tuple(py::cast(py_str), sample_info, rtn);
    }
    else if (type_name == "DDS_Bytes")
    {
      auto typed = dynamic_cast<DDS::BytesDataReader *>(it);
      if (!typed)
        throw std::runtime_error("Reader type mismatch for DDS_Bytes");
      DDS_Bytes data;
      rtn = typed->take_next_sample(data, *sample_info.raw());
      py::bytes py_data;

      if (DDS_OctetSeq_get_length(&data.value) > 0)
      {
        int length = DDS_OctetSeq_get_length(&data.value);
        DDS_Octet *buffer = DDS_OctetSeq_get_contiguous_buffer(&data.value);
        py_data = py::bytes(reinterpret_cast<const char *>(buffer), length);
      }
      else
      {
        py_data = py::bytes("");
      }

      return std::make_tuple(py_data, sample_info, rtn);
    }
    else
    {
      return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_UNSUPPORTED);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception in take_next_sample: " << e.what() << std::endl;
    return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR);
  }
}

DDS::DataReader *DRPy::raw() const { return it; }

// DDS::ReturnCode_t DRPy::read(StringSeqPy &data_values,
//                              SampleInfoSeqPy &sample_infos,
//                              int max_samples,
//                              SampleStateMaskEnum sample_mask,
//                              ViewStateMaskEnum view_mask,
//                              InstanceStateMaskEnum instance_mask)
// {
//   return static_cast<DDS::ZRDDSDataReader<DDS_String, DDS_StringSeq> *>(it)->read(*data_values.raw(), *sample_infos.raw(), max_samples,
//                                                                                   getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
// }

// DDS::ReturnCode_t DRPy::take(StringSeqPy &data_values,
//                              SampleInfoSeqPy &sample_infos,
//                              int max_samples,
//                              SampleStateMaskEnum sample_mask,
//                              ViewStateMaskEnum view_mask,
//                              InstanceStateMaskEnum instance_mask)
// {
//   return static_cast<DDS::ZRDDSDataReader<DDS_String, DDS_StringSeq> *>(it)->take(*data_values.raw(), *sample_infos.raw(), max_samples,
//                                                                                   getMask(sample_mask), getMask(view_mask), getMask(instance_mask));
// }

void init_DataReader(py::module_ &m)
{
  py::class_<DRPy>(m, "DataReader")
      .def(py::init<DDS::DataReader *>(), py::arg("data_reader"))
      .def("take_next_sample", &DRPy::take_next_sample, "take the next sample from the topic");
  // .def("read", &DRPy::read, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
  //      py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
  //      py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
  //      py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
  //      "Read data from the topic")
  // .def("take", &DRPy::take, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
  //      py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
  //      py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
  //      py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
  //      "Take data from the topic");
}

// else
// {
//   auto typed = dynamic_cast<DDS::BytesDataReader *>(it);
//   if (!typed)
//     throw std::runtime_error("Reader type mismatch for DDS_Bytes");
//   DDS_Bytes data;
//   rtn = typed->take_next_sample(data, *sample_info.raw());
//   py::bytes py_data;

//   if (DDS_OctetSeq_get_length(&data.value) > 0)
//   {
//     int length = DDS_OctetSeq_get_length(&data.value);
//     DDS_Octet *buffer = DDS_OctetSeq_get_contiguous_buffer(&data.value);
//     py_data = py::bytes(reinterpret_cast<const char *>(buffer), length);
//   }
//   else
//   {
//     py_data = py::bytes("");
//   }
//   py::module_ pickle = py::module_::import("pickle");

//   // pickle.loads(serialized)
//   py::object obj = pickle.attr("loads")(py_data);
//   return std::make_tuple(obj, sample_info, rtn);
// }
// else if (type_name == "DDS_KeyedBytes")
// {
//   auto typed = dynamic_cast<DDS::KeyedBytesDataReader *>(it);
//   if (!typed)
//     throw std::runtime_error("Reader type mismatch for DDS_Bytes");
//   DDS_KeyedBytes data;
//   rtn = typed->take_next_sample(data, *sample_info.raw());

//   return std::make_tuple(py::cast(KeyedBytesPy(data)), sample_info, rtn);
// }
// else
// {
//   throw std::runtime_error(std::string("Unsupported type: ") + type_name);
// }