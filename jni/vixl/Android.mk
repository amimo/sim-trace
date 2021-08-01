LOCAL_PATH:= $(call my-dir)

vixl_root := $(LOCAL_PATH)/
vixl_src_include_path := $(vixl_root)/src/
vixl_test_include_path := $(vixl_src_include_path) $(vixl_root)/test/

vixl_common_files := \
  src/code-buffer-vixl.cc \
  src/compiler-intrinsics-vixl.cc \
  src/cpu-features.cc \
  src/utils-vixl.cc

vixl_src_files_arm := \
  src/aarch32/assembler-aarch32.cc \
  src/aarch32/disasm-aarch32.cc \
  src/aarch32/instructions-aarch32.cc \
  src/aarch32/macro-assembler-aarch32.cc \
  src/aarch32/constants-aarch32.cc \
  src/aarch32/location-aarch32.cc \
  src/aarch32/operands-aarch32.cc

vixl_src_files_arm64 := \
  src/aarch64/assembler-aarch64.cc \
  src/aarch64/cpu-aarch64.cc \
  src/aarch64/cpu-features-auditor-aarch64.cc \
  src/aarch64/pointer-auth-aarch64.cc \
  src/aarch64/decoder-aarch64.cc \
  src/aarch64/disasm-aarch64.cc \
  src/aarch64/instructions-aarch64.cc \
  src/aarch64/instrument-aarch64.cc \
  src/aarch64/logic-aarch64.cc \
  src/aarch64/macro-assembler-aarch64.cc \
  src/aarch64/operands-aarch64.cc \
  src/aarch64/simulator-aarch64.cc


vixl_cpp_flags := \
  -DVIXL_GENERATE_SIMULATOR_INSTRUCTIONS_VALUE=0 \
  -DVIXL_CODE_BUFFER_MMAP \
  -DVIXL_INCLUDE_SIMULATOR_AARCH64 \
  -DVIXL_INCLUDE_TARGET_AARCH64 \
  -Wall \
  -Wextra \
  -Werror \
  -fdiagnostics-show-option \
  -Wredundant-decls \
  -Wunreachable-code \
  -Wmissing-noreturn \
  -pedantic \
  -std=c++11 \

# Explicitly enable the write-strings warning. VIXL uses
# const correctly when handling string constants.
vixl_cpp_flags += \
  -Wwrite-strings \

vixl_cpp_flags_release := \
  $(vixl_cpp_flags) \
  -O3 \

vixl_cpp_flags_debug := \
  $(vixl_cpp_flags) \
  -DVIXL_DEBUG \
  -UNDEBUG \
  -O2 \
  -ggdb3 \

VIXL_COVERAGE := false

ifeq ($(ART_COVERAGE), true)
  VIXL_COVERAGE := true
endif

# Shared libraries for target - arm64
include $(CLEAR_VARS)
LOCAL_CLANG := true
LOCAL_CPPFLAGS := $(vixl_cpp_flags_release)
LOCAL_CLANG_CFLAGS := -Wimplicit-fallthrough
LOCAL_C_INCLUDES := $(vixl_src_include_path)
ifeq ($(TARGET_ARCH),arm)
LOCAL_SRC_FILES :=  $(vixl_common_files) $(vixl_src_files_arm)
else
LOCAL_SRC_FILES :=  $(vixl_common_files) $(vixl_src_files_arm64)
endif
LOCAL_MODULE := libvixl-arm
include $(BUILD_STATIC_LIBRARY)
