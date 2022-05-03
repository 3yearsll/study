#include<stdio.h>
#include <malloc.h>
//打印数组
void ArrayPrint(int* arr, int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}
}

//冒泡排序
//冒泡排序第一轮可以确定数组中的最大值
void BubbleSort(int* arr, int length) {
	int i, j;
	for (i = 0; i < length-1; i++) {
		for (j = 0; j < length-i-1; j++) {
			if (arr[j] > arr[i]) {
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}
	}
	ArrayPrint(arr, length);
}

//选择排序
void SelectionSort(int* arr, int length) {
	int i, j;
	for (i = 0; i < length; i++) {
		//设当前数为最小值
		int min = arr[i];
		//记录最小值的数组下标
		int index = i;
		for (j = i + 1; j < length; j++) {
			//找到最小值并更新下标
			if (arr[j] < min) {
				min = arr[j];
				index = j;
			}
		}
		//如果i!=index则说明最小数发生改变,交换当前数和最小数的位置
		if (index != i) {
			arr[index] = arr[i];
			arr[i] = min;
		}
		
	}
	ArrayPrint(arr, length);
}

//直接插入排序
void StraightInsertSort(int* arr, int length) {
	int i, j;
	int count = 0;
	//i是待排序数列
	//j是已排序数列
	for (i = 1; i < length; i++) {
		count++;
		int temp = arr[i];
		//如果待排序数<当前数则将当前数右移
		for (j = i -1 ; j >= 0&&arr[j]>temp; j--) {
				arr[j+1] = arr[j];
			
		}
		arr[j+1] = temp;
	}
	ArrayPrint(arr, length);
	printf("\n");
	printf("%d", count);
}

//希尔排序
//基于插入排序,将数组按照下标分为不同的增量,对这些增量进行排序,最后再对整个数组进行一次插入排序
void ShellSort(int* arr, int length) {
	
	int add, i, j;
	//add为增量,最开始是长度一半,然后一直自除2
	for (add = length / 2; add > 0; add /= 2) {
		
		for (i = add; i < length; i++) {
			int temp = arr[i];
			for (j = i; j >= add && arr[j - add] > temp; j-=add) {
				arr[j] = arr[j - add];
			}
			arr[j] = temp;
		}
	}
	
}

//快速排序(分而治之思想)
//每次找一个数作为基准,然后遍历数组将比基准小的放在基准左边,比基准大的放在基准右边
//同时用到双指针的技巧
void QuickSort(int* arr, int low,int high) {
	
	if (low >= high) {
		return;
	}
	//定义双指针
	int i = low;
	int j = low;
	//遍历数组,遇到比基准小的把他们放到基准左边
	while (i<high)
	{
		
		if (arr[i] < arr[high]) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			j++;
		}
		i++;
	}
	int temp = arr[j];
	arr[j] = arr[high];
	arr[high] = temp;
	//循环结束后,j就是基准所处于该数组的正确位置
	//进行递归
	QuickSort(arr, 0, j - 1);
	QuickSort(arr, j + 1, high);
	
}

//计数排序
//计数排序适用于数据较少的情况
void CountingSort(int* arr, int *sorted_arry,int length) {
	int max = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	int *temparr = (int*)malloc(sizeof(int) * (max + 1));

	for (int i = 0; i < max + 1; i++) {
		temparr[i] = 0;
	}

	for (int i = 0; i < length; i++) {
		temparr[arr[i]]++;
	}
	int j = 0;
	for (int i = 0; i < max + 1; i++) {
		while (temparr[i]>0)
		{
			sorted_arry[j++] = i;
			temparr[i]--;
		}
	}
	//释放临时数组
	free(temparr);
}

//归并排序
//将分完组的数组进行排序
void MergeCombine(int*arr,int *temp_arr,int left,int right,int mid){
	int l_pos=left;
	int r_pos=mid+1;
	int temp_pos=left;
	while(l_pos<=mid&&r_pos<=right){
		if(arr[l_pos]<arr[r_pos]){
			temp_arr[temp_pos++]=arr[l_pos++];
		}else{
			temp_arr[temp_pos++]=arr[r_pos++];
		}
	}

	//检测是否有剩余未排序数组
	while(l_pos<=mid){
		temp_arr[temp_pos++]=arr[l_pos++];
	}

	while(r_pos<=right){
		temp_arr[temp_pos++]=arr[r_pos++];

	}

	//将临时数组的结果复制到原数组
	while(left<=right){
		arr[left]=temp_arr[left];
		left++;
	}
}
//将数组进行分组
void MergeSort(int* arr,int *temp_arr,int left,int right){
	if(left<right){
		int mid=(left+right)/2;
		MergeSort(arr,temp_arr,left,mid);
		MergeSort(arr,temp_arr,mid+1,right);
		MergeCombine(arr,temp_arr,left,right,mid);
	}

}

int main(void) {
	
	int arr2[20] = { 2,1,5,3,6,4,7,34,5,35,23,32,21,1,3,5,73,234,2,56 };
	ShellSort(arr2,20);
	ArrayPrint(arr2,20);
}