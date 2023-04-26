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

library('lhz-log', sources:src, include_directories:include, dependencies:deps, install:true, install_dir: 'lib')

install_headers(include_install, install_dir:'include')