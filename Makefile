
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
LDFLAGS = -lm

all: Hangman.exe
	./Hangman.exe

#
# Das Rezept baut jetzt keine fertigen ausfuehrbaren (EXE) Dateien mehr.
# Es wird eine Vorstufe, eine sogenannte Objekt-Datei aus dem C Quellcode
# erstellt.  In einer Objekt-Datei ist der C Code bereits kompiliert und
# kann einer EXE-Datei zugefuegt werden (LINKER).
#
%.o:%.c printHang.h
	$(CC) $(CFLAGS) -c -o $@ $<

#
# Jetzt muss genau gesagt werden, welche vorkompilierten Objekt-Dateien fuer
# die EXE-Datei notwendig sind und einen entsprechenden Kompilieraufruf geben.
#
Hangman.exe: Hangman.c printHang.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
