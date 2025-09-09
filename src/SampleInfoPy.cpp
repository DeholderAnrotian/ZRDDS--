#include "Aliases.h"
#include "SampleInfoPy.h"

SIPy::SampleInfoPy()
{
  it = new DDS::SampleInfo();
}

SIPy::SampleInfoPy(DDS::SampleInfo *intputSampleInfo)
    : it(intputSampleInfo) {}

SIPy::SampleInfoPy(const SampleInfoPy &other) noexcept
{
  it = new DDS::SampleInfo(*other.it);
}
SIPy::~SampleInfoPy()
{
  delete it;
}

DDS::SampleInfo *SIPy::raw() const { return it; }

DDS_Boolean SIPy::valid_data() { return it->valid_data; }

void init_SampleInfo(py::module_ &m)
{
  py::class_<SIPy>(m, "SampleInfo")
      .def(py::init<>())
      .def(py::init<DDS::SampleInfo *>(), py::arg("sample_info"))
      .def(py::init<const SIPy &>(), py::arg("other"))
      .def("valid_data", &SIPy::valid_data, "Check if the data is valid");
}