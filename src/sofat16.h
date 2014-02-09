
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

typedef struct
{
    unsigned char jmp[3];
    unsigned char oem[8];
    unsigned short sector_size;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short total_sectors_short; // if zero, later field is used
    unsigned char media_descriptor;
    unsigned short fat_size_sectors;
    unsigned short sectors_per_track;
    unsigned short number_of_heads;
    unsigned long hidden_sectors;
    unsigned long total_sectors_long;

    unsigned char drive_number;
    unsigned char current_head;
    unsigned char boot_signature;
    unsigned long volume_id;
    char volume_label[11];
    char fs_type[8];
    char boot_code[448];
    unsigned short boot_sector_signature;
} Fat16BootSector;

class FAT16Analyzer
{
    FILE *fs;

    unsigned short *fat1;
    unsigned short *fat2;

    int fat1Start;
	int fat2Start;

    vector<Fat16Entry> entries;

    int loadEntries();
    int loadFats();

public:

    FAT16Analyzer();
    FAT16Analyzer(char *fname);
    ~FAT16Analyzer();

    void vf();
    void bl();
    void bd();
    void cf1();
    void cf2();
};

#endif