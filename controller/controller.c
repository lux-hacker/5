#include "controller.h"
#include <stdio.h>
#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>

int getInt();
void addNewNode(Graph*);
void addNewEdge(Graph*);
void deleteExistNode(Graph*);
void deleteExistEdge(Graph*);
void findWay(Graph*);
void findShortestWay(Graph*);
void findSCC(Graph*);

int getInt(){
    char *msg = "";
    while (1) {
        printf("%s", msg);
        char *input = readline("");
        msg = "======[MUST BE NUMBER]======\n--> ";
        char *ptr;
        int value = (int) strtol(input, &ptr, 10);
        if (strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            return value;
        }
        free(input);
    }
}

void menu(){
    printf("======[Graph to PNG]======\n");
    printf("Enter filename of future picture\n--> ");
    char* pict_name = readline("");
    Graph* graph = createGraph();
    while(1){
        printMenu();
        int n = getInt();
        switch (n) {
            case 0:{
                freeGraph(graph);
                free(pict_name);
                return;
            }
            case 1:{
                addNewNode(graph);
                graphToPng(graph, pict_name);
                break;
            }
            case 2:{
                addNewEdge(graph);
                graphToPng(graph, pict_name);
                break;
            }
            case 3:{
                deleteExistNode(graph);
                graphToPng(graph, pict_name);
                break;
            }
            case 4:{
                deleteExistEdge(graph);
                graphToPng(graph, pict_name);
                break;
            }
            case 5:{
                printGraph(graph);
                break;
            }
            case 6:{
                findWay(graph);
                break;
            }
            case 7:{
                findShortestWay(graph);
                break;
            }
            case 8:{
                findSCC(graph);
                break;
            }
            default:{
                printf("======[ERROR]======\n");
                printf("This menu point doesn't exist\n");
                break;
            }
        }
    }
}

void addNewNode(Graph* graph){
    char* id = NULL;
    char* msg = "";
    do{
        if(id != NULL){
            free(id);
            id = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id (4 letters): ");
        id = readline("");
    } while(strlen(id) != 4);

    int n = addNode(graph, id);
    if(n == 1){
        printf("======[ERROR]======\n");
        printf("This node have already existed\n");
        free(id);
    }
}

void addNewEdge(Graph* graph){
    char* id1 = NULL;
    char* id2 = NULL;
    char* msg = "";
    do{
        if(id1 != NULL){
            free(id1);
            id1 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id1 (4 letters): ");
        id1 = readline("");
    } while(strlen(id1) != 4);
    msg = "";
    do{
        if(id2 != NULL){
            free(id2);
            id2 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id2 (4 letters): ");
        id2 = readline("");
    } while(strlen(id2) != 4);

    printf("Enter weight of edge: ");
    int w = getInt();

    int n = addEdge(graph, id1, id2, w);
    if(n == 1){
        printf("======[ERROR]======\n");
        printf("Graph empty\n");
    } else if (n == 2){
        printf("======[ERROR]======\n");
        printf("Some node doesn't exist or loop\n");
    }
    free(id1);
    free(id2);
}

void deleteExistNode(Graph* graph){
    char* id = NULL;
    char* msg = "";
    do{
        if(id != NULL){
            free(id);
            id = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id (4 letters): ");
        id = readline("");
    } while(strlen(id) != 4);

    int n = deleteNode(graph, id);
    if(n == 1){
        printf("======[ERROR]======\n");
        printf("This node doesn't exist\n");
    }
    free(id);
}

void deleteExistEdge(Graph* graph){
    char* id1 = NULL;
    char* id2 = NULL;
    char* msg = "";
    do{
        if(id1 != NULL){
            free(id1);
            id1 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id1 (4 letters): ");
        id1 = readline("");
    } while(strlen(id1) != 4);
    msg="";
    do{
        if(id2 != NULL){
            free(id2);
            id2 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id2 (4 letters): ");
        id2 = readline("");
    } while(strlen(id2) != 4);

    int n = deleteEdge(graph, id1, id2);
    if(n == 1){
        printf("======[ERROR]======\n");
        printf("There nodes don't exist\n");
    }
    free(id1);
    free(id2);
}

void findWay(Graph* graph){
    char* id1 = NULL;
    char* id2 = NULL;
    char* msg = "";
    do{
        if(id1 != NULL){
            free(id1);
            id1 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id1 (4 letters): ");
        id1 = readline("");
    } while(strlen(id1) != 4);
    msg="";
    do{
        if(id2 != NULL){
            free(id2);
            id2 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id2 (4 letters): ");
        id2 = readline("");
    } while(strlen(id2) != 4);

    List* way = dfs(graph, id1, id2);
    if(way != NULL){
        printWay(way);
        freeList(way);
    } else {
        printf("======[ERROR]======\n");
        printf("This way doesn't exist\n");
    }
    free(id1);
    free(id2);
}

void findShortestWay(Graph* graph){
    char* id1 = NULL;
    char* id2 = NULL;
    char* msg = "";
    do{
        if(id1 != NULL){
            free(id1);
            id1 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id1 (4 letters): ");
        id1 = readline("");
    } while(strlen(id1) != 4);
    msg="";
    do{
        if(id2 != NULL){
            free(id2);
            id2 = NULL;
        }
        printf("%s", msg);
        msg = "======[ERROR]======\n  Len of id must be 4!\n";
        printf("Enter string id2 (4 letters): ");
        id2 = readline("");
    } while(strlen(id2) != 4);

    List* way = shortestWay(graph, id1, id2);
    if(way != NULL){
        printWay(way);
        freeList(way);
    } else {
        printf("======[ERROR]======\n");
        printf("This way doesn't exist or exist negative loop\n");
    }
    free(id1);
    free(id2);
}

void findSCC(Graph* graph){
    Vector* SCC = getSCC(graph);
    for(int i = 0; i < SCC->size; i++){
        printf("Component #%d: ", i + 1);
        printWay(SCC->components[i]);
        freeList(SCC->components[i]);
    }
    free(SCC->components);
    free(SCC);
}
