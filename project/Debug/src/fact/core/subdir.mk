################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/src/fact/core/AllOfFact.cpp \
/Users/wangbo/Codes/muse/code/src/fact/core/AnyOfFact.cpp \
/Users/wangbo/Codes/muse/code/src/fact/core/BaseFact.cpp 

OBJS += \
./src/fact/core/AllOfFact.o \
./src/fact/core/AnyOfFact.o \
./src/fact/core/BaseFact.o 

CPP_DEPS += \
./src/fact/core/AllOfFact.d \
./src/fact/core/AnyOfFact.d \
./src/fact/core/BaseFact.d 


# Each subdirectory must supply rules for building sources it contributes
src/fact/core/AllOfFact.o: /Users/wangbo/Codes/muse/code/src/fact/core/AllOfFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fact/core/AnyOfFact.o: /Users/wangbo/Codes/muse/code/src/fact/core/AnyOfFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fact/core/BaseFact.o: /Users/wangbo/Codes/muse/code/src/fact/core/BaseFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


