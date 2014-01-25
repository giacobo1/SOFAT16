testeme: main.o sofat16.o
	g++ -Wall -O0 main.o sofat16.o -o testeme

main.o: sofat16.h main.cpp
	g++ -c main.cpp

sofat16.o: sofat16.h sofat16.cpp
	g++ -c sofat16.cpp

clear_obj:
	rm *o