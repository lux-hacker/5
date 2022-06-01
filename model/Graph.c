#include "Graph.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void _dfs(Graph*, int, int, int*, int*, int);
void _dfs1(Graph*, int, int*, List*);
void _dfs2(Graph*, int, int*, int);
int _shortestWay(Graph*, int*, int*);

#define INT_MAX 10000000

Graph* createGraph(){
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->size = 0;
    graph->nodes = NULL;
    graph->matrix = NULL;
    graph->weights = NULL;
    return graph;
}

int addNode(Graph* graph, char* node){
    if(graph->nodes == NULL){
        graph->nodes = (char**) malloc(sizeof(char*));
        graph->nodes[0] = node;
        graph->size = 1;
        graph->matrix = (int**) malloc(sizeof(int*));
        graph->matrix[0] = (int*) malloc(sizeof(int));
        graph->matrix[0][0] = 0;
        graph->weights = (int**) malloc(sizeof(int*));
        graph->weights[0] = (int*) malloc(sizeof(int));
        graph->weights[0][0] = 0;
        return 0;
    }

    for(int i = 0; i < graph->size; i++){
        if(strcmp(graph->nodes[i], node) == 0) return 1;
    }

    graph->size++;
    graph->nodes = (char**) realloc(graph->nodes, graph->size * sizeof(char*));
    graph->nodes[graph->size - 1] = node;
    graph->matrix = (int**) realloc(graph->matrix, graph->size * sizeof(int*));
    graph->matrix[graph->size - 1] = NULL;
    graph->weights = (int**) realloc(graph->weights, graph->size * sizeof(int*));
    graph->weights[graph->size - 1] = NULL;
    for(int i = 0; i < graph->size; i++){
        graph->matrix[i] = (int*) realloc(graph->matrix[i], graph->size * sizeof(int));
        graph->matrix[i][graph->size - 1] = 0;
        graph->weights[i] = (int*) realloc(graph->weights[i], graph->size * sizeof(int));
        graph->weights[i][graph->size - 1] = 0;
        if(i == graph->size - 1) {
            for(int j = 0; j < graph->size; j++){
                graph->matrix[i][j] = 0;
                graph->weights[i][j] = 0;
            }
        }
    }
    return 0;
}

int addEdge(Graph* graph, char* n1, char* n2, int w){
    if(graph->size == 0) return 1;
    int id1 = -1, id2 = -1;
    for(int i = 0; i < graph->size; i++){
        if(strcmp(n1, graph->nodes[i]) == 0) id1 = i;
        else if(strcmp(n2, graph->nodes[i]) == 0) id2 = i;
    }

    if(id1 == -1 || id2 == -1) return 2;

    graph->matrix[id1][id2] = 1;

    graph->weights[id1][id2] = w;

    return 0;
}

int deleteEdge(Graph* graph, char* n1, char* n2){
    if(graph->size == 0) return 1;
    int id1 = -1, id2 = -1;
    for(int i = 0; i < graph->size; i++){
        if(strcmp(n1, graph->nodes[i]) == 0) id1 = i;
        else if(strcmp(n2, graph->nodes[i]) == 0) id2 = i;
    }

    if(id1 == -1 || id2 == -1) return 2;

    graph->matrix[id1][id2] = 0;

    graph->weights[id1][id2] = 0;
    return 0;
}

int deleteNode(Graph* graph, char* node){
    if(graph->size == 0) return 1;
    int id = -1;
    for(int i = 0; i < graph->size; i++){
        if(strcmp(node, graph->nodes[i]) == 0) id = i;
    }
    if(id == -1) return 2;

    char* buf = graph->nodes[id];
    for(int i = id; i < graph->size - 1; i++){
        graph->nodes[i] = graph->nodes[i+1];
    }
    graph->nodes = (char**) realloc(graph->nodes, (graph->size - 1) * sizeof(char*));
    free(buf);

    for(int i = 0; i < graph->size; i++){
        for(int j = id; j < graph->size - 1; j++){
            graph->matrix[i][j] = graph->matrix[i][j+1];
            graph->weights[i][j] = graph->weights[i][j+1];
        }
        graph->matrix[i] = (int*) realloc(graph->matrix[i], (graph->size - 1) * sizeof(int));
        graph->weights[i] = (int*) realloc(graph->weights[i], (graph->size - 1) * sizeof(int));
    }

    for(int i = id; i < graph->size - 1; i++){
        for(int j = 0; j < graph->size - 1; j++){
            graph->matrix[i][j] = graph->matrix[i+1][j];
            graph->weights[i][j] = graph->weights[i+1][j];
        }
    }
    free(graph->matrix[graph->size - 1]);
    free(graph->weights[graph->size - 1]);
    graph->weights = (int**) realloc(graph->weights, (graph->size - 1) * sizeof(int*));
    graph->matrix = (int**) realloc(graph->matrix, (graph->size - 1) * sizeof(int*));
    graph->size--;
    return 0;
}

