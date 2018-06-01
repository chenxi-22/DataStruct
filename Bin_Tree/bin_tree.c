#include "bin_tree.h"
#include <stdlib.h>
#include <unistd.h>
#include "seqstack.h"

#define HEAD printf("=================%s================\n",__FUNCTION__);

void TreeInit(TreeNode** proot)//初始化二叉树
{
  if(proot == NULL) {
    return;
  }
  *proot = NULL;
}

void TreePreOrder(TreeNode* root)//先序访问二叉树
{
  if(root == NULL) {
    return;
  }
  printf("%c ",root->data);
  //递归访问左子树
  TreePreOrder(root->lchild);
  //递归访问右子树
  TreePreOrder(root->rchild);
  return;
}

void TreeInOrder(TreeNode* root)//中序访问二叉树
{
  if(root == NULL) {
    return;
  }
  //递归访问左子树
  TreeInOrder(root->lchild);
  printf("%c ", root->data);
  //递归访问右子树
  TreeInOrder(root->rchild);
  return;
}

void TreePostOrder(TreeNode* root)//后序访问二叉树
{
  if(root == NULL) {
    return;
  }
  //递归访问左子树
  TreePostOrder(root->lchild);
  //递归访问右子树
  TreePostOrder(root->rchild);
  printf("%c ",root->data);
  return;
}

void TreeLevelOrder(TreeNode* root)//层序访问二叉树
{
  if(root == NULL) {
    return;
  }
  SeqQueue queue;
  SeqQueueType front;
  SeqQueueInit(&queue);
  SeqQueuePush(&queue,root);

  while(1) {
    SeqQueueGetFront(&queue, &front);
    if(front == NULL) {
      return;
    }
    printf("%c ", front->data);
    if(front->lchild != NULL) {
      SeqQueuePush(&queue, front->lchild);
    }
    if(front->rchild != NULL) {
      SeqQueuePush(&queue, front->rchild);
    }
    SeqQueuePop(&queue);
  }
}

TreeNode* CreatTreeNode(TreeNodeType value)//创建新的节点
{
  TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
  new_node->data = value;
  new_node->lchild = NULL;
  new_node->rchild = NULL;

  return new_node;
}

TreeNode* _TreeCreat(TreeNodeType array[], size_t size, size_t* index, TreeNodeType null_node)
{
  if(*index >= size || array[*index] == null_node) {
    return NULL;
  }

  TreeNode* root;
  TreeInit(&root);
  //根节点
  root = CreatTreeNode(array[*index]);
  (*index)++;
  //左子树
  root->lchild = _TreeCreat(array, size, index, null_node);
  (*index)++;
  //右子树
  root->rchild = _TreeCreat(array, size, index, null_node);

  return root;
}

TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node)//根据先序创建二叉树 
{
  if(array == NULL || size == 0) {
    return NULL;
  }

  size_t index = 0;
  return _TreeCreat(array, size, &index, null_node);
}

void TreeNodeDestroy(TreeNode** root)//销毁节点
{
  if(root == NULL) {
    return;
  }

  free(*root);
  *root = NULL;
}

void TreeDestroy(TreeNode* root)//销毁二叉树
{
  if(root == NULL) {
    return;
  }

  TreeDestroy(root->lchild);
  TreeDestroy(root->rchild);
  TreeNodeDestroy(&root);
}

TreeNode* TreeClone(TreeNode* root)//深度复制二叉树
{
  if(root == NULL) {
    return NULL;
  }
  TreeNode* new_node = CreatTreeNode(root->data);
  new_node->lchild = TreeClone(root->lchild); 
  new_node->rchild = TreeClone(root->rchild); 

  return new_node;
}

size_t _TreeSize(TreeNode* root, size_t* count)
{
  if(root == NULL) {
    return *count;
  }

  (*count)++;
  _TreeSize(root->lchild, count);
  _TreeSize(root->rchild, count);

  return *count;
}

size_t TreeSize(TreeNode* root)//求二叉树节点的个数
{
  if(root == NULL) {
    return 0;
  }
  size_t count = 0;
  return _TreeSize(root, &count);
}

