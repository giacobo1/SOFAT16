testeme: main.o sofat16.o
	g++ -Wall -O0 main.o sofat16.o -o testeme

main.o: sofat16.h main.cpp
	g++ -c main.cpp

sofat16.o: sofat16.h sofat16.cpp
	g++ -c sofat16.cpp

clear_obj:
	rm *o

clear_exe:
	rm testeme

build_filesystem:
	dd if=/dev/zero of=disco bs=1M count=2

format_filesystem:
	mkfs.vfat -F16 disco

mount_filesystem:
	sudo mount -o disco mp
