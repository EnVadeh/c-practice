#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
  uint64_t seed;
  uint64_t hashValue;
} hashTable;

typedef enum{
  TYPE_UINT = 4,
  TYPE_INT = 4,
  TYPE_FLOAT = 4,
  TYPE_DOUBLE = 8,
  TYPE_HT = 32
} dataType;

typedef struct{
  void* mPointer;
  uint8_t baseSize;
  uint16_t mSize;
  uint16_t mCurrent;
  dataType pType;
} mutableArray;

mutableArray* initArray(dataType type){
  uint8_t b = 8;
  mutableArray* tempArray = (mutableArray*) malloc(sizeof(mutableArray));
  tempArray->baseSize = 8;
  tempArray->mSize = 0;
  tempArray->pType = type;
  tempArray->mCurrent = 0;
  tempArray->mPointer = malloc(type * b);
    if(!tempArray->mPointer){
      printf("couldn't allocate Memory for the array data");
      free(tempArray->mPointer);
    }
  return tempArray;
}

void resize(mutableArray* mArray, uint16_t size){
  if(size==mArray->mSize)
    return;
  mArray->mSize = size;
  mArray->mPointer = realloc(mArray->mPointer, (mArray->pType) * size);
  return;
}

void insert(mutableArray* mArray, const void* data, uint16_t index){
  if(index > mArray->mSize){
    printf("Index out of bounds");
    return;
  }
  char* targetMemory = (char*)mArray->mPointer + (index * mArray->pType); //the locaiton of the memory that we want to populate, in bytes
  memcpy(targetMemory, data, mArray->pType); //we copy to that byte location the data
  mArray->mCurrent = index; 
}

void* retreive(mutableArray* mArray, uint16_t index){
  if(index > mArray->mSize){
    printf("Index out of bounds");
  }
  char* targetMemory = (char*)mArray->mPointer + (index * mArray->pType); //This returns a void pointer to one part of the contiguous memory 
  return targetMemory;
}

int main(){
  mutableArray* arr = initArray(TYPE_UINT);
  resize(arr, 10);
  int value = 1000;
  insert(arr, &value, 5);
  int* x = (int*)retreive(arr, 5);
  printf("The retrieved value is: %d", *x); //dereferencing the pointer
  return 0;
}
