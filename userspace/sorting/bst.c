#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct node{
int key;
struct node *left, *right;
};
typedef struct node* NODE;
void inorder(NODE);
void insert(int);
void printTree();
NODE root;
int main()
{
	int *arr;
	int i,j,k, op,input;
	while(1)
	{
		printf("Enter operation\n 1- Insert\n 2- Delete\n 3-Print\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("Enter the value to insert\n");
				scanf("%d",&input);
				insert(input);
				printf("Node inserted\n");
				break;
			case 2:
				printf("Node deleted\n");
				break;
			case 3:
				printTree();
				break;
			default:
				printf("Invalid argument!!!\n");
				sleep(1);
		}

	}
return 0;
}

void insert(int value)
{
	NODE new,temp;
	if(root == NULL)
	{
		new = (NODE)malloc(sizeof(struct node));
		new->left = new->right = NULL;
		root = new;
		root->key = value;
	}
	else
	{
		temp = root;
		NODE prev;
		while(temp)
		{
			if(value < temp->key )
			{
				prev = temp;
				temp = temp->left;
			}
			else
			{
				prev=temp;
				temp = temp->right;
			}
		}
		new = (NODE) malloc(sizeof(struct node));
		new->key = value;
		if(prev->key > value)
			prev->left = new;
		else
			prev->right = new;
	}
}
void printNode(NODE temp)
{
	if(temp->left != NULL || temp->right != NULL)
	{
		printf("     %d\n",temp->key);
		if(temp->left != NULL)
			printf("%d\n",temp->left->key);
		if(temp->right != NULL)
			printf("      %d\n\n",temp->right->key);
	}

}
void printLeft(NODE temp)
{
	while(temp)
	{
		printNode(temp);
		temp = temp->left;
	}
	
}
void printRight(NODE temp)
{
	while(temp)
	{
		printNode(temp);
		temp = temp->right;
	}
}
void printTree()
{
	pthread_t pthd1, pthd2;
	pthread_create(&pthd1,NULL,(void *)printLeft,(void *)root);
	pthread_join(pthd1,NULL);
	printf("Left branch ends\n");
	pthread_create(&pthd2,NULL,(void *)printRight,(void *)root);
	pthread_join(pthd2,NULL);
	printf("Right branch ends\n");
}
