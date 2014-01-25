#include "sofat16.h"

FAT16Analyzer::FAT16Analyzer(FILE *fs)
{
	this->fs = fs;

	fopen(fs, "rb");

	if (fs == NULL)
	{
		printf("Erro ao abrir o arquivo com o sistema de arquivo.\n\n");
		exit(1);
	}

	loadEntries();
}

FAT16Analyzer::~FAT16Analyzer()
{
	fclose(fs);
}

void FAT16Analyzer::loadEntries()
{
	
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
