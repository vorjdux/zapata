################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../resource/ExchangeToken.cpp \
../resource/Login.cpp 

OBJS += \
./resource/ExchangeToken.o \
./resource/Login.o 

CPP_DEPS += \
./resource/ExchangeToken.d \
./resource/Login.d 


# Each subdirectory must supply rules for building sources it contributes
resource/%.o: ../resource/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I../../zapata-core -I../../zapata-http -I../../zapata-net -I../../zapata-rest -I../ -I/usr/include/zapata -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


