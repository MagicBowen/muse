################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/wangbo/Codes/muse/code/src/promise/ExistPromise.cpp \
/Users/wangbo/Codes/muse/code/src/promise/NegativePromise.cpp \
/Users/wangbo/Codes/muse/code/src/promise/NotExistPromise.cpp \
/Users/wangbo/Codes/muse/code/src/promise/Result.cpp \
/Users/wangbo/Codes/muse/code/src/promise/SequentialPromise.cpp 

OBJS += \
./src/promise/ExistPromise.o \
./src/promise/NegativePromise.o \
./src/promise/NotExistPromise.o \
./src/promise/Result.o \
./src/promise/SequentialPromise.o 

CPP_DEPS += \
./src/promise/ExistPromise.d \
./src/promise/NegativePromise.d \
./src/promise/NotExistPromise.d \
./src/promise/Result.d \
./src/promise/SequentialPromise.d 


# Each subdirectory must supply rules for building sources it contributes
src/promise/ExistPromise.o: /Users/wangbo/Codes/muse/code/src/promise/ExistPromise.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/promise/NegativePromise.o: /Users/wangbo/Codes/muse/code/src/promise/NegativePromise.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/promise/NotExistPromise.o: /Users/wangbo/Codes/muse/code/src/promise/NotExistPromise.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/promise/Result.o: /Users/wangbo/Codes/muse/code/src/promise/Result.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/promise/SequentialPromise.o: /Users/wangbo/Codes/muse/code/src/promise/SequentialPromise.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/Users/wangbo/Codes/muse/code/include" -I/Users/wangbo/Codes/googletest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