void freeGraph(Graph* graph){
    for(int i = 0; i < graph->size; i++){
        free(graph->nodes[i]);
        free(graph->matrix[i]);
        free(graph->weights[i]);
    }

    free(graph->nodes);
    free(graph->matrix);
    free(graph->weights);

    free(graph);
}

void _dfs(Graph* graph, int v, int p, int* parent, int* color, int b) {
    if (color[v])
        return;
    parent[v] = p;
    color[v] = 1;

    if (v == b) return;

    for (int i = 0; i < graph->size; ++i) {
        if (graph->matrix[v][i] == 1 && color[i] == 0)
            _dfs(graph, i, v, parent, color, b);
    }
    color[v] = 2;
}

void _dfs2(Graph* graph, int src, int* components, int count){
    components[src] = count;
    for (int i = 0; i < graph->size; ++i) {
        if (graph->matrix[src][i] == 1 && components[i] == 0)
            _dfs2(graph, i, components, count);
    }
}

void _dfs1(Graph* graph, int src, int* color, List* order){
    color[src] = 1;
    for (int i = 0; i < graph->size; ++i) {
        if (graph->matrix[src][i] == 1 && color[i] == 0)
            _dfs1(graph, i, color, order);
    }
    pushBack(order, graph->nodes[src], src);
}

List* dfs(Graph* graph, char* n1, char* n2){
    if(graph->size == 0) return NULL;
    int id1 = -1, id2 = -1;
    for(int i = 0; i < graph->size; i++){
        if(strcmp(n1, graph->nodes[i]) == 0) id1 = i;
        else if(strcmp(n2, graph->nodes[i]) == 0) id2 = i;
    }

    if(id1 == -1 || id2 == -1) return NULL;

    int* parent = (int*) malloc(graph->size * sizeof(int));
    int* color = (int*) malloc(graph->size * sizeof(int));
    for(int i = 0; i < graph->size; i++){
        color[i] = 0;
        parent[i] = -1;
    }
    _dfs(graph, id1, id2, parent, color, id2);

    if(color[id1] == 0 || color[id2] == 0) return NULL;

    List* way = (List*) malloc(sizeof(List));
    way->head = NULL;

    pushFront(way, graph->nodes[id2], id2);
    int n = id2;
    while(1){
        n = parent[n];
        if(n == id2){
            break;
        } else {
            pushFront(way, graph->nodes[n], n);
        }
    }

    free(parent);
    free(color);
    return way;
}

void pushFront(List* list, char* str, int id){
    if(list->head == NULL){
        list->head = (ListNode*) malloc(sizeof(ListNode));
        list->head->next = NULL;
        list->head->node = str;
        list->tail = list->head;
        list->head->id = id;
        list->head->prev = NULL;
    } else {
        ListNode* t = (ListNode*) malloc(sizeof(ListNode));
        t->next = list->head;
        list->head->prev = t;
        t->prev = NULL;
        list->head = t;
        t->node = str;
        t->id = id;
    }
}

void pushBack(List* list, char* str, int id){
    if(list->tail == NULL){
        list->tail = (ListNode*) malloc(sizeof(ListNode));
        list->tail->next = NULL;
        list->tail->node = str;
        list->head = list->tail;
        list->tail->id = id;
        list->tail->prev = NULL;
    } else {
        ListNode* t = (ListNode*) malloc(sizeof(ListNode));
        list->tail->next = t;
        t->prev = list->tail;
        list->tail = t;
        t->node = str;
        t->id = id;
        t->next = NULL;
    }
}

