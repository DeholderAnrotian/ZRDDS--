// #include <pybind11/pybind11.h>

// // 示例函数
// int add(int a, int b)
// {
//   return a + b + 1;
// }

// // Python 模块入口
// PYBIND11_MODULE(zrdds_python, m)
// {
//   m.doc() = "Minimal ZRDDS Python binding example";
//   m.def("add", &add, "A function that adds two numbers");
// }
#include <pybind11/pybind11.h>
#include <ZRDDSCppSimpleInterface.h>
namespace py = pybind11;

py::capsule get_participant_factory()
{

  DDS::DomainParticipantFactory *factory = DDS::DomainParticipantFactory::get_instance();
  if (!factory)
  {
    throw std::runtime_error("Failed to get DomainParticipantFactory instance");
  }
  return py::capsule(factory, [](void *p) {});
}

PYBIND11_MODULE(zrdds_python, m)
{
  m.doc() = "Minimal ZRDDS Python binding example";
  m.def("get_participant_factory", &get_participant_factory, "A function that adds two numbers");
}