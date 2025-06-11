# Переменные
TARGET = main
SOURCES = main.c
CFLAGS = -Wall -O2
LIBS = -lportaudio -lm

# Объявляем цели как фиктивные (не файлы)
.PHONY: all clean rebuild

# Основная цель - всегда пересобирать
all: rebuild

# Обычная сборка (с проверкой зависимостей)
$(TARGET): $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

# Принудительная пересборка
rebuild: clean $(TARGET)

# Удаление бинарника
clean:
	rm -f $(TARGET)