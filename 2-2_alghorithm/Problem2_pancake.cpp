#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PANCAKES 30
#define INPUT_FILE "input_pancake.txt"  // 입력 파일 이름

// 스택을 출력하는 함수
void print_stack(int stack[], int size) {
    for (int i = 0; i < size; i++) {
        if (i > 0) printf(" ");
        printf("%d", stack[i]);
    }

}

// 스택에서 특정 위치까지 뒤집는 함수
void flip(int stack[], int k) {
    // k번째 위치까지 스택을 뒤집음
    for (int i = 0; i <= k / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[k - i];
        stack[k - i] = temp;
    }
}

// 스택을 정렬하고 뒤집기 순서를 생성하는 함수
void sort_stack(int stack[], int size) {
    int flips[MAX_PANCAKES];
    int flip_count = 0;

    // 제일 큰 수가 0번째, 제일 작은 수가 n번째에 오도록 정렬
    for (int i = size - 1; i > 0; i--) {
        int max_index = 0;
        for (int j = 1; j <= i; j++) {
            if (stack[j] > stack[max_index]) {
                max_index = j;
            }
        }
        if (max_index != i) {
            // 가장 큰 팬케이크를 위로 올리기 위해 최대 index까지 뒤집음
            if (max_index > 0) {
                flip(stack, max_index);
                flips[flip_count++] = 6 % (max_index + 1);
            }
            // 현재 위치에 가장 큰 팬케이크를 올리기 위해 i까지 뒤집음
            flip(stack, i);
            flips[flip_count++] = 6 % (i + 1);
        }
    }

    // 정렬된 스택 출력
    printf("(");
    print_stack(stack, size);
    printf(")");
    printf("\n");

    // 뒤집기 작업 순서 출력
    for (int i = 0; i < flip_count; i++) {
        printf("%d ", flips[i]);
    }
    printf("0\n");


}

int main() {
    FILE* input = fopen(INPUT_FILE, "r");

    if (input == NULL) {
        perror("파일 열기 오류");
        return 1;
    }

    int stack[MAX_PANCAKES];
    int size;

    // 파일에서 각 줄 읽기
    char line[256];
    for (int i = 0; i < 3; i++) {
        if (fgets(line, sizeof(line), input) == NULL) {
            fprintf(stderr, "파일 읽기 오류 또는 줄이 부족함\n");
            fclose(input);
            return 1;
        }

        size = 0;
        int value;
        char* token = strtok(line, " \n");
        while (token != NULL) {
            value = atoi(token);
            stack[size++] = value;
            token = strtok(NULL, " \n");
        }

        // 원래 스택 출력
        print_stack(stack, size);

        // 스택을 정렬하고 뒤집기 순서 출력
        sort_stack(stack, size);
    }

    fclose(input);

    return 0;
}