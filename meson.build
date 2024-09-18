project('project_template', 'cpp',
  version : '0.1',
  default_options: ['cpp_std=c++23,c++20,c++17',],
  )

hipo = subproject('hipo')

exe = executable('project_template', 'src/main.cpp', cpp_args : '-std=c++17')

cpp_std = get_option('cpp_std')

message('C++ standard: ' + cpp_std)
