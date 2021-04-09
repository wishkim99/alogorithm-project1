#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10000  //데이터 셋 크기 지정(10000, 50000, 100000, 500000.......늘리기)
#define swap(x,y,t)  ((y)=(t)) //swap함수 
#define Swap(x,y) ((x)=(y)) //Swap
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) //SWAP함수

int orig_arr[MAX_SIZE];    //랜덤으로 만든 데이터를 저장할 원본 배열    
int arr[MAX_SIZE];
int mid;// 데이터 배열
int n; //전역변수(데이터 셋 크기를 받음) 

clock_t st, fin, used_time = 0;    //실행 시간 측정을 위한 변수

								   //(1) Selection sort~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void selectionSort(int arr[], int n)
{
	int min, tmp;

	for (int i = 0; i<n - 1; i++) //i가 for문을 돌때
	{
		min = i; //최솟값은 i
		for (int j = i + 1; j<n; j++)
			if (arr[j]< arr[min])  //배열 j값이 최솟값(min)값보다 작으면
				min = j; //j값이 최솟값이 됨.
		SWAP(arr[i], arr[min], tmp);
	}
}


//(2) Median-of-three Quick sort~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sp(int arr[], int a, int b) { //교환

	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;

}
void medianQuickSort(int arr[], int first, int mid, int last) {

	if (arr[mid]<arr[first])
		sp(arr, mid, first); //배열 중간값이 첫번째 값보다 작을 때 중간값과 첫번째 교환

	if (arr[last]<arr[mid])
		sp(arr, last, mid); //배열 마지막 값이 중간값보다 작을 때 마지막값과 중간값 교환

	if (arr[mid]<arr[first])
		sp(arr, mid, first); //배열 중간값이 처음값보다 작을 때 중간값과 처음값 교환

}

void medianQuickSort(int arr[], int first, int last) {

	int i, j;
	int pivot;
	mid = (first + last) / 2; //중간값

	medianQuickSort(arr, first, mid, last); //처음, 중간, 마지막 값 우선정렬

	if (last - first + 1>3) { //median of quick sort는 젤 처음 3개의 값으로 정렬을 시작하기 때문에 3보다 커야한다.
		pivot = arr[mid]; //피봇을 배열의 중간값으로 설정
		sp(arr, mid, last - 1);
		i = first;
		j = last - 1; //제일 마지막은 이미 정렬되어있으므로 마지막 바로 앞에 값으로 설정

		while (true) {
			while (arr[++i]<pivot && i<last); //배열의 i가 증가할때 피봇보다 작으면서 last보다 작을동안
			while (arr[--j]>pivot && first<j); //배열의 j가 감소할때 피봇보다 크면서 first보다 클동안
			if (i >= j)
				break;
			sp(arr, i, j); //
		}
		sp(arr, i, last - 1);
		medianQuickSort(arr, first, i - 1); //앞부분 배열(처음부터 i-1까지)
		medianQuickSort(arr, i + 1, last); //뒷부분 배열(i+1부터 마지막값까지)
	}
}


//(3) Shell Sort~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void insertion(int  arr[], int first, int last, int gap) //shellSort의 부분집합에 사용되는 삽입 함수
{
	int i, j, k;

	for (i = first + gap; i <= last; i = i + gap) // 첫 번째 원소는 정렬 할 필요가 없고 그 다음 배열 값을 k 값으로 설정. 따라 초기값은 first + gap
	{
		k = arr[i];      // k값은 배열 i가 된다

		for (j = i - gap; j >= first && k < arr[j]; j = j - gap) //gap 감소
			arr[j] = arr[j + gap]; //배열 j값이 j+gap 값이 됨.
		arr[j + gap] = k; //k값이 j+jap값이 됨.
	}
}
void shellSort(int  arr[], int n)
{
	int i, gap;

	for (gap = n / 2; gap>0; gap = gap / 2) //gap값을 반씩 줄여나가야 함
	{
		if ((gap % 2) == 0)    //gap이 짝수일 경우 홀수로 만들어야함
			gap++;

		for (i = 0; i<gap; i++) //부분리스크 삽입 정렬
			insertion(arr, i, n - 1, gap);
	}
}

