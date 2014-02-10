#include "sofat16.h"

FAT16Analyzer::FAT16Analyzer()
{
	fat1 = NULL;
	fat2 = NULL;
}

FAT16Analyzer::FAT16Analyzer(char *fname)
{
	this->fs = fopen(fname, "rb+");

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
	int i, bsStart;
	Fat16Entry entry;

	bsStart = 0;

	fseek(fs, bsStart, SEEK_SET);

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

	dataStart = (int)sizeof(Fat16Entry) * 512 + 0x800 + ftell(fs);

	entries.clear();

	for (i = 0; i < bs.root_dir_entries; i++)
	{
		fread(&entry, sizeof(entry), 1, fs);
		entries.push_back(entry);
	}

	fat1Start = bsStart + 0x800;
	fat2Start = fat1Start + bs.fat_size_sectors * bs.sector_size;

	loadFats();

	return 0;
}

int FAT16Analyzer::loadFats()
{
	fatSize = (fat2Start - fat1Start) / 2;

	if (fat1 == NULL) fat1 = new unsigned short[fatSize];
	if (fat2 == NULL) fat2 = new unsigned short[fatSize];

	fseek(fs, fat1Start, SEEK_SET);
	fread(fat1, sizeof(unsigned short), fatSize, fs);

	fseek(fs, fat2Start, SEEK_SET);
	fread(fat2, sizeof(unsigned short), fatSize, fs);

	return 0;
}

void FAT16Analyzer::vf()
{
	for (int i = 0; i < fatSize; i++)
	{
		if (fat1[i] != fat2[i])
		{
			printf("DIF %d:%d,%d\n", i, fat1[i], fat2[i]);
		}
	}
}

void FAT16Analyzer::bl()
{
	bool *freeBlocks = new bool[fatSize];
	bool firstComma = true;

	for (int i = 2; i < fatSize; i++)
	{
		freeBlocks[i] = true;
	}

	for (int i = 2; i < fatSize; i++)
	{
		if (fat1[i] == 0xffff) continue;
		
		freeBlocks[fat1[i]] = false;
	}

	for (int i = 0; i < (int)entries.size(); i++)
	{
		freeBlocks[entries[i].starting_cluster] = false;
	}

	printf("LIVRE ");

	for (int i = 2; i < fatSize; i++)
	{
		if (freeBlocks[i])
		{
			if (!firstComma)
			{
				printf(",");
			}
			else firstComma = false;

			printf("%d", i);
		}
	}

	printf("\n");

	delete [] freeBlocks;
}

void FAT16Analyzer::bd()
{
	
}

void FAT16Analyzer::cf1()
{
	fseek(fs, fat1Start, SEEK_SET);

	for (int i = 0; i < fatSize; i++)
	{
		fwrite(&fat2[i], sizeof(unsigned short), 1, fs);
	}
}

void FAT16Analyzer::cf2()
{
	fseek(fs, fat2Start, SEEK_SET);

	for (int i = 0; i < fatSize; i++)
	{
		fwrite(&fat1[i], sizeof(unsigned short), 1, fs);
	}
}