size_t _TreeLeafSize(TreeNode* root, size_t* count)  
{
  if(root == NULL) {
    return *count;
  }
  if(root->lchild == NULL && root->rchild == NULL) {
    return (*count)++;
  }
  _TreeLeafSize(root->lchild, count);
  _TreeLeafSize(root->rchild, count);

  return *count;
}
  
size_t TreeLeafSize(TreeNode* root)//求二叉树叶子节点个数 
{
  if(root == NULL) {
    return 0;
  }
  size_t count = 0;
  return _TreeLeafSize(root, &count);  
}

size_t TreeLeafSize1(TreeNode* root)//求二叉树叶子节点个数纯递归
{
  if(root == NULL) {
    return 0;
  }
  if(root->lchild == NULL && root->rchild == NULL) {
    return 1;
  }
  return TreeLeafSize1(root->rchild) + TreeLeafSize1(root->lchild);  
}

size_t TreeKLevelSize(TreeNode* root, int K)//求二叉树第K层节点个数 
{
  if(root == NULL || K <= 0) {
    return 0;
  }
  if(K == 1) {
    return 1;
  }
  
  return TreeKLevelSize(root->lchild, K-1) + TreeKLevelSize(root->rchild, K-1);
}

size_t TreeHeight(TreeNode* root)//求二叉树的深度
{
  if(root == NULL) {
    return 0;
  }
  size_t lheight = TreeHeight(root->lchild);
  size_t rheight = TreeHeight(root->rchild);
  return 1 + (lheight > rheight ? lheight : rheight);
}

TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find)//查找二叉树
{
  if(root == NULL) {
    return NULL;
  }
  SeqQueue queue;
  SeqQueueType front;
  SeqQueueInit(&queue);
  SeqQueuePush(&queue,root);

  while(1) {
    SeqQueueGetFront(&queue, &front);
    if(front->data == to_find) {
      return front;
    }
    if(front->lchild == NULL && front->rchild == NULL) {
      return NULL;
    }
    if(front->lchild != NULL) {
      SeqQueuePush(&queue, front->lchild);
    }
    if(front->rchild != NULL) {
      SeqQueuePush(&queue, front->rchild);
    }
    SeqQueuePop(&queue);
  }
}

TreeNode* LChild(TreeNode* node)//查找某一个节点的左子树
{
  if(node == NULL) {
    return NULL;
  }
  return node->lchild;
}

TreeNode* RChild(TreeNode* node)//查找某一个节点的右子树
{
  if(node == NULL) {
    return NULL;
  }
  return node->rchild;
}

TreeNode* Parent(TreeNode* root, TreeNode* node)//查找某个节点的父节点
{
  if(root == NULL) {
    return NULL;
  }
  if(root == node) {
    return NULL;
  }

  SeqQueue queue;
  SeqQueueType front;
  SeqQueueInit(&queue);
  SeqQueuePush(&queue,root);

  while(1) {
    SeqQueueGetFront(&queue, &front);
    if(front->lchild == node || front->rchild == node) {
      return front;
    }
    if(front->lchild == NULL && front->rchild == NULL) {
      return NULL;
    }
    if(front->lchild != NULL) {
      SeqQueuePush(&queue, front->lchild);
    }
    if(front->rchild != NULL) {
      SeqQueuePush(&queue, front->rchild);
    }
    SeqQueuePop(&queue);
  }
  return NULL;
}

void TreePreOrderByLoop(TreeNode* root)//先序访问二叉树(非递归方式)
{
  if(root == NULL) {
    return;
  }

  SeqStack stack;
  SeqStackInit(&stack);
  SeqStackPush(&stack, root);
  TreeNode* top = NULL;

  while(SeqStackGetFront(&stack, &top)) {
    SeqStackPop(&stack);
    printf("%c ",top->data);
    if(top->rchild != NULL) {
      SeqStackPush(&stack, top->rchild);
    }
    if(top->lchild != NULL) {
      SeqStackPush(&stack, top->lchild);
    }
  }
  printf("\n");
}

