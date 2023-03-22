#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


//This is an extra function for mergeSort to call upon in order for it to work closer to how it is supposed to work
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int left = m - l + 1;
	int right = r - m;
	int leftArr[left], rightArr[right];
	if(extraMemoryAllocated == 0)
	{
	extraMemoryAllocated = extraMemoryAllocated + sizeof(i) + sizeof(j) + sizeof(k) + sizeof(left) + sizeof(right);
	extraMemoryAllocated += sizeof(leftArr);
	extraMemoryAllocated += sizeof(rightArr);
	}
	
	for(i = 0; i < left; i++)
	{
		leftArr[i] = arr[l + i];
	}
	for(j = 0; j < right; j++)
	{
		rightArr[j] = arr[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
	while(i < left && j < right)
	{
		if(leftArr[i] <= rightArr[j])
		{
			arr[k] = leftArr[i];
			i++;
		}
		else
		{
			arr[k] = rightArr[j];
			j++;
		}
		k++;
	}
	while(i < left)
	{
		arr[k] = leftArr[i];
		i++;
		k++;
	}
	while(i < right)
	{
		arr[k] = rightArr[j];
		j++;
		k++;
	}
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int mid = l + (r - l) / 2;
		mergeSort(pData, l, mid);
		mergeSort(pData,mid + 1, r);
		merge(pData,l,mid,r);
	}
	
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, testValue;
	extraMemoryAllocated = sizeof(i) + sizeof(j) + sizeof(testValue);
	for(i = 1; i < n; i++)
	{
		testValue = pData[i];
		j = i - 1;
		while(j >= 0 && pData[j] > testValue)
		{
			pData[j + 1] = pData[j];
			j = j - 1;
		}
		pData[j+1] = testValue;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j, temp;
	extraMemoryAllocated = sizeof(i) + sizeof(j) + sizeof(temp);
	for (i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(pData[j] > pData[j+1])
			{
			temp = pData[j];
			pData[j] = pData[j+1];
			pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, minVal, temp;
	extraMemoryAllocated = sizeof(i) + sizeof(j) + sizeof(minVal) + sizeof(temp);
	for(i = 0; i < n-1; i++)
	{
		minVal = i; 
		for(j = i + 1; j < n; j++)
		{
			if(pData[j] < pData[minVal])
			{
				minVal = j;
					
			}
		}
		if(minVal != i)
		{
			temp = pData[i];
			pData[i] = pData[minVal];
			pData[minVal] = temp;
		}	
		
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		for(int i = 0; i < dataSz; i++)
		{
			fscanf(inFile,"%d",&(*ppData)[i]);
		}
		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		/*
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		*/
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}