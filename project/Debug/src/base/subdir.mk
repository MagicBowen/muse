################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/src/base/ConsoleState.cpp \
/Users/wangbo/Codes/muse/code/src/base/log.cpp 

OBJS += \
./src/base/ConsoleState.o \
./src/base/log.o 

CPP_DEPS += \
./src/base/ConsoleState.d \
./src/base/log.d 


# Each subdirectory must supply rules for building sources it contributes
src/base/ConsoleState.o: /Users/wangbo/Codes/muse/code/src/base/ConsoleState.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/base/log.o: /Users/wangbo/Codes/muse/code/src/base/log.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


