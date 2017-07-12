LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_LDLIBS    := -lm -llog

LOCAL_MODULE := CoordinateJniLib
LOCAL_SRC_FILES := coordinateJniLib.c
include $(BUILD_SHARED_LIBRARY)