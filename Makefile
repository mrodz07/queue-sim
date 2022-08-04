default: output

output: simulation.c librands.a libmystatistics.a libmyutils.a 
	cc -Wall -Wextra -lm -lpthread $^ -g -o $@

libmyutils.a: myutils.o
	ar -rcv $@ $^

libmymath.a: mymath.o
	ar -rcv $@ $^

librands.a: rands.o
	ar -rcv $@ $^

libmystatistics.a: mystatistics.o
	ar -rcv $@ $^

.PHONY: clean
	
clean: 
	rm *.o *.a output
