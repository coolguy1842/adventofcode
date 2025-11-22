project('aoc', 'cpp', default_options: [ 'cpp_std=c++23' ])

sources = []
foreach day : run_command(meson.project_source_root() + '/tools/getDays.sh', meson.project_source_root(), check: true).stdout().strip().split('\n')
    if day != ''
        sources += 'src/Days/Day' + day + '.cpp'
    endif
endforeach

days_hpp = custom_target(
    'days_header',
    input: sources,
    output: 'Days.hpp',
    command: [ meson.project_source_root() + '/tools/genDaysHeader.sh',  meson.project_source_root() + '/include/Days', '@OUTPUT@' ]
)

cpp_flags = []
link_flags = []

if get_option('buildtype') == 'debug'
    c_flags = [ '-O0', '-ggdb3', '-Wno-c23-extensions)' ]
    link_flags = [ '-fsanitize=address', '-fno-omit-frame-pointer' ]
elif get_option('buildtype') == 'release'
    c_flags = [ '-O3', '-ffast-math' ]
endif

executable(
    'aoc',
    sources: [
        'src/Util/Timer.cpp',
        'src/Util/StringUtil.cpp',
        'src/IDay.cpp',
        'src/main.cpp',
        sources,
        days_hpp
    ],
    include_directories: include_directories(
        'include'
    ),
    dependencies: [
        dependency('CLI11')
    ],
    cpp_args: cpp_flags,
    link_args: link_flags,
    native: true
)