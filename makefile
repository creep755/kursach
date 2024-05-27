# Название исполняемого файла
TARGET = speech-recognizer

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -lasound -L

# Исходные файлы
SOURCES = main.c record_audio.c recognition.c
HEADERS = record_audio.h recognition.h vosk_api.h

# Цель по умолчанию
all: $(TARGET)

# Компиляция
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Очистка
clean:
	rm -f $(TARGET)