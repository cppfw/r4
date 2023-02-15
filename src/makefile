include prorab.mk
include prorab-license.mk
include prorab-clang-format.mk

$(eval $(call prorab-try-simple-include, $(CONANBUILDINFO_DIR)conanbuildinfo.mak))

this_name := r4

this_soname := 0

$(eval $(call prorab-config, ../config))

this_cxxflags += $(addprefix -I,$(CONAN_INCLUDE_DIRS))
this_cxxflags_test += $(addprefix -I,$(CONAN_INCLUDE_DIRS))
this_ldflags += $(addprefix -L,$(CONAN_LIB_DIRS))

$(eval $(prorab-build-lib))

$(eval $(prorab-clang-format))

this_src_dir := 
this_license_file := ../LICENSE
$(eval $(prorab-license))
