################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../resource/UserExchangeToken.cpp \
../resource/UserLogin.cpp \
../resource/UsersCollection.cpp \
../resource/UsersDocument.cpp 

OBJS += \
./resource/UserExchangeToken.o \
./resource/UserLogin.o \
./resource/UsersCollection.o \
./resource/UsersDocument.o 

CPP_DEPS += \
./resource/UserExchangeToken.d \
./resource/UserLogin.d \
./resource/UsersCollection.d \
./resource/UsersDocument.d 


# Each subdirectory must supply rules for building sources it contributes
resource/%.o: ../resource/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I../../zapata-core -I../../zapata-http -I../../zapata-net -I../../zapata-rest -I../../zapata-oauth -I../../zapata-mongodb -I../ -I/usr/include/zapata -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

