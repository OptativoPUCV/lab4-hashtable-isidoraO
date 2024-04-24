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

long resolverColision(HashMap *map, long pos)
{
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)         return pos;
  return resolverColision(map, pos + 1);
}

void insertMap(HashMap * map, char * key, void * value) {
  if(map==NULL || key==NULL || value==NULL) return;
  long pos = hash(key, map->capacity);

  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)
    map->buckets[pos] = createPair(key, value);
  else
  {
    pos = resolverColision(map, pos);
    map->buckets[pos] = createPair(key, value);
  }
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *temp;
  temp = (HashMap *)malloc(sizeof(HashMap));
  if(temp == NULL) return NULL;

  temp->buckets = (Pair **) calloc((capacity),sizeof(Pair*));
  if(temp->buckets == NULL) return NULL;
  
  temp->capacity = (capacity);
  temp->current = -1;
  temp->size = 0;
  
  return temp;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long pos = hash(key, map->capacity);
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)        return NULL;
  if(map->buckets[pos]->key == key) return map->buckets[pos];


    return map->buckets[pos]->value;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
