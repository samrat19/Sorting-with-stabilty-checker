// Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#define MID 9999;

int checkstabilty(int arr[][20], int n);
void mergesort1(int a[][20],int  n);
void quicksortalgo(int a[][20], int  n);
void insertionsort(int a[][20], int n);
int Partition(int[][20], int, int);
void quicksort(int[][20], int, int);

void Merge(int ARR[][20], int p, int q, int r)
{
	int n1 = q - p + 1;//Size of 1st Subarray
	int n2 = r - q;//Size of 2nd Subarray
	int L[2][10], R[2][10];//L and R are Left and Right Subarrays
	int i, j;
	for (i = 1; i <= n1; i++)
	{
		L[0][i] = ARR[0][p + i - 1];
		L[1][i] = ARR[1][p + i - 1];
	}
	for (j = 1; j <= n2; j++)
	{
		R[0][j] = ARR[0][q + j];
		R[1][j] = ARR[1][q + j];
	}
	L[0][n1 + 1] = MID;
	L[1][n1 + 1] = MID;
	R[0][n2 + 1] = MID;
	R[1][n2 + 1] = MID;
	i = 1;
	j = 1;
	int k;
	for (k = p; k <= r; k++)
	{
		if (L[0][i] <= R[0][j])
		{
			ARR[0][k] = L[0][i];
			ARR[1][k] = L[1][i];
			i = i + 1;
		}
		else
		{
			ARR[0][k] = R[0][j];
			ARR[1][k] = R[1][j];
			j = j + 1;
		}
	}
}

void MergeSort(int ARR[][20], int p, int r)
{
	if (p<r)
	{
		int q = ((p + r) / 2);
		MergeSort(ARR, p, q);
		MergeSort(ARR, q + 1, r);
		Merge(ARR, p, q, r);
	}
}

void printArray(int a[][20], int size)
{
	int i,j,k;
	FILE *file1;
	file1 = fopen("Assignment.txt", "a");
	fprintf(file1,"\nSorted Array: \n");
	for (i = 1; i <= size; i++)
	{
		fprintf(file1, "%d\t", a[0][i]);
	}
	printf("\nSorted Array: \n");
	for (i = 0; i<2; i++)
	{
		for (j = 1; j <= size; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
	k = checkstabilty(a, size);
	if (k == 0) {
		printf("\nStable");
		fprintf(file1, "\nStable");
	}
	else if (k == 1) {
		printf("\nUnstable");
		fprintf(file1, "\nUnstable");
	}
	fclose(file1);
}


int main()
{
	int arr[2][20],c, i,j, n,choice,element=1;
	FILE *file;
	srand(time(0));
	printf("how manuy numbers to be inserted: ");
	scanf_s("%d", &n);
	file = fopen("Assignment.txt", "w");
	fprintf(file, "Unsorted Array: \n");
	for (i = 0; i < n; i++)
	{
	    int rd = rand() % 101;
		arr[0][i] = rd;
		fprintf(file, "%d\t", rd);
		printf("%d\t",rd);
	}
	fclose(file);
	file = fopen("Assignment.txt", "r");
	for (i=0; i < n; i++) {
		arr[1][i] = 1;
	}
	for (i = 0; i < n; i++)
	{
		int k = 2;
		if (arr[1][i] == 1)
		{
			for (j = i + 1; j <= n; j++)
			{
				if (arr[0][i] == arr[0][j])
				{
					arr[1][j] = k;
					k = k + 1;
				}
			}
		}
	}
	printf("\n The elements generated are : \n");
	for (i = 0; i<2; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n1.Merge Sort\n2.Quick Sort\n3.Insertion Sort\n");
	printf("\nenter choice: ");
	scanf_s("%d", &choice);
	switch (choice) {
	case 1:mergesort1(arr, n);
		break;
	case 2:quicksortalgo(arr, n);
		break;
	case 3:insertionsort(arr, n);
		break;
	case 4:printf("Check Stability???? \n p");
	default:printf("\nWrong Choice");
		break;
	}
	_getch();
}

void mergesort1(int a[][20], int n) {
	int i;
	MergeSort(a, 0, n);
	printArray(a, n);
}

void insertionsort(int arr[][20], int n) {

	int c, d, t,k;
	FILE * f1;
	f1 = fopen("Assignment.txt", "a");
	fprintf(f1, "\nLook step by step: \n");
	for (c = 1; c <= n ; c++) {

		d = c;
		while (d > 0 && arr[0][d - 1] > arr[0][d]) {

			t = arr[0][d]; 
			arr[0][d] = arr[0][d - 1];
			arr[0][d - 1] = t;

			t = arr[1][d];
			arr[1][d] = arr[1][d - 1];
			arr[1][d - 1] = t;
			d--;
		}
		if (c == n)
			break;
		printf("\nStep %d: ", c);
		fprintf(f1, "Step %d", c);
		for (k = 0; k < n; k++) {
			printf(" %d ", arr[0][k]);
			fprintf(f1, "%d ", arr[0][k]);
		}
		printf(" \n ");
		fprintf(f1," \n ");
	}
	fclose(f1);
	printArray(arr, n);
}
int Partition(int arr[][20], int p, int r)
{
	int x = arr[0][r];
	int i = p - 1;
	int j;
	for (j = p; j<r; j++)
	{
		if (arr[0][j] <= x)
		{
			i = i + 1;
			int temp = arr[0][i];
			arr[0][i] = arr[0][j];
			arr[0][j] = temp;
			temp = arr[1][i];
			arr[1][i] = arr[1][j];
			arr[1][j] = temp;
		}
	}
	int temp = arr[0][i + 1];
	arr[0][i + 1] = arr[0][r];
	arr[0][r] = temp;
	temp = arr[1][i + 1];
	arr[1][i + 1] = arr[1][r];
	arr[1][r] = temp;
	return i + 1 ;
}
void quicksort(int arr[][20], int p, int r)
{
	if (p<r)
	{
		int q = Partition(arr, p, r);
		quicksort(arr, p, q- 1);
		quicksort(arr, q + 1, r);
	}
}
void quicksortalgo(int arr[][20], int n) {
	quicksort(arr, 0, n);
	printArray(arr, n);
}
int checkstabilty(int arr[][20], int n) {
	int i, j, mark = 0;
	for (i = 1; i < 2; i++) {
		for (j = 0; j < n; j++) {
			if (arr[1][j] > arr[1][j + 1]) {
				if (arr[0][j] >= arr[0][j + 1]) {
					mark = mark + 1;
				}
				else {
					mark = 0;
				}
			}
		}
	}
	if (mark == 0) {
		return 0;
	}
	else {
		return 1;
	}
}