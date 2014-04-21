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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
/**
 * Crea una nueva cola de prioridades.
 */
priority_queue* make_pq(){
    priority_queue* new = (priority_queue*) malloc(sizeof(priority_queue));
    new->min = NULL;
    new->nodes = 0;
    return new;
}
/**
 * Devuelve el elemento minimo.
 */
int find_min(priority_queue pq){
    return pq.min->elem;
}
/**
 * Combina dos colas circulares
 */
void combine_queue(heap_box* min1, heap_box* min2){
    if (min1 == NULL || min2 == NULL) return;
    heap_box* left1 = (heap_box*) min1->left; //Necesita right
    heap_box* right2 = (heap_box*) min2->right; // Necesita left
    min1->left = (struct heap_box*) min2;
    min2->right = (struct heap_box*) min1;
    left1->right = (struct heap_box*)right2;
    right2->left = (struct heap_box*)left1;
}
/**
 * Mezcla dos colas de prioridades
 */
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
/**
 * Inserta un nuevo elemento en la cola de prioridades
 */
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
/**
 * Remueve el elemento de la lista de roots.
 */
void remove_from_rootl(heap_box* min){
    heap_box* min_left = (heap_box*) min->left;
    heap_box* min_right = (heap_box*) min->right;
    min_left->right = (struct heap_box*) min_right;
    min_right->left = (struct heap_box*) min_left;
    min->left = (struct heap_box*) min;
    min->right = (struct heap_box*) min;
}
/**
 * Enlaza w a v
 */
void link(heap_box* w, heap_box* v){
    w->parent = (struct heap_box*) v;
    heap_box* children = (heap_box*) v->children;
    combine_queue(w,children);
}
/**
 * Cambia dos elementos
 */
void swap(heap_box* v, heap_box* w){
    heap_box* tmp = v;
    v = w;
    w = tmp;
}
/**
 * Enlaza duplicados.
 */
void linkdupes(heap_box* v, heap_box** rank_array){
    heap_box *w = rank_array[v->rank];
    while (w != NULL){
        rank_array[v->rank] = NULL;
        if (w->elem <= v->elem) swap(v,w);
        remove_from_rootl(w);
        link(w,v);
    }
    rank_array[v->rank] = v;
}

/**
 * Elimina el padre de los nuevos elementos de la lista
 * de raices y llama a la funcion que enlaza duplicados.
 */
void cleanup(heap_box* c,priority_queue* p){
    // Busco un nuevo minimo
    p->min = c;
    if (c == NULL) return;
    // Inicializando el arreglo
    long int size = lround(log( (double) p->nodes));
    heap_box* (*rank_array) = (heap_box**) malloc(sizeof(heap_box*)*size);
    int i;
    for (i = 0; i != size; i++) {
        rank_array[i] = NULL;
    }
    // Para toda caja de la lista le quito su padre.
    heap_box* start = c;
    do {
        c->parent = NULL;
        if (p->min->elem > c->elem) p->min = c;
        linkdupes(c,rank_array);
        c = (heap_box*) c->right;
    } while ( c!= start);
}



/**
 * Elimina el elemento minimo de la cola y lo retorna.
 */
char* delete_min(priority_queue* p){
    if (p->min == NULL) return NULL;

    char* result = malloc(sizeof(char));
    *result = find_min(*p);

    heap_box* min = p->min;
    heap_box* min_left = (heap_box*) min->left;
    remove_from_rootl(min);
    heap_box* children = (heap_box*) min->children;
    combine_queue(children,min_left);
    cleanup(children,p);
    min->left = NULL;
    min->right = NULL;
    min->children = NULL;
    free(min);
    return result;
}

void main(){
    priority_queue* prueba = make_pq();
    insert(prueba,'<');
    insert(prueba,'s');
    insert(prueba,'d');
    insert(prueba,'a');
    char* result; 
    do{
        result = delete_min(prueba);
        printf("%c\n",*result);
    }while (result != NULL);
}
