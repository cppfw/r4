include prorab.mk
include prorab-license.mk
include prorab-clang-format.mk

$(info g++ version:)
$(info $(shell g++ --version))

this_name := r4

this_soname := 0

$(eval $(call prorab-config, ../config))

$(eval $(prorab-build-lib))

$(eval $(prorab-clang-format))

this_src_dir := $(this_name)
this_license_file := ../LICENSE
$(eval $(prorab-license))
