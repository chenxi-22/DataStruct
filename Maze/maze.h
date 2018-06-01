#pragma once

#include <stdio.h>
#include <stddef.h>
#include "seqstack.h"

#define ROW 6
#define COL 6


typedef struct Maze{
  int map[ROW][COL];
}Maze;

void MazeInit(Maze* maze);//初始化地图
void MazeMapPrint(Maze* maze);//打印地图
void GetPathMaze(Maze* maze,Point entry);//查找路径



