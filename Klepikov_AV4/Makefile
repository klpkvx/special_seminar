FLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Wcast-qual -Wno-suggest-attribute=format

OPT = -O3

CC = g++

all:  a01.out a02.out a03.out a04.out a05.out a06.out
%.o: %.c
	${CC} -c ${FLAGS} ${OPT}  $<

%.out: %.o tasks.o func.o
	${CC} $^ -o  $@ -lm

clean:
	rm -f *.out *.o *.d