void TreeInOrderByLoop(TreeNode* root)//中序访问二叉树(非递归方式)
{
  if(root == NULL) {
    return;
  }

  SeqStack stack;
  SeqStackInit(&stack);
  TreeNode* cur = root;
  TreeNode* top = NULL;

  while(1) {
    while(cur != NULL) {
      SeqStackPush(&stack, cur);
      cur = cur->lchild;
    }
    if(!SeqStackGetFront(&stack, &top)) {
      break;
    }
    SeqStackPop(&stack);
    printf("%c ",top->data);
    cur = top->rchild;
  }
  printf("\n");
  return;
}

void TreePostOrderByLoop(TreeNode* root)//后序访问二叉树(非递归方式)
{
  if(root == NULL) {
    return;
  }
  SeqStack stack;
  SeqStackInit(&stack);
  TreeNode* cur = root;
  TreeNode* top = NULL;
  TreeNode* pre = NULL;

  while(1) {
    while(cur != NULL) {
      SeqStackPush(&stack, cur);
      cur = cur->lchild;
    }
    if(!SeqStackGetFront(&stack, &top)) {
      break;
    }
    if(pre == top->rchild || top->rchild == NULL) {
      SeqStackPop(&stack);
      printf("%c ",top->data);
      pre = top;
    } else {
      cur = top->rchild;
    }
  }
  printf("\n");
  return;
}

void Swap(TreeNode** a, TreeNode** b)
{
  TreeNode* tmp = *a;
  *a = *b;
  *b = tmp;
}

void TreeMirror(TreeNode* root)//求一个二叉树的镜像二叉树
{
  if(root == NULL) {
    return;
  }
  Swap(&root->lchild, &root->rchild);
  TreeMirror(root->lchild);
  TreeMirror(root->rchild);
  return;
}

void TreeMirrorByLoop(TreeNode* root)//求一个二叉树的镜像二叉树
{
  if(root == NULL) {
    return;
  }
  SeqQueue q;
  SeqQueueInit(&q);
  SeqQueuePush(&q, root);
  TreeNode* front = NULL;

  while(1) {
    SeqQueueGetFront(&q, &front); 
    if(front == NULL) {
      break;
    }
    Swap(&front->lchild, &front->rchild);
    if(front->lchild != NULL) {
      SeqQueuePush(&q, front->lchild);
    }
    if(front->rchild != NULL) {
      SeqQueuePush(&q, front->rchild);
    }
    SeqQueuePop(&q);
  }
  printf("\n");
  return;
}

int isCompleteTree(TreeNode* root)//判断一个树是否为满二叉树
{
  if(root == NULL) {
    return -1;//空树没有意义
  }
  SeqQueue q;
  SeqQueueInit(&q);
  SeqQueuePush(&q, root);

  TreeNode* front = NULL;
  int flag = 0;
  while(1) {
    SeqQueueGetFront(&q, &front);
    SeqQueuePop(&q);
    if(front == NULL) {
      break;
    }
    if(flag == 0) {
      if(front->rchild != NULL && front->lchild != NULL) {
        SeqQueuePush(&q, front->lchild);
        SeqQueuePush(&q, front->rchild);
      } else if(front->lchild == NULL && front->rchild != NULL) {
        return 0;
      } else if(front->lchild != NULL && front->rchild == NULL) {
        flag = 1;
        SeqQueuePush(&q, front->lchild);
      } else {
        flag = 1;
      }    
    } else {
      if(front->rchild == NULL && front->lchild == NULL) {
        ;
      } else {
        return 0;
      }
    }
  }
  return 1;
}

size_t Find(TreeNodeType in_order[], TreeNodeType to_find, 
            size_t in_order_left, size_t in_order_right)//查找函数查找new_node在中序遍历里的下标
{
  if(in_order == NULL) {
    return (size_t)-1;
  }
  size_t i = in_order_left;
  for(; i < in_order_right; ++i) {
    if(in_order[i] == to_find) {
      return i;
    }
  }
  return (size_t)-1;
}

