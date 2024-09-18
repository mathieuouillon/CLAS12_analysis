project('project_template', 'cpp',
  version : '0.1',
  default_options: ['cpp_std=c++23,c++20,c++17',],
  )

subproject('hipo')
hipo = dependency('hipo4')

inc = include_directories('include')

exe = executable('project_template', 'src/main.cpp',include_directories : inc, cpp_args : '-std=c++17', dependencies: hipo)

cpp_std = get_option('cpp_std')

message('C++ standard: ' + cpp_std)
