/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  Implementacion de heap
 *
 *        Version:  1.0
 *        Created:  17/04/14 14:58:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruben (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct{
    struct heap_box* left;
    struct heap_box* right;
    struct heap_box* parent;
    struct heap_box* children;
    char elem;
    int rank;   
    //int marked; //Creo que no es necesario cuando no se hace delete ni decrease key
} heap_box;

typedef struct{
    heap_box* min;
    int nodes;
} priority_queue;

priority_queue* make_pq(){
    priority_queue* new = (priority_queue*) malloc(sizeof(priority_queue));
    new->min = NULL;
    new->nodes = 0;
    return new;
}

int find_min(priority_queue pq){
    return pq.min->elem;
}

void combine_queue(heap_box* min1, heap_box* min2){
    if (min1 == NULL || min2 == NULL) return;
    heap_box* left1 = (heap_box*) min1->left; //Necesita right
    heap_box* right2 = (heap_box*) min2->right; // Necesita left
    min1->left = (struct heap_box*) min2;
    min2->right = (struct heap_box*) min1;
    left1->right = (struct heap_box*)right2;
    right2->left = (struct heap_box*)left1;
}

priority_queue meld(priority_queue p1, priority_queue p2){
    if ((p1.min == NULL && p2.min == NULL) || (p1.min != NULL && p2.min == NULL)) return p1;
    if (p1.min == NULL && p2.min != NULL) return p2;

    priority_queue presult;
    heap_box* min1 = p1.min;
    heap_box* min2 = p2.min;
    combine_queue(min1,min2);
    if (find_min(p1) < find_min(p2)){
        presult.min = p1.min;
    } else {
        presult.min = p2.min;
    }
    presult.nodes = p1.nodes + p2.nodes;
    return presult;
}

void insert(priority_queue* p, char elem){
    priority_queue new;
    heap_box* new_elem = (heap_box*) malloc(sizeof(heap_box));
    new_elem->left =(struct heap_box*) new_elem;
    new_elem->parent = NULL;
    new_elem->right = (struct heap_box*)new_elem;
    new_elem->elem = elem;
    new_elem->rank = 0;
    new_elem->children = NULL;
    new.min = new_elem;
    new.nodes = 1;
    priority_queue result = meld(new,*p);
    p->min = result.min;
    p->nodes =  result.nodes;
}

char* delete_min(priority_queue* p){
    if (p->min == NULL) return NULL;
    char* result = malloc(sizeof(char));
    *result = find_min(*p);
    heap_box* min = p->min;
    heap_box* min_left = min->left;
    heap_box* min_right = min->right;
    min_left->right = min_right;
    min_right->left = min_left;
    heap_box* children = min->children;
    combine_queue(children,min_left);
    min->left = NULL;
    min->right = NULL;
    min->children = NULL;
    long int size = lround(log(p->nodes));
    heap_box* rank_array = (heap_box*) malloc(sizeof(size));
    
    free(min);
    
}

void main(){
    priority_queue* prueba = make_pq();
    insert(prueba,'<');
    insert(prueba,'s');
    insert(prueba,'d');
    insert(prueba,'a');
    heap_box * start = prueba->min;
    heap_box* tmp = (heap_box*) prueba->min->right;
    while (tmp != start){
        printf("%c\n",tmp->elem);
        tmp =(heap_box*) tmp->right;
    }
        printf("%c\n",tmp->elem);
        printf("%d\n",prueba->nodes);
}
