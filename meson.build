project('skim_rgd', 'cpp',
  version : '0.1',
  default_options: ['cpp_std=c++23,c++20,c++17',],
  )

subproject('hipo')
hipo = dependency('hipo4')

root_dep = dependency('ROOT')

inc = include_directories('include')

exe = executable('skim_rgd', sources : ['src/main.cpp', 'src/skimer/Reader.cpp'], include_directories : inc, cpp_args : '-std=c++20', dependencies: [hipo])

cpp_std = get_option('cpp_std')

message('C++ standard: ' + cpp_std)
