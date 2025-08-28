# from setuptools import setup

# setup()
# from setuptools import setup, Extension
# import pybind11

# ext_modules = [
#     Extension(
#         'zrpy.zrdds_python',  # 注意这里是完整包路径
#         sources=['bindings.cpp'],  # 你的 cpp 文件
#         include_dirs=[pybind11.get_include()],
#         language='c++',
#     )
# ]

from setuptools import setup, find_packages

setup(
    name='zrpy',
    version='0.1.0',
    packages=find_packages(),
    package_data={
        'zrpy': ['*.pyd'],  # 打包 .pyd 文件
    },
    include_package_data=True,
    zip_safe=False,
)
