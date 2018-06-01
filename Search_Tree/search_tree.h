#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef char SearchTreeType;

typedef struct SearchTreeNode {
  SearchTreeType data;
  struct SearchTreeNode* lchild;
  struct SearchTreeNode* rchild;
} SearchTreeNode;

void SearchTreeInit(SearchTreeNode** pRoot); //初始化二叉搜索树

void SearchTreeInsert(SearchTreeNode** pRoot, SearchTreeType to_insert);//二叉搜索树插入

SearchTreeNode* SearchTreeFind(SearchTreeNode* root, 
                               SearchTreeType to_find); //查找二叉搜索树

void SearchTreeRemove(SearchTreeNode** pRoot, SearchTreeType to_remove);//删除二叉搜索树中某一个元素

void SearchTreeInsertByLoop(SearchTreeNode** pRoot, SearchTreeType to_insert);//非递归版本二叉搜索树插入

SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root, 
                               SearchTreeType to_find); //非递归版本查找二叉搜索树

void SearchTreeRemoveByLoop(SearchTreeNode** pRoot, SearchTreeType to_remove);//非递归版本删除二叉搜索树中某一个元素
