.PHONY: clean all                                               

all : test

test : thread.o main.o cond.o
	    gcc $^ -o $@ -lpthread

%.o : %.c 
	    gcc -c $^ -o $@

clean:
	    rm -rf *.o 
