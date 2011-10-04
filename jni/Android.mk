LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := honei
LOCAL_SRC_FILES := la.c test.c

include $(BUILD_SHARED_LIBRARY)
