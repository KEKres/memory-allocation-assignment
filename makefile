

all: firstfit bestfit

firstfit: firstfit.cpp
    g++ -Wall -Werror -std=c++20 -o firstfit main.cpp firstfit.cpp

bestfit: bestfit.cpp
    g++ -Wall -Werror -std=c++20 -o bestfit main.cpp bestfit.cpp

clean:
    rm -f firstfit bestfit *.dSYM
