e = dependency('enlightenment')

src = files([
  'config.c',
  'e_int_config_randr2_fork.c',
  'e_mod_main.c'
])

module = shared_module('module',
                       src,
                       dependencies : [e, elm],
                       install_dir: install_dir,
                       install: true,
                       name_prefix: '')
