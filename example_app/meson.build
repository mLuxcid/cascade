sources = [
  'src/main.c'
]

incdirs = [
  include_directories('..' / 'include'),
  include_directories('src')
]

dependencies = []
dependencies += dependency('glfw3', required : true)

executable('example_app',
  sources,
  include_directories : incdirs,
  dependencies : dependencies,
  link_with : cascade)
 
