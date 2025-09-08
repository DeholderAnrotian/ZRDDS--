#pragma once
#include "DefaultQos.h"
#include "QosWrapperMacro.h"

DECLARE_QOS_WRAPPER(TopicQos, DDS_TopicQos, DDS_TOPIC_QOS_DEFAULT)
DECLARE_QOS_WRAPPER(PublisherQos, DDS_PublisherQos, DDS_PUBLISHER_QOS_DEFAULT)
DECLARE_QOS_WRAPPER(SubscriberQos, DDS_SubscriberQos, DDS_SUBSCRIBER_QOS_DEFAULT)
DECLARE_QOS_WRAPPER(DataWriterQos, DDS_DataWriterQos, DDS_DATAWRITER_QOS_DEFAULT)
DECLARE_QOS_WRAPPER(DataReaderQos, DDS_DataReaderQos, DDS_DATAREADER_QOS_DEFAULT)
DECLARE_QOS_WRAPPER(DomainParticipantQos, DDS_DomainParticipantQos, DDS_DOMAINPARTICIPANT_QOS_DEFAULT)

void init_Qos(py::module_ &m);
