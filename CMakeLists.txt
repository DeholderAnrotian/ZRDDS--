cmake_minimum_required(VERSION 3.15)
project(zrdds_python_bindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(ZRDDS_INCLUDE_DIR "$ENV{ZRDDS_HOME}/include")
set(ZRDDS_LIB_DIR "$ENV{ZRDDS_HOME}/lib")

set(pybind11_DIR ".venv/Lib/site-packages/pybind11/share/cmake/pybind11") 
add_definitions(-DPYBIND11_DETAILED_ERROR_MESSAGES -D_ZRDDSCPPINTERFACE)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp"
    "src/*/*.cpp"
)

pybind11_add_module(
    zrdds_python                  
    MODULE                 
    ${SOURCE_FILES}        # 所有源文件
)

target_link_libraries(zrdds_python PRIVATE ${ZRDDS_LIB_DIR}/ZRDDSCppz_VS2019.lib) 
target_include_directories(zrdds_python PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(zrdds_python PRIVATE ${CMAKE_SOURCE_DIR}/src/QosPy)
target_include_directories(zrdds_python PRIVATE ${CMAKE_SOURCE_DIR}/src/SeqPy)
target_include_directories(zrdds_python PRIVATE ${CMAKE_SOURCE_DIR}/src/ListenerPy)
target_include_directories(zrdds_python PRIVATE ${CMAKE_SOURCE_DIR}/src/Enum)

target_include_directories(zrdds_python PRIVATE ${ZRDDS_INCLUDE_DIR}/CPlusPlusInterface)
target_include_directories(zrdds_python PRIVATE ${ZRDDS_INCLUDE_DIR}/ZRDDSSecurityInterface)
target_include_directories(zrdds_python PRIVATE ${ZRDDS_INCLUDE_DIR}/ZRDDSCoreInterface)

# add_custom_command(TARGET zrdds_python POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E echo "Copying zrdds_python .pyd to target folder..."
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:zrdds_python> ${PROJECT_SOURCE_DIR}/zrpy/
#     COMMENT "Copy zrdds_python .pyd to source folder"
# )