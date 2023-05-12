include prorab.mk
include prorab-license.mk
include prorab-clang-format.mk

this_name := r4

this_soname := 0

$(eval $(call prorab-config, ../config))

$(eval $(prorab-build-lib))

$(eval $(prorab-clang-format))

this_src_dir := 
this_license_file := ../LICENSE
$(eval $(prorab-license))
