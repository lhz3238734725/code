project('lhz-log', 'c')

src = ['./src/lhz_log.c']
include = ['./src']
deps = []

config_data = configuration_data()
#设置日志等级宏
configure_file(
    output:'config.h',
    configuration:config_data
)

library('lhz-log', sources:src, install:true, include_directories:include, dependencies:deps)