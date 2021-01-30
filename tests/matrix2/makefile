include prorab.mk

this_name := tests

this_srcs := $(call prorab-src-dir)

$(eval $(call prorab-config, ../../config))

this_ldlibs += -lm

this_no_install := true

$(eval $(prorab-build-app))

include $(d)../test_target.mk
