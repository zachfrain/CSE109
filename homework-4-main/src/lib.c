#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	printf("\nList: \n\n\t"); 
	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}

//Initialize an empty list (head and tail to NULL)
void initList(List* list_pointer){
	//Setting the head to NULL
	list_pointer -> head = NULL;
	//Setting the tail to NULL
	list_pointer -> tail = NULL;
}

//Create a new node containing the param item
Node* createNode(void* item){
	//Create a null node pointer
	Node* node = NULL;
	//Allocating memory for the created node
	node = (Node*)malloc(sizeof(Node));
	//Setting the node's item pointer to the parameter 'item'
	node -> item = item;
	//Setting the node's next pointer to null (this is only one node so there is nothing following it)
	node -> next = NULL;
	//Return the pointer to the newly created node
	return node;
}

//Create a node using the item parameter and insert that node at the tail of the linked list
int insertAtTail(List* list_pointer, void* item){
	//Using createNode to create the Node being inserted
	Node* node = createNode(item);
	//Checking if memory allocation for node was successful, return 1 if not.
	if(node == NULL){
		printf("Malloc failed to allocate memory.");
		return 1;
	}
	//If the tail of the list is NULL
	if(list_pointer -> tail == NULL){
		//Setting the tail to point at node
		list_pointer -> tail = node;
	} else /*If tail is not NULL*/ {
		//Setting the current tail's next pointer to point at node
		list_pointer -> tail -> next = node;
		//Setting the tail pointer to point at node
		list_pointer -> tail = node;
	}
	//If this is the first node in the list
	if(list_pointer -> head == NULL){
		//Setting the head pointer to point at node
		list_pointer -> head = node;
	}
	return 0; //The return must be 0 because the only failure would have been caught at this point
}

//Create a node using the item parameter and insert that node at the head of the linked list
int insertAtHead(List* list_pointer, void* item){
	//Using createNode to create the Node being inserted
	Node* node = createNode(item);
	//Checking if memory allocation for node was successful, return 1 if not.
	if(node == NULL){
		printf("Malloc failed to allocate memory.");
		return 1;
	}
	node -> next = list_pointer -> head; //Setting node's next pointer to point to the current head of the list
	list_pointer -> head = node; //Setting the head pointer for the list to point to node.
	//If this is the first node in the list
	if(list_pointer -> tail == NULL){
		//Setting the tail pointer to point at node
		list_pointer -> tail = node;
	}
	return 0; //The return must be 0 because the only failure would have been caught at this point
}

//Create a node using the item parameter and insert that node in the list at the specified index parameter.
int insertAtIndex(List* list_pointer, int index, void* item){
	int listSize = sizeof(list_pointer) / sizeof(struct Node*); //creating listSize to determine the size of the list
	if(index == 0 && list_pointer -> head == NULL){
		return insertAtHead(list_pointer, item); //if the index is 0 and the head is NULL, return insertAtHead
	}
	if(index > listSize){
		exit(0); //if the index is greater than the size of the list, the program will crash
	}
	Node* node = createNode(item); //using createNode to create the node that will be inserted in the list
	if(node == NULL){ //checking if the memory allocation worked, if not, return 1
		printf("Malloc failed to allocate memory.\n");
		return 1;
	}
	Node* temp = list_pointer -> head; //creating a temp node at the beginning of the list in order to iterate the list
	for(int i = 0; i < index - 1; i++){
		temp = (Node*)temp -> next; //temp is being set to the next node every time this loop runs
	}
	if(!temp -> next){ //this is only true if the index given is the tail of the list
		node -> next = NULL; //there will be no next node if this is the tail, so set next to NULL
		temp -> next = (struct Node*)node;
		list_pointer -> tail = node;
	}
	node -> next = temp -> next; //setting the next for node to the next for temp
	temp -> next = (struct Node*)node; //setting next for temp to node
	return 0; //The return must be 0 because the only failure would have been caught at this point
}

