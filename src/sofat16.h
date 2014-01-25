#ifndef SOFAT16_H
#define SOFAT16_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

typedef struct
{
    unsigned char first_byte;
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    unsigned long start_sector;
    unsigned long length_sectors;
} PartitionTable;

typedef struct
{
    unsigned char filename[8];
    unsigned char ext[3];
    unsigned char attributes;
    unsigned char reserved[10];
    unsigned short modify_time;
    unsigned short modify_date;
    unsigned short starting_cluster;
    unsigned long file_size;
} Fat16Entry;

enum EntryFlag
{
	unused = 0x00,
	deleted = 0xE5,
	directory = 0x2E
};

class FAT16Analyzer
{
	FILE *fs;

	vector<Fat16Entry> fat1;
	vector<Fat16Entry> fat2;

	void loadEntries();

public:

	FAT16Analyzer(FILE *fs);
	~FAT16Analyzer();

	void vf();
	void bl();
	void bd();
	void cf1();
	void cf2();
};

#endif