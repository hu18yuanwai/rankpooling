-include .build_debug/fisher.d

.build_debug/fisher.l: \
	.build_debug/fisher.d \

debug/fisher: .build_debug/fisher.l \
	.build_debug/fisher.o \

