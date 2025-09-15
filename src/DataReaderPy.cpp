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
        //DDS_KeyedString
        // KeyedString
        else if (string_equal(type_name, "DDS_KeyedString"))
        {
            try
            {
                auto typed = dynamic_cast<DDS::KeyedStringDataReader *>(reader);
                if (!typed)
                    throw std::runtime_error("Reader type mismatch for DDS_KeyedString");

                DDS_KeyedString data;

                rtn = typed->take_next_sample(data, *sample_info.raw());

                if (rtn != DDS::RETCODE_OK)
                {
                    std::cout << "take_next_sample returned " << rtn << std::endl;
                    return std::make_tuple(py::none(), sample_info, rtn);
                }

                std::cout << "finish (KeyedString sample received)" << std::endl;


                // 构造 Python 封装对象 KeyedStringPy
                py::object py_ks = py::cast(KeyedStringPy(data));

                // 返回 (KeyedStringPy, sample_info, return_code)
                return std::make_tuple(py_ks, sample_info, rtn);
            }
            catch (const std::exception &e)
            {
                std::cerr << "[KeyedString Reader] Exception: " << e.what() << std::endl;
                return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR);
            }
        }

        // DDS_Bytes
        else if (string_equal(type_name, "DDS_Bytes"))
        {
            auto typed = dynamic_cast<DDS::BytesDataReader *>(reader);
            if (!typed)
                throw std::runtime_error("Reader type mismatch for DDS_Bytes");

            DDS_Bytes data;
            rtn = typed->take_next_sample(data, *sample_info.raw());

            // 提取 OctetSeq -> Python bytes
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
        //KeyedBytes
        else if (string_equal(type_name, "DDS_KeyedBytes"))
        {
            try
            {
                auto typed = dynamic_cast<DDS::KeyedBytesDataReader *>(reader);
                if (!typed)
                    throw std::runtime_error("Reader type mismatch for DDS_KeyedBytes");

                DDS_KeyedBytes data;

                rtn = typed->take_next_sample(data, *sample_info.raw());

                if (rtn != DDS::RETCODE_OK)
                {
                    // 没有数据，返回 None
                    std::cout << "take_next_sample returned " << rtn << std::endl;
                    return std::make_tuple(py::none(), sample_info, rtn);
                }

                std::cout << "finish (KeyedBytes sample received)" << std::endl;

                // 直接用构造函数封装
                KeyedBytesPy kb(data);

                // 返回 (KeyedBytesPy, sample_info, return_code)
                return std::make_tuple(py::cast(kb), sample_info, rtn);
            }
            catch (const std::exception &e)
            {
                std::cerr << "[KeyedBytes Reader] Exception: " << e.what() << std::endl;
                return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR);
            }
        }



        else
        {
            throw std::runtime_error(std::string("Unsupported type: ") + type_name);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in take_next_sample: " << e.what() << std::endl;
        return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR );
    }
}

