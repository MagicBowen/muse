################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/test/TestPromise.cpp \
/Users/wangbo/Codes/muse/code/test/main.cpp 

OBJS += \
./test/TestPromise.o \
./test/main.o 

CPP_DEPS += \
./test/TestPromise.d \
./test/main.d 


# Each subdirectory must supply rules for building sources it contributes
test/TestPromise.o: /Users/wangbo/Codes/muse/code/test/TestPromise.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test/main.o: /Users/wangbo/Codes/muse/code/test/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


