#ifdef LL
#define LL

class LL {
    struct Node {
      Node* next;
      int data;
    }
    
    void printList(Linklist*x);
    void addToFront(Linklist*x, int y);
    void push(Linklist*x, int y);
    int pop (Linklist**head);
}

#endif
