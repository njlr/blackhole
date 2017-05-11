include_defs('//BUCKAROO_DEPS')

cxx_library(
  name = 'blackhole',
  exported_headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  srcs = glob([
    'src/**/*.cpp',
  ]),
  compiler_flags = [
    '-std=c++14',
  ],
  deps = BUCKAROO_DEPS,
  visibility = [
    'PUBLIC',
  ],
)
