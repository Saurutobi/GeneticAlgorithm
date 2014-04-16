//Authors: Marcel Englmaier & Michael Sharp

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>


#define BITLENGTH 20
#define GENELENGTH 4
#define MAXGENERATIONS 2
#define CROSSOVERRATE 0.7
#define MUTATIONRATE 0.001

#define debug 1

struct subject
{
	int bits[BITLENGTH];
	float fitness;
};

struct timeval start;
struct timeval end;

float AssignFitness(int [], float);
int BinToDec(int[]);
int ParseBits(int[] , int *);
void Crossover(int *, int *);
void MakeMeABaby(float, double, struct subject *, int *);
void Mutate(int *);
void PrintChromo(int[]);
void PrintGeneSymbol(int);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	double populationSize = atoi(argv[1]);
	float target = (float)atoi(argv[2]);
	printf("Running with:\n    Population Size = %.0f\n    Bit Length = %d\n", populationSize, BITLENGTH);
	
	long int i = 0;
	int j = 0;
	struct subject *sheep = (struct subject*)malloc(sizeof(struct subject) * populationSize);
	
	gettimeofday(&start, NULL);
	
	//make the Adam&Eve generation
	for(i = 0; i < populationSize; i++)
	{
		if(debug == 0)
		{
			printf("subject %d bits = ", i);
		}
		for(j = 0; j < BITLENGTH; j++)
		{
			sheep[i].bits[j] = rand() %2;
			if(debug == 0)
			{
				printf("%d", sheep[i].bits[j]);
			}
		}
		sheep[i].fitness = 0.0f;
		if(debug == 0)
		{
			printf(" with fitness %f\n", sheep[i].fitness);
		}
	}
	
	int howLongThisShitTook = 0;
	
	int solutionFound = 0;	//0 if false, 1 if true
	
	struct subject *fuckSpawn = (struct subject*)malloc(sizeof(struct subject) * populationSize);
	
	while(solutionFound != 1)
	{
		float totalFitness = 0.0f;
		
		for(i = 0; i < populationSize; i++)
		{
			sheep[i].fitness = AssignFitness(sheep[i].bits, target);
			if(debug == 0)
			{
				printf("\n subject %d with fitness %f\n", i, sheep[i].fitness);
			}
			totalFitness += sheep[i].fitness;
			if(debug == 0)
			{
				printf(" Total Fitness%f\n", totalFitness);
			}
		}
	
		for(i = 0; i < populationSize; i++)
		{
			if(sheep[i].fitness == 999.0f)
			{
				printf("It's been found. It took %d generations to find\n", howLongThisShitTook);
				solutionFound = 1;
				break;
			}
		}
		
		long fuckSpawnPopulationSize = 0;
		
		int fuckSpawn1Bits[BITLENGTH];
		int fuckSpawn2Bits[BITLENGTH];
		if(solutionFound != 1)
		{
			printf("Creating New Generation\n");
			while(fuckSpawnPopulationSize < populationSize)
			{
				MakeMeABaby(totalFitness, populationSize, sheep, fuckSpawn1Bits);
				MakeMeABaby(totalFitness, populationSize, sheep, fuckSpawn2Bits);
				
				Crossover(fuckSpawn1Bits, fuckSpawn2Bits);
				
				Mutate(fuckSpawn1Bits);
				Mutate(fuckSpawn2Bits);
			
				for(i = 0; i < BITLENGTH; i++)
				{
					fuckSpawn[fuckSpawnPopulationSize].bits[i] = fuckSpawn1Bits[i];
					fuckSpawn[fuckSpawnPopulationSize + 1].bits[i] = fuckSpawn2Bits[i];
				}
				
				if(debug == 0)
				{
					printf("fuckspawn%d: ", fuckSpawnPopulationSize);
					for(i = 0; i < BITLENGTH; i++)
					{
						printf("%d", fuckSpawn[fuckSpawnPopulationSize].bits[i]);
					}
					printf("\nfuckspawn%d: ",fuckSpawnPopulationSize + 1);
					for(i = 0; i < BITLENGTH; i++)
					{
						printf("%d", fuckSpawn[fuckSpawnPopulationSize + 1].bits[i]);
					}
					printf("\n");
				}
				fuckSpawn[fuckSpawnPopulationSize].fitness = 0.0f;
				fuckSpawn[fuckSpawnPopulationSize + 1].fitness = 0.0f;
				fuckSpawnPopulationSize += 2;
			}
			
			for(i = 0; i < populationSize; i++)
			{
				sheep[i] = fuckSpawn[i];
			}
			
			howLongThisShitTook++;
			printf("New Generation done! Now on Generation %d\n", howLongThisShitTook);
		}
		
		if(howLongThisShitTook > MAXGENERATIONS)
		{
			printf("Did not find a solution in maximum allowable runs\n");
			solutionFound = 1;
		}
	}
	
	gettimeofday(&end, NULL);
	int timeran = (((end.tv_sec - start.tv_sec) * 1000000) +(end.tv_usec - start.tv_usec));
	printf("Completed in %d Nano Seconds\n", timeran);
	
	return 0;
}

