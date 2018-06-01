#include "search_tree.h"

#define HEAD printf("======================%s=======================\n",__FUNCTION__);

void SearchTreeInit(SearchTreeNode** pRoot) //初始化二叉搜索树
{
  if(pRoot == NULL) {
    return;//非法输入
  }
  *pRoot = NULL;
  return;
}

SearchTreeNode* CreatTreeNode(SearchTreeType node) 
{
  SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
  new_node->data = node;
  new_node->lchild = NULL;
  new_node->rchild = NULL;
  return new_node;
}

//这里定义规则，二叉搜索树中不允许出现相同的元素
void SearchTreeInsert(SearchTreeNode** pRoot, SearchTreeType to_insert)//二叉搜索树插入
{
  if(pRoot == NULL) {
    return;
  }
  if(*pRoot == NULL) {
    *pRoot = CreatTreeNode(to_insert);
    return;
  }
  SearchTreeNode* root = *pRoot;
  if(to_insert < root->data) {
    SearchTreeInsert(&root->lchild, to_insert);
  } if(to_insert > root->data) {
    SearchTreeInsert(&root->rchild, to_insert);
  } else {
    return;
  }
}

SearchTreeNode* SearchTreeFind(SearchTreeNode* root, 
                               SearchTreeType to_find) //查找二叉搜索树
{
  if(root == NULL) {
    return NULL;
  }
  if(to_find < root->data) {
    return SearchTreeFind(root->lchild, to_find);
  } else if(to_find > root->data) {
    return SearchTreeFind(root->rchild, to_find);
  } else {
    return root;
  }
}

void DestroyNode(SearchTreeNode** pRoot)
{
  free(*pRoot);
  *pRoot = NULL;
}

void SearchDestroy(SearchTreeNode** pRoot)//销毁二叉搜索树
{
  if(pRoot == NULL) {
    return;
  }
  if(*pRoot == NULL) {
    return;
  }
  SearchTreeNode* root = *pRoot;
  SearchDestroy(&root->lchild);
  SearchDestroy(&root->rchild);
  DestroyNode(&root);
  return;
}

void SearchTreeInsertByLoop(SearchTreeNode** pRoot, SearchTreeType to_insert)//非递归版本二叉搜索树插入
{
  if(pRoot == NULL) {
    return;
  }
  if(*pRoot == NULL) {
    *pRoot = CreatTreeNode(to_insert);
    return;
  }

  SearchTreeNode* root = *pRoot;
  SearchTreeNode* pre = NULL;
  while(root != NULL) {
    if(to_insert < root->data) {
      pre = root;
      root = root->lchild;
    } else if(to_insert > root->data) {
      pre = root;
      root = root->rchild;
    } else {
      return;
    }
  }
  if(to_insert > pre->data) {
    pre->rchild = CreatTreeNode(to_insert);
  } else {
    pre->lchild = CreatTreeNode(to_insert);
  }
  return;
}

SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root, 
                               SearchTreeType to_find) //非递归版本查找二叉搜索树
{
  if(root == NULL) {
    return NULL;
  }
  while(root != NULL) {
    if(to_find > root->data) {
      root = root->rchild;
    } else if(to_find < root->data){
      root = root->lchild;
    } else {
      return root;
    }
  }
  return NULL;
}

void SearchTreeRemove(SearchTreeNode** pRoot, SearchTreeType to_remove)//删除二叉搜索树中某一个元素
{
  if(pRoot == NULL) {
    return;
  }
  if(*pRoot == NULL) {
    return;
  }
  SearchTreeNode* root = *pRoot;
  if(to_remove > root->data) {
    SearchTreeRemove(&root->rchild, to_remove);
  } else if(to_remove < root->data) {
    SearchTreeRemove(&root->lchild, to_remove);
  } else {
    if(root->lchild == NULL && root->rchild == NULL) {
      DestroyNode(&root);
      return;
    } else if(root->lchild != NULL && root->rchild == NULL) {
      SearchTreeNode* cur = root;
      root = root->lchild;
      DestroyNode(&cur);
      return;
    } else if(root->lchild == NULL && root->rchild != NULL) {
      SearchTreeNode* cur = root;
      root = root->rchild;
      DestroyNode(&cur);
      return;
    } else {
      SearchTreeNode* min = root->rchild;
      SearchTreeNode* pre = min;
      while(min->lchild != NULL) {
        pre = min;
        min = min->lchild;
      }
      root->data = min->data;
      pre->lchild = min->rchild;
      DestroyNode(&min);
      return;
    }
  }
}

