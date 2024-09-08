#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PANCAKES 30
#define INPUT_FILE "input_pancake.txt"  // �Է� ���� �̸�

// ������ ����ϴ� �Լ�
void print_stack(int stack[], int size) {
    for (int i = 0; i < size; i++) {
        if (i > 0) printf(" ");
        printf("%d", stack[i]);
    }

}

// ���ÿ��� Ư�� ��ġ���� ������ �Լ�
void flip(int stack[], int k) {
    // k��° ��ġ���� ������ ������
    for (int i = 0; i <= k / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[k - i];
        stack[k - i] = temp;
    }
}

// ������ �����ϰ� ������ ������ �����ϴ� �Լ�
void sort_stack(int stack[], int size) {
    int flips[MAX_PANCAKES];
    int flip_count = 0;

    // ���� ū ���� 0��°, ���� ���� ���� n��°�� ������ ����
    for (int i = size - 1; i > 0; i--) {
        int max_index = 0;
        for (int j = 1; j <= i; j++) {
            if (stack[j] > stack[max_index]) {
                max_index = j;
            }
        }
        if (max_index != i) {
            // ���� ū ������ũ�� ���� �ø��� ���� �ִ� index���� ������
            if (max_index > 0) {
                flip(stack, max_index);
                flips[flip_count++] = 6 % (max_index + 1);
            }
            // ���� ��ġ�� ���� ū ������ũ�� �ø��� ���� i���� ������
            flip(stack, i);
            flips[flip_count++] = 6 % (i + 1);
        }
    }

    // ���ĵ� ���� ���
    printf("(");
    print_stack(stack, size);
    printf(")");
    printf("\n");

    // ������ �۾� ���� ���
    for (int i = 0; i < flip_count; i++) {
        printf("%d ", flips[i]);
    }
    printf("0\n");


}

int main() {
    FILE* input = fopen(INPUT_FILE, "r");

    if (input == NULL) {
        perror("���� ���� ����");
        return 1;
    }

    int stack[MAX_PANCAKES];
    int size;

    // ���Ͽ��� �� �� �б�
    char line[256];
    for (int i = 0; i < 3; i++) {
        if (fgets(line, sizeof(line), input) == NULL) {
            fprintf(stderr, "���� �б� ���� �Ǵ� ���� ������\n");
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

        // ���� ���� ���
        print_stack(stack, size);

        // ������ �����ϰ� ������ ���� ���
        sort_stack(stack, size);
    }

    fclose(input);

    return 0;
}