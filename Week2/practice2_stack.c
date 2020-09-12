//Template
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int nData;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *top;
}Stack;

void InitializeStack(Stack *stack);
void Push(Stack *stack, int nData);
int Pop(Stack *stack);
void DeleteStack(Stack *stack);


int main(void){
	//source code
	Stack stack;

	InitializeStack(&stack);
	Push(&stack, 5);
	Push(&stack, 3);
	Push(&stack, 1);
	Push(&stack, 2);
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	Push(&stack, 7);
	Push(&stack, 8);
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));
	printf("%d\n", Pop(&stack));

	DeleteStack(&stack);
	return 0;
}

void InitializeStack(Stack *stack){
	//source code
	stack->top = NULL;
}

void Push(Stack *stack, int nData){
	//source code
	Node *new_node;

	new_node = malloc(sizeof(Node));
	new_node->nData = nData;
	new_node->next = stack->top;
	stack->top = new_node;
}

int Pop(Stack *stack){
	//source code
	int value;
	Node *target_node;

	if (stack->top == NULL) {
		printf("Empty stack\n");
		return 0;
	}

	value = stack->top->nData;
	target_node = stack->top;
	stack->top = stack->top->next;
	free(target_node);

	return value;
}

void DeleteStack(Stack *stack) {
	Node *n, *next;

	for (n = stack->top; n != NULL; n = next) {
		next = n->next;
		free(n);
	}
}