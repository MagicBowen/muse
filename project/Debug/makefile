################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include test/subdir.mk
-include src/simulation/subdir.mk
-include src/promise/subdir.mk
-include src/fact/core/subdir.mk
-include src/fact/subdir.mk
-include src/event/subdir.mk
-include src/base/subdir.mk
-include build/test/CMakeFiles/test_muse.dir/subdir.mk
-include build/src/CMakeFiles/muse.dir/simulation/subdir.mk
-include build/src/CMakeFiles/muse.dir/promise/core/subdir.mk
-include build/src/CMakeFiles/muse.dir/promise/subdir.mk
-include build/src/CMakeFiles/muse.dir/fact/core/subdir.mk
-include build/src/CMakeFiles/muse.dir/fact/subdir.mk
-include build/src/CMakeFiles/muse.dir/event/subdir.mk
-include build/src/CMakeFiles/muse.dir/base/subdir.mk
-include build/CMakeFiles/3.4.1/CompilerIdCXX/subdir.mk
-include build/CMakeFiles/3.4.1/CompilerIdC/subdir.mk
-include build/CMakeFiles/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: muse

# Tool invocations
muse: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++  -o "muse" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) muse
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