//(4) Bitonic sort~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void bitonicSwap(int arr[], int i, int j, int seq)
{
	if (seq == (arr[i]>arr[j])) //오름차순 정렬
		Swap(arr[i], arr[j]); //배열 i,j 교환
}

void bitonic(int arr[], int down, int count, int seq)
{
	if (count>1) //정렬 갯수
	{
		int t = count / 2;
		for (int i = down; i<down + t; i++)  //i가 작은값(down)부터 down+t까지 for문을 돌때
			bitonicSwap(arr, i, i + t, seq); //i와 i+t 교환

		bitonic(arr, down, t, seq); //작은 값->큰값(오름차순)
		bitonic(arr, down + t, t, seq); //큰 값에서->작은값(내림차순)
	}
}


void bitonicSort(int arr[], int down, int count, int seq)
{
	if (count>1)
	{
		int t = count / 2;

		bitonicSort(arr, down, t, 1); //오름차순 정렬

		bitonicSort(arr, down + t, t, 0); //내림차순 정렬

		bitonic(arr, down, count, seq); //오름차순정렬
	}
}

void sort(int arr[], int n, int up)
{
	bitonicSort(arr, 0, n, up); //전체 배열 정렬
}



//(5) Odd-Even Merge sort~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void oddEvenMerge1(int i, int j)
{
	if (arr[i] > arr[j]) //배열 i가 j보다 클때
		Swap(i, j); //i,j 교환
}
void oddEvenMerge(int arr, int n, int dis) { //dis=비교할 거리
	{
		int t = dis * 2;
		if (t < n)
		{
			oddEvenMerge(arr, n, t); // 짝수 반복
			oddEvenMerge(arr + dis, n, t); // 홀수 반복

			for (int i = arr + dis; i + dis < arr + n; i += t)
				oddEvenMerge1(i, i + dis); //배열 i가 i+dis보다 크면 교환
		}
		else
			oddEvenMerge1(arr, arr + dis); //t가 n보다 작으면 arr,arr+dis 교환


		oddEvenMerge1(arr, arr + dis); //arr가 arr+dis보다 크면 arr, arr + dis 서로 교환
	}
}
void oddEvenMergeSort(int arr[], int n)
{
	if (n>1)
	{
		int t = n / 2;
		oddEvenMergeSort(arr, t);
		oddEvenMergeSort(arr + t, t);
		oddEvenMerge(*arr, n, 1);
	}
}

//원본 배열을 복사하는 함수
void CopyArr(void)
{
	int i;
	for (i = 0; i<n; i++)  //i가 for문을 돌때
		arr[i] = orig_arr[i]; //원본배열을 배열 i로
}

//실행 시간 측정 및 출력 함수
void CalcTime(void)
{
	used_time = fin - st;
	printf("\n실행 시간 : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}


void main() //메인함수
{
	int i;

	n = MAX_SIZE;
	for (i = 0; i<n; i++)
		orig_arr[i] = rand(); //랜덤으로 설정

	printf("데이터 셋 크기 : %d\n\n", n);

	CopyArr();
	st = clock();
	printf("(1) Selection sort");  //선택정렬 시간재기
	selectionSort(arr, n);
	fin = clock();
	CalcTime();

	CopyArr();
	st = clock();
	printf("(2) Median-of-three Quick sort"); //중간퀵 정렬 시간 재기
	medianQuickSort(arr, 0, n);
	fin = clock();
	CalcTime();

	CopyArr();
	st = clock();
	printf("(3) Shell Sort"); //셸 정렬 시간 재기
	shellSort(arr, n);
	fin = clock();
	CalcTime();

	CopyArr();
	st = clock();
	printf("4) Bitonic sort"); //바이오틱 정렬 시간 재기
	bitonicSort(arr, 0, n, 0);
	fin = clock();
	CalcTime();

	CopyArr();
	st = clock();
	printf("(5) Odd-Even Merge sort"); //짝홀 합병 정렬 시간 재기
	oddEvenMergeSort(arr, n);
	fin = clock();
	CalcTime();
}



