include prorab.mk

this_name := tests

this_out_dir := build

this_srcs := main.cpp

this_cxxflags += -std=c++17 -fPIC

ifeq ($(debug),true)
    this_cxxflags += -D DEBUG
endif

this_ldlibs += -lstdc++ -lm

this_no_install := true

$(eval $(prorab-build-app))

include $(d)../test_target.mk
