LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#deactivate if target-specifc flags need to be used
LOCAL_CFLAGS += -O3 -funroll-loops


#activate for NEON support
#ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
#    LOCAL_CFLAGS := -DHONEI_NEON=1 -mfloat-abi=softfp -mfpu=neon -O3 -ftree-vectorize -funroll-loops -march=armv7-a
#    LOCAL_SRC_FILES += la.c.neon test.c.neon benchmark.c.neon
#endif

#activate for TEGRA2
#LOCAL_CFLAGS += -march=armv7-a -mtune=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -O3 -funroll-loops

LOCAL_MODULE    := honei
LOCAL_SRC_FILES := la.c bicgstab.c cg.c test.c benchmark.c
TARGET_ARCH_ABI := armeabi-v7a armeabi

LOCAL_C_INCLUDES += sources/android/cpufeatures
LOCAL_STATIC_LIBRARIES += cpufeatures

include $(BUILD_SHARED_LIBRARY)
include $(ANDROID_NDK)/sources/android/cpufeatures/Android.mk
