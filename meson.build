project(
  'project_template',
  'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
  ],
)

# ROOT dependency
root_dep = dependency(
  'ROOT',
  required: true,
  method: 'cmake',
)

# handle ROOT
root_dep_inc_dirs = []
root_dep_link_args = []
if root_dep.found()
  root_dep_inc_dirs = include_directories(
    run_command('root-config', '--incdir', check: true).stdout().strip(),
  )
  root_libdir = run_command('root-config', '--libdir', check: true).stdout().strip()
  # ROOT libraries that we need (safer than `root-config --libs`)
  root_dep_link_args = [
    '-L' + root_libdir,
    '-lCore',
    '-lGenVector',
    '-lROOTDataFrame',
    '-lROOTVecOps',
    '-lTreePlayer',
    '-lROOTGpadv7',
    '-lMathCore',
    '-lRIO',
    '-lHist',
    '-lGpad',
  ]
endif
root_dep_inc_dirs = include_directories(
  run_command('root-config', '--incdir', check: true).stdout().strip(),
)

subdir('hipo4')

inc = include_directories('include')

executable(
  'project_template',
  'src/main.cpp',
  include_directories: [inc,root_dep_inc_dirs],
  cpp_args: '-std=c++17',
  dependencies: hipo_dep,
  link_args: root_dep_link_args,
  build_rpath: root_libdir,
)




