#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

// I add new function "ifInterval" to check if the 2 object Intervals (the same us you did)
// and i changed "checkConnection" function -> new object called "tempCheck"
// "tempCheck" run from the begging of the list, to tempRun and checking color

typedef struct Interval
{
	int index;	// every Obj have a index
	int x, y;	// [x,y]
	int deg;
	int color;
	int* arrConn;	// arry of connection - if Obj connect to another there-1, else-0
	struct Interval* next;
}Interval;


void GreedyColoring();

Interval* create(int k);
void checkConnection(Interval* objInter, int k);
int getEdge(Interval* objInter, int k);
int maxDeg(Interval* objInter, int k);
int degMaxComplement(Interval* objInter, int k);
int minDeg(Interval* objInter, int k);
int degMinComplement(Interval* objInter, int k);
void printTheFamily(Interval* objInter);
int ComplementEdges(int edge, int k); //// edge from 'getEdge' function
int biggestColor(Interval* objInter, int k);
void printOptionalColoring(Interval* objInter, int k);

int ifInterval(Interval* temp, Interval* tempRun);


void main()
{
	GreedyColoring();

	system("pause");
}

void GreedyColoring()
{
	int k;
	printf("Please input k\n");
	scanf("%d", &k);

	Interval* objInter = create(k);
	checkConnection(objInter, k);

	printTheFamily(objInter);
	printf("G Edges = %d\n", getEdge(objInter, k));
	printf("Maximum Degree of G = %d\n", maxDeg(objInter, k));
	printf("Minimum Degree of G = %d\n", minDeg(objInter, k));
	printf("Chromatic Number of G = %d\n", biggestColor(objInter, k));
	printf("G`s Complement Edges = %d\n", ComplementEdges(getEdge(objInter, k), k));
	printf("Maximum Degree of G`s Complement = %d\n", degMaxComplement(objInter, k));
	printf("Minimum Degree of G`s Complement = %d\n", degMinComplement(objInter, k));
	printOptionalColoring(objInter, k);
}

Interval* create(int k)   ////input
{
	if (k == 0) exit();
	int x, y, num = k;
	int i = 0;
	Interval* objInter = (Interval*)malloc(sizeof(Interval));
	Interval* head = objInter;

	objInter->arrConn = (int*)calloc(k, sizeof(int));

	objInter->color = 1;

	objInter->next = NULL;
	objInter->index = i;

	printf("You will now be asked to enter a family of %d intervals:\n", k);
	printf("%dth Interval: ", i + 1);
	scanf(" %d %d", &x, &y);
	objInter->x = x;
	objInter->y = y;
	num--;
	i++;

	while (num != 0)
	{
		Interval* temp = (Interval*)malloc(sizeof(Interval));
		temp->next = NULL;

		temp->arrConn = (int*)calloc(k, sizeof(int));

		temp->color = 1;

		temp->index = i++;
		printf("%dth Interval: ", i);
		scanf(" %d %d", &x, &y);
		temp->x = x;
		temp->y = y;

		objInter->next = temp;
		objInter = objInter->next;
		num--;
	}

	return head;
}

void checkConnection(Interval* objInter, int k)
{
	Interval* temp = objInter;
	if (objInter == NULL)
		exit();
	if (temp->next == NULL) exit();

	Interval* tempRun = temp->next;
	Interval* tempCheck = objInter;


	while (temp)
	{
		while (tempRun)
		{
			if (ifInterval(temp, tempRun))
			{
				if (temp->color == tempRun->color)
				{
					tempRun->color++;
					while (tempCheck != tempRun)
					{
						if (ifInterval(tempCheck, tempRun))
							if (tempCheck->color == tempRun->color)
								tempRun->color++;
						tempCheck = tempCheck->next;
					}
					tempCheck = objInter;
				}
			}
			tempRun = tempRun->next;
		}
		temp = temp->next;
		if (temp->next)
			tempRun = temp->next;
		else break;
	}
}

int ifInterval(Interval* temp, Interval* tempRun)
{
	if (((temp->x >= tempRun->x && temp->x <= tempRun->y) || (temp->y >= tempRun->x && temp->y <= tempRun->y)) || ((tempRun->x >= temp->x && tempRun->x <= temp->y) || (tempRun->y >= temp->x && tempRun->y <= temp->y)))
	{
		temp->arrConn[tempRun->index] = 1;
		tempRun->arrConn[temp->index] = 1;
		return 1;
	}
	else return 0;
}

int getEdge(Interval* objInter, int k)
{
	Interval* temp = objInter;
	int i;
	int edge = 0;
	int degree = 0;

	while (temp)
	{
		for (i = 0; i < k; i++)
		{
			if (temp->arrConn[i] == 1)
			{
				edge += temp->arrConn[i];
				degree++;
			}
		}
		temp->deg = degree;
		degree = 0;
		temp = temp->next;
	}
	return (edge / 2);
}

int maxDeg(Interval* objInter, int k)
{
	Interval* temp = objInter;
	int max = temp->deg;
	temp = temp->next;
	while (temp)
	{
		if (max < temp->deg)
			max = temp->deg;
		temp = temp->next;
	}
	return max;
}

int degMaxComplement(Interval* objInter, int k)
{
	return k - 1 - minDeg(objInter, k);
}

int minDeg(Interval* objInter, int k)
{
	Interval* temp = objInter;
	int min = temp->deg;
	temp = temp->next;
	while (temp)
	{
		if (min > temp->deg)
			min = temp->deg;
		temp = temp->next;
	}
	return min;
}

int degMinComplement(Interval* objInter, int k)
{
	return k - 1 - maxDeg(objInter, k);
}

void printTheFamily(Interval* objInter)
{
	Interval* temp = objInter;
	printf("The Intervals family is:\n");
	while (temp)
	{
		printf("[%d,%d]", temp->x, temp->y);
		if (temp->next != NULL)
			printf(",");
		temp = temp->next;
	}
	printf("\n");
}

int ComplementEdges(int edge, int k)
{
	return ((k - 1) * (k - 1) - edge) / 2;
}

int biggestColor(Interval* objInter, int k)
{
	Interval* temp = objInter;
	int max = temp->color;
	temp = temp->next;
	while (temp)
	{
		if (max < temp->color)
			max = temp->color;
		temp = temp->next;
	}
	return max;
}

void printOptionalColoring(Interval* objInter, int k)
{
	printf("Optional Coloring: ");
	Interval* temp = objInter;
	int color = biggestColor(objInter, k);
	int i;

	int boll = 0;

	for (i = 1; i <= color; i++)
	{
		printf("{");
		while (temp)
		{
			if (temp->color == i)
			{
				printf("[%d,%d]", temp->x, temp->y);
				temp = temp->next;
				boll = 1;
			}
			else temp = temp->next;
		}
		if (boll)
			printf("} = %d", i);
		if (i + 1 <= color)
			printf(", ");
		boll = 0;
		temp = objInter;
	}
	printf("\n");
}
