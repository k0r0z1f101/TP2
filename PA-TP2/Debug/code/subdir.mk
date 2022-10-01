################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/Game.cpp \
../code/GameObject.cpp \
../code/GameSnow.cpp \
../code/Player.cpp \
../code/Snowflake.cpp \
../code/SnowflakeNoContact.cpp \
../code/SnowflakeRebound.cpp \
../code/SnowflakeSine.cpp \
../code/main.cpp 

CPP_DEPS += \
./code/Game.d \
./code/GameObject.d \
./code/GameSnow.d \
./code/Player.d \
./code/Snowflake.d \
./code/SnowflakeNoContact.d \
./code/SnowflakeRebound.d \
./code/SnowflakeSine.d \
./code/main.d 

OBJS += \
./code/Game.o \
./code/GameObject.o \
./code/GameSnow.o \
./code/Player.o \
./code/Snowflake.o \
./code/SnowflakeNoContact.o \
./code/SnowflakeRebound.o \
./code/SnowflakeSine.o \
./code/main.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.cpp code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/Game.d ./code/Game.o ./code/GameObject.d ./code/GameObject.o ./code/GameSnow.d ./code/GameSnow.o ./code/Player.d ./code/Player.o ./code/Snowflake.d ./code/Snowflake.o ./code/SnowflakeNoContact.d ./code/SnowflakeNoContact.o ./code/SnowflakeRebound.d ./code/SnowflakeRebound.o ./code/SnowflakeSine.d ./code/SnowflakeSine.o ./code/main.d ./code/main.o

.PHONY: clean-code

