//Authors: Marcel Englmaier & Michael Sharp

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define BITLENGTH 20

struct subject
{
	int bits[BITLENGTH];
	float fitness;
};

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int populationSize = atoi(argv[1]);
	printf("Running with:\n    Population Size = %d\n    Bit Length = %d\n", populationSize, BITLENGTH);
	
	int i = 0;
	int j= 0;
	struct subject sheep[populationSize];
	
	//make the Adam&Eve generation
	for(i = 0; i < populationSize; i++)
	{
		for(j = 0; j < BITLENGTH; j++)
		{
			sheep[i].bits[j] = rand() %2;
		}
		sheep[i].fitness = 0.0f;
		printf("subject %d bits = ", i);
		for(j = 0; j < BITLENGTH; j++)
		{
			printf("%d", sheep[i].bits[j]);
		}
		printf(" with fitness %f\n", i, sheep[i].bits, sheep[i].fitness);
	}
	
	
	
	
	
	
	
	return 0;
}





