#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct elephants {
	int order;
	int weight;
	int IQ;
};
typedef struct elephants Elephant;
typedef Elephant* ElephantPtr;

void findLongestSequence(ElephantPtr elephant, int len);
int compare(const void* a, const void* b) {
	Elephant* ea = (Elephant*)a;
	Elephant* eb = (Elephant*)b;

	if (ea->weight != eb->weight) {
		return ea->weight - eb->weight; // weight ascending
	}
	else {
		return eb->IQ - ea->IQ; // IQ descending
	}
}

void main() {
	FILE* fr = fopen("input_SmartElephant.txt", "r");

	if (fr == NULL) { // fopen fail
		printf("Can't find file\n");
		exit(0);
	}

	char temp[20]; // array for reading file
	int length = 0;
	ElephantPtr elephant = NULL;

	// Read the file line by line and store elephant information
	while (fgets(temp, sizeof(temp), fr) != NULL) {
		elephant = (ElephantPtr)realloc(elephant, sizeof(Elephant) * (length + 1)); // realloc: Change the size of a dynamically allocated memory block
		(elephant + length)->weight = atoi(strtok(temp, " ")); // cut lines based on spaces
		(elephant + length)->IQ = atoi(strtok(NULL, " "));
		(elephant + length)->order = length + 1; // save order
		length++;
	}

	qsort(elephant, length, sizeof(Elephant), compare); // sort elephant struct array

	// for (int i = 0; i < length; i++) { // for sorting check
	//     printf("%d : %d %d\n", i, elephant[i].weight, elephant[i].IQ);
	// }

	findLongestSequence(elephant, length);

	fclose(fr);
	free(elephant);
}

void findLongestSequence(ElephantPtr elephant, int len) {
	int* dp = (int*)malloc(sizeof(int) * len);  // Store the length of the longest sequence up to each elephant
	int* prev = (int*)malloc(sizeof(int) * len);  // Store the previous elephant for each elephant (for sequence reconstruction)

	for (int i = 0; i < len; i++) {
		dp[i] = 1;  // Initial setting: The sequence containing only itself has a length of 1
		prev[i] = -1;  // Indicate that there is no previous elephant
	}

	// Count the length of the longest sequence and find the longest sequence
	int max_index = 0;
	for (int i = 1; i < len; i++) {
		for (int j = 0; j < i; j++) {
			if ((elephant[i].weight > elephant[j].weight) &&
				(elephant[i].IQ < elephant[j].IQ) &&
				dp[i] < dp[j] + 1) {
				dp[i] = dp[j] + 1;
				prev[i] = j;
			}
		}
		if (dp[i] > dp[max_index]) {
			max_index = i;
		}
	}

	// Reconstruct the longest sequence
	int* result = (int*)malloc(sizeof(int) * dp[max_index]);
	int k = dp[max_index];
	for (int i = max_index; i != -1; i = prev[i]) {
		result[--k] = elephant[i].order;
	}

	// Print the result
	printf("%d\n", dp[max_index]);
	for (int i = 0; i < dp[max_index]; i++) {
		printf("%d\n", result[i]);
	}

	free(dp);
	free(prev);
	free(result);
}



