#Desmond Hui  - Assignment 1
#ID: 3152710
CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lm -lc -lncurses -ltinfo
APP = App
$(APP): main.o player.o splash_art.o level_test.o
	 $(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
.PHONY:
clean:
	rm -f *.o $(APP)
run: $(APP)
	./$(APP)
