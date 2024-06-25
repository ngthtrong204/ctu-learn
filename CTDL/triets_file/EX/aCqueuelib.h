#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef int ElementType;
typedef int Position;

typedef struct{
	ElementType data[MAXSIZE];
	Position front;
	Position rear;
}Queue;

void makeNull(Queue *Q){
	Q->front = Q->rear = -1;
}

int isEmptyQ(Queue Q){
	return Q.front == -1;
}

int isFullQ(Queue Q){
	return ((Q.rear+1) % MAXSIZE == Q.front);
}

void enQueue(Queue *Q, ElementType x){
	if(isFullQ(*Q)){
		printf("Queue is full");
		return;
	}
	else {
        if (isEmptyQ(*Q)) {
            Q->front = 0;
            Q->rear = 0;
        } else {
            Q->rear = (Q->rear + 1) % MAXSIZE;
        }
        Q->data[Q->rear] = x;
	}
}

ElementType deQueue(Queue *Q){
	int x;
	if(isEmptyQ(*Q)){
		printf("Queue is empty");
		return -1;
	}
	else{
		x = Q->data[Q->front];
		if (Q->front == Q->rear) {
            makeNull(Q); 
        } else {
            Q->front = (Q->front + 1) % MAXSIZE;
        }
    	return x;
	}
}

