# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/khl/cnshe_robot_xiaohai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/khl/cnshe_robot_xiaohai

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/khl/cnshe_robot_xiaohai/CMakeFiles /home/khl/cnshe_robot_xiaohai/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/khl/cnshe_robot_xiaohai/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named cnshe_robot_xiaohai.out

# Build rule for target.
cnshe_robot_xiaohai.out: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cnshe_robot_xiaohai.out
.PHONY : cnshe_robot_xiaohai.out

# fast build rule for target.
cnshe_robot_xiaohai.out/fast:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/build
.PHONY : cnshe_robot_xiaohai.out/fast

src/LLog/LLog.o: src/LLog/LLog.cpp.o

.PHONY : src/LLog/LLog.o

# target to build an object file
src/LLog/LLog.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/LLog/LLog.cpp.o
.PHONY : src/LLog/LLog.cpp.o

src/LLog/LLog.i: src/LLog/LLog.cpp.i

.PHONY : src/LLog/LLog.i

# target to preprocess a source file
src/LLog/LLog.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/LLog/LLog.cpp.i
.PHONY : src/LLog/LLog.cpp.i

src/LLog/LLog.s: src/LLog/LLog.cpp.s

.PHONY : src/LLog/LLog.s

# target to generate assembly for a file
src/LLog/LLog.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/LLog/LLog.cpp.s
.PHONY : src/LLog/LLog.cpp.s

src/common/ini/iniconfig.o: src/common/ini/iniconfig.cpp.o

.PHONY : src/common/ini/iniconfig.o

# target to build an object file
src/common/ini/iniconfig.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/ini/iniconfig.cpp.o
.PHONY : src/common/ini/iniconfig.cpp.o

src/common/ini/iniconfig.i: src/common/ini/iniconfig.cpp.i

.PHONY : src/common/ini/iniconfig.i

# target to preprocess a source file
src/common/ini/iniconfig.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/ini/iniconfig.cpp.i
.PHONY : src/common/ini/iniconfig.cpp.i

src/common/ini/iniconfig.s: src/common/ini/iniconfig.cpp.s

.PHONY : src/common/ini/iniconfig.s

# target to generate assembly for a file
src/common/ini/iniconfig.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/ini/iniconfig.cpp.s
.PHONY : src/common/ini/iniconfig.cpp.s

src/common/serial_communication/serial_communication.o: src/common/serial_communication/serial_communication.cpp.o

.PHONY : src/common/serial_communication/serial_communication.o

# target to build an object file
src/common/serial_communication/serial_communication.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/serial_communication/serial_communication.cpp.o
.PHONY : src/common/serial_communication/serial_communication.cpp.o

src/common/serial_communication/serial_communication.i: src/common/serial_communication/serial_communication.cpp.i

.PHONY : src/common/serial_communication/serial_communication.i

# target to preprocess a source file
src/common/serial_communication/serial_communication.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/serial_communication/serial_communication.cpp.i
.PHONY : src/common/serial_communication/serial_communication.cpp.i

src/common/serial_communication/serial_communication.s: src/common/serial_communication/serial_communication.cpp.s

.PHONY : src/common/serial_communication/serial_communication.s

# target to generate assembly for a file
src/common/serial_communication/serial_communication.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/serial_communication/serial_communication.cpp.s
.PHONY : src/common/serial_communication/serial_communication.cpp.s

src/common/tcp_client/central_server_tcp.o: src/common/tcp_client/central_server_tcp.cpp.o

.PHONY : src/common/tcp_client/central_server_tcp.o

# target to build an object file
src/common/tcp_client/central_server_tcp.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/central_server_tcp.cpp.o
.PHONY : src/common/tcp_client/central_server_tcp.cpp.o

src/common/tcp_client/central_server_tcp.i: src/common/tcp_client/central_server_tcp.cpp.i

.PHONY : src/common/tcp_client/central_server_tcp.i

# target to preprocess a source file
src/common/tcp_client/central_server_tcp.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/central_server_tcp.cpp.i
.PHONY : src/common/tcp_client/central_server_tcp.cpp.i

src/common/tcp_client/central_server_tcp.s: src/common/tcp_client/central_server_tcp.cpp.s

.PHONY : src/common/tcp_client/central_server_tcp.s

