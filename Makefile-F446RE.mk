
# Choose which SDK to use
DEFINES += -DSTM32CUBE
#DEFINES += -DLIBOPENCM3

STM32_SDK   = lib/STM32Cube_FW_F4_V1.16.0
BSP         = $(STM32_SDK)/Drivers/BSP/STM32F4xx-Nucleo
CMSIS       = $(STM32_SDK)/Drivers/CMSIS
HAL         = $(STM32_SDK)/Drivers/STM32F4xx_HAL_Driver

STARTUP_SRC = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f446xx.s
LIB_SRCS    := $(wildcard $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/*.c $(HAL)/Src/*.c $(BSP)/*.c)
LIB_SRCS    := $(filter-out $(wildcard $(HAL)/Src/*template.c), $(LIB_SRCS))

ifdef USE_LIBOPENCM3
LIB_SRCS    += $(wildcard lib/libopencm3/lib/stm32/f4/*.c lib/libopencm3/lib/stm32/common/*.c lib/libopencm3/lib/stm32/*.c)
INCLUDES    += -I lib/libopencm3/include
endif

LIB_SRCS    += $(wildcard lib/ushell/*.c)

INCLUDES    += -I $(CMSIS)/Include
INCLUDES    += -I $(CMSIS)/Device/ST/STM32F4xx/Include
INCLUDES    += -I $(HAL)/Inc
INCLUDES    += -I $(BSP)

INCLUDES    += -I include/bsp/stm32f446xx
INCLUDES    += -I lib
INCLUDES    += -I lib/ushell

DEFINES     += -DEMBEDDED
DEFINES     += -DSTM32F4XX
DEFINES     += -DSTM32F446xx
DEFINES     += -DUSE_STM32F4XX_NUCLEO
DEFINES     += -DUSE_HAL_DRIVER

LINKER_SCRIPT = linker/STM32F446RETx_FLASH.ld

MCU         = -mcpu=cortex-m4 -mthumb
FPU         = -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Set Compilation and Linking Flags
CFLAGS      = $(MCU) $(FPU) \
              $(DEFINES) $(INCLUDES) \
              -std=gnu11 \
              $(DEBUG) $(OPTIMIZE) \
              -ffunction-sections -fdata-sections
ASFLAGS     = $(MCU) $(FPU) \
              -g -Wa,--warn -x assembler-with-cpp
LDFLAGS     = $(MCU) $(FPU) \
              -specs=nano.specs -specs=nosys.specs \
              -g -gdwarf-2 \
              -T$(LINKER_SCRIPT) \
              -Xlinker --gc-sections -Wl,-Map=$(PROJ_NAME).map \
               $(LIBS)

OPENOCD_TARGET = target/stm32f4x.cfg
