#pragma once
#include <pybind11/pybind11.h>
#include <ZRDDSCppWrapper.h>
#include <Publisher.h>
#include "ReturnCode_t.h"
#include "DataWriterPy.h"
#include "StatusKindMaskEnum.h"
#include "QosPy.h"
#include <set>

namespace py = pybind11;

class PublisherPy
{
public:
  PublisherPy(DDS::Publisher *inputPublisher);
  ~PublisherPy();

  // 返回底层原生指针
  DDS::Publisher *raw() const;

  // 封装常用方法
  DataWriterPy *create_datawriter(TopicPy *the_topic,
                                  const DataWriterQosPy &qoslist,
                                  DDS::DataWriterListener* a_listener,
                                  const StatusKindMaskEnum &mask);

  DDS::ReturnCode_t delete_datawriter(DataWriterPy *writer);

private:
  DDS::Publisher *it;
  std ::set<DataWriterPy *> DataWriters; // 用于跟踪创建的 DataWriterPy 实例
};

// pybind11 绑定函数
void init_Publisher(py::module_ &m);
