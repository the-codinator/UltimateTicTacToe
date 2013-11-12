# Makefile
#

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lm

all: game bots

bot1: bot1.c gameio.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bot2: bot2.c gameio.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

bots: bot.c gameio.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	cp bots bot1
	mv bots bot2

game: engine.o gameio.o
	$(CC) $(CFLAGS) $^ -o $@

engine.o: engine.c gameio.h
	$(CC) -c $(CFLAGS) $< -o $@

gameio.o: gameio.c gameio.h o2u
	$(CC) -c $(CFLAGS) $< -o $@

swap:
	mv bot1 tmp_bot
	mv bot2 bot1
	mv tmp_bot bot2

clean:
	rm -rf bot1 bot2 tmp_bot bots
	rm -rf engine.o gameio.o
	rm -rf Board.dat
	rm -rf game

