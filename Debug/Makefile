################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../climate.cpp \
../digitsdisplay.cpp \
../global_varibals.cpp \
../leds.cpp \
../Prog.cpp \
../repeatingHandler.cpp \
../RTC.cpp \
../sleeping.cpp \
../sounder.cpp \
../WDR.cpp \
../menu.cpp \
../push_button.cpp \
../sensor.cpp \
../Timing.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
climate.o \
digitsdisplay.o \
global_varibals.o \
leds.o \
Prog.o \
repeatingHandler.o \
RTC.o \
sleeping.o \
sounder.o \
WDR.o \
menu.o \
push_button.o \
sensor.o \
Timing.o

OBJS_AS_ARGS +=  \
climate.o \
digitsdisplay.o \
global_varibals.o \
leds.o \
Prog.o \
repeatingHandler.o \
RTC.o \
sleeping.o \
sounder.o \
WDR.o \
menu.o \
push_button.o \
sensor.o \
Timing.o

C_DEPS +=  \
climate.d \
digitsdisplay.d \
global_varibals.d \
leds.d \
Prog.d \
repeatingHandler.d \
RTC.d \
sleeping.d \
sounder.d \
WDR.d \
menu.d \
push_button.d \
sensor.d \
Timing.d

C_DEPS_AS_ARGS +=  \
climate.d \
digitsdisplay.d \
global_varibals.d \
leds.d \
Prog.d \
repeatingHandler.d \
RTC.d \
sleeping.d \
sounder.d \
WDR.d \
menu.d \
push_button.d \
sensor.d \
Timing.d

OUTPUT_FILE_PATH +=WDR_Atmega16a.elf

OUTPUT_FILE_PATH_AS_ARGS +=WDR_Atmega16a.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





























./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"E:\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega16a -B "E:\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega16a" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.9.2
	$(QUOTE)E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="WDR_Atmega16a.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega16a -B "E:\Atmel Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega16a"  
	@echo Finished building target: $@
	"E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "WDR_Atmega16a.elf" "WDR_Atmega16a.hex"
	"E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "WDR_Atmega16a.elf" "WDR_Atmega16a.eep" || exit 0
	"E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "WDR_Atmega16a.elf" > "WDR_Atmega16a.lss"
	"E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "WDR_Atmega16a.elf" "WDR_Atmega16a.srec"
	"E:\Atmel Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "WDR_Atmega16a.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "WDR_Atmega16a.elf" "WDR_Atmega16a.a" "WDR_Atmega16a.hex" "WDR_Atmega16a.lss" "WDR_Atmega16a.eep" "WDR_Atmega16a.map" "WDR_Atmega16a.srec" "WDR_Atmega16a.usersignatures"
	