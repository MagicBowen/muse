################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/src/simulation/Simulation.cpp 

OBJS += \
./src/simulation/Simulation.o 

CPP_DEPS += \
./src/simulation/Simulation.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulation/Simulation.o: /Users/wangbo/Codes/muse/code/src/simulation/Simulation.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


