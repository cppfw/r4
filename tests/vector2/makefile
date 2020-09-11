include prorab.mk

this_name := tests

this_out_dir := build

this_srcs := main.cpp

this_cxxflags += -std=c++14 -fPIC

this_ldlibs += -lstdc++

this_no_install := true

$(eval $(prorab-build-app))

include $(d)../test_target.mk
