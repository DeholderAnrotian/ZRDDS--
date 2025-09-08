#pragma once
#include "ZRBuiltinTypes.h"
#include "ZRSequence.h"
#include "SampleInfo.h"
#include "SeqWrapperMacro.h"

// DECLARE_SEQ_WRAPPER(BooleanSeq, DDS_BooleanSeq, DDS_Boolean)
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
