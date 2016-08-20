-include .build_debug/DenseTrackStab.d

.build_debug/DenseTrackStab.l: \
	.build_debug/DenseTrackStab.d \

debug/DenseTrackStab: .build_debug/DenseTrackStab.l \
	.build_debug/DenseTrackStab.o \

