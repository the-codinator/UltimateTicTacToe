# Makefile
#

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lm

all: engine bots

bot1: bot1.c gameio.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bot2: bot2.c gameio.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

bots: bot.c gameio.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	cp bots bot1
	mv bots bot2

engine: engine.c gameio.h
	$(CC) $(CFLAGS) $< -o $@

swap:
	mv bot1 .tmp_bot
	mv bot2 bot1
	mv .tmp_bot bot2

clean:
	rm -rf bot1
	rm -rf bot2
	rm -rf engine
	rm -rf Board.dat

