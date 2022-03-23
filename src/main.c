#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256
static int stack[STACK_SIZE];

typedef enum {
	HALT,
	JUMP,
	FJUMP,
	CALL,
	RET,
	PUSH,
	POP,
	LOAD,
	STORE,
	MOV,
	SET,
	ADD,
	SUB,
	MUL,
	DIV,
	AND,
	OR,
	NOT
} InstructionSet;

typedef enum {
	A,B,C,D,E,F,PC,SP,
	NUM_OF_REGS
} Registers;

static int registers[NUM_OF_REGS];
int *instructions;
int instruction_count = 0;
int instruction_size = 4;

#define sp (registers[SP])
#define ip (registers[PC])

static bool running = true;

int fetch() {
	return instructions[ip];
}

void eval(int instrc) {
	switch (instrc) {
	case HALT: { 
		running = false;
		break;
	}
	case ADD: {
		int a = stack[sp--];
		int b = stack[sp];
		stack[sp] = a + b;
		break; 
	}
	case SUB: {
		int a = stack[sp--];
		int b = stack[sp];
		stack[sp] = a - b;
		break;
	}
	case MUL: {
		int a = stack[sp--];
		int b = stack[sp];
		stack[sp] = a * b;
		break;
	}
	case JUMP: {
		ip = instructions[++ip];
		break; 
	 }
	case FJUMP: {
		if (stack[sp--]) 
			ip = stack[sp--];
		break;
	}
	case LOAD: {
		sp++;
		stack[sp] = stack[instructions[++ip]];
		break; 
	}
	case STORE: {
		stack[instructions[++ip]] = stack[sp--]; 
		break;
	}
	case PUSH: {
		sp++;
		stack[sp] = instructions[++ip];	
		break;	
	}
	case POP: {
		int popped = stack[sp--];
		printf("%d\n", popped);
		break;
	}
	case CALL: {
		stack[++sp] = ip; 
		break;
	}
	case RET: {
		ip = stack[sp--];
		break;
	}
	}
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf("Error: no input file, shutting down\n");
		return -1;
	}

	char *filename = argv[1];

	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Error: input file could not be read\n");
		return -1;
	}

	instructions = malloc(sizeof(*instructions) * instruction_size);

	int scanner;
	int i = 0;

	while (fscanf(file, "%d", &scanner) > 0) {
		instructions[i] = scanner;
		i++;
		if (i >= instruction_size) {
			instruction_size *= 2;
			instructions = realloc(instructions, sizeof(*instructions) * instruction_size);
		}
		}
	
	instruction_count = i;

	fclose(file);

	sp = -1;

	while (running) {
		eval(fetch());
		ip++;
	}

	free(instructions);
}

