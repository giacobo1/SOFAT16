testeme: main.o sofat16.o
	g++ -Wall -O3 main.o sofat16.o -o testeme

main.o: sofat16.h main.cpp
	g++ -c main.cpp

sofat16.o: sofat16.h sofat16.cpp
	g++ -c sofat16.cpp

clear_obj:
	rm *o

clear_exe:
	rm testeme
clear_tester:
	rm sf16_tester

build_tester:
	g++ sofat16_tester.cpp -o sf16_tester

build_filesystem:
	dd if=/dev/zero of=disco bs=512 count=65536

format_filesystem:
	mkfs.msdos -F 16 disco

mount_filesystem:
	sudo mount disco mp_sofat16

umount_filesystem:
	sudo umount mp_sofat16
