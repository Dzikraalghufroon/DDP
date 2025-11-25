TARGET = main

CC = gcc
CFLAGS = -Wall -Wextra -Icontroller -Imodel -Iview -Iutils

SRC = \
    main.c posAnggaran.c ui.c utils.c transaksi.c rekapitulasi.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