void freeList(List* list){
    ListNode* head = list->head;
    while(head != NULL){
        ListNode* t = head;
        head = head->next;
        free(t);
    }
    free(list);
}

int _shortestWay(Graph* graph, int* parent, int* d) {
    for(int k = 0; k < graph->size - 1; k++) {
        for (int i = 0; i < graph->size; i++) {
            for (int j = 0; j < graph->size; j++) {
                if (graph->matrix[i][j] == 1) {
                    if (d[j] > d[i] + graph->weights[i][j]) {
                        d[j] = d[i] + graph->weights[i][j];
                        parent[j] = i;
                    }
                }
            }
        }
    }

    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (graph->matrix[i][j] == 1) {
                if (d[j] > d[i] + graph->weights[i][j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

List* shortestWay(Graph* graph, char* n1, char* n2){
    if(graph->size == 0) return NULL;
    int id1 = -1, id2 = -1;
    for(int i = 0; i < graph->size; i++){
        if(strcmp(n1, graph->nodes[i]) == 0) id1 = i;
        else if(strcmp(n2, graph->nodes[i]) == 0) id2 = i;
    }

    if(id1 == -1 || id2 == -1) return NULL;

    int* parent = (int*) malloc(graph->size * sizeof(int));
    int* d = (int*) malloc(graph->size * sizeof(int));

    for(int i = 0; i < graph->size; i++){
        d[i] = INT_MAX;
        parent[i] = -1;
    }

    d[id1] = 0;

    int k = _shortestWay(graph, parent, d);

    if(k == 1){
        free(parent);
        free(d);
        return NULL;
    }

    List* way = (List*) malloc(sizeof(List));
    way->head = NULL;

    pushFront(way, graph->nodes[id2], id2);
    int n = id2;
    while(1){
        n = parent[n];
        if(n == -1){
            break;
        } else {
            pushFront(way, graph->nodes[n], n);
        }
    }

    free(parent);
    free(d);
    return way;
}

Vector* getSCC(Graph* graph){
    Graph* T_graph = createGraph();
    T_graph->size = graph->size;
    T_graph->nodes = graph->nodes;
    T_graph->weights = graph->weights;
    T_graph->matrix = (int**) malloc(graph->size * sizeof(int*));
    for(int i = 0; i < graph->size; i++){
        T_graph->matrix[i] = (int*) malloc(graph->size * sizeof(int));
        for(int j = 0; j < graph->size; j++){
            T_graph->matrix[i][j] = graph->matrix[j][i];
        }
    }

    List* order = (List*) malloc(sizeof(List));
    order->tail = NULL;
    order->head = NULL;

    int* color = (int*) malloc(graph->size * sizeof(int));
    int* components = (int*) malloc(graph->size * sizeof(int));
    for(int i = 0; i < graph->size; i++){
        color[i] = 0;
        components[i] = 0;
    }

    for(int i = 0; i < graph->size; i++){
        if(color[i] == 0)
            _dfs1(graph, i, color, order);
    }

    int count = 0;
    ListNode* tail = order->tail;
    while(tail != NULL){
        if(components[tail->id] == 0){
            count++;
            _dfs2(T_graph, tail->id, components, count);
        }
        tail = tail->prev;
    }

    Vector* SCC = (Vector*) malloc(sizeof(Vector));
    SCC->size = count;
    SCC->components = (List**) malloc(SCC->size * sizeof(List*));
    for(int i = 0; i < count; i++){
        SCC->components[i] = (List*) malloc(sizeof(List));
        SCC->components[i]->head = NULL;
        SCC->components[i]->tail = NULL;
    }
    for(int i = 0; i < graph->size; i++){
        pushBack(SCC->components[components[i] - 1], graph->nodes[i], i);
    }

    free(color);
    free(components);
    for(int i = 0; i < graph->size; i++){
        free(T_graph->matrix[i]);
    }
    free(T_graph->matrix);
    free(T_graph);
    freeList(order);
    return SCC;
}
