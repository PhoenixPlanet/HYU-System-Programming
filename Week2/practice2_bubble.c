//Template
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int compare(int a, int b) {
	if (a > b)
		return 1;
	else
		return -1;
}


/***************************************************************
define bubble sort that uses pointer to 'compare' function above
***************************************************************/

void bubbleSort(int* target, int(*compare_func)(int, int)) {
	int i, j, t;
	for (i = 0; i < SIZE - 1; i++) {
		for (j = 0; j < SIZE - 1 - i; j++) {
			if (compare_func(target[j], target[j + 1]) > 0) {
				t = target[j];
				target[j] = target[j + 1];
				target[j + 1] = t;
			}
		}
	}
}



int main() {
	int i;
	int n_array[SIZE] = { 2, -9, 10, 15, 1, 3, -12, 5, 4, 1 };

	//source code
	bubbleSort(n_array, compare);

	for (i = 0; i < SIZE; i++) {
		printf("%d ", n_array[i]);
	}

	return 0;
}
