project('glad', 'c',
  version : '0.1', default_options : ['warning_level=2', 'c_std=c11'])

incdir = include_directories('include')

glad = static_library('glad',
  'src/glad.c',
  include_directories : incdir,
  install : true)

glad_dep = declare_dependency(include_directories : incdir,
  link_with : glad)
