SRCS = $(wildcard ./*/*.c)
CC = avr-gcc
PROGS = $(patsubst %.c,%,$(SRCS))
FLAGS = -std=c11 -Os -DBAUD=9600 -DF_CPU=16000000UL -mmcu=atmega328p

all: $(PROGS)

%: %.c
		$(CC) $(FLAGS) -o $@ $<
clean: 
		rm -f $(PROGS)
