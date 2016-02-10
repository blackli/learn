#include <stdio.h>

int binary_search(int *arr, int len, int aim);

int main()
{
	int arr[] = {1, 2, 8, 19, 20, 29};
	printf("ret=%d", binary_search(arr, sizeof(arr)/sizeof(int), 29));
	return 1;
}

int binary_search(int *arr, int len, int aim)
{
	int low = 0, high = len - 1, middle;
	while (low <= high) {
		middle = low + ((high-low)>>1);	
		if (arr[middle] == aim)
		{
			 return middle;
		}
		else if (arr[middle] < aim)
		{
			low = middle + 1;
		}
		else
		{
			high = middle - 1;
		}
	}
	return -1;
}
