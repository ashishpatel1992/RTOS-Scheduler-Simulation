SOURCE	= scheduler_driver.c
OUT	= scheduler.out
CC	 = gcc
FLAGS	 = -lm
LFLAGS	 = 

scheduler_driver:scheduler_driver.c
	$(CC)  $(SOURCE) -o $(OUT) $(FLAGS)

clean:
	rm -f $(OBJS) $(OUT)