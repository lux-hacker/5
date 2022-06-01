#include "view.h"
#include <stdio.h>
#include <stdlib.h>

void printMenu(){
    printf("======[WELCOME TO MENU]======\n");
    printf("0) Exit\n");
    printf("1) Add node\n");
    printf("2) Add edge\n");
    printf("3) Delete node\n");
    printf("4) Delete edge\n");
    printf("5) Print adjacency matrix\n");
    printf("6) Find way\n");
    printf("7) Find shortest way\n");
    printf("8) Find strongly connected components\n");
    printf("--> ");
}

void graphToPng(Graph* graph, char* filename){
    FILE* fd = fopen("buf.dot", "w");
    fprintf(fd, "digraph G{\n");
    for(int i = 0; i < graph->size; i++){
        for(int j = 0; j < graph->size; j++){
            if(graph->matrix[i][j] == 1){
                fprintf(fd, "    %s -> %s [label=\" %d\"];\n", graph->nodes[i], graph->nodes[j], graph->weights[i][j]);
            } else if (i == j){
                fprintf(fd, "    %s;\n", graph->nodes[i]);

            }
        }
    }
    fprintf(fd, "}\n");
    fclose(fd);
    char cmd[255] = {0};
    sprintf(cmd, "dot -Tpng buf.dot -o %s", filename);
    system(cmd);
    remove("buf.dot");
}

void printGraph(Graph* graph){
    printf("     ");
    for(int i = 0; i < graph->size; i++){
        printf("%5s", graph->nodes[i]);
    }
    printf("  |  ");
    printf("     ");
    for(int i = 0; i < graph->size; i++){
        printf("%5s", graph->nodes[i]);
    }
    printf("\n");
    for(int i = 0; i < graph->size; i++){
        printf("%5s", graph->nodes[i]);
        for(int j = 0; j < graph->size; j++){
            printf("%5d", graph->matrix[i][j]);
        }
        printf("  |  ");
        printf("%5s", graph->nodes[i]);
        for(int j = 0; j < graph->size; j++){
            printf("%5d", graph->weights[i][j]);
        }
        printf("\n");
    }
}

void printWay(List* way){
    ListNode* head = way->head;
    while(head->next != NULL){
        printf("%s->", head->node);
        head = head->next;
    }
    printf("%s\n", head->node);
}
