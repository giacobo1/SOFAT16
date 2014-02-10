#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>

int main(int argc, char const *argv[])
{

	if(argc == 2)
	{
		if ("-bd" == std::string(argv[1]))
		{
			FILE *fs;

			if((fs = fopen("mp_sofat16/removed.txt","w+")) == NULL)exit(1);
			for(int i = 0; i < 4*2048; i++)fprintf(fs, "%c",'A');
			fclose(fs);

			if((fs = fopen("mp_sofat16/removed.txt","w+")) == NULL)exit(1);
			for(int i = 0; i < 3*2048; i++)fprintf(fs, "%c",'A');
			fclose(fs);
		}
		else if ("-cf1" == std::string(argv[1]))
		{
			
			srand(time(NULL));

			int fat2Start = 0x800;

			FILE *fs;

			if((fs = fopen("disco","rb+")) == NULL)exit(1);

			printf("Corrompendo a primeira FAT.\n");
			fseek(fs,fat2Start,SEEK_SET);
			for(int i = 0; i < sizeof(unsigned short) * 10; i++)fprintf(fs,"%d",(unsigned short)rand() % 10);
			

			fclose(fs);

		}
		else if ("-cf2" == std::string(argv[1]))
		{

			srand(time(NULL));

			int fat2Start = 0x8800;

			FILE *fs;

			if((fs = fopen("disco","rb+")) == NULL)exit(1);

			printf("Corrompendo a Copia da FAT.\n");
			fseek(fs,fat2Start,SEEK_SET);
			for(int i = 0; i < sizeof(unsigned short) * 10; i++)fprintf(fs,"%d",(unsigned short)rand() % 10);
			
			fclose(fs);
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


	return 0;
}