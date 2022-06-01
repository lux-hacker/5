#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

typedef struct Graph{
    char** nodes;
    int** matrix;
    int size;
    int** weights;
} Graph;

typedef struct ListNode{
    char* node;
    int id;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct List{
    ListNode* head;
    ListNode* tail;
} List;

typedef struct Vector{
    List** components;
    int size;
} Vector;

void pushBack(List*, char*, int);
void pushFront(List*, char*, int);
void freeList(List*);

Graph* createGraph();

List* dfs(Graph*, char*, char*);
List* shortestWay(Graph*, char*, char*);
Vector* getSCC(Graph*);

int addNode(Graph*, char*);
int addEdge(Graph*, char*, char*, int);
int deleteNode(Graph*, char*);
int deleteEdge(Graph*, char*, char*);

void freeGraph(Graph*);

#endif //LAB5_GRAPH_H
