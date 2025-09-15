#include <pybind11/pybind11.h>
#include "StatusKindMaskEnum.h"
#include "ViewStateMaskEnum.h"
#include "SampleStateMaskEnum.h"
#include "InstanceStateMaskEnum.h"
#include "DomainParticipantFactoryPy.h"
#include "DomainParticipantPy.h"
#include "TopicPy.h"
#include "TopicDescriptionPy.h"
#include "SubscriberPy.h"
#include "PublisherPy.h"
#include "DataReaderPy.h"
#include "DataWriterPy.h"
#include "SampleInfoPy.h"
#include "KeyedBytesPy.h"
#include "KeyedStringPy.h"
#include "SeqPy.h"
#include "QosPy.h"

namespace py = pybind11;

void init_ReturnCode_t(py::module_ &);

PYBIND11_MODULE(zrdds_python, m)
{
  init_StatusKindMaskEnum(m);
  init_ViewStateMaskEnum(m);
  init_SampleStateMaskEnum(m);
  init_InstanceStateMaskEnum(m);
  init_ReturnCode_t(m);

  init_DomainParticipantFactory(m);
  init_DomainParticipant(m);

  init_TopicDescription(m);
  init_Topic(m);

  init_DataReader(m);
  init_DataWriter(m);
  init_Subscriber(m);
  init_Publisher(m);
  init_SampleInfo(m);

  init_Seq(m);
  init_Qos(m);
  init_KeyedBytes(m);
  init_KeyedString(m);
}
