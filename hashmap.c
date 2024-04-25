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

long resolverColision(HashMap *map, long pos, char *key)
{
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)         return pos;
  if(strcmp(map->buckets[pos]->key,key) == 0) 
    return pos;
  return resolverColision(map, (pos + 1) % map->capacity, key);
}

void insertMap(HashMap * map, char * key, void * value) {
  if(map==NULL || key==NULL || value==NULL) return;
  long pos = hash(key, map->capacity);

  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)
    map->buckets[pos] = createPair(key, value);
  else
  {
    pos = resolverColision(map, pos, key);
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
  long pos = hash(key, map->capacity);
  
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)        return;
  if(strcmp(map->buckets[pos]->key,key) == 0)
    map->buckets[pos]->key = NULL;
  else
  {
    pos = resolverColision(map, pos, key);
    if(map->buckets[pos] == NULL) return;
    
    map->buckets[pos]->key = NULL;
  }
  map->size--;
}

Pair * searchMap(HashMap * map,  char * key) { 
  long pos = hash(key, map->capacity);
  if(map->buckets[pos] == NULL || map->buckets[pos]->key == NULL)       return NULL;
  
  if(map->buckets[pos]->key == key)
    return map->buckets[pos];
  else
    pos = resolverColision(map, pos, key);
  
  map->current = pos;
  return map->buckets[pos];
}

Pair * firstMap(HashMap * map) {
  long pos = 0;
  for(; pos <= map->capacity; pos++)
  {
    if(map->buckets[pos] != NULL && map->buckets[pos]->key != NULL)
      break;
  } 
  printf("%li", pos);
  map->current = pos;
  printf("%s", map->buckets[pos]->key);
  return map->buckets[pos];
}

Pair * nextMap(HashMap * map) {
  long pos;
  for(pos = map->current + 1; pos < map->capacity; pos++)
    {
      if(map->buckets[pos] != NULL)
        break;
    }
    
  return map->buckets[pos];
}