# target to generate assembly for a file
src/common/tcp_client/central_server_tcp.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/central_server_tcp.cpp.s
.PHONY : src/common/tcp_client/central_server_tcp.cpp.s

src/common/tcp_client/tcp_client.o: src/common/tcp_client/tcp_client.cpp.o

.PHONY : src/common/tcp_client/tcp_client.o

# target to build an object file
src/common/tcp_client/tcp_client.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/tcp_client.cpp.o
.PHONY : src/common/tcp_client/tcp_client.cpp.o

src/common/tcp_client/tcp_client.i: src/common/tcp_client/tcp_client.cpp.i

.PHONY : src/common/tcp_client/tcp_client.i

# target to preprocess a source file
src/common/tcp_client/tcp_client.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/tcp_client.cpp.i
.PHONY : src/common/tcp_client/tcp_client.cpp.i

src/common/tcp_client/tcp_client.s: src/common/tcp_client/tcp_client.cpp.s

.PHONY : src/common/tcp_client/tcp_client.s

# target to generate assembly for a file
src/common/tcp_client/tcp_client.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/tcp_client/tcp_client.cpp.s
.PHONY : src/common/tcp_client/tcp_client.cpp.s

src/common/udp_client/udp_client.o: src/common/udp_client/udp_client.cpp.o

.PHONY : src/common/udp_client/udp_client.o

# target to build an object file
src/common/udp_client/udp_client.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/udp_client/udp_client.cpp.o
.PHONY : src/common/udp_client/udp_client.cpp.o

src/common/udp_client/udp_client.i: src/common/udp_client/udp_client.cpp.i

.PHONY : src/common/udp_client/udp_client.i

# target to preprocess a source file
src/common/udp_client/udp_client.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/udp_client/udp_client.cpp.i
.PHONY : src/common/udp_client/udp_client.cpp.i

src/common/udp_client/udp_client.s: src/common/udp_client/udp_client.cpp.s

.PHONY : src/common/udp_client/udp_client.s

# target to generate assembly for a file
src/common/udp_client/udp_client.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/udp_client/udp_client.cpp.s
.PHONY : src/common/udp_client/udp_client.cpp.s

src/common/work_base/work_base.o: src/common/work_base/work_base.cpp.o

.PHONY : src/common/work_base/work_base.o

# target to build an object file
src/common/work_base/work_base.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/work_base/work_base.cpp.o
.PHONY : src/common/work_base/work_base.cpp.o

src/common/work_base/work_base.i: src/common/work_base/work_base.cpp.i

.PHONY : src/common/work_base/work_base.i

# target to preprocess a source file
src/common/work_base/work_base.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/work_base/work_base.cpp.i
.PHONY : src/common/work_base/work_base.cpp.i

src/common/work_base/work_base.s: src/common/work_base/work_base.cpp.s

.PHONY : src/common/work_base/work_base.s

# target to generate assembly for a file
src/common/work_base/work_base.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/common/work_base/work_base.cpp.s
.PHONY : src/common/work_base/work_base.cpp.s

src/component/chassis_device/yixin_chassis_device/yixin_chassis.o: src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.o

.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.o

# target to build an object file
src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.o
.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.o

src/component/chassis_device/yixin_chassis_device/yixin_chassis.i: src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.i

.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.i

# target to preprocess a source file
src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.i
.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.i

src/component/chassis_device/yixin_chassis_device/yixin_chassis.s: src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.s

.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.s

# target to generate assembly for a file
src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.s
.PHONY : src/component/chassis_device/yixin_chassis_device/yixin_chassis.cpp.s

src/component/gas_detection/gas_detection.o: src/component/gas_detection/gas_detection.cpp.o

.PHONY : src/component/gas_detection/gas_detection.o

# target to build an object file
src/component/gas_detection/gas_detection.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/gas_detection/gas_detection.cpp.o
.PHONY : src/component/gas_detection/gas_detection.cpp.o

src/component/gas_detection/gas_detection.i: src/component/gas_detection/gas_detection.cpp.i

.PHONY : src/component/gas_detection/gas_detection.i

# target to preprocess a source file
src/component/gas_detection/gas_detection.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/gas_detection/gas_detection.cpp.i
.PHONY : src/component/gas_detection/gas_detection.cpp.i

src/component/gas_detection/gas_detection.s: src/component/gas_detection/gas_detection.cpp.s

