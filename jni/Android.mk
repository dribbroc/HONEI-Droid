LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -DHONEI_NEON=1 -mfloat-abi=softfp -mfpu=neon
    !LOCAL_SRC_FILES += la.c.neon test.c.neon
endif

LOCAL_MODULE    := honei
LOCAL_SRC_FILES := la.c bicgstab.c cg.c test.c benchmark.c
TARGET_ARCH_ABI := armeabi-v7a armeabi

include $(BUILD_SHARED_LIBRARY)
