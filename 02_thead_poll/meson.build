project('lhz-thread-poll', 'c')

src = ['./src/lhz_thread_poll.c']
include = ['./src']
deps = []

log_dep = dependency('lhz-log', version: '>=1.0.0')
deps += log_dep


include_install = ['./src/lhz_thread_poll.h']


# 生成并安装库文件
lhz_thread_poll_lib = library('lhz-thread-poll', sources:src, include_directories:include, dependencies:deps, install:true, install_dir: 'lib', link_args: ['-pthread'])

# 安装头文件
install_headers(include_install, install_dir:'include')
# 安装文件
pkgconfig = import('pkgconfig')
pkgconfig.generate(lhz_thread_poll_lib,
                   description: 'it is a library which achieve a simple thread poll',
                   version: '1.0.0',
                   libraries: ['-lpthread', '-llhz-log']
                   )