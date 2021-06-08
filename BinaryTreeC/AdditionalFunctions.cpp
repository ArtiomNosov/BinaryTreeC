#include <stdlib.h>
#include <assert.h>
#include "AdditionalFunctions.h"
int get_max_number_low_then_choice_number_in_array_go_beck(int* array, int lenght, int number) {
	if (array == NULL || lenght <= 0) {
		assert(0);
		return -1;
	}
	int max = INT_MIN;
	while (lenght > 0) {
		if (*array < number && *array > max)
			max = *array;
		if (lenght > 1)array--;
		lenght--;
	}
	return max;
}