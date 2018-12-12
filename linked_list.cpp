/*
 * This program shows how to create and maintain a linked list.
 *
 * Dr. Xiao Qin <xqin@auburn.edu>
 *
 * Samuel Ginn College of Engineering
 * Auburn University, AL 36849-5347 
 * http://www.eng.auburn.edu/~xqin/
 *
 */ 
//Bug 1,  Bug 2, Bug 3, Bug 4
#include <iostream>
#include <assert.h>
#include <cstdlib>
using namespace std;

struct node {
   int data;
   node *next;
};

typedef node* nodePtr;

void insertNode(nodePtr& root, int info);
//Another possible prototype
//void insertNode(nodePtr& root, nodePtr newNodePtr);
void insertNodeSortedList(nodePtr& root, int info);
void appendNode(nodePtr& root, int info);

void printList(nodePtr root);
void deleteHead(nodePtr& root);
void deleteTail(nodePtr& root);
void deleteTail1(nodePtr& root); //another way to implement deleteTail()
void deleteNode(nodePtr& root, int info); //delete a node, where data==info

int main()
{
   nodePtr head;       
   nodePtr current;  // This will point to each node as it traverses the list

   head = NULL; //Initially, it is an empty list
   cout << "Test printList() and delete() when the list is emply...\n";
   printList(head);
   deleteHead(head);
   deleteTail(head);

   cout << "Test insertNode: 8, 3, and 15 are inserted to the list...\n";
   insertNode(head, 8);
   insertNode(head, 3);
   insertNode(head, 15);
   printList(head);
  
   cout << "Test deleteHead: 15 should be deleted from the list...\n"; 
   deleteHead(head);
   printList(head);

   //How many test cases should we cover for deleteTail?
   cout << "Test deleteTail: 8 should be deleted from the list...\n"; 
   deleteTail(head);
   printList(head);
   cout << "Test deleteTail1: 3 should be deleted from the list...\n"; 
   deleteTail1(head);
   printList(head);
  
   cout << "Test appendNode: 25, 14, 82 and 62 are inserted to the list...\n";
   appendNode(head, 25);
   appendNode(head, 14);
   appendNode(head, 82);
   appendNode(head, 62);
   printList(head);

   cout << "Test deleteNode: 25, the first node ...\n";
   deleteNode(head, 25);
   printList(head);

   cout << "Test deleteNode: 62, the last node ...\n";
   deleteNode(head, 62);
   printList(head);
  
   cout << "Test deleteNode: 33, no such a node ...\n";
   deleteNode(head, 33);
   printList(head);

   cout << "Test deleteNode: 14, only one node left after this deletion ...\n";
   deleteNode(head, 14);
   printList(head);

   //This test case will discover Bug 2
   cout << "Test deleteNode: 82, emply list after this deletion ...\n";
   deleteNode(head, 82);
   printList(head);

   assert(head == NULL);
   cout << "Test insertNodeSortedList: Insert 9 ...\n";
   insertNodeSortedList(head, 9);
   printList(head);
   //The following statement discovers Bug 3
   cout << "Test insertNodeSortedList: Insert 5 ...\n";
   insertNodeSortedList(head, 5);
   printList(head);
   cout << "Test insertNodeSortedList: Insert 3 ...\n";
   insertNodeSortedList(head, 3);
   printList(head);
   cout << "Test insertNodeSortedList: Insert 8 ...\n";
   insertNodeSortedList(head, 8);
   printList(head);
   cout << "Test insertNodeSortedList: Insert 15 ...\n";
   insertNodeSortedList(head, 15);
   printList(head);

   return 0;
}

void printList(nodePtr root) {
   nodePtr cur;
   
   if (root == NULL) 
      cout << "This is an empty list\n";

   cur = root;
   while (cur != NULL) {
      cout << cur->data << endl;
      cur = cur->next;
   }
}

void insertNode(nodePtr& root, int info) {
   nodePtr cur;

   cur = new node; //Do not use this: new nodePtr
   assert(cur != NULL); //Ensure that memory is allocatd 
   
   cur->data = info;
   cur->next = NULL;

   if (root == NULL) //If the list is empty, cur becomes the root
      root = cur;
   else { //Insert cur as the root of the list
      cur->next = root;
      root = cur;
   }
}
 