TreeNode* _TreeRebuild(TreeNodeType pre_order[], size_t size, size_t* pre_order_index, 
                       TreeNodeType in_order[], size_t in_order_left, size_t in_order_right)
{
  if(pre_order == NULL || in_order == NULL || size == 0) {
    return NULL;
  }
  if(pre_order_index == NULL) {
    return NULL;
  }
  if(in_order_left >= in_order_right) {
    return NULL;
  }

  TreeNode* new_node = CreatTreeNode(pre_order[*pre_order_index]);
  (*pre_order_index)++;
  size_t in_order_cur = Find(in_order, new_node->data, in_order_left, in_order_right);
  assert(in_order_cur != (size_t)-1);//断言条件不满足会自己调用abort，发送信号终止进程

  //递归遍历左右子树
  new_node->lchild = _TreeRebuild(pre_order, size, pre_order_index, 
                                  in_order, in_order_left, in_order_cur);
  new_node->rchild = _TreeRebuild(pre_order, size, pre_order_index, 
                                  in_order, in_order_cur + 1, in_order_right);
  return new_node;
}

TreeNode* TreeRebuild(TreeNodeType pre_order[], size_t size, TreeNodeType in_order[])//根据先序与中序遍历结果创建二叉树
{
  if(pre_order == NULL || in_order == NULL || size == 0) {
    return NULL;
  }
  //pre_order_index为先序遍历下标
  //in_order_left与in_order_righ所构成一个区域
  //前闭后开的区域为节点的中序遍历区域
  size_t pre_order_index = 0;
  size_t in_order_left = 0;
  size_t in_order_right = size;
  return _TreeRebuild(pre_order, size, &pre_order_index, in_order, in_order_left, in_order_right);
}
  
///////////////////////////////////////////////////////////////////////
//测试代码
//////////////////////////////////////////////////////////////////////

void TestPreOrder()
{
  HEAD;
  TreeNode* root;
  TreeInit(&root);
  TreeNode* a = CreatTreeNode('a');
  TreeNode* b = CreatTreeNode('b');
  TreeNode* c = CreatTreeNode('c');
  TreeNode* d = CreatTreeNode('d');
  TreeNode* e = CreatTreeNode('e');
  TreeNode* f = CreatTreeNode('f');
  TreeNode* g = CreatTreeNode('g');
  
  a->lchild = b;
  b->lchild = d;
  b->rchild = e;
  e->lchild = g;
  a->rchild = c;
  c->rchild = f;
  TreePreOrder(a);
  printf("\n");
}

void TestInOrder()
{
  HEAD;
  TreeNode* root;
  TreeInit(&root);
  TreeNode* a = CreatTreeNode('a');
  TreeNode* b = CreatTreeNode('b');
  TreeNode* c = CreatTreeNode('c');
  TreeNode* d = CreatTreeNode('d');
  TreeNode* e = CreatTreeNode('e');
  TreeNode* f = CreatTreeNode('f');
  TreeNode* g = CreatTreeNode('g');
  
  a->lchild = b;
  b->lchild = d;
  b->rchild = e;
  e->lchild = g;
  a->rchild = c;
  c->rchild = f;
  TreeInOrder(a);
  printf("\n");
}

void TestPostOrder()
{
  HEAD;
  TreeNode* root;
  TreeInit(&root);
  TreeNode* a = CreatTreeNode('a');
  TreeNode* b = CreatTreeNode('b');
  TreeNode* c = CreatTreeNode('c');
  TreeNode* d = CreatTreeNode('d');
  TreeNode* e = CreatTreeNode('e');
  TreeNode* f = CreatTreeNode('f');
  TreeNode* g = CreatTreeNode('g');
  
  a->lchild = b;
  b->lchild = d;
  b->rchild = e;
  e->lchild = g;
  a->rchild = c;
  c->rchild = f;
  TreePostOrder(a);
  printf("\n");
}

