project('lhz-log', 'c')

src = ['./src/lhz_log.c']
include = ['./src']
deps = []

include_install = ['./src/lhz_log.h']

config_data = configuration_data()
#设置日志等级宏
configure_file(
    output:'config.h',
    configuration:config_data
)

# 生成并安装库文件
library('lhz-log', sources:src, include_directories:include, dependencies:deps, install:true, install_dir: 'lib')
# 安装头文件
install_headers(include_install, install_dir:'include')
# 安装文件
pkgconfig = import('pkgconfig')
pkgconfig.generate(lhz_log_lib,
                   description: 'it is a simple log',
                   version: '1.0.0'
                   )
