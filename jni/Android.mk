LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := honei
LOCAL_SRC_FILES := la.c test.c benchmark.c
TARGET_ARCH_ABI := armeabi-v7a

include $(BUILD_SHARED_LIBRARY)
