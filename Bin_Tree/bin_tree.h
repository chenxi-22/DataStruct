#pragma once

#include <stdio.h>
#include <stddef.h>
#include "seqqueue.h"
#include "seqstack.h"
#include <assert.h>

typedef char TreeNodeType;

typedef struct TreeNode{
  TreeNodeType data;
  struct TreeNode* lchild;
  struct TreeNode* rchild;
}TreeNode;

void TreeInit(TreeNode** proot);//初始化二叉树

void TreePreOrder(TreeNode* root);//先序访问二叉树

void TreeInOrder(TreeNode* root);//中序访问二叉树

void TreePostOrder(TreeNode* root);//后序访问二叉树

void TreeLevelOrder(TreeNode* root);//层序访问二叉树

TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node);//根据先序创建二叉树 

void TreeDestroy(TreeNode* root);//销毁二叉树

TreeNode* TreeClone(TreeNode* root);//深度复制二叉树

size_t TreeSize(TreeNode* root);//求二叉树节点的个数

size_t TreeLeafSize(TreeNode* root);//求二叉树叶子节点个数 

size_t TreeKLevelSize(TreeNode* root, int K);//求二叉树第K层节点个数 

size_t TreeHeight(TreeNode* root);//求二叉树的高度

TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find);//查找二叉树

TreeNode* LChild(TreeNode* node);//查找某一个节点的左子树

TreeNode* RChild(TreeNode* node);//查找某一个节点的右子树

TreeNode* Parent(TreeNode* root, TreeNode* node);//查找某个节点的父节点

void TreePreOrderByLoop(TreeNode* root);//先序访问二叉树(非递归方式)

void TreeInOrderByLoop(TreeNode* root);//中序访问二叉树(非递归方式)

void TreePostOrderByLoop(TreeNode* root);//后序访问二叉树(非递归方式)

void TreeMirror(TreeNode* root);//求一个二叉树的镜像二叉树

int isCompleteTree(TreeNode* root);//判断一个树是否为满二叉树

TreeNode* TreeRebuild(TreeNodeType pre_order[], size_t size, TreeNodeType in_order[]);//根据先序与中序遍历结果创建二叉树









