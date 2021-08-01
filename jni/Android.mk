LOCAL_PATH := $(call my-dir)

ifeq ($(TARGET_ARCH),arm64)

include $(CLEAR_VARS)
LOCAL_MODULE    := sim-trace
LOCAL_SRC_FILES := sim-trace.cpp
LOCAL_STATIC_LIBRARIES := libvixl-arm
LOCAL_CFLAGS := -DVIXL_INCLUDE_SIMULATOR_AARCH64
LOCAL_C_INCLUDES := $(LOCAL_PATH)/vixl $(LOCAL_PATH)/vixl/src
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := test
LOCAL_SRC_FILES := test.cpp
LOCAL_STATIC_LIBRARIES := sim-trace
LOCAL_C_INCLUDES := $(LOCAL_PATH)/vixl $(LOCAL_PATH)/vixl/src
include $(BUILD_EXECUTABLE)

include $(LOCAL_PATH)/vixl/Android.mk

endif
