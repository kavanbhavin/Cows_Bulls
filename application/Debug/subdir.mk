################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app_main.c \
../cows_bulls_model.c \
../uart_utility.c 

CMD_SRCS += \
../lnk_msp430f2274.cmd 

OBJS += \
./app_main.obj \
./cows_bulls_model.obj \
./uart_utility.obj 

C_DEPS += \
./app_main.pp \
./cows_bulls_model.pp \
./uart_utility.pp 

C_SRCS_QUOTED += \
"../app_main.c" \
"../cows_bulls_model.c" \
"../uart_utility.c" 


# Each subdirectory must supply rules for building sources it contributes
app_main.obj: ../app_main.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=msp -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/common" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/family1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --sat_reassoc=off --fp_reassoc=off --plain_char=unsigned --printf_support=minimal --preproc_with_compile --preproc_dependency="app_main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

cows_bulls_model.obj: ../cows_bulls_model.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=msp -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/common" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/family1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --sat_reassoc=off --fp_reassoc=off --plain_char=unsigned --printf_support=minimal --preproc_with_compile --preproc_dependency="cows_bulls_model.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

uart_utility.obj: ../uart_utility.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=msp -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/common" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/family1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --sat_reassoc=off --fp_reassoc=off --plain_char=unsigned --printf_support=minimal --preproc_with_compile --preproc_dependency="uart_utility.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


