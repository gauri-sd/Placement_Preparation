#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
}NODE;

NODE *front=NULL;
NODE *rear=NULL;

void enqueue(int n)
{
	NODE *NN;
	NN=(NODE *)malloc(sizeof(NODE));
	NN->data=n;
	
	if(rear==NULL)
	{
		rear=NN;
		front=NN;
	}
	else
	{
		rear->next=NN;
		rear=rear->next;
	}
}
void disp()
{
	NODE *temp;
	temp=front;
	if(temp==NULL)
	{
		printf("Queue is Empty\n");
	}
	while(temp!=NULL)
	{
		printf("%d\t",temp->data);
		temp=temp->next;
	}
}
void dequeue()
{	
	NODE *temp;
	if(rear==NULL)
	{
		printf("\nQueue is Empty\n");
	}
	else
	{
		temp=front;
		front=front->next;
		printf("%d\t",temp->data);
		free(temp);
		//printf("%d\t",temp->next->data);
	}
	disp();
	//peek();
}

void peek()
{
	if(front!=NULL)	
	{
		printf("%d\t",front->data);
	}
}

void main()
{
	int n,op;
	do{
	printf("\n1. Enqueue\t2. Peek\t3. Dequeue\t4. Display\t5. Exit\n");
	scanf("%d",&op);
	switch(op)
	{
		case 1:printf("Enter Element to insert..\n");
			scanf("%d",&n);
			enqueue(n);
			break;
		case 2:peek();
			break;	
		case 3:dequeue();
			break;
		case 4: display();
			break;
		case 5:exit(0);		
			break;
		default :	printf("\n!!!Error\n");	
			break;
	}
	}while(op!=4);
}
