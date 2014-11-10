LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellojni
LOCAL_CFLAGS := -Werror
LOCAL_SRC_FILES := hellojni.c
LOCAL_LBLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
