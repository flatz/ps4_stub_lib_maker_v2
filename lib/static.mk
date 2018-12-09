WINE = wine
WINE_PATH_TOOL = winepath

CC = $(WINE) orbis-clang
AR = $(WINE) orbis-ar

TARGET = $(notdir $(CURDIR))
OUTPUT = $(CURDIR)/$(TARGET)

OBJS = $(patsubst %.c,%.c.o,$(wildcard *.c)) $(patsubst %.S,%.S.o,$(wildcard *.S))

COMMON_FLAGS = -Wall
COMMON_FLAGS += -I../../include
COMMON_FLAGS += -D__LIB__

CFLAGS = $(COMMON_FLAGS)

ASFLAGS = $(COMMON_FLAGS)
ASFLAGS += -D__ASM__

.PHONY: all clean

all: post-build

pre-build:

post-build: main-build

main-build: pre-build $(TARGET).a

$(TARGET).a: $(OBJS)
	$(AR) rcs $@ $^

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.S.o: %.S
	$(CC) $(ASFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET).a
