CC = gcc
CFLAGS = -Wall -Wextra
TARGET = texteditor
INSTALL_DIR = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): main.c
    $(CC) $(CFLAGS) $^ -o $@

clean:
    rm -f $(TARGET)

install: $(TARGET)
    mkdir -p $(INSTALL_DIR)
    cp $(TARGET) $(INSTALL_DIR)
    chmod +x $(INSTALL_DIR)/$(TARGET)

uninstall:
    rm -f $(INSTALL_DIR)/$(TARGET)
