LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := efiwrapper_host-$(TARGET_BUILD_VARIANT)
LOCAL_MODULE_STEM := efiwrapper_host
LOCAL_CLANG := false
LOCAL_CFLAGS := $(EFIWRAPPER_HOST_CFLAGS)
LOCAL_STATIC_LIBRARIES := \
	libefiwrapper_host-$(TARGET_BUILD_VARIANT)
LOCAL_SRC_FILES := \
	main.c \
	disk.c
LOCAL_LDFLAGS := -ldl
LOCAL_MODULE_HOST_ARCH := $(EFIWRAPPER_HOST_ARCH)
LOCAL_C_INCLUDES := $(EFIWRAPPER_HOST_C_INCLUDES)
include $(BUILD_HOST_EXECUTABLE)