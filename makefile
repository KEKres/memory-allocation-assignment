.default: all

PROGRAMS=firstfit bestfit

all: $(PROGRAMS)

clean:
	rm -rf $(PROGRAMS) *.o *.dSYM

firstfit: firstfit.o main.o
	g++ -Wall -Werror -std=c++20 -g -o $@ $^

bestfit: bestfit.o main.o
	g++ -Wall -Werror -std=c++20 -g -o $@ $^
