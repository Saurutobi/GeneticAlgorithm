//Authors: Marcel Englmaier & Michael Sharp

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define BITLENGTH 20
#define MAXGENERATIONS 400

struct subject
{
	int bits[BITLENGTH];
	float fitness;
};

float assignFitness(int [], float);
void makeMeABaby(float, struct subject *, int &);

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
		
		unsigned long int fuckSpawnPopulationSize = 0;
		
		int fuckSpawn1Bits[BITLENGTH];
		int fuckSpawn2Bits[BITLENGTH];
		
		while(fuckSpawnPopulationSize < populationSize)
		{
			makeMeABaby(totalFitness, sheep, fuckSpawn1Bits);
			makeMeABaby(totalFitness, sheep, fuckSpawn2Bits);
			
			//crossover(1,2)
			
			//mutate 1
			//mutate 2
			
			struct subject temp;
			temp.bits = fuckSpawn1Bits;
			temp.fitness = 0.0f;
			fuckSpawn[fuckSpawnPopulationSize++] = temp;
			temp.bits = fuckSpawn2Bits;
			fuckSpawn[fuckSpawnPopulationSize++] = temp;
			
			
			
			
		}
		
		for(i = 0; i < populationSize; i++)
		{
			sheep[i] = fuckSpawn[i];
		}
		
		free(fuckSpawn1Bits);
		free(fuckSpawn2Bits);
		
		howLongThisShitTook++;
		
		if(howLongThisShitTook > MAXGENERATIONS)
		{
			printf("Did not find a solution in max allowable runs");
			solutionFound = 1;
			
		}
	}
	
	return 0;
}

float assignFitness(int bits[], float target)
{
	return 1.0f;
}

void makeMeABaby(float totalFitness, struct subject *test, int & meh)
{
	int i = 0;
	for(i = 0; i < BITLENGTH; i++)
	{
		meh[i] = 1;
	}
}













