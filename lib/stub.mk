WINE = wine
WINE_PATH_TOOL = winepath

CC = $(WINE) orbis-clang
LD = $(WINE) orbis-ld
FIX_STUB = $(CURDIR)/../../fix_stub.py
EMD_MAKER = $(CURDIR)/../../emd_maker.py

TARGET = $(notdir $(CURDIR))
OUTPUT = $(CURDIR)/$(TARGET)

SRCS = $(wildcard *.def)

ASMS = $(SRCS:.def=.S)
CS = $(SRCS:.def=.c)
EMDS = $(SRCS:.def=.emd)
OBJS = $(SRCS:.def=.c.o) $(SRCS:.def=.S.o)

STUBS = $(patsubst %.def,%_tau_stub.a,$(SRCS))
WEAK_STUBS = $(patsubst %.def,%_tau_stub_weak.a,$(SRCS))

COMMON_FLAGS = -Wall
COMMON_FLAGS += -I../../include
COMMON_FLAGS += -D__LIB__

CFLAGS = $(COMMON_FLAGS)
CFLAGS += -fno-builtin
CFLAGS += -Wno-return-type

ASFLAGS = $(COMMON_FLAGS)
ASFLAGS += -D__ASM__

.PHONY: all clean

.INTERMEDIATE: $(ASMS) $(CS) $(EMDS) $(OBJS)
.PRECIOUS: $(TARGET).map $(STUBS) $(WEAK_STUBS)

all: post-build

pre-build:

post-build: main-build

main-build: pre-build $(STUBS) $(WEAK_STUBS)

$(STUBS): $(TARGET).map
	@mv $(patsubst %_tau_stub.a,%_stub.a,$@) $@
	@$(FIX_STUB) $@

$(WEAK_STUBS): $(TARGET).map
	@mv $(patsubst %_tau_stub_weak.a,%_stub_weak.a,$@) $@
	@$(FIX_STUB) $@

$(TARGET).map: $(OBJS) $(EMDS)
	$(LD) --oformat=prx --prx-stub-output-dir=$(CURDIR) --Map=$@ -o $(TARGET).prx $^
	@rm -f $(TARGET).prx

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.S.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

%.emd %.c %.S: %.def
	@$(EMD_MAKER) $<

clean:
	@rm -f $(ASMS) $(CS) $(EMDS) $(OBJS) $(TARGET).map $(TARGET).prx $(STUBS) $(WEAK_STUBS)
