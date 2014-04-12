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

float assignFitness(int [], float);
void makeMeABaby(float, struct subject *, int *);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	double populationSize = atoi(argv[1]);
	float target = (float)atoi(argv[2]);
	printf("Running with:\n    Population Size = %f\n    Bit Length = %d\n", populationSize, BITLENGTH);
	
	int i = 0;
	int j= 0;
	struct subject *sheep = (struct subject*)malloc(sizeof(struct subject) * populationSize);
	
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
		printf(" with fitness %f\n", sheep[i].fitness);
	}
	
	int howLongThisShitTook = 0;
	
	int solutionFound = 0;	//0 if false, 1 if true
	
	struct subject *fuckSpawn = (struct subject*)malloc(sizeof(struct subject) * populationSize);
	
	while(solutionFound != 1)
	{
		float totalFitness = 0.0f;
		
		for(i = 0; i < populationSize; i++)
		{
			sheep[i].fitness = assignFitness(sheep[i].bits, target);
			printf("subject %d with fitness %f\n", i, sheep[i].fitness);
			totalFitness += sheep[i].fitness;
			printf(" Total Fitness%f\n", totalFitness);
		}
	
		for(i = 0; i < populationSize; i++)
		{
			if(sheep[i].fitness == 999.0f)
			{
				printf("It's been found. It took %d generations to find", howLongThisShitTook);
				solutionFound = 1;
				break;
			}
		}
		
		double fuckSpawnPopulationSize = 0;
		
		int* fuckSpawn1Bits = malloc(sizeof(int) * BITLENGTH);
		int* fuckSpawn2Bits = malloc(sizeof(int) * BITLENGTH);
		
		while(fuckSpawnPopulationSize < populationSize)
		{
			makeMeABaby(totalFitness, sheep, fuckSpawn1Bits);
			makeMeABaby(totalFitness, sheep, fuckSpawn2Bits);
			fuckSpawnPopulationSize++;
		}
		
		free(fuckSpawn1Bits);
		free(fuckSpawn1Bits);
		
		
		
		
		
		if(totalFitness > 100.0f)
		{
			printf("done\n");
			return 0;
		}
	
	
	}
	
	return 0;
}

float assignFitness(int bits[], float target)
{
	return 1.0f;
}

void makeMeABaby(float totalFitness, struct subject *test, int * meh)
{
	int i = 0;
	for(i = 0; i < BITLENGTH; i++)
	{
		meh[i] = 1;
	}
}













