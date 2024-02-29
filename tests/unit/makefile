include prorab.mk
include prorab-test.mk

this_name := r4_unit_tests

this_srcs += $(call prorab-src-dir, src)

$(eval $(call prorab-config, ../../config))

this_cxxflags += -isystem ../../src

this_ldlibs += -ltst -lutki -lm

this_no_install := true

$(eval $(prorab-build-app))

this_test_cmd := $(prorab_this_name) --junit-out=out/$(c)/junit.xml --jobs=$(prorab_nproc)
this_test_deps := $(prorab_this_name)
this_test_ld_path := ../../src/out/$(c)
$(eval $(prorab-test))
