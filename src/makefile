include prorab.mk
include myci.mk

$(eval $(call myci-try-include, $(CONANBUILDINFO_DIR)conanbuildinfo.mak))

this_name := r4

this_soname := 0

$(eval $(call prorab-config, ../config))

this_cxxflags += $(addprefix -I,$(CONAN_INCLUDE_DIRS))
this_cxxflags_test += $(addprefix -I,$(CONAN_INCLUDE_DIRS))
this_ldflags += $(addprefix -L,$(CONAN_LIB_DIRS))

$(eval $(prorab-build-lib))
