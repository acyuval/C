#include <stdio.h>
#include <stdlib.h>

/* Define the structure for a node in the linked list */
struct Node {
    int data;
    struct Node* next;
};
struct Node * flip (struct Node * head);
struct Node * recflip (struct Node * head, struct Node ** new_head); 
/* Function to create a new node */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

/* Function to print the linked list */
void printList(struct Node* head) {
    struct Node* current = head;
    int counter = 0;
	while (current != NULL && counter < 10) {
        printf("%d -> ", current->data);
        current = current->next;
		counter++;
    }
    printf("NULL\n");
}

int main() {
    /* Initialize the head of the linked list */
    struct Node* head = NULL;
    struct Node* current = head;
	struct Node * new_head = NULL;
    /* Create and add nodes to the linked list */
    int i;
    for (i = 1; i <= 10; ++i) {
        struct Node* newNode = createNode(i * 10);
        newNode->next = head;
        head = newNode;
    }

    /* Print the linked list */
    printf("Linked List: ");
    printList(head);

	recflip(head ,&new_head);
/* 	flip(head); */

    printf("\nLinked List after: ");
    printList(new_head);
    /* Free memory by deleting all nodes */
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}



struct Node * flip (struct Node * head)
{
	struct Node * prev = NULL , *cur = NULL , *next = NULL;

	cur = head;
	while(next != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;	
	}

	return; 
}

struct Node * recflip (struct Node * head, struct Node ** new_head)
{
	struct Node * temp_node = NULL;

	if(head->next == NULL)
	{
		*new_head = head;
		return head; 
	}

	temp_node = recflip(head->next, new_head);
	head->next = NULL;
	temp_node->next = head;
	return head;

	 
}