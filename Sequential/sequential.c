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

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int populationSize = atoi(argv[1]);
	float target = (float)atoi(argv[2]);
	printf("Running with:\n    Population Size = %d\n    Bit Length = %d\n", populationSize, BITLENGTH);
	
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
	
	while(solutionFound != 1)
	{
		float totalFitness = 0.0f;
		
		for(i = 0; i < populationSize; i++)
		{
			sheep[i].fitness = assignFitness(sheep[i].bits, target);
			//printf("subject %d with fitness %f\n", i, sheep[i].fitness);
			totalFitness += sheep[i].fitness;
			//printf(" Total Fitness%f\n", totalFitness);
			
			
			
			
			
			
			
			
		}
	
	
	
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















