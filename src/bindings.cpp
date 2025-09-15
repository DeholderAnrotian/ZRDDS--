#include <pybind11/pybind11.h>
#include "StatusKindMaskEnum.h"
#include "ViewStateMaskEnum.h"
#include "SampleStateMaskEnum.h"
#include "InstanceStateMaskEnum.h"

#include "DomainParticipantFactoryPy.h"
#include "DomainParticipantPy.h"
#include "TopicDescriptionPy.h"
#include "TopicPy.h"

#include "SubscriberPy.h"
#include "PublisherPy.h"
#include "DataReaderPy.h"
#include "DataWriterPy.h"

#include "SampleInfoPy.h"
#include "QosPy.h"

#include "DataReaderListenerPy.h"
#include "DataWriterListenerPy.h"
#include "DomainParticipantListenerPy.h"
#include "SubscriberListenerPy.h"
#include "PublisherListenerPy.h"
#include "TopicListenerPy.h"

namespace py = pybind11;

void init_ReturnCode_t(py::module_ &);

PYBIND11_MODULE(zrdds_python, m)
{
  py::class_<DDS::DataReader, std::unique_ptr<DDS::DataReader, py::nodelete>>(m, "DDS_DataReader");
  py::class_<DDS::DataWriter, std::unique_ptr<DDS::DataWriter, py::nodelete>>(m, "DDS_DataWriter");
  py::class_<DDS::Subscriber, std::unique_ptr<DDS::Subscriber, py::nodelete>>(m, "DDS_Subscriber");
  py::class_<DDS::Publisher, std::unique_ptr<DDS::Publisher, py::nodelete>>(m, "DDS_Publisher");
  py::class_<DDS::Topic, std::unique_ptr<DDS::Topic, py::nodelete>>(m, "DDS_Topic");
  py::class_<DDS::DomainParticipant, std::unique_ptr<DDS::DomainParticipant, py::nodelete>>(m, "DDS_DomainParticipant");
  init_StatusKindMaskEnum(m);
  init_ViewStateMaskEnum(m);
  init_SampleStateMaskEnum(m);
  init_InstanceStateMaskEnum(m);
  init_ReturnCode_t(m);

  init_DomainParticipantFactory(m);
  init_DomainParticipant(m);
  init_TopicDescription(m);
  init_Topic(m);

  init_DataReaderListener(m);
  init_DataWriterListener(m);
  init_SubscriberListener(m);
  init_PublisherListener(m);
  init_TopicListener(m);
  init_DomainParticipantListener(m);

  init_DataReader(m);
  init_DataWriter(m);
  init_Subscriber(m);
  init_Publisher(m);

  init_SampleInfo(m);

  init_Qos(m);
}
