# CSE 109 - Systems Software - Spring 2022 - Homework 4

**Due Date: 3/7/2022 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

You will implement a linked list data structure in this assignment. The linked list will consist of a `head` pointer and a tail pointer. The head pointer will point to a `Node` struct, which will hold a data void pointer as well as a pointer to the next node in the list. The `tail` pointer will point to the final node in the linked list. The `next` pointer on the tail will point to `NULL`.


```
  ┌─────────┐    ┌─────────┐   ┌─────────┐    ┌─────────┐
  │     head│--->│  void*  │-->│  void*  │--->│  void*  │---> NULL
  │         │    └─────────┘   └─────────┘    └─────────┘
  │     tail│--------------------------------------^
  └─────────┘
```


The `List` and `Node` structs are declared in `linkedlist.h`, along with a number of functions you will need to implement.

```c
// Initialize an empty list. The head and tail pointers should point to NULL.
void initList(List* list_pointer);

// Create Node struct containing a void pointer to an item, return pointer to the newly created Node struct
Node* createNode(void* item);

// Insert new Node at the end of the list, containing a void pointer to item. The next pointer on this Node
// points to NULL. On success return 0. On failure, return 1.
int insertAtTail(List* list_pointer, void* item);

// Insert a Node at the head of the list, containing a void pointer to item. The next pointer on the
// newly created node points to the previous head of the list. On success return 0. On failure, return 1.
int insertAtHead(List* list_pointer, void* item);

// Insert a Node at the specified index, containing a void pointer to item. If the index is greater than
// the length of the list, the program should crash. On success return 0. On failure, return 1.
int insertAtIndex(List* list_pointer, int index, void* item);

// Remove Node from the end of list and return the void pointer it contains. The preceeding Node should
// point to NULL after this operation. On failure return a NULL pointer.
void* removeTail(List* list_pointer);

// Remove Node from start of list and return return the void pointer it contains. The following Node should 
// be the new head of the list. On failure return a NULL pointer.
void* removeHead(List* list_pointer);

// Insert Node item at a specified index and return return the void pointer it contains. The Node at the specified
// index before this function is called should be the next Node following the newly inserted Node.
// On failure return a NULL pointer.
void* removeAtIndex(List* list_pointer, int index);

// Return the pointer stored in the Node at the specified index. On failure return a NULL pointer. 
void* itemAtIndex(List* list_pointer, int index);
```

There is a print function that is already implemented for you. This will help you inspect the list as you write the above functions.

## Build Instructions

Write build instructions here. Explain to the user all the steps necessary to build this project including:

- What software (including versions) are needed?
  **The two software that I used are Visual Studio Code and Ubuntu. My Visual Studio Code is currently running on version 1.65.0, and my Ubuntu is running on version 20.04 LTS.**
- What system architectures and operating systems are supported?
  **I am currently using the 'Windows_NT x64 10.0.19043' operating system and it worked for me. I am unsure which other operating systems and system architectures work and don't work.**
- What commands need to be entered to build the project?
  **To build the project, I input the command 'make test' into Ubuntu. Following that, I input the command './build/bin/test' to run the executable 'test' which was created by the make command entered previously.**

## Usage

Write usage instructions here. Explain to the user how they can integrate your library into their project. Usage instructions might include:

- What the user should `#include` into their project and where.
  **The user will have to include "linkedlist.h" and <stdlib.h> in the files 'test.c', 'lib.c' and 'main.c'. They would also have to include <stdio.h> in the file 'lib.c'.**
- An example command of how the user might build their project to link to your library.
  **gcc test/test.c -c -I include**
- How to create a linked list using your library.
  **To create a linked list using my library, the user would start by declaring a List and a void*, for this example the List will be named '*list' and the void* will be named 'item'. After declaring the two variables, the user will input the command 'list = (List*)malloc(sizeof(List));' to allocate the memory of the list. Lastly, the user would enter the command 'initList(list);'. **
- How to use the linked list.
  **To use the linked list, you have 7 functions: insertAtTail(List* list_pointer, void* item), int insertAtIndex(List* list_pointer, int index, void* item), int insertAtHead(List* list_pointer, void* item), void* removeTail(List* list_pointer), void* removeHead(List* list_pointer), void* removeAtIndex(List* list_pointer, int index), and void* itemAtIndex(List* list_pointer, int index). These 7 functions are self-explainable and do what their name says they do.**
- How to clean up the linked list to avoid leaking memory.
  **To clean up the linked list and avoid leaking memory, the user should accompany every 'insert' method, with one 'remove' method. By doing this, each malloc statement will have a free statement.**

## Examples

Write two examples demonstrating how to use your linked list library. These example should be complete in the sense that the user can just copy and paste them into their code and everything should work as long as they follow the build and usage instructions you gave them.

I will be using these variables in both examples:

**int v = 0x111111;
int w = 0x222222;
int x = 0x333333;
int y = 0x444444;
int z = 0x555555;**

1)
List *list1; void* item1;
list1 = (List *)malloc(sizeof(List));
initList(list1);
insertAtHead(list1, &v);
insertAtHead(list1, &w);
insertAtIndex(list1, 1, &x);
removeHead(list1);
removeAtIndex(list1,0);
removeTail(list1);

2)
List *list2; void* item2;
list2 = (List *)malloc(sizeof(List));
initList(list2);
insertAtTail(list2, &z);
insertAtHead(list2, &y);
removeTail(list2);
insertAtIndex(list2, 0, &x);
removeAtIndex(list2, 1);
removeHead(list2);
