project('quickscreen', 'c')

e = dependency('enlightenment')
elm = dependency('elementary')

dir_module_e = e.get_pkgconfig_variable('modules')
release = e.get_pkgconfig_variable('release')
host_os = host_machine.system()
cc = meson.get_compiler('c')

if host_os == 'linux'
   if cc.has_header_symbol('features.h', '__UCLIBC__')
      host_os = 'linux-uclibc'
   elif cc.has_header_symbol('features.h', '__dietlibc__')
      host_os = 'linux-dietlibc'
   else
      host_os = 'linux-gnu'
   endif
endif
module_arch = '@0@-@1@-@2@'.format(host_os, host_machine.cpu_family(), release)


dir_prefix = get_option('prefix')
install_mod_dir = join_paths(dir_module_e, meson.project_name())
install_dir = join_paths(install_mod_dir, module_arch)
dir_data   = join_paths(dir_prefix, get_option('datadir'))
install_data_dir = join_paths(dir_data, meson.project_name())
inc_dir = include_directories('.')

config_h = configuration_data()
config_h.set_quoted('MODULE_DIR', install_dir)
config_h.set_quoted('PACKAGE_DATA_DIR', install_data_dir)

subdir('src')
subdir('data')

configure_file(output: 'config.h', install: false, configuration: config_h)

install_data('module.desktop', install_dir : install_mod_dir)
