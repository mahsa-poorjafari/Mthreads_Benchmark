################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Mthreads_Benchmark.cpp \
../src/SimpleCar.cpp \
../src/airconditioner.cpp \
../src/convar.cpp \
../src/warning.cpp \
../src/windows.cpp 

OBJS += \
./src/Mthreads_Benchmark.o \
./src/SimpleCar.o \
./src/airconditioner.o \
./src/convar.o \
./src/warning.o \
./src/windows.o 

CPP_DEPS += \
./src/Mthreads_Benchmark.d \
./src/SimpleCar.d \
./src/airconditioner.d \
./src/convar.d \
./src/warning.d \
./src/windows.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


