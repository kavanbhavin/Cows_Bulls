################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/bsp.c 

OBJS += \
./bsp/bsp.obj 

C_DEPS += \
./bsp/bsp.pp 

C_SRCS_QUOTED += \
"../bsp/bsp.c" 


# Each subdirectory must supply rules for building sources it contributes
bsp/bsp.obj: ../bsp/bsp.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=msp -g --define=__MSP430F2274__ --define=MAX_HOPS=3 --define=MRFI_CC2500 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/drivers" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/bsp/boards/EZ430RF" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/common" --include_path="C:/Users/Kavan/Downloads/Cows_Bulls/radio_example/application/../drivers/mrfi/radios/family1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --diag_warning=225 --sat_reassoc=off --fp_reassoc=off --plain_char=unsigned --printf_support=minimal --preproc_with_compile --preproc_dependency="bsp/bsp.pp" --obj_directory="bsp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