void TestLevelOrder()
{
  HEAD;
  TreeNode* root;
  TreeInit(&root);
  TreeNode* a = CreatTreeNode('a');
  TreeNode* b = CreatTreeNode('b');
  TreeNode* c = CreatTreeNode('c');
  TreeNode* d = CreatTreeNode('d');
  TreeNode* e = CreatTreeNode('e');
  TreeNode* f = CreatTreeNode('f');
  TreeNode* g = CreatTreeNode('g');
  
  a->lchild = b;
  b->lchild = d;
  b->rchild = e;
  e->lchild = g;
  a->rchild = c;
  c->rchild = f;
  TreeLevelOrder(a);
  printf("\n");
}

void TestCreate()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  TreeInOrder(root);
  printf("\n");
  TreePostOrder(root);
  printf("\n");
  TreeLevelOrder(root);
  printf("\n");
}

void TestDestroy()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  TreeDestroy(root);
  printf("root expected NULL, actual %p\n",root);
  //TreePreOrder(root);
  printf("\n");
}

void TestClone()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  TreeNode* new_node = TreeClone(root);
  TreePreOrder(new_node);
  printf("\n");
}

void TestSize()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  size_t num = TreeSize(root);
  printf("expect size 7, actual size %lu\n",num);
  printf("\n");
}

void TestLeafSize()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  size_t num = TreeLeafSize(root);
  printf("expect size 3, actual size %lu\n",num);
  printf("\n");
}

void TestKSize()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  size_t num = TreeKLevelSize(root, 2);
  printf("expect size 2, actual size %lu\n",num);
  printf("\n");
  num = TreeKLevelSize(root, 3);
  printf("expect size 3, actual size %lu\n",num);
  printf("\n");
}

void TestHeight()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  size_t deep = TreeHeight(root);
  printf("expect deep 4, actual deep %lu\n",deep);
  printf("\n");
}

void TestFind()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  TreeNodeType data = TreeFind(root, 'c')->data;
  printf("expect data c, actual data %c\n",data);
  printf("expect data NULL, actual data %p\n",TreeFind(root, 'z'));
}

void TestLeafSize1()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  size = TreeLeafSize1(root);
  printf("size expected 3, actual %lu\n",size);
}

void TestParent()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrder(root);
  printf("\n");
  TreeNode* parent = Parent(root, root->lchild->lchild);
  printf("parent expected %p, parent atucal %p\n",root->lchild, parent);
}

void TestPreOrderByLoop()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePreOrderByLoop(root);
}

void TestInOrderByLoop()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreeInOrderByLoop(root);
}

void TestPostOrderByLoop()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreePostOrderByLoop(root);
}

void TestMirror()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  TreeInOrderByLoop(root);
  TreeMirrorByLoop(root);
  TreeInOrderByLoop(root);
  TreeMirror(root);
  TreeInOrderByLoop(root);
}

void TestisCompleteTree()
{
  HEAD;
  TreeNodeType array[] = "abd##eg###c#f##";
  size_t size = sizeof(array)/sizeof(array[0]) - 1;
  TreeNode* root = TreeCreate(array, size, '#');
  int ret = isCompleteTree(root);
  printf("ret expected 0,ret actual %d\n",ret);
}

void TestTreeRebuild()
{
  HEAD;
  TreeNodeType pre_order[] = "abdegcf";
  TreeNodeType in_order[] = "dbgeafc";
  size_t size = sizeof(pre_order)/sizeof(pre_order[0]);
  TreeNode* root = TreeRebuild(pre_order, size, in_order);
  TreePreOrder(root);
  printf("\n");
  TreeInOrder(root);
  printf("\n");
}

int main()
{
  TestPreOrder();
  TestInOrder();
  TestPostOrder();
  TestLevelOrder();//判断条件
  TestCreate();
  TestDestroy();
  TestClone();
  TestSize();
  TestLeafSize();
  TestKSize();
  TestHeight();
  TestFind();
  TestLeafSize1();
  TestParent();
  TestPreOrderByLoop();
  TestInOrderByLoop();
  TestPostOrderByLoop();
  TestMirror();
  TestisCompleteTree();
  TestTreeRebuild();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
}














