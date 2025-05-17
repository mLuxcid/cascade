project('cascade', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c17'])

sources = [
  'src/platform/window.c'
]
incdir = include_directories('include')

dependencies = []
dependencies += dependency('cglm',  required : true)
dependencies += dependency('glfw3',
  default_options: ['default_library=static'],
  required : true)

glad_proj = subproject('glad')
glad = glad_proj.get_variable('glad_dep')

dependencies += glad

cascade = static_library('cascade',
  sources,
  include_directories : incdir,
  dependencies : dependencies,
  install : true)

cascade_dep = declare_dependency(
  include_directories : incdir,
  link_with : cascade)

