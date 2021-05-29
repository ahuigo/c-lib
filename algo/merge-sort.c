	#include <stdio.h>
	#include <stdlib.h>
	#include <errno.h>
	#include <stdarg.h>
	#include <string.h>


int min(int x, int y) {
    return x < y ? x : y;
}
void merge_sort(int arr[], int len) {
    int* a = arr;
    int* b = (int*) malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) { //logN
        for (start = 0; start < len; start += seg + seg) { //n
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}



int main(void){
		int arr[10] = {2, 1, 5, 6, 3,  7, 4, 9, 8 ,0};
		//shell_sort(arr, 10);
        merge_sort(arr, 10);
		int i = 0;
		while(i<10){
			printf("%d\t", arr[i++]);
		}
}
