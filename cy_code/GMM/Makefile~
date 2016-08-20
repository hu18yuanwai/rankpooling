# set the binaries that have to be built
TARGETS := getGMM

# set the build configuration set
#BUILD := release
BUILD := debug

# set bin and build dirs
BUILDDIR := .build_$(BUILD)
BINDIR := $(BUILD)

# libraries
LDLIBS = $(addprefix -l, $(LIBS) $(LIBS_$(notdir $*)))
LIBS := \
	boost_program_options boost_regex boost_system boost_filesystem \
	opencv_core opencv_imgproc opencv_video opencv_nonfree opencv_features2d opencv_flann opencv_calib3d opencv_objdetect opencv_legacy opencv_highgui \
	avformat avutil avcodec swscale z
#LIBS_hog2D := boost_python-mt

# set some flags and compiler/linker specific commands
CXXFLAGS = -pipe -D __STDC_CONSTANT_MACROS -D STD=std -Wall $(CXXFLAGS_$(BUILD)) -I. -I/usr/local/include -I ../
CXXFLAGS_debug := -ggdb
CXXFLAGS_release := -O3 -DNDEBUG -ggdb
LDFLAGS = -L/usr/local/lib -pipe -Wall $(LDFLAGS_$(BUILD))
LDFLAGS_debug := -ggdb
LDFLAGS_release := -O3 -ggdb

include make/generic.mk
