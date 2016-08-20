-include .build_debug/getGMM.d

.build_debug/getGMM.l: \
	.build_debug/getGMM.d \

debug/getGMM: .build_debug/getGMM.l \
	.build_debug/getGMM.o \

