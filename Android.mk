LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := imagezero
LOCAL_SRC_FILES := file.cpp libiz.cpp main.cpp portableimage.cpp table.cpp
LOCAL_CFLAGS := -O2 -Winline -W -Wall -fomit-frame-pointer -fno-rtti -fno-exceptions -c -fPIC
include $(BUILD_STATIC_LIBRARY)