.PHONY : src/component/gas_detection/gas_detection.s

# target to generate assembly for a file
src/component/gas_detection/gas_detection.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/gas_detection/gas_detection.cpp.s
.PHONY : src/component/gas_detection/gas_detection.cpp.s

src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.o: src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.o

.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.o

# target to build an object file
src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.o
.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.o

src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.i: src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.i

.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.i

# target to preprocess a source file
src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.i
.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.i

src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.s: src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.s

.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.s

# target to generate assembly for a file
src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.s
.PHONY : src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.cpp.s

src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.o: src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.o

.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.o

# target to build an object file
src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.o
.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.o

src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.i: src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.i

.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.i

# target to preprocess a source file
src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.i
.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.i

src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.s: src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.s

.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.s

# target to generate assembly for a file
src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.s
.PHONY : src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.cpp.s

src/component/xf/audio.o: src/component/xf/audio.c.o

.PHONY : src/component/xf/audio.o

# target to build an object file
src/component/xf/audio.c.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/audio.c.o
.PHONY : src/component/xf/audio.c.o

src/component/xf/audio.i: src/component/xf/audio.c.i

.PHONY : src/component/xf/audio.i

# target to preprocess a source file
src/component/xf/audio.c.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/audio.c.i
.PHONY : src/component/xf/audio.c.i

src/component/xf/audio.s: src/component/xf/audio.c.s

.PHONY : src/component/xf/audio.s

# target to generate assembly for a file
src/component/xf/audio.c.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/audio.c.s
.PHONY : src/component/xf/audio.c.s

src/component/xf/linuxrec.o: src/component/xf/linuxrec.c.o

.PHONY : src/component/xf/linuxrec.o

# target to build an object file
src/component/xf/linuxrec.c.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/linuxrec.c.o
.PHONY : src/component/xf/linuxrec.c.o

src/component/xf/linuxrec.i: src/component/xf/linuxrec.c.i

.PHONY : src/component/xf/linuxrec.i

# target to preprocess a source file
src/component/xf/linuxrec.c.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/linuxrec.c.i
.PHONY : src/component/xf/linuxrec.c.i

src/component/xf/linuxrec.s: src/component/xf/linuxrec.c.s

.PHONY : src/component/xf/linuxrec.s

# target to generate assembly for a file
src/component/xf/linuxrec.c.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/linuxrec.c.s
.PHONY : src/component/xf/linuxrec.c.s

src/component/xf/speech_recognizer.o: src/component/xf/speech_recognizer.c.o

.PHONY : src/component/xf/speech_recognizer.o

# target to build an object file
src/component/xf/speech_recognizer.c.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/speech_recognizer.c.o
.PHONY : src/component/xf/speech_recognizer.c.o

src/component/xf/speech_recognizer.i: src/component/xf/speech_recognizer.c.i

.PHONY : src/component/xf/speech_recognizer.i

# target to preprocess a source file
src/component/xf/speech_recognizer.c.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/speech_recognizer.c.i
.PHONY : src/component/xf/speech_recognizer.c.i

src/component/xf/speech_recognizer.s: src/component/xf/speech_recognizer.c.s

.PHONY : src/component/xf/speech_recognizer.s

# target to generate assembly for a file
src/component/xf/speech_recognizer.c.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/speech_recognizer.c.s
.PHONY : src/component/xf/speech_recognizer.c.s

src/component/xf/xf.o: src/component/xf/xf.cpp.o

.PHONY : src/component/xf/xf.o

# target to build an object file
src/component/xf/xf.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/xf.cpp.o
.PHONY : src/component/xf/xf.cpp.o

src/component/xf/xf.i: src/component/xf/xf.cpp.i

.PHONY : src/component/xf/xf.i

# target to preprocess a source file
src/component/xf/xf.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/xf.cpp.i
.PHONY : src/component/xf/xf.cpp.i

src/component/xf/xf.s: src/component/xf/xf.cpp.s

.PHONY : src/component/xf/xf.s

# target to generate assembly for a file
src/component/xf/xf.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/component/xf/xf.cpp.s
.PHONY : src/component/xf/xf.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/robots/xiaohai_robot/xiaohai_robot.o: src/robots/xiaohai_robot/xiaohai_robot.cpp.o

.PHONY : src/robots/xiaohai_robot/xiaohai_robot.o

