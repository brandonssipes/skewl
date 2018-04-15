#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

struct Linklist {
  Linklist* next;
  int data;
}; 

void print_list(Linklist* head) {
  Linklist * current = head;

  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}

void addToFront(Linklist * head, int data){
  Linklist * current = head;
  Linklist * newone = (Linklist*)malloc(sizeof(Linklist));
  newone->data = data;
  newone->next = current;
  head=newone;
}

//append to the end
void push(Linklist * head, int data) {
  Linklist * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = (Linklist*) malloc(sizeof(Linklist));
  current->next->data = data;
  current->next->next = NULL;
}

//pop from the front
int pop(Linklist ** head) {
  int retval;
  Linklist * next_node = NULL;

  if (*head == NULL) {
    return -1;
  }

  next_node = (*head)->next;
  retval = (*head)->data;
  free(*head);
  *head = next_node;

  return retval;
}
/**
 * Some of aviv's code that I stole.  So currently my code does not work
 * so look at his and see if I can make this work.
 * tbh I don't even know if aviv's code will help at all
 * I just kind of stole it with out a great understanding of what it is doing
 * I think it is a linked list with strings though
 */
/*
struct word{
  char str[1024];
  int count;
};

struct word_list{
  struct word * list;
  int last;
  int size;
};


struct word_list * new_word_list(int s){
  struct word_list * l = malloc(sizeof(struct word_list));
  l->list = malloc(sizeof(struct word)*s);
  l->last = 0;
  l->size = s;
  return l;
}

void add_word(char *s,struct word_list * l){
  int i;

  for(i=0;i<l->last;i++){
    if( strcmp(s,l->list[i].str) == 0){
      l->list[i].count++;
      return;
    }
  }

  if(l->last+1 == l->size){
    l->list = realloc(l->list, sizeof(struct word)*l->size*2);
    l->size*=2;
  }

  strcpy(l->list[l->last].str,s);
  l->list[l->last].count=1;
  l->last++;

}
*/
