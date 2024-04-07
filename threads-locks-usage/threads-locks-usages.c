/*Pick your favorite data structure, such as a B-tree or other slightly
more interesting structure. Implement it, and start with a simple
locking strategy such as a single lock. Measure its performance as
the number of concurrent threads increases.*/

// Searching a key on a B-tree in C

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

//noi tom lai thi arr val dung de chua 'keys'
//count dung de dem xem co bao nhieu keys (number of keys)
//con link la array chua pointer toi cac child node 

struct BTreeNode {
  //val[MAX + 1] la array of interger, size cua array la MAX + 1 (3+1)
  //cai nay giong nhu no se dai dien cho so key ma 1 node can hold trong b-tree. 
  int val[MAX + 1], count; //count thi co ve nhu se keep track current number of value (keys) duoc stored trong node 
  //link la array of pointer de point toi child nodes 
  struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;


// Create a node
struct BTreeNode *createNode(int val, struct BTreeNode *child) {
  struct BTreeNode *newNode;
  newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  newNode->val[1] = val;
  newNode->count = 1;
  newNode->link[0] = root;
  newNode->link[1] = child;
  return newNode;
}

// Insert node
void insertNode(int val, int pos, struct BTreeNode *node,
        struct BTreeNode *child) {
  int j = node->count; //j dung de dem xem co bao nhieu keys (hay number of keys)
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
}

// Split node
void splitNode(int val, int *pval, int pos, struct BTreeNode *node,
         struct BTreeNode *child, struct BTreeNode **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  j = median + 1;
  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  } else {
    insertNode(val, pos - median, *newNode, child);
  }
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
}

// Set the value
//Presumably val la value cua node
//pval la pointer den cai value do 
//node la node 
//child la pointer den voi cai pointer cua child 
int setValue(int val, int *pval,
           struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  //neu nhu khong co node thi
  if (!node) {
    //value cua pvalue se set theo val (integer)
    *pval = val;
    //pointer child se set NULL 
    *child = NULL;
    //return 1, tuc la ko success, hay co error nao do 
    return 1;
  }
  
  //tai sao la val < node->val[1] chu khong phai la val < node->value[0]?
  if (val < node->val[1]) {
    //pos o day co the la position, neu nhu no nho hon val[1]thi ta xem xet cho no la position 0 (?)
    pos = 0;
  } else {
    //node->count luc nay co the la 3 hoac 4 di
    //thi pos = 3 - 4? nhu vay co y nghia gi? co ve ta se di nguoc ve chu khong phai cong len 
    for (pos = node->count; 
        (val < node->val[pos] && pos > 1); pos--)
      ;
    if (val == node->val[pos]) {
      printf("Duplicates are not permitted\n");
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child)) {
    if (node->count < MAX) {
      insertNode(*pval, pos, node, *child);
    } else {
      splitNode(*pval, pval, pos, node, *child, child);
      return 1;
    }
  }
  return 0;
}

// Insert the value
void insert(int val) {
  int flag, i;
  struct BTreeNode *child;

  flag = setValue(val, &i, root, &child);
  printf("here is a flag: %d\n", flag);
  if (flag)
    root = createNode(i, child);
}

// Search node
void search(int val, int *pos, struct BTreeNode *myNode) {
  if (!myNode) {
    return;
  }

  if (val < myNode->val[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count;
       (val < myNode->val[*pos] && *pos > 1); (*pos)--)
      ;
    if (val == myNode->val[*pos]) {
      printf("%d is found\n", val);
      return;
    }
  }
  search(val, pos, myNode->link[*pos]);

  return;
}

// Traverse then nodes
void traversal(struct BTreeNode *myNode) {
  int i;
//   printf("Here is root node: %p\n", (void*)myNode);
  if (myNode) {
    for (i = 0; i < myNode->count; i++) {
    //   printf("i: %d\n", i);
    //   printf("myNode->count: %d\n", myNode->count);
      traversal(myNode->link[i]);
      printf("%d ", myNode->val[i + 1]);
    }
    traversal(myNode->link[i]);
  }
}

int main() {
  int ch;
  //o day chac la insert node vao trong root? 
  insert(8);
  insert(9);
  insert(10);
  insert(11);
  insert(15);
  insert(16);
  insert(17);
  insert(18);
  insert(20);
  insert(23);

  traversal(root);

  printf("\n");
  search(11, &ch, root);
}



