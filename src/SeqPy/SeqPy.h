#pragma once
#include "ZRBuiltinTypes.h"
#include "ZRSequence.h"
#include "SampleInfo.h"
#include "SeqWrapperMacro.h"
class BooleanSeqPy
{
public:
  BooleanSeqPy()
  {
    DDS_BooleanSeq_initialize(it);
  }
  explicit BooleanSeqPy(DDS_BooleanSeq *input) : it(input){}
  ~BooleanSeqPy(){}
  DDS_BooleanSeq *raw() const { return it; }
  std::vector<DDS_Boolean> to_list() const
  {
    auto n = DDS_BooleanSeq_get_length(it);
    DDS_Boolean *temp = new DDS_Boolean[n];
    std::vector<DDS_Boolean> result;
    result.resize(n);
    DDS_BooleanSeq_to_array(it, temp, n);
    for (int i = 0; i < n; i++)
    {
      result[i] = temp[i];
    }
    delete[] temp;
    return result;
  }

private:
  DDS_BooleanSeq *it{nullptr};
};
inline void init_BooleanSeq(py::module_ &m)
{
  py::class_<BooleanSeqPy>(m, "BooleanSeq")
      .def(py::init<>())
      .def("to_list", &BooleanSeqPy::to_list,
           "Convert to a Python list");
};
DECLARE_SEQ_WRAPPER(OctetSeq, DDS_OctetSeq, DDS_Octet)
DECLARE_SEQ_WRAPPER(ShortSeq, DDS_ShortSeq, DDS_Short)
DECLARE_SEQ_WRAPPER(UShortSeq, DDS_UShortSeq, DDS_UShort)
DECLARE_SEQ_WRAPPER(LongSeq, DDS_LongSeq, DDS_Long)
DECLARE_SEQ_WRAPPER(ULongSeq, DDS_ULongSeq, DDS_ULong)
DECLARE_SEQ_WRAPPER(LongLongSeq, DDS_LongLongSeq, DDS_LongLong)
DECLARE_SEQ_WRAPPER(ULongLongSeq, DDS_ULongLongSeq, DDS_ULongLong)
DECLARE_SEQ_WRAPPER(FloatSeq, DDS_FloatSeq, DDS_Float)
DECLARE_SEQ_WRAPPER(DoubleSeq, DDS_DoubleSeq, DDS_Double)
DECLARE_SEQ_WRAPPER(StringSeq, DDS_StringSeq, DDS_String)
DECLARE_SEQ_WRAPPER(KeyedStringSeq, DDS_KeyedStringSeq, DDS_KeyedString)
DECLARE_SEQ_WRAPPER(BytesSeq, DDS_BytesSeq, DDS_Bytes)
DECLARE_SEQ_WRAPPER(KeyedBytesSeq, DDS_KeyedBytesSeq, DDS_KeyedBytes)
DECLARE_SEQ_WRAPPER(ZeroCopyBytesSeq, DDS_ZeroCopyBytesSeq, DDS_ZeroCopyBytes)
DECLARE_SEQ_WRAPPER(SampleInfoSeq, DDS_SampleInfoSeq, DDS_SampleInfo)

void init_Seq(pybind11::module_ &m);
