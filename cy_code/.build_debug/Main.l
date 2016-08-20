-include .build_debug/Main.d

.build_debug/Main.l: \
	.build_debug/Main.d \

debug/Main: .build_debug/Main.l \
	.build_debug/Main.o \

