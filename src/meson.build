e = dependency('enlightenment')

src = files([
  'legacy_config.c',
  'e_mod_main.c',
  'ui_advanced_config.c',
  'ui_wizard_config.c'
])

module = shared_module('module',
                       src, 
                       include_directories : inc_dir,
                       dependencies : [e, elm],
                       install_dir: install_dir,
                       install: true,
                       name_prefix: '')
