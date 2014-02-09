#include "sofat16.h"


int main(int argc, char *argv[])
{

	if(argc == 2)
	{
		if ("-vf" == string(argv[1]))
		{
			FAT16Analyzer fsys("disco");
			fsys.vf();
		}
		else if ("-bl" == string(argv[1]))
		{
			FAT16Analyzer fsys("disco");
			fsys.bl();

		}
		else if ("-bd" == string(argv[1]))
		{
			FAT16Analyzer fsys("disco");
			fsys.bd();

		}
		else if ("-cf1" == string(argv[1]))
		{
			FAT16Analyzer fsys("disco");
			fsys.cf1();

		}
		else if ("-cf2" == string(argv[1]))
		{
			FAT16Analyzer fsys("disco");
			fsys.cf2();
		}
		else
		{
			printf("Argumento invalido.\n");
			exit(1);		
		}

		exit(EXIT_SUCCESS);	
	
	}
	else
	{
		printf("Numero insuficiente de parametros.\n");
		exit(1);
	}
	
}