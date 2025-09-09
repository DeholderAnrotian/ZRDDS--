#include "SeqPy.h"

void init_Seq(pybind11::module_ &m)
{
  init_BooleanSeq(m);
  init_OctetSeq(m);
  init_ShortSeq(m);
  init_UShortSeq(m);
  init_LongSeq(m);
  init_ULongSeq(m);
  init_LongLongSeq(m);
  init_ULongLongSeq(m);
  init_FloatSeq(m);
  init_DoubleSeq(m);
  init_StringSeq(m);
  init_KeyedStringSeq(m);
  init_BytesSeq(m);
  init_KeyedBytesSeq(m);
  init_ZeroCopyBytesSeq(m);
  init_SampleInfoSeq(m);
}