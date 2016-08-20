-include .build_debug/genDescriptor.d

.build_debug/genDescriptor.l: \
	.build_debug/genDescriptor.d \

debug/genDescriptor: .build_debug/genDescriptor.l \
	.build_debug/genDescriptor.o \

