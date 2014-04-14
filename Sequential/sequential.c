//Authors: Marcel Englmaier & Michael Sharp

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define BITLENGTH 20
#define GENELENGTH 4
#define MAXGENERATIONS 400

struct subject
{
	int bits[BITLENGTH];
	float fitness;
};

float assignFitness(int [], float);
void makeMeABaby(float, struct subject *, int &);
int binToDec(int bits[]);
int parseBits(int bits[], int* buffer);
void printGeneSymbol(int val);
void printChromo(int bits[]);

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
		
		// unsigned long int fuckSpawnPopulationSize = 0;
		
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

int	binToDec(int bits[])
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
	printf("counterBuffer %d \n", counterBuffer);
	return counterBuffer;
}
	
float assignFitness(int bits[], float target)
{
	//holds decimal values of gene sequence
	int buffer[(int)(BITLENGTH / GENELENGTH)];
	
	int num_elements = ParseBits(bits, buffer);
	printf("new element %d \n",num_elements);
	// ok, we have a buffer filled with valid values of: operator - number - operator - number..
	// now we calculate what this represents.
	float result = 0.0f;
	int n;
	for ( n=0; n < num_elements-1; n+=2)
	{
		switch (buffer[n])
		{
			case 10:

				result += buffer[n+1];
				break;

			case 11:
				
				result -= buffer[n+1];
				break;

			case 12:

				result *= buffer[n+1];
				break;

			case 13:
	
				result /= buffer[n+1];
				break;

		}//end switch

	}

	// Now we calculate the fitness. First check to see if a solution has been found
	// and assign an arbitarily high fitness score if this is so.

	printf("\n result %d \n", result); 
	if (result == (float)target)

		return 999.0f;

	else

		return 1/(float)fabs((double)(target - result));
	//	return result;
}
void PrintChromo(int bits[])
{	
	//holds decimal values of gene sequence
	int buffer[(int)(BITLENGTH / GENELENGTH)];
	
	//parse the bit string
	int num_elements = ParseBits(bits, buffer);
	int p;
	for ( p=0; p<num_elements; p++)
  {
		PrintGeneSymbol(buffer[p]);
  }

	return;
}

void PrintGeneSymbol(int val)
{
	if (val < 10 )
		
		printf("%d", val);
	
	else
	{
		switch (val)
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
			
		}//end switch
}
return;
}		

void makeMeABaby(float totalFitness, struct subject *test, int & meh)
{
	int i = 0;
	for(i = 0; i < BITLENGTH; i++)
	{
		meh[i] = 1;
	}
}













