#-------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error Please set DEVKITARM in your environment. export DEVKITARM=/path/to/devkitARM)
endif

include $(DEVKITARM)/base_tools

#-------------------------------------------------------------------------------

ROM_CODE ?= BPRE
OFFSET ?= 0x08730000
DEBUG ?= RTC
# RTC_DEBUG
export BUILD := build
export SRC := src
export BINARY := $(BUILD)/linked.o
export RESOURCES := graphics
export WALLCLOCK := $(RESOURCES)/wallclock
export MISC := $(RESOURCES)/misc

export ARMIPS ?= armips.exe
export GFX ?= gbagfx.exe
export PREPROC ?= preproc.exe
export LD := $(PREFIX)ld

export ASFLAGS := -mthumb
# -D$(ROM_CODE) indica que lo que hay en ROM_CODE puede usarse para directivas de preprocesador.
export INCLUDES := -I $(SRC) -I . -I include -D$(DEBUG)
export WARNINGFLAGS :=	-Wall -Wno-discarded-array-qualifiers \
	-Wno-int-conversion
export CFLAGS := -g -O2 $(WARNINGFLAGS) -std=gnu17 -mthumb $(INCLUDES) -mcpu=arm7tdmi \
	-march=armv4t -mno-thumb-interwork -fno-inline -fno-builtin -mlong-calls -DROM_$(ROM_CODE) \
	-fdiagnostics-color -mtune=arm7tdmi -finline -mabi=apcs-gnu
# -mabi=apcs-gnu #EABI version 0
# -mabi=aapcs #EABI version 5
# -mthumb-interwork #el código admite llamadas ARM y Thumb, genera código más grande. usar sólo en EABI menor a 5. 
export DEPFLAGS = -MT $@ -MMD -MP -MF "$(@:%.o=%.d)"
export LDFLAGS := -T linker.ld -r $(ROM_CODE).ld 

# $(BUILD)/$(SRC)/siirtc.o: CFLAGS := -mthumb-interwork
#-------------------------------------------------------------------------------
	
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Generated
IMAGES_MISC:= $(call rwildcard,$(MISC),*.png)
IMAGES_WALLCLOCK:= $(call rwildcard,$(WALLCLOCK),*.png)
TILEMAP_WALLCLOCK:= $(call rwildcard,$(WALLCLOCK),*.bin)
PALETTE:= $(call rwildcard,$(RESOURCES),*.pal)

# png .4bpp
GBA4BPP_MISC := $(IMAGES_MISC:%.png=%.4bpp)

# png comprimido
GBA4BPP_WALLCLOCK := $(IMAGES_WALLCLOCK:%.png=%.4bpp)
GBA4BPP_LZ_WALLCLOCK := $(GBA4BPP_WALLCLOCK:%=%.lz)

# paletas
# GBA_PAL := $(IMAGES:%.png=%.pal)
GBAPAL := $(PALETTE:%.pal=%.gbapal)

# tilemap comprimido
GBA_BIN_LZ_WALLCLOCK := $(TILEMAP_WALLCLOCK:%=%.lz)

# Sources
# C_MAIN función principal que inicializa el sistema. Se compila primero que nada.
# C_MAIN := $(call rwildcard,$(SRC),gfx.c)
# HEADERS := $(call rwildcard,$(SRC),*.h)
C_SRC := $(call rwildcard,$(SRC),*.c)
S_SRC := $(call rwildcard,$(SRC),*.s)

# Binaries
# C_MAIN := $(C_MAIN:%.c=$(BUILD)/%.o)
C_OBJ := $(C_SRC:%.c=$(BUILD)/%.o)
S_OBJ := $(S_SRC:%.s=$(BUILD)/%.o)
SIIRTC_OBJ := $(SRC)/siirtc_pokefirered.o

# ALL_OBJ := $(C_MAIN) $(C_OBJ) $(S_OBJ)
ALL_OBJ := $(C_OBJ) $(S_OBJ)
# $(SIIRTC_OBJ)

#-------------------------------------------------------------------------------

.PHONY: all rom clean graphics

all: clean graphics rom
 
rom: main$(ROM_CODE).asm $(BINARY) $(SIIRTC_OBJ)
	@echo "\nCreating ROM"
	$(ARMIPS) main$(ROM_CODE).asm -definelabel insertinto $(OFFSET) -sym offsets.txt

clean:
	rm -rf $(BINARY)
	rm -rf $(BUILD)/$(SRC)
	rm -rf $(GBA4BPP_LZ_WALLCLOCK)
	rm -rf $(GBA_BIN_LZ_WALLCLOCK)
	rm -rf $(GBAPAL)
# rm -rf $(GBA_BIN_LZ)

$(BINARY): $(ALL_OBJ)
	@echo "\nLinking ELF binary $@"
	@$(LD) $(LDFLAGS) -o $@ $^
	
$(BUILD)/%.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -E -c $< -o $(BUILD)/$*.i
	@$(PREPROC) $(BUILD)/$*.i charmap.txt | $(CC) $(CFLAGS) -x c -o $@ -c -

$(BUILD)/%.o: %.s
	@echo -e "Assembling $<"
	@mkdir -p $(@D)
	$(PREPROC) "$<" charmap.txt | @$(AS) $(ASFLAGS) -o $@

# %.gbapal: %.pal ; $(GFX) $< $@ -num_colors 16	
%.4bpp: %.png  ; $(GFX) $< $@
%.pal: %.png  ; $(GFX) $< $@
%.gbapal: %.pal ; $(GFX) $< $@
%.lz: % ; $(GFX) $< $@

pngto4bpp: $(GBA4BPP_MISC) $(GBA4BPP_WALLCLOCK)

gba4bpptolz: $(GBA4BPP_LZ_WALLCLOCK)
	rm -rf $(GBA4BPP_WALLCLOCK)

pngtopal: $(GBA_PAL)

paltogbapal: $(GBAPAL)
#	rm -rf $(GBA_PAL)

bintolz: $(GBA_BIN_LZ_WALLCLOCK)

graphics: pngto4bpp gba4bpptolz paltogbapal bintolz