//Remove the tail node and return the void reference to it
void* removeTail(List* list_pointer){
	if(list_pointer -> tail == NULL){ //if the tail of the list is NULL, this function will fail and a null will be returned
		return NULL;
	}

	void* voidReturn = list_pointer -> tail -> item; //initializing the void reference which will be returned

	if(list_pointer -> head == list_pointer -> tail){ //if there is only one node in the list
		Node* freeNode = list_pointer -> tail; //initializing the freeNode, which will be used to deallocate the memory previously allocated by the tail node
		list_pointer -> head = NULL; list_pointer -> tail = NULL; //setting the head and tail to NULL (the head and tail were both the same node)
		free(freeNode); //deallocating the memory of the removed node
		return voidReturn; //return the void reference
	}

	Node* temp = list_pointer -> head; //creating a temp node set to head
	while(temp -> next != (struct Node*)list_pointer -> tail){ //iterate until temp is the node 1 index before tail
		temp = (Node*)temp -> next;
	}
	Node* freeNode = (Node*)temp -> next; //initializing the freeNode, which will be used to deallocate the memory previously allocated by the tail node
	temp -> next = NULL; //setting the previous tail to NULL
	list_pointer -> tail = temp; //setting the tail to temp
	free(freeNode); //deallocating the memory of the removed node
	return voidReturn; //return the void reference
}

//Remove the head node and return the void reference to it
void* removeHead(List* list_pointer){
	if(list_pointer -> head == NULL){ //if the head of the list is NULL, this function will fail and a null will be returned
		return NULL;
	}

	void* voidReturn = list_pointer -> head -> item; //initializing the void reference which will be returned

	if(list_pointer -> head == list_pointer -> tail){ //if there is only one node in the list
		Node* freeNode = list_pointer -> head; //initializing the freeNode, which will be used to deallocate the memory previously allocated by the head node
		list_pointer -> head = NULL; list_pointer -> tail = NULL; //setting the head and tail to NULL (the head and tail were both the same node)
		free(freeNode); //deallocating the memory of the removed node
		return voidReturn; //return the void reference
	}

	Node* freeNode = list_pointer -> head; //initializing the freeNode, which will be used to deallocate the memory previously allocated by the head node
	list_pointer -> head = (Node*)list_pointer -> head -> next; //setting the current head of the list to the node following it
	free(freeNode); //deallocating the memory of the removed node
	return voidReturn; //return the void reference
}

//Remove the node at the give nindex and return the void reference to it
void* removeAtIndex(List* list_pointer, int index){
	if(index == 0){
		return removeHead(list_pointer); //if the index given is 0, this can be re-written as removeHead
	}
	Node* temp = list_pointer -> head; //creating a temp node pointed at the head of the list
	for(int i = 0; i < index - 1; i++){
		temp = (Node*)temp -> next; //iterating through the list
	}
	if(!temp){ //if the index given is out of bounds, NULL will be returned
		return NULL;
	}
	if(!temp -> next){
		return removeTail(list_pointer); //if the index given is the last index, this can be re-written as removeTail
	}
	Node* freeNode = (Node*)temp -> next; //initializing the freeNode, which will be used to deallocate the memory previously allocated by node at the given index
	void* voidReturn = freeNode -> item; //initializing the void reference which will be returned
	temp -> next = freeNode -> next; //setting the next pointer of temp to the next pointer of freeNode
	free(freeNode); //deallocating the memory of the removed node
	return voidReturn; //return the void reference
}

//Return the void reference to the item at the given index
void* itemAtIndex(List* list_pointer, int index){
	Node* temp = list_pointer -> head; //creating a temp node pointer at the head of the list
	for(int i = 0; i < index; i++){
		temp = temp -> next; //iterating through the list until the node at index is reached
	}
	return temp -> item; //return the void reference to the item at the given index
}
