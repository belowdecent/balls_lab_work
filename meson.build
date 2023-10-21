project('Lab2', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

sdl2_dep = dependency('sdl2')
sdl2_image_dep = dependency('sdl2_image')

exe = executable(
  'lab2', 'lab2.cpp', 'Ball.cpp', 'Limiter.cpp',
  install : true,
  dependencies: [sdl2_dep, sdl2_image_dep])

test('basic', exe)