void appendNode(nodePtr& root, int info) {
   nodePtr cur;
   nodePtr pre;

   cur = new node; //Do not use this: new nodePtr
   assert(cur != NULL); //Ensure that memory is allocatd 
   
   cur->data = info;
   cur->next = NULL;

   if (root == NULL) //If the list is empty, cur becomes the root
      root = cur;
   else { //Append the new node at the end of the list
      pre = root;
      while (pre->next != NULL) 
         pre = pre->next;
   
      pre->next = cur;
   }
}
 
void deleteHead(nodePtr& root) {
   nodePtr cur;

   if (root != NULL) {
      cur = root; //Deleted node must be returned to the OS
      root = root->next;
      delete cur;
   }
   else 
      cout << "This is an empty list. No head is deleted!\n";
}

void deleteTail(nodePtr& root) {
   nodePtr cur, pre;
  
   if (root == NULL) //Case 1: Empty list
      cout << "This is an empty list. No tail is deleted!\n";
   else { 
      if (root->next == NULL) { //Case 2: List has one node
         free(root);
         root = NULL;
      }
      else { //Case 3: List has more than one node
         pre = root;
         cur = root->next;
         while (cur->next != NULL) {
            pre = cur;
            cur = cur->next;
         }
         
         pre->next = NULL;
         free(cur); //delete cur, which is pointing at the last node
      }
   }
}

void deleteTail1(nodePtr& root) {
   nodePtr cur, pre;
  
   if (root == NULL) //Case 1: Empty list
      cout << "This is an empty list. No tail is deleted!\n";
   else { 
      pre = NULL;
      cur = root;
      while (cur->next != NULL) {
         pre = cur;
         cur = cur->next;
      }
    
      if (pre == NULL) { //Case 2: one node
         assert(cur == root);
         delete root;
         root = NULL;
      }
      else {
         pre->next = NULL;
         delete cur; //delete cur, which is pointing at the last node
      }
   }
}

void deleteNode(nodePtr& root, int info) {
   nodePtr cur, pre;
  
   if (root == NULL) //Empty list
      cout << "This is an empty list. No node is deleted!\n";
   else { 
      pre = NULL;
      cur = root;
      while (cur != NULL) { //cur->next != NULL is Bug 1 - core dump occur
         if (cur->data != info) { //compare and does not match
            pre = cur;
            cur = cur->next;
         }
         else { //match and delete node pointed by cur
            if (pre == NULL) { //cur is pointing to the first node
               root = root->next;
               delete cur;
               cur = root;
            }
            else { //cur is NOT pointing to the first node
               pre->next = cur->next;
               delete cur;
               cur = pre->next; 
            }
         }
      }
      
      //Bug 2: With the following two statement, only when delete one-node list, can core dump occur 
      //pre->next = NULL;  //adding these two statements - core dump occur
      //delete cur; //delete cur, which is pointing at the last node
   }
}

void insertNodeSortedList(nodePtr& root, int info) { //Maintain a sorted list, non-decreasing order
   nodePtr cur;
   nodePtr pre;
   nodePtr new_ptr;

   new_ptr = new node; //Do not use this: new nodePtr
   assert(new_ptr != NULL); //Ensure that memory is allocatd 
   
   new_ptr->data = info;
   new_ptr->next = NULL;

   if (root == NULL) //If the list is empty, cur becomes the root
      //root = cur; //Bug 3: core dump occur
      root = new_ptr;
   else { //Append the new node at the end of the list
      pre = NULL;
      cur = root;
      while ((cur != NULL) && (cur->data < info)) {
         pre = cur;
         cur = cur->next;
      }
   
      /*This is Bug 4
      //cur == NULL, insert new node as the last node in the list
      if (cur == NULL) {
        pre->next = new_ptr;
      else {
        new_ptr->next = cur; //can we switch these two statements?
        pre->next = new_ptr;
      }*/
      
      if (pre == NULL) { //insert new node to the head of the list
         new_ptr->next = root;
         root = new_ptr;
      }
      else { //insert new node in the list, non-head node
         new_ptr->next = cur;
         pre->next = new_ptr;
      }
   }
}
