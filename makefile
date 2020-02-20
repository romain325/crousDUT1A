/***********************makefile*****************************/
CC       = gcc
CFLAGS   = -Wall
LDFLAGS  = 
OBJFILES = lectOuv.o list.o tri.o crous.o main.o
TARGET   = gestion_crous

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