void SearchTreeRemoveByLoop(SearchTreeNode** pRoot, SearchTreeType to_remove)//非递归版本删除二叉搜索树中某一个元素
{
  if(pRoot == NULL) {
    return;
  }
  if(*pRoot == NULL) {
    return;
  }

  SearchTreeNode* root = *pRoot;
  SearchTreeNode* parent = root;
  while(root != NULL) {
    if(to_remove > root->data) {
      parent = root;
      root = root->rchild;
    } else if(to_remove < root->data) {
      parent = root;
      root = root->lchild;
    } else {
      break;
    }
  }
  if(root == NULL) {
    return;
  }

  if(root->lchild == NULL && root->rchild == NULL) {
    DestroyNode(&root);
    return;
  } else if(root->lchild != NULL && root->rchild == NULL) {
    SearchTreeNode* cur = root;
    root = root->lchild;
    DestroyNode(&cur);
    return;
  } else if(root->lchild == NULL && root->rchild != NULL) {
    SearchTreeNode* cur = root;
    root = root->rchild;
    DestroyNode(&cur);
    return;
  } else {
    SearchTreeNode* min = root->rchild;
    SearchTreeNode* pre = min;
    while(min->lchild != NULL) {
      pre = min;
      min = min->lchild;
    }
    root->data = min->data;
    pre->lchild = min->rchild;
    DestroyNode(&min);
    return;
  }
}

//////////////////////////////////////////////////////////////////////////
///测试代码
//////////////////////////////////////////////////////////////////////////

void PreOrder(SearchTreeNode* root)
{
  if(root == NULL) {
    return;
  }
  printf("%c ", root->data);
  PreOrder(root->lchild);
  PreOrder(root->rchild);
}

void InOrder(SearchTreeNode* root)
{
  if(root == NULL) {
    return;
  }
  InOrder(root->lchild);
  printf("%c ", root->data);
  InOrder(root->rchild);
}

void SearchTreePrintChar(SearchTreeNode* root) 
{
  if(root == NULL) {
    return;
  }
  PreOrder(root);
  printf("\n");
  InOrder(root);
  printf("\n");
  return;
}

void TestInsert()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsert(&root, 'a');
  SearchTreeInsert(&root, 'b');
  SearchTreeInsert(&root, 'z');
  SearchTreeInsert(&root, 'x');
  SearchTreeInsert(&root, 'c');
  SearchTreePrintChar(root);
}

void TestFind()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsert(&root, 'a');
  SearchTreeInsert(&root, 'b');
  SearchTreeInsert(&root, 'z');
  SearchTreeInsert(&root, 'x');
  SearchTreeInsert(&root, 'c');
  SearchTreeNode* cur = SearchTreeFind(root, 'c');
  printf("cur expected c, cur actual %c\n",cur->data);
}

void TestRemove()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsert(&root, 'a');
  SearchTreeInsert(&root, 'b');
  SearchTreeInsert(&root, 'z');
  SearchTreeInsert(&root, 'x');
  SearchTreeInsert(&root, 'c');
  SearchTreePrintChar(root);
  SearchTreeRemove(&root, 'a');
  SearchTreePrintChar(root);
  SearchTreeRemove(&root, 'a');
  SearchTreePrintChar(root);
  SearchTreeRemove(&root, 'b');
  SearchTreePrintChar(root);
  SearchTreeRemove(&root, 'z');
  SearchTreePrintChar(root);
}

void TestInsertByLoop()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsertByLoop(&root, 'd');
  SearchTreeInsertByLoop(&root, 'c');
  SearchTreeInsertByLoop(&root, 'n');
  SearchTreeInsertByLoop(&root, 'x');
  SearchTreeInsertByLoop(&root, 'a');
  SearchTreeInsertByLoop(&root, 'e');
  SearchTreePrintChar(root);
}

void TestFindByLoop()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsertByLoop(&root, 'd');
  SearchTreeInsertByLoop(&root, 'c');
  SearchTreeInsertByLoop(&root, 'n');
  SearchTreeInsertByLoop(&root, 'x');
  SearchTreeInsertByLoop(&root, 'a');
  SearchTreeInsertByLoop(&root, 'e');
  SearchTreeNode* cur = SearchTreeFind(root, 'c');
  printf("cur expected c, cur actual %c\n",cur->data);
}

void TestRemoveByLoop()
{
  HEAD;
  SearchTreeNode* root;
  SearchTreeInit(&root);
  SearchTreeInsertByLoop(&root, 'd');
  SearchTreeInsertByLoop(&root, 'c');
  SearchTreeInsertByLoop(&root, 'n');
  SearchTreeInsertByLoop(&root, 'x');
  SearchTreeInsertByLoop(&root, 'a');
  SearchTreeInsertByLoop(&root, 'e');
  SearchTreePrintChar(root);
  SearchTreeRemoveByLoop(&root, 'a');
  SearchTreePrintChar(root);
}

int main()
{
  TestInsert();
  TestFind();
  TestRemove();
  TestInsertByLoop();
  TestFindByLoop();
  TestRemoveByLoop();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
} 


