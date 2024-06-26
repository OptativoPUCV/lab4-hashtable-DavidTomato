#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    int x = hash(key, map->capacity);
    while(map->buckets[x] != NULL){
        if(is_equal(map->buckets[x]->key, key)){
           map->buckets[x]->value = value;
           return;
        }
        x = (x+1) % map->capacity;
    }
    Pair * y = createPair(key, value);
    map->buckets[x] = y;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
    map->current = -1;
    map->size = 0;
    map->capacity = capacity;
    return map;
}

void eraseMap(HashMap * map,  char * key) {   
    void *dato = searchMap(map, key);
    if(dato != NULL){
        int x = hash(key, map->capacity);
        map->size--;
        free(dato);
        map->buckets[x]->key = NULL;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    int x = hash(key, map->capacity);
    while(map->buckets[x] != NULL){
        if(is_equal(map->buckets[x]->key, key)){
          map->current = x;
          return map->buckets[x];
        }
        x++;
      }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    int x=0;
    while(x < map->capacity){
        if(map->buckets[x] != NULL){
          map->current = x;
          return map->buckets[x];
        }
        x++;
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
