#include <pybind11/pybind11.h>
#include "DomainParticipantFactoryPy.h"
#include "DomainParticipantPy.h"
#include "QosEnum.h"
#include "StatusKindMaskEnum.h"
// #include "DomainParticipantQosPy.h"
// #include "DomainParticipantListenerPy.h"
namespace py = pybind11;

void init_ReturnCode_t(py::module_ &);

PYBIND11_MODULE(zrdds_python, m)
{
  init_QosEnum(m);
  init_StatusKindMaskEnum(m);
  init_DomainParticipantFactory(m);
  init_DomainParticipant(m);
  init_ReturnCode_t(m);
  // init_DomainParticipantQos(m);
  // init_DomainParticipantListener(m);
}
