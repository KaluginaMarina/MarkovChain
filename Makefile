MarkovChain: main.c mindless_machine.c mindless_machine.h chain.c chain.h
	gcc -o MarkovChain -std=c11 -Wall -Werror	main.c mindless_machine.c mindless_machine.h chain.c chain.h
