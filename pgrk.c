/* YINXIA LI cs610 2705 prp */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int* OutDegNode2705(int** mat,int edgeNo,int vertexNo);
void initValue2705(int val, int vertexNo, float* pgrkCur, float* pgrkPrev);
float eRate2705(int iteration);//, float errorRate);
void printFirstLine2705(int vertexNo, float *pgrkPrev);
void printForLessThanTen2705(int vertexNo, int iterNo, float *pgrkCur);
void printForMoreThanTen2705(int vertexNo, int iterNo, float *pgrkCur);
int**  Matrix2705(int vertexNo);

int main(int argc, char *argv[])
{
    int * outDegree;
    int** mat;
    int i, j, v1, v2, vertexNo, edgeNo;
	int cnt, iterNo, iteration, initialValue;
	float d = 0.85, errorRate = 0;
	float pgrkSum;
    float* pgrkCur, * pgrkPrev, * Diff;

	if (argc == 4)
    {
        iteration = atoi(argv[1]);
        initialValue = atoi(argv[2]);
        //printf("\nIteration: %d  IntitialValue: %d  File:%s\n",iteration,initialValue,filepath);
	}
	else
	{
	    printf("Error: wrong paramters!!!");
	    exit(0);
	}
	//read file and initalize value and matrix
    FILE * openF;
	openF = fopen(argv[3], "r");
	if (openF == NULL)
    {
        printf("\n Could not open the file\n");
        exit(0);
	}
	fscanf(openF,"%d %d", &vertexNo, &edgeNo);

    mat = Matrix2705(vertexNo);//creat matrix and initialized it
    for(j = 0; j < edgeNo; j++)
    {
        fscanf(openF,"%d %d", &v1, &v2);
        mat[v1][v2] = 1;
    }

    pgrkCur = (float *) malloc (vertexNo * sizeof(float));
	pgrkPrev = (float *) malloc (vertexNo * sizeof(float));
	Diff = (float *) malloc (vertexNo * sizeof(float));

// if vertex nuber > 10, reinitialize iteration and iterationval
	if(vertexNo > 10)
    {
        iteration = 0;
        initialValue = -1;
    }

    initValue2705(initialValue, vertexNo, pgrkCur, pgrkPrev); //initialize vector
    outDegree = OutDegNode2705(mat, edgeNo, vertexNo);

    if (vertexNo < 10){
       printFirstLine2705(vertexNo, pgrkPrev);
    }

    if (iteration < 1){
        errorRate = eRate2705(iteration);//, errorRate);
        iterNo = 1; cnt = 0;

        while (cnt != vertexNo)
        {
            cnt = 0;
            for(i = 0; i < vertexNo; i++)
            {
                pgrkSum = 0;
                for(j = 0; j < vertexNo; j ++)
                {
                    if(mat[j][i] == 1)
                    {
                        pgrkSum = pgrkSum + pgrkPrev[j]/(float)outDegree[j];
                    }
                }
                pgrkCur[i] = ((1-d) / (vertexNo)) + (d * pgrkSum);
                Diff[i] = pgrkPrev[i] - pgrkCur[i];
                if(Diff[i] < errorRate){
                    cnt = cnt + 1; //error node
                }
            }

			for(i = 0; i < vertexNo; i++){
				pgrkPrev[i] = pgrkCur[i];
			}
            if(vertexNo <= 10){
                printForLessThanTen2705(vertexNo, iterNo, pgrkCur);
            }
            iterNo ++;
        }
        if(vertexNo > 10){
            printForMoreThanTen2705(vertexNo, iterNo, pgrkCur);
        }
        printf("\n");
    }
    else
    {
		for(int n = 0; n < iteration; n++){

			for(i = 0; i < vertexNo; i++){
				pgrkSum = 0;
				for(j = 0; j < vertexNo; j++){
					if( mat[j][i] == 1){
						pgrkSum = pgrkSum + pgrkPrev[j] / (float)outDegree[j];
					}
				}
				pgrkCur[i] = ((1-d)/(float)(vertexNo)) + (d * pgrkSum);
			}
			for(i = 0; i < vertexNo; i++){
				pgrkPrev[i] = pgrkCur[i];
			}

			printf("\n Iter : %2d :", n+1);
			for(i = 0; i < vertexNo; i++){
				printf("P[%2d]=%.7f ", i, pgrkCur[i]);
			}
		}
        printf("\n");
	}
	fclose(openF);
}

//The following are functions
int* OutDegNode2705(int** mat,int edgeNo, int vertexNo)
{
    int * outDegree = (int *) malloc (sizeof(int *) * vertexNo);
    for(int j=0; j < vertexNo; j++)
    {
        outDegree[j] = 0;
        for (int i=0; i < vertexNo; i++)
        {
            outDegree[j] = outDegree[j] + mat[j][i];
        }
    }
    return outDegree;
}


void initValue2705(int val, int vertexNo, float* pgrkCur, float* pgrkPrev)
{
    for(int i = 0; i < vertexNo; i++){
        if (val == 0)
        {   pgrkPrev[i] =0;
            pgrkCur[i] =0;
        }
        else if(val == 1)
        {
            pgrkPrev[i] =1;
            pgrkCur[i] =0;
        }
        else if (val == (-1))
        {
            pgrkPrev[i] = (1 / (float)vertexNo);
            pgrkCur[i] =0;
        }
        else if (val == (-2))
        {
            pgrkPrev[i] = (1 / (float)sqrt(vertexNo));
            pgrkCur[i] =0;
        }
        else
        {
            printf ("Error! Please enter a number from 0, 1, -1, -2\n");
            exit(0);
        }
    }
}

//iteration number
float eRate2705(int iteration)//, float errorRate)
{
    float errorRate;
    if (iteration == 0)
    {
        errorRate = 0.00001;
    }
    else
    {
        errorRate= pow(10, iteration);
    }
    return errorRate;
}


void printFirstLine2705(int vertexNo, float *pgrkPrev){

    printf("\n Base : %2d :", 0);
    for(int i = 0; i < vertexNo; i ++){
        printf("P[%2d]=%.7f ", i, pgrkPrev[i]);
    }
}

void printForLessThanTen2705(int vertexNo, int iterNo, float *pgrkCur){

    printf("\n Iter : %2d :", iterNo);
    for(int i = 0;i < vertexNo; i++){
        printf("P[%2d]=%.7f ", i, pgrkCur[i]);
    }
}

void printForMoreThanTen2705(int vertexNo, int iterNo, float *pgrkCur){

        printf("\nIter : %2d", iterNo -1);
        for(int i = 0;i < vertexNo; i++){
            printf("\nP[%2d]=%.7f", i, pgrkCur[i]);
            if(i == 4){
                printf("\n   ... Other vertices omitted \n");
                break;
            }
        }
}

int** Matrix2705(int vertexNo)
{
    int ** mat = (int **) malloc (sizeof(int **) * vertexNo);
    for (int i = 0; i < vertexNo; i++) {
        mat[i] = (int *) malloc(sizeof(int) * vertexNo);
    }
    for(int x = 0; x< vertexNo ; x++){
            for(int y = 0; y < vertexNo; y++){
                mat[x][y]= 0;
            }
    }
    return mat;
}
