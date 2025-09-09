#pragma once
#include <pybind11/pybind11.h>
#include "DomainParticipant.h"
#include "TopicPy.h"
#include "QosPy.h"
#include "SubscriberPy.h"
#include "PublisherPy.h"
#include "StatusKindMaskEnum.h"
#include <set>

namespace py = pybind11;

class DomainParticipantPy
{
public:
  DomainParticipantPy(DDS::DomainParticipant *intputDomainParticipant);

  ~DomainParticipantPy();

  DDS::DomainParticipant *raw() const;

  TopicPy *create_topic(const char *topic_name,
                        const char *type_name,
                        const TopicQosPy &qoslist,
                        // DDS::TopicListener *a_listener,
                        const StatusKindMaskEnum &mask);

  SubscriberPy *create_subscriber(const SubscriberQosPy &qoslist,
                                  // SubscriberListener *a_listener,
                                  const StatusKindMaskEnum &mask);
  PublisherPy *create_publisher(const PublisherQosPy &qoslist,
                                // PublisherListener *a_listener,
                                const StatusKindMaskEnum &mask);

  DDS::ReturnCode_t delete_contained_entities();

private:
  DDS::DomainParticipant *it;

  std::set<TopicPy *> Topics;

  std::set<SubscriberPy *> Subscribers;

  std::set<PublisherPy *> Publishers;
};

void init_DomainParticipant(py::module_ &m);