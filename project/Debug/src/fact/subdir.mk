################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/src/fact/CollisionFact.cpp \
/Users/wangbo/Codes/muse/code/src/fact/DistanceLessFact.cpp \
/Users/wangbo/Codes/muse/code/src/fact/StopFact.cpp 

OBJS += \
./src/fact/CollisionFact.o \
./src/fact/DistanceLessFact.o \
./src/fact/StopFact.o 

CPP_DEPS += \
./src/fact/CollisionFact.d \
./src/fact/DistanceLessFact.d \
./src/fact/StopFact.d 


# Each subdirectory must supply rules for building sources it contributes
src/fact/CollisionFact.o: /Users/wangbo/Codes/muse/code/src/fact/CollisionFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fact/DistanceLessFact.o: /Users/wangbo/Codes/muse/code/src/fact/DistanceLessFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/fact/StopFact.o: /Users/wangbo/Codes/muse/code/src/fact/StopFact.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


