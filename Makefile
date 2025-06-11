# Имя исполняемого файла
TARGET = main

# Файлы исходников
SRC = main.c

# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -Wall -O2

# Линковка с PortAudio и math (для tanh, если нужно позже)
LDFLAGS = -lportaudio -lm

# Основная цель
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ #$(LDFLAGS)

# Удалить бинарник
clean:
	rm -f $(TARGET)
