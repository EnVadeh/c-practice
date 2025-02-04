#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct{
  void* mPointer;
} row;

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

typedef struct node{
  void* mData;
  dataType mType;
  struct node* left;
  struct node* right;
} node;

node* initNode(void* data, dataType type){
  node* tempNode;
  tempNode->mData = malloc(type);
  tempNode->mType = type;
  return tempNode;
}

//I think I understand why linkedlist is interesting, I will have raw pointers for other nodes from just this node
//So here's what I'll do, I will keep going left of the rootnode until I find an empty Node, same with right 
void addNode(node* rootNode, void* data, dataType type, char* direction){
  node* newNode = initNode(data, type);
  if(direction == 0){ //this node is to the left of the other node
    node* currentNode = rootNode;
    node* tempNode = currentNode->left;
    while(tempNode!=NULL){
      currentNode = tempNode;
      tempNode = currentNode->left;
    }
    newNode->right = currentNode;
    currentNode->left = newNode;
    return;
  }
  node* currentNode = rootNode;
  node* tempNode = currentNode->right;
  while(tempNode!=NULL){
    currentNode = tempNode;
    tempNode = currentNode->right;
  }
    newNode->left= currentNode;
    currentNode->right = newNode;
  return;
}

void deleteNode();//Main thing is how to delete it? do I take a value? check value? do I just delete by index??? 

//Let's write a quaternion
typedef struct{
  double x;
  double y;
  double z;
}vec3;

double dot(vec3* u, vec3* v){
  double d = u->x*v->x + u->y*v->y + u->z*v->z;
  return d;
}

vec3* cross(vec3* u, vec3* v){
  vec3* temp = (vec3*)malloc(sizeof(vec3));
  temp->x = ((u->y * v->z) - (u->z * v->y));
  temp->y = ((u->z * v->x) - (u->x * v->z));
  temp->z = ((u->x * v->y) - (u->y * v->x));
  return temp;
}

double length(vec3* u){
  double l = (u->x * u->x) + (u->y * u->y) + (u->z * u->z); 
  l = sqrt(l);
  return l;
}

typedef struct{
  vec3* v; //vector component
  double s; //scalar component
}quaternion; 

//if I want to free the 'u' and have only the v to have data, then I should do memcpy and free. 
quaternion* init(vec3* u, double x){
  quaternion* q = (quaternion*)malloc(sizeof(quaternion));
  q->v = u;
  q->s = x; 
  return q;
}

int main(){
  mutableArray* arr = initArray(TYPE_UINT);
  resize(arr, 10);
  int value = 2000;
  int value2 = 3000;
  insert(arr, &value, 5);
  int* x = (int*)retreive(arr, 5);
  printf("The retrieved value is: %d", *x); //dereferencing the pointer
  insert(arr, &value2, 5);
  printf("another value is: %d", *(int*)retreive(arr, 5));
  return 0;
}
