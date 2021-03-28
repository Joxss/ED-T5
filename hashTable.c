#include "hashTable.h"

typedef struct{
    List *indexes;
    int nIndex;
}hTable;

Htable createHashTable(int n){
    hTable *hashTable = (hTable*)malloc(sizeof(hTable));
    hashTable->indexes = (List*)malloc(sizeof(List) * n);
    for(int i=0; i<n; i++){
        hashTable->indexes[i] = createLista();
    }
    hashTable->nIndex = n;
    return hashTable;
}

int hash(char *key, int n){
    int soma=0;
    for(int i=0; i<strlen(key); i++){
        soma += key[i]*(i+1);
    }
    return soma % n;
}

void hashInsert(Htable ht, char *key, void *data){
    hTable *hashTable = (hTable*)ht;
    int index = hash(key,hashTable->nIndex);
    List lista = hashTable->indexes[index];
    listInsert(lista,data);
}

int hashKeyExist(Htable ht, char *key){
    hTable *hashTable = (hTable*)ht;

    int index = hash(key,hashTable->nIndex);
    List lista = hashTable->indexes[index];
    Node node = listGetById(lista,key);

    if(node != NULL) return 1;
    return 0;
}

void *hashGetKey(Htable ht, char *key){
    hTable *hashTable = (hTable*)ht;

    int index = hash(key,hashTable->nIndex);
    List lista = hashTable->indexes[index];
    Node node = listGetById(lista,key);
    if(node != NULL) return nodeGetData(node);
    return NULL;
}

void *hashRemoveKey(Htable ht, char *key){
    hTable *hashTable = (hTable*)ht;

    int index = hash(key,hashTable->nIndex);
    List lista = hashTable->indexes[index];
    Node node = listGetById(lista,key);

    if(node != NULL) return listRemoveNode(lista,node);

    return NULL;
}

void freeHashTable(Htable ht, void(*freeFunc)(void*)){
    hTable *hashTable = (hTable*)ht;
    for(int i=0; i<hashTable->nIndex; i++){
        freeLista(hashTable->indexes[i],freeFunc);
    }
    free(hashTable->indexes);
    free(hashTable);
}

void freeHashTable2(Htable ht){
    hTable *hashTable = (hTable*)ht;
    for(int i=0; i<hashTable->nIndex; i++){
        freeLista2(hashTable->indexes[i]);
    }
    free(hashTable->indexes);
    free(hashTable);
}