#include "sofat16.h"

FAT16Analyzer::FAT16Analyzer()
{
	fat1 = NULL;
	fat2 = NULL;
}

FAT16Analyzer::FAT16Analyzer(char *fname)
{
	this->fs = fopen(fname, "rb");
	
	if (fs == NULL)
	{
		printf("Erro ao abrir o arquivo com o sistema de arquivo.\n\n");
		exit(1);
	}

	fat1 = NULL;
	fat2 = NULL;

	loadEntries();
}

FAT16Analyzer::~FAT16Analyzer()
{
	fclose(fs);
}

int FAT16Analyzer::loadEntries()
{
	int i, bsStart, fat1Start, fat2Start;
    PartitionTable pt[4];
	Fat16BootSector bs;
    Fat16Entry entry;

	if (fs == NULL)
	{
		printf("Disc not found!\n");
        return -1;
	}
    
    fseek(fs, 0x1BE, SEEK_SET);
    fread(pt, sizeof(PartitionTable), 4, fs);
    
    for (i = 0; i < 4; i++)
	{        
        if(pt[i].partition_type == 4 || pt[i].partition_type == 6 || pt[i].partition_type == 14)
		{
            break;
        }
    }
    
    if (i == 4)
	{
        printf("No FAT16 filesystem found, exiting...\n");
        return -1;
    }

	bsStart = 512 * pt[i].start_sector;

	fseek(fs, bsStart, SEEK_SET);
    //fread(&bs, sizeof(Fat16BootSector), 1, fs);

	fread(&bs.jmp, sizeof(unsigned char), 3, fs);
	fread(&bs.oem, sizeof(unsigned char), 8, fs);
	fread(&bs.sector_size, sizeof(unsigned short), 1, fs);
	fread(&bs.sectors_per_cluster, sizeof(unsigned char), 1, fs);
	fread(&bs.reserved_sectors, sizeof(unsigned short), 1, fs);
	fread(&bs.number_of_fats, sizeof(unsigned char), 1, fs);
	fread(&bs.root_dir_entries, sizeof(unsigned short), 1, fs);
	fread(&bs.total_sectors_short, sizeof(unsigned short), 1, fs);
	fread(&bs.media_descriptor, sizeof(unsigned char), 1, fs);
	fread(&bs.fat_size_sectors, sizeof(unsigned short), 1, fs);
	fread(&bs.sectors_per_track, sizeof(unsigned short), 1, fs);
	fread(&bs.number_of_heads, sizeof(unsigned short), 1, fs);
	fread(&bs.hidden_sectors, sizeof(unsigned long), 1, fs);
	fread(&bs.total_sectors_long, sizeof(unsigned long), 1, fs);
	fread(&bs.drive_number, sizeof(unsigned char), 1, fs);
	fread(&bs.current_head, sizeof(unsigned char), 1, fs);
	fread(&bs.boot_signature, sizeof(unsigned char), 1, fs);
	fread(&bs.volume_id, sizeof(unsigned long), 1, fs);
	fread(&bs.volume_label, sizeof(char), 11, fs);
	fread(&bs.fs_type, sizeof(char), 8, fs);
	fread(&bs.boot_code, sizeof(char), 448, fs);
	fread(&bs.boot_sector_signature, sizeof(unsigned short), 1, fs);

	fseek(fs, (bs.reserved_sectors - 1 + bs.fat_size_sectors * bs.number_of_fats) * bs.sector_size, SEEK_CUR);

	entries.clear();

	for (i = 0; i < bs.root_dir_entries; i++)
	{
        fread(&entry, sizeof(entry), 1, fs);
		entries.push_back(entry);
    }

	fat1Start = bsStart + 1024;
	fat2Start = fat1Start + bs.fat_size_sectors * bs.sector_size;

	loadFats(fat1Start, fat2Start);

	return 0;
}

int FAT16Analyzer::loadFats(int fat1Start, int fat2Start)
{
	if (fs == NULL)
	{
		printf("Disc not found!\n");
        return -1;
	}

	if (fat1 == NULL) fat1 = new unsigned short[65536];
	if (fat2 == NULL) fat2 = new unsigned short[65536];

	fseek(fs, fat1Start, SEEK_SET);
	fread(fat1, sizeof(unsigned short), 65536, fs);

	unsigned short test;

	test = fat1[0];
	test = fat1[1];
	test = fat1[2];

	fseek(fs, fat2Start, SEEK_SET);
	fread(fat2, sizeof(unsigned short), 65536, fs);

	return 0;
}

void FAT16Analyzer::vf()
{

}

void FAT16Analyzer::bl()
{

}

void FAT16Analyzer::bd()
{

}

void FAT16Analyzer::cf1()
{

}

void FAT16Analyzer::cf2()
{

}