int	BinToDec(int bits[])
{
	int val = 0;
	int valueToAdd = 1;
	int k = 0;
	for(k = GENELENGTH - 1; k >= 0; k--)
	{
		if(debug == 0)
		{
			printf("k=%d ", bits[k]);
		}
		if(bits[k] == 1)
		{
			val += valueToAdd;
		}
		valueToAdd *= 2;
	}
	return val;
}

int ParseBits(int bits[], int* buffer)
{
	int counterBuffer = 0;
	int operator = 1;
	int currentGene = 0;
	int i = 0;
	for(i = 0; i < BITLENGTH; i += GENELENGTH)
	{
		currentGene = BinToDec(&bits[i]);
		if(debug == 0)
		{
			printf("this gene %d \n", currentGene);
		}
		if(operator == 1)
		{
			if((currentGene < 10) || (currentGene > 13))
			{
				continue;
			}
			else
			{
				operator = 0;
				buffer[counterBuffer++] = currentGene;
				continue;
			}
		}
		else
		{
			if (currentGene > 9)
			{
				continue;
			}
			else
			{
				operator = 1;
				buffer[counterBuffer++] = currentGene;
				continue;
			}
		}
	}
	
	for(i = 0; i < counterBuffer; i++)
	{
		if((buffer[i] == 13) && (buffer[i + 1] == 0))
		{
			buffer[i] = 10;
		}
	}

	return counterBuffer;
}
	
float AssignFitness(int bits[], float target)
{
	int buffer[(int)(BITLENGTH / GENELENGTH)];
	int numberOfElements = ParseBits(bits, buffer);
	float result = 0.0f;
	
	int i;
	for(i = 0; i < numberOfElements - 1; i += 2)
	{
		switch (buffer[i])
		{
			case 10:
				result += buffer[i + 1];
				break;
			case 11:
				result -= buffer[i + 1];
				break;
			case 12:
				result *= buffer[i + 1];
				break;
			case 13:
				result /= buffer[i + 1];
				break;
			default:
				break;
		}
	}

	if(debug == 0)
	{
		printf("\n result %f \n", result); 
	}
	if(result == (float)target)
	{
		return 999.0f;
	}
	else
	{
		return 1/(float)fabs((double)(target - result));
	}
}

void PrintChromo(int bits[])
{
	printf("I AM PRINTCHROMO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	int buffer[(int)(BITLENGTH / GENELENGTH)];
	int numberOfElements = ParseBits(bits, buffer);
	int p;
	for(p = 0; p < numberOfElements; p++)
	{
		PrintGeneSymbol(buffer[p]);
	}
}

void PrintGeneSymbol(int val)
{
	switch(val)
	{
	case 10:
		printf("+");
		break;
	case 11:
		printf("-");
		break;
	case 12:
		printf("*");
		break;
	case 13:
		printf("/");
		break;
	default:
		printf("%d", val);
		break;
	}
}		

void Crossover(int * first, int * second)
{
	double random = (double)rand() / (double)RAND_MAX;
	if(random < CROSSOVERRATE)
	{
		random = (double)rand() / (double)RAND_MAX;
		int crossOver = (int)(random * BITLENGTH);
		int i = 0;
		for(i = crossOver; i < BITLENGTH; i++)
		{
			int temp = second[i];
			first[i] = second[i];
			second[i] = temp;
		}
	}
}

void Mutate(int * doMe)
{
	int i = 0;
	for(i = 0; i < BITLENGTH; i++)
	{
		double random = (double)rand() / (double)RAND_MAX;
		if(random < MUTATIONRATE && doMe[i] == 0)
		{
			doMe[i] = 1;
		}
		else if(random < MUTATIONRATE && doMe[i] == 1)
		{
			doMe[i] = 0;
		}
	}
}

void MakeMeABaby(float totalFitness, double popSize, struct subject *test, int * meh)
{
	double random = (double)rand() / (double)(RAND_MAX - 1);
	float slice = (float)(random * totalFitness);
	float currentFitness = 0.0f;
	
	int i = 0;
	for(i = 0; i < popSize; i++)
	{
		currentFitness += test[i].fitness;
		if(currentFitness >= slice)
		{
			int j;
			if(debug == 0)
			{
				printf("\nfit parent found\n");
			}
			for(j = 0; j < BITLENGTH; j++)
			{
				if(debug == 0)
				{
					printf("%d", test[i].bits[j]);
				}
				meh[j] = test[i].bits[j];
			}
			if(debug == 0)
			{
				printf("\n");
			}
			break;
		}
		else
		{
			if(debug == 0)
			{
				printf(" %dUnfit Parent found", i);
			}
		}
	}
}
