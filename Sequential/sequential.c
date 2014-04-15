//Authors: Marcel Englmaier & Michael Sharp

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


#define BITLENGTH 20
#define GENELENGTH 4
#define MAXGENERATIONS 4
#define CROSSOVERRATE 0.7
#define MUTATIONRATE 0.001

struct subject
{
	int bits[BITLENGTH];
	float fitness;
};

float AssignFitness(int [], float);
int BinToDec(int[]);
int ParseBits(int[] , int* );
void CrossOver(int[], int[]);
void MakeMeABaby(float, double, struct subject *, int[]);
void Mutate(int[]);
void PrintChromo(int[]);
void PrintGeneSymbol(int);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	double populationSize = atoi(argv[1]);
	float target = (float)atoi(argv[2]);
	printf("Running with:\n    Population Size = %f\n    Bit Length = %d\n", populationSize, BITLENGTH);
	
	long int i = 0;
	int j = 0;
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
			sheep[i].fitness = AssignFitness(sheep[i].bits, target);
			printf("\n subject %d with fitness %f\n", i, sheep[i].fitness);
			PrintChromo(sheep[i].bits);
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
		
		long fuckSpawnPopulationSize = 0;
		
		int fuckSpawn1Bits[BITLENGTH];
		int fuckSpawn2Bits[BITLENGTH];
		
		while(fuckSpawnPopulationSize < populationSize)
		{
			MakeMeABaby(totalFitness, populationSize, sheep, fuckSpawn1Bits);
			MakeMeABaby(totalFitness, populationSize, sheep, fuckSpawn2Bits);
			
			//crossover(fuckSpawn1Bits, fuckSpawn2Bits);
			
			//Mutate(fuckSpawn1Bits);
			//Mutate(fuckSpawn2Bits);
			
			for(i = 0; i < BITLENGTH; i++)
			{
				sheep[fuckSpawnPopulationSize].bits[i] = fuckSpawn1Bits[i];
				sheep[fuckSpawnPopulationSize + 1].bits[i] = fuckSpawn1Bits[i];
			}
			fuckSpawn[fuckSpawnPopulationSize].fitness = 0.0f;
			fuckSpawn[fuckSpawnPopulationSize + 1].fitness = 0.0f;
			fuckSpawnPopulationSize += 2;
			// struct subject temp;
			// temp.bits = fuckSpawn1Bits;
			// temp.fitness = 0.0f;
			// fuckSpawn[fuckSpawnPopulationSize++] = temp;
			// temp.bits = fuckSpawn2Bits;
			// fuckSpawn[fuckSpawnPopulationSize++] = temp;
		}
		
		for(i = 0; i < populationSize; i++)
		{
			sheep[i] = fuckSpawn[i];
		}
		
		howLongThisShitTook++;
		
		if(howLongThisShitTook > MAXGENERATIONS)
		{
			printf("Did not find a solution in max allowable runs");
			solutionFound = 1;
		}
	}
	
	return 0;
}

int	BinToDec(int bits[])
{
	int val = 0;
	int valueToAdd = 1;
	int k = 0;
	for(k = GENELENGTH - 1; k >= 0; k--)
	{

		printf("k=%d ", bits[k]);
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
	int l = 0;
	for(l = 0; l < BITLENGTH; l += GENELENGTH)
	{
		currentGene = BinToDec(&bits[l]);
		printf("this gene %d \n", currentGene);
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
	
	int m;
	for(m = 0; m < counterBuffer; m++)
	{
		if((buffer[m] == 13) && (buffer[m + 1] == 0))
		{
			buffer[m] = 10;
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

	printf("\n result %f \n", result); 
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

void Crossover(int first[], int second[])
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

void Mutate(int doMe[])
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

void MakeMeABaby(float totalFitness, double popSize, struct subject *test, int meh[])
{
	double random = (double)rand() / (double)RAND_MAX;
	float slice = (float)(random * totalFitness);
	float currentFitness = 0.0f;
	
	int i = 0;
	for(i = 0; i < popSize; i++)
	{
		currentFitness += test[i].fitness;
		
		if(currentFitness >= slice)
		{
			meh = test[i].bits;
		}
	}
}