# target to build an object file
src/robots/xiaohai_robot/xiaohai_robot.cpp.o:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/robots/xiaohai_robot/xiaohai_robot.cpp.o
.PHONY : src/robots/xiaohai_robot/xiaohai_robot.cpp.o

src/robots/xiaohai_robot/xiaohai_robot.i: src/robots/xiaohai_robot/xiaohai_robot.cpp.i

.PHONY : src/robots/xiaohai_robot/xiaohai_robot.i

# target to preprocess a source file
src/robots/xiaohai_robot/xiaohai_robot.cpp.i:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/robots/xiaohai_robot/xiaohai_robot.cpp.i
.PHONY : src/robots/xiaohai_robot/xiaohai_robot.cpp.i

src/robots/xiaohai_robot/xiaohai_robot.s: src/robots/xiaohai_robot/xiaohai_robot.cpp.s

.PHONY : src/robots/xiaohai_robot/xiaohai_robot.s

# target to generate assembly for a file
src/robots/xiaohai_robot/xiaohai_robot.cpp.s:
	$(MAKE) -f CMakeFiles/cnshe_robot_xiaohai.out.dir/build.make CMakeFiles/cnshe_robot_xiaohai.out.dir/src/robots/xiaohai_robot/xiaohai_robot.cpp.s
.PHONY : src/robots/xiaohai_robot/xiaohai_robot.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... cnshe_robot_xiaohai.out"
	@echo "... src/LLog/LLog.o"
	@echo "... src/LLog/LLog.i"
	@echo "... src/LLog/LLog.s"
	@echo "... src/common/ini/iniconfig.o"
	@echo "... src/common/ini/iniconfig.i"
	@echo "... src/common/ini/iniconfig.s"
	@echo "... src/common/serial_communication/serial_communication.o"
	@echo "... src/common/serial_communication/serial_communication.i"
	@echo "... src/common/serial_communication/serial_communication.s"
	@echo "... src/common/tcp_client/central_server_tcp.o"
	@echo "... src/common/tcp_client/central_server_tcp.i"
	@echo "... src/common/tcp_client/central_server_tcp.s"
	@echo "... src/common/tcp_client/tcp_client.o"
	@echo "... src/common/tcp_client/tcp_client.i"
	@echo "... src/common/tcp_client/tcp_client.s"
	@echo "... src/common/udp_client/udp_client.o"
	@echo "... src/common/udp_client/udp_client.i"
	@echo "... src/common/udp_client/udp_client.s"
	@echo "... src/common/work_base/work_base.o"
	@echo "... src/common/work_base/work_base.i"
	@echo "... src/common/work_base/work_base.s"
	@echo "... src/component/chassis_device/yixin_chassis_device/yixin_chassis.o"
	@echo "... src/component/chassis_device/yixin_chassis_device/yixin_chassis.i"
	@echo "... src/component/chassis_device/yixin_chassis_device/yixin_chassis.s"
	@echo "... src/component/gas_detection/gas_detection.o"
	@echo "... src/component/gas_detection/gas_detection.i"
	@echo "... src/component/gas_detection/gas_detection.s"
	@echo "... src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.o"
	@echo "... src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.i"
	@echo "... src/component/nuclear_radiation_measuring/nuclear_radiation_measuring.s"
	@echo "... src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.o"
	@echo "... src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.i"
	@echo "... src/component/robot_arm_device/dz_robot_arm/dz_robot_arm.s"
	@echo "... src/component/xf/audio.o"
	@echo "... src/component/xf/audio.i"
	@echo "... src/component/xf/audio.s"
	@echo "... src/component/xf/linuxrec.o"
	@echo "... src/component/xf/linuxrec.i"
	@echo "... src/component/xf/linuxrec.s"
	@echo "... src/component/xf/speech_recognizer.o"
	@echo "... src/component/xf/speech_recognizer.i"
	@echo "... src/component/xf/speech_recognizer.s"
	@echo "... src/component/xf/xf.o"
	@echo "... src/component/xf/xf.i"
	@echo "... src/component/xf/xf.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/robots/xiaohai_robot/xiaohai_robot.o"
	@echo "... src/robots/xiaohai_robot/xiaohai_robot.i"
	@echo "... src/robots/xiaohai_robot/xiaohai_robot.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