std::tuple<py::object, SampleInfoPy, DDS::ReturnCode_t> DataReaderPy::read_next_sample()
{
    SampleInfoPy sample_info;
    DDS::ReturnCode_t rtn;

    DDS::TopicDescription *topic_description = reader->get_topicdescription();
    const char *type_name = topic_description->get_type_name();

    try
    {
        // DDS_Octet
        if (string_equal(type_name, "DDS_Octet"))
        {
            auto typed = dynamic_cast<DDS::OctetDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Octet");
            DDS::Octet value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_Boolean
        else if (string_equal(type_name, "DDS_Boolean"))
        {
            auto typed = dynamic_cast<DDS::BooleanDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Boolean");
            DDS::Boolean value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_Short
        else if (string_equal(type_name, "DDS_Short"))
        {
            auto typed = dynamic_cast<DDS::ShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Short");
            DDS::Short value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_UShort
        else if (string_equal(type_name, "DDS_UShort"))
        {
            auto typed = dynamic_cast<DDS::UShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_UShort");
            DDS::UShort value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_Long
        else if (string_equal(type_name, "DDS_Long"))
        {
            auto typed = dynamic_cast<DDS::LongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Long");
            DDS::Long value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_ULong
        else if (string_equal(type_name, "DDS_ULong"))
        {
            auto typed = dynamic_cast<DDS::ULongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULong");
            DDS::ULong value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_LongLong
        else if (string_equal(type_name, "DDS_LongLong"))
        {
            auto typed = dynamic_cast<DDS::LongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_LongLong");
            DDS::LongLong value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_ULongLong
        else if (string_equal(type_name, "DDS_ULongLong"))
        {
            auto typed = dynamic_cast<DDS::ULongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULongLong");
            DDS::ULongLong value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_Float
        else if (string_equal(type_name, "DDS_Float"))
        {
            auto typed = dynamic_cast<DDS::FloatDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Float");
            DDS::Float value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_Double
        else if (string_equal(type_name, "DDS_Double"))
        {
            auto typed = dynamic_cast<DDS::DoubleDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Double");
            DDS::Double value;
            rtn = typed->read_next_sample(value, *sample_info.raw());
            return std::make_tuple(py::cast(value), sample_info, rtn);
        }
        // DDS_String
        else if (string_equal(type_name, "DDS_String"))
        {
            auto typed = dynamic_cast<DDS::StringDataReader *>(reader);
            if (!typed)
                throw std::runtime_error("Reader type mismatch for DDS_String");

            DDS::String value = nullptr;
            rtn = typed->read_next_sample(value, *sample_info.raw());

            std::string py_str;
            if (value)
                py_str = std::string(value);
            else
                py_str = ""; // 空字符串安全处理

            return std::make_tuple(py::cast(py_str), sample_info, rtn);
        }
        //DDS_KeyedString
        // KeyedString
        else if (string_equal(type_name, "DDS_KeyedString"))
        {
            try
            {
                auto typed = dynamic_cast<DDS::KeyedStringDataReader *>(reader);
                if (!typed)
                    throw std::runtime_error("Reader type mismatch for DDS_KeyedString");

                DDS_KeyedString data;

                rtn = typed->read_next_sample(data, *sample_info.raw());

                if (rtn != DDS::RETCODE_OK)
                {
                    std::cout << "take_next_sample returned " << rtn << std::endl;
                    return std::make_tuple(py::none(), sample_info, rtn);
                }

                std::cout << "finish (KeyedString sample received)" << std::endl;


                // 构造 Python 封装对象 KeyedStringPy
                py::object py_ks = py::cast(KeyedStringPy(data));

                // 返回 (KeyedStringPy, sample_info, return_code)
                return std::make_tuple(py_ks, sample_info, rtn);
            }
            catch (const std::exception &e)
            {
                std::cerr << "[KeyedString Reader] Exception: " << e.what() << std::endl;
                return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR);
            }
        }

        // DDS_Bytes
        else if (string_equal(type_name, "DDS_Bytes"))
        {
            auto typed = dynamic_cast<DDS::BytesDataReader *>(reader);
            if (!typed)
                throw std::runtime_error("Reader type mismatch for DDS_Bytes");

            DDS_Bytes data;
            rtn = typed->read_next_sample(data, *sample_info.raw());

            // 提取 OctetSeq -> Python bytes
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
        //KeyedBytes
        else if (string_equal(type_name, "DDS_KeyedBytes"))
        {
            try
            {
                auto typed = dynamic_cast<DDS::KeyedBytesDataReader *>(reader);
                if (!typed)
                    throw std::runtime_error("Reader type mismatch for DDS_KeyedBytes");

                DDS_KeyedBytes data;

                rtn = typed->read_next_sample(data, *sample_info.raw());

                if (rtn != DDS::RETCODE_OK)
                {
                    // 没有数据，返回 None
                    std::cout << "take_next_sample returned " << rtn << std::endl;
                    return std::make_tuple(py::none(), sample_info, rtn);
                }

                std::cout << "finish (KeyedBytes sample received)" << std::endl;

                // 直接用构造函数封装
                KeyedBytesPy kb(data);

                // 返回 (KeyedBytesPy, sample_info, return_code)
                return std::make_tuple(py::cast(kb), sample_info, rtn);
            }
            catch (const std::exception &e)
            {
                std::cerr << "[KeyedBytes Reader] Exception: " << e.what() << std::endl;
                return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR);
            }
        }



        else
        {
            throw std::runtime_error(std::string("Unsupported type: ") + type_name);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in take_next_sample: " << e.what() << std::endl;
        return std::make_tuple(py::none(), sample_info, DDS::ReturnCode_t::DDS_RETCODE_ERROR );
    }
}

std::tuple<py::list, py::list, DDS::ReturnCode_t> DataReaderPy::take(
    int max_samples,
    SampleStateMaskEnum sample_mask_enum,
    ViewStateMaskEnum view_mask_enum,
    InstanceStateMaskEnum instance_mask_enum)
{
    py::list py_values;
    py::list py_infos;
    DDS::ReturnCode_t rtn;

    DDS::SampleStateMask s_mask = getMask(sample_mask_enum);
    DDS::ViewStateMask v_mask = getMask(view_mask_enum);
    DDS::InstanceStateMask i_mask = getMask(instance_mask_enum);

    DDS::TopicDescription* topic_desc = reader->get_topicdescription();
    const char* type_name = topic_desc->get_type_name();

    try
    {
        if (string_equal(type_name, "DDS_Octet"))
        {
            auto typed = dynamic_cast<DDS::OctetDataReader*>(reader);
            if (!typed)
                throw std::runtime_error("Reader type mismatch for DDS_Octet");

            DDS::OctetSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            // 初始化序列
            DDS_OctetSeq_initialize(&data_seq);
            DDS_SampleInfoSeq_initialize(&info_seq);

            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );

                //遍历序列，转成 Python list
            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];

                // 跳过无效数据
                if (!info.valid_data)
                    continue;

                // 提取数据
                DDS::Octet value = data_seq[i];
                py_values.append(value);

                // 封装 SampleInfo
                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            // 返还 loan
            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }


            // 清理
            DDS_OctetSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Boolean
        else if (string_equal(type_name, "DDS_Boolean"))
        {
            auto typed = dynamic_cast<DDS::BooleanDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Boolean");

            DDS::BooleanSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Boolean value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_BooleanSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);

        }
        // DDS_Short
        else if (string_equal(type_name, "DDS_Short"))
        {
            auto typed = dynamic_cast<DDS::ShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Short");
            DDS::ShortSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Short value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ShortSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_UShort
        else if (string_equal(type_name, "DDS_UShort"))
        {
            auto typed = dynamic_cast<DDS::UShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_UShort");
            DDS::UShortSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::UShort value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_UShortSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Long
        else if (string_equal(type_name, "DDS_Long"))
        {
            auto typed = dynamic_cast<DDS::LongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Long");
            DDS::LongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Long value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_LongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_ULong
        else if (string_equal(type_name, "DDS_ULong"))
        {
            auto typed = dynamic_cast<DDS::ULongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULong");
            DDS::ULongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::ULong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ULongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_LongLong
        else if (string_equal(type_name, "DDS_LongLong"))
        {
            auto typed = dynamic_cast<DDS::LongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_LongLong");
            DDS::LongLongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::LongLong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_LongLongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_ULongLong
        else if (string_equal(type_name, "DDS_ULongLong"))
        {
            auto typed = dynamic_cast<DDS::ULongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULongLong");
            DDS::ULongLongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::ULongLong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ULongLongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
    
        }
        
        // DDS_Float
        else if (string_equal(type_name, "DDS_Float"))
        {
            auto typed = dynamic_cast<DDS::FloatDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Float");
            DDS::FloatSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Float value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_FloatSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_Double
        else if (string_equal(type_name, "DDS_Double"))
        {
            auto typed = dynamic_cast<DDS::DoubleDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Double");
            DDS::DoubleSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Double value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_DoubleSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_String
        else if (string_equal(type_name, "DDS_String"))
        {
            auto typed = dynamic_cast<DDS::StringDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_String");

            DDS::StringSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );

            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];
                if (!info.valid_data)
                    continue;

                // StringSeq 元素是 const char*
                const char* value = data_seq[i];
                py_values.append(py::str(value ? value : ""));

                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }

            DDS_StringSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Bytes
        else if (string_equal(type_name, "DDS_Bytes"))
        {
            auto typed = dynamic_cast<DDS::BytesDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Bytes");

            DDS::BytesSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            rtn = typed->take(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
            if (rtn != DDS_RETCODE_OK && rtn != DDS_RETCODE_NO_DATA)
            return std::make_tuple(py::list(), py::list(), rtn);

            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];
                if (!info.valid_data)
                    continue;

                // 提取 Bytes 里的 OctetSeq
                const DDS::Bytes &bytes_struct = data_seq[i];
                const DDS::OctetSeq &octets = bytes_struct.value;

                py::bytes py_data;
                if(DDS_OctetSeq_get_length(&octets) > 0)
                {
                    int length = DDS_OctetSeq_get_length(&octets);
                    DDS_Octet* buffer = DDS_OctetSeq_get_contiguous_buffer(&octets);
                    py_data = py::bytes(reinterpret_cast<const char*>(buffer), length);
                }
                else
                {
                    py_data = py::bytes("");
                }

                py_values.append(py_data);

                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }

            DDS_BytesSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }



        else
        {
            throw std::runtime_error(std::string("Unsupported type in take(): ") + type_name);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in take(): " << e.what() << std::endl;
        return std::make_tuple(py::list(), py::list(), DDS::RETCODE_ERROR);
    }
}

std::tuple<py::list, py::list, DDS::ReturnCode_t> DataReaderPy::read(
    int max_samples,
    SampleStateMaskEnum sample_mask_enum,
    ViewStateMaskEnum view_mask_enum,
    InstanceStateMaskEnum instance_mask_enum)
{
    py::list py_values;
    py::list py_infos;
    DDS::ReturnCode_t rtn;

    DDS::SampleStateMask s_mask = getMask(sample_mask_enum);
    DDS::ViewStateMask v_mask = getMask(view_mask_enum);
    DDS::InstanceStateMask i_mask = getMask(instance_mask_enum);

    DDS::TopicDescription* topic_desc = reader->get_topicdescription();
    const char* type_name = topic_desc->get_type_name();

    try
    {
        if (string_equal(type_name, "DDS_Octet"))
        {
            auto typed = dynamic_cast<DDS::OctetDataReader*>(reader);
            if (!typed)
                throw std::runtime_error("Reader type mismatch for DDS_Octet");

            DDS::OctetSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            // 初始化序列
            DDS_OctetSeq_initialize(&data_seq);
            DDS_SampleInfoSeq_initialize(&info_seq);

            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );

                //遍历序列，转成 Python list
            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];

                // 跳过无效数据
                if (!info.valid_data)
                    continue;

                // 提取数据
                DDS::Octet value = data_seq[i];
                py_values.append(value);

                // 封装 SampleInfo
                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            // 返还 loan
            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }


            // 清理
            DDS_OctetSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Boolean
        else if (string_equal(type_name, "DDS_Boolean"))
        {
            auto typed = dynamic_cast<DDS::BooleanDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Boolean");

            DDS::BooleanSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Boolean value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_BooleanSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);

        }
        // DDS_Short
        else if (string_equal(type_name, "DDS_Short"))
        {
            auto typed = dynamic_cast<DDS::ShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Short");
            DDS::ShortSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Short value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ShortSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_UShort
        else if (string_equal(type_name, "DDS_UShort"))
        {
            auto typed = dynamic_cast<DDS::UShortDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_UShort");
            DDS::UShortSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::UShort value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_UShortSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Long
        else if (string_equal(type_name, "DDS_Long"))
        {
            auto typed = dynamic_cast<DDS::LongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Long");
            DDS::LongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Long value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_LongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_ULong
        else if (string_equal(type_name, "DDS_ULong"))
        {
            auto typed = dynamic_cast<DDS::ULongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULong");
            DDS::ULongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::ULong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ULongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_LongLong
        else if (string_equal(type_name, "DDS_LongLong"))
        {
            auto typed = dynamic_cast<DDS::LongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_LongLong");
            DDS::LongLongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::LongLong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_LongLongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_ULongLong
        else if (string_equal(type_name, "DDS_ULongLong"))
        {
            auto typed = dynamic_cast<DDS::ULongLongDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_ULongLong");
            DDS::ULongLongSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::ULongLong value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_ULongLongSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
    
        }
        
        // DDS_Float
        else if (string_equal(type_name, "DDS_Float"))
        {
            auto typed = dynamic_cast<DDS::FloatDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Float");
            DDS::FloatSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Float value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_FloatSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }

        // DDS_Double
        else if (string_equal(type_name, "DDS_Double"))
        {
            auto typed = dynamic_cast<DDS::DoubleDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Double");
            DDS::DoubleSeq data_seq;
            DDS::SampleInfoSeq info_seq;
            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
             //遍历序列，转成 Python list
             for (int i = 0; i < data_seq.length(); ++i)
             {
                 DDS::SampleInfo &info = info_seq[i];
 
                 // 跳过无效数据
                 if (!info.valid_data)
                     continue;
 
                 // 提取数据
                 DDS::Double value = data_seq[i];
                 py_values.append(value);
 
                 // 封装 SampleInfo
                 SampleInfoPy py_info;
                 *py_info.raw() = info;
                 py_infos.append(py_info);
             }
 
             // 返还 loan
             rtn = typed->return_loan(data_seq, info_seq);
             if (rtn != DDS::RETCODE_OK)
             {
                 std::cerr << "return_loan failed with code " << rtn << std::endl;
             }
 
 
             // 清理
             DDS_DoubleSeq_finalize(&data_seq);
             DDS_SampleInfoSeq_finalize(&info_seq);
 
             return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_String
        else if (string_equal(type_name, "DDS_String"))
        {
            auto typed = dynamic_cast<DDS::StringDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_String");

            DDS::StringSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );

            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];
                if (!info.valid_data)
                    continue;

                // StringSeq 元素是 const char*
                const char* value = data_seq[i];
                py_values.append(py::str(value ? value : ""));

                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }

            DDS_StringSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }
        // DDS_Bytes
        else if (string_equal(type_name, "DDS_Bytes"))
        {
            auto typed = dynamic_cast<DDS::BytesDataReader *>(reader);
            if (!typed) throw std::runtime_error("Reader type mismatch for DDS_Bytes");

            DDS::BytesSeq data_seq;
            DDS::SampleInfoSeq info_seq;

            rtn = typed->read(
                data_seq,
                info_seq,
                max_samples,
                s_mask,
                v_mask,
                i_mask
            );
            if (rtn != DDS_RETCODE_OK && rtn != DDS_RETCODE_NO_DATA)
            return std::make_tuple(py::list(), py::list(), rtn);

            for (int i = 0; i < data_seq.length(); ++i)
            {
                DDS::SampleInfo &info = info_seq[i];
                if (!info.valid_data)
                    continue;

                // 提取 Bytes 里的 OctetSeq
                const DDS::Bytes &bytes_struct = data_seq[i];
                const DDS::OctetSeq &octets = bytes_struct.value;

                py::bytes py_data;
                if(DDS_OctetSeq_get_length(&octets) > 0)
                {
                    int length = DDS_OctetSeq_get_length(&octets);
                    DDS_Octet* buffer = DDS_OctetSeq_get_contiguous_buffer(&octets);
                    py_data = py::bytes(reinterpret_cast<const char*>(buffer), length);
                }
                else
                {
                    py_data = py::bytes("");
                }

                py_values.append(py_data);

                SampleInfoPy py_info;
                *py_info.raw() = info;
                py_infos.append(py_info);
            }

            rtn = typed->return_loan(data_seq, info_seq);
            if (rtn != DDS::RETCODE_OK)
            {
                std::cerr << "return_loan failed with code " << rtn << std::endl;
            }

            DDS_BytesSeq_finalize(&data_seq);
            DDS_SampleInfoSeq_finalize(&info_seq);

            return std::make_tuple(py_values, py_infos, rtn);
        }



        else
        {
            throw std::runtime_error(std::string("Unsupported type in take(): ") + type_name);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in take(): " << e.what() << std::endl;
        return std::make_tuple(py::list(), py::list(), DDS::RETCODE_ERROR);
    }
}

DDS::DataReader *DRPy::raw() const { return reader; }


void init_DataReader(py::module_ &m)
{
  py::class_<DRPy>(m, "DataReader")
      .def(py::init<DDS::DataReader *>(), py::arg("data_reader"))
      .def("take_next_sample", &DRPy::take_next_sample, "take the next sample from the topic")
      .def("read_next_sample", &DRPy::read_next_sample, "read the next sample from the topic")
      .def("take", &DRPy::take, py::arg("max_samples"),
            py::arg("sample_mask") = SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM,
            py::arg("view_mask")   = ViewStateMaskEnum::ANY_VIEW_STATE_ENUM,
            py::arg("instance_mask") = InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM,
            "Take samples from the topic")
      .def("read", &DRPy::read, py::arg("max_samples"),
            py::arg("sample_mask") = SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM,
            py::arg("view_mask")   = ViewStateMaskEnum::ANY_VIEW_STATE_ENUM,
            py::arg("instance_mask") = InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM,
            "Read samples from the topic");

  // .def("read", &DRPy::read, py::arg("data_values"), py::arg("sample_infos"), py::arg("max_samples"),
  //      py::arg("sample_mask") = py::cast(SampleStateMaskEnum::ANY_SAMPLE_STATE_ENUM),
  //      py::arg("view_mask") = py::cast(ViewStateMaskEnum::ANY_VIEW_STATE_ENUM),
  //      py::arg("instance_mask") = py::cast(InstanceStateMaskEnum::ANY_INSTANCE_STATE_ENUM),
  //      "Read data from the topic")
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