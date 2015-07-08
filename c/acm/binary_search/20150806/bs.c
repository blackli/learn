#include <stdio.h>

int binary_search(int *search_arr, int len, int aim);

int main()
{
	int search_arr[] = {1, 2, 3, 7, 10, 18, 11};
	printf("%d\n", binary_search(search_arr, sizeof(search_arr)/sizeof(int), 3));
	return 0;
}

int binary_search(int *search_arr, int len, int aim)
{
	int low = 0;
	int high = len - 1;
	int middle;
	while (low <= high)
	{
		middle = (low + high)/2;
		if (search_arr[middle] == aim)
			return middle;
		else if (search_arr[middle] < aim)
			low = middle + 1;
		else if (search_arr[middle] > aim)
			high = middle - 1;
	}
		
	return -1;
}
