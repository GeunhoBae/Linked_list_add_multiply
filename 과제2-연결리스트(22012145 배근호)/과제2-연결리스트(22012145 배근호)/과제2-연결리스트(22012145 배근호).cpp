// 학번: 22012145
// 이름: 배근호

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

struct node {
	int data;
	struct node* link;
};
struct node* ptr = NULL;

struct node* make_list(char[]);
void print_list(struct node*);
struct node* add(struct node*, struct node*);
struct node* multiply(struct node*, struct node*);

void main()
{
	char fname[40];
	char first[1000], second[1000];
	struct node* A, * B, * C, * D;
	FILE* fp;

	printf("파일 이름? ");
	gets_s(fname);
	fp = fopen(fname, "r");
	fscanf(fp, "%s%s", first, second);

	A = make_list(first);
	B = make_list(second);
	C = add(A, B);
	D = multiply(A, B);

	printf("첫번째 수 = ");
	print_list(A);
	printf("\n두번째 수 = ");
	print_list(B);
	printf("\n두 수의 합 = ");
	print_list(C);
	printf("\n두 수의 곱 = ");
	print_list(D);

}

struct node* make_list(char file_data[]) {
	ptr = NULL;
	for (int i = 0; i < strlen(file_data); i++) {
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		temp->data = file_data[i] - '0';
		temp->link = ptr;
		ptr = temp;
	}
	return ptr;
}

void print_list(struct node* printed_list) {
	struct node* x,* y,* z;
	x = printed_list; y = NULL; z = NULL;
	while (x) {
		y = x;
		x = x->link;
		y->link = z;
		z = y;
	}
	for (; z; z = z->link) printf("%d", z->data);
	printf("\n");
}

struct node* add(struct node* A, struct node* B) {
	ptr = NULL;
	int value;
	int carry = 0;
	struct node* x, * y, * z;

	while (A && B) {
		struct node* temp = (struct node*)malloc(sizeof(struct node));

			value = A->data + B->data + carry;
			value > 9 ? carry = 1 : carry = 0;
			value = value % 10;
			temp->data = value;
			temp->link = ptr;
			ptr = temp;
			A = A->link;
			B = B->link;
	}
	if (!A && !B && carry > 0) {
		struct node* temp = (struct node*)malloc(sizeof(struct node));
		temp->data = 1;
		temp->link = ptr;
		ptr = temp;
	}

	if (A == NULL) {
		while (B) {
			struct node* temp = (struct node*)malloc(sizeof(struct node));
			temp->data = B->data + carry;
			temp->link = ptr;
			ptr = temp;
			B = B->link;
			carry = 0;
		}
	}
	else if (B == NULL) {
		while (A) {
			struct node* temp = (struct node*)malloc(sizeof(struct node));
			temp->data = A->data + carry;
			temp->link = ptr;
			ptr = temp;
			A = A->link;
			carry = 0;
		}
	}
	x = ptr; y = NULL; z = NULL;
	while (x) {
		y = x;
		x = x->link;
		y->link = z;
		z = y;
	}
	return z;
}

struct node* multiply(struct node* A, struct node* B) {
	int value;
	int digit_B = 0;
	struct node* x, * y, * z, *single, *result, *original_A;
	result = NULL;
	original_A = A;

	while (B) {
		ptr = NULL;
		int carry = 0;

		while (A) {
			struct node* temp = (struct node*)malloc(sizeof(struct node));

			value = (A->data * B->data) + carry;
			carry = value / 10;
			value = value % 10;
			temp->data = value;
			temp->link = ptr;
			ptr = temp;
			A = A->link;
		}

		if (carry > 0) {
			struct node* temp = (struct node*)malloc(sizeof(struct node));
			temp->data = carry;
			temp->link = ptr;
			ptr = temp;
		}

		A = original_A;
		B = B->link;

		x = ptr; y = NULL; z = NULL;
		while (x) {
			y = x;
			x = x->link;
			y->link = z;
			z = y;
		}
		ptr = z;

		for (int i = 0; i < digit_B; i++) {
			struct node* temp = (struct node*)malloc(sizeof(struct node));

			temp->data = 0;
			temp->link = ptr;
			ptr = temp;
		}
		digit_B++;

		single = ptr;
		result = add(result, single);

		x = result; y = NULL; z = NULL;
		while (x) {
			y = x;
			x = x->link;
			y->link = z;
			z = y;
		}
		result = z;
	}
	return result;
}