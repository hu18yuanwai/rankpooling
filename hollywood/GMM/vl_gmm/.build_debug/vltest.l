-include .build_debug//home/cy/lib/vlfeat/vl/mathop.d
-include .build_debug//home/cy/lib/vlfeat/vl/random.d
-include .build_debug//home/cy/lib/vlfeat/vl/host.d
-include .build_debug//home/cy/lib/vlfeat/vl/kdtree.d
-include .build_debug//home/cy/lib/vlfeat/vl/kmeans.d
-include .build_debug//home/cy/lib/vlfeat/vl/generic.d
-include .build_debug/vltest.d
-include .build_debug//home/cy/lib/vlfeat/vl/gmm.d

.build_debug/vltest.l: \
	.build_debug//home/cy/lib/vlfeat/vl/mathop.d \
	.build_debug//home/cy/lib/vlfeat/vl/random.d \
	.build_debug//home/cy/lib/vlfeat/vl/host.d \
	.build_debug//home/cy/lib/vlfeat/vl/kdtree.d \
	.build_debug//home/cy/lib/vlfeat/vl/kmeans.d \
	.build_debug//home/cy/lib/vlfeat/vl/generic.d \
	.build_debug/vltest.d \
	.build_debug//home/cy/lib/vlfeat/vl/gmm.d \

debug/vltest: .build_debug/vltest.l \
	.build_debug//home/cy/lib/vlfeat/vl/mathop.o \
	.build_debug//home/cy/lib/vlfeat/vl/random.o \
	.build_debug//home/cy/lib/vlfeat/vl/host.o \
	.build_debug//home/cy/lib/vlfeat/vl/kdtree.o \
	.build_debug//home/cy/lib/vlfeat/vl/kmeans.o \
	.build_debug//home/cy/lib/vlfeat/vl/generic.o \
	.build_debug/vltest.o \
	.build_debug//home/cy/lib/vlfeat/vl/gmm.o \

