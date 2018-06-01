#include "maze.h"

#define HEAD printf("==============%s==============\n",__FUNCTION__);

void MazeInit(Maze* maze)//初始化地图
{
  if(maze == NULL) {
    return;
  }

  int map[ROW][COL] = {
    {0,1,0,0,0,0},
    {0,1,1,1,0,0},
    {0,1,0,1,1,0},
    {1,1,0,0,1,1},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
  };

  size_t i = 0;
  size_t j = 0;
  for(; i < ROW; ++i) {
    for(j = 0; j < COL; ++j) {
      maze->map[i][j] = map[i][j];
    }
  }

  return;
}

void MazeMapPrint(Maze* maze)//打印地图
{
  if(maze == NULL) {
    return;
  }

  printf("\n");
  size_t i = 0;
  size_t j = 0;
  for(; i < ROW; ++i) {
    for(j = 0; j < COL; ++j) {
      printf("%2d ",maze->map[i][j]);
    }
    printf("\n");
  }
}

int CanStay(Maze* maze, Point cur)//是否能够落脚
{
  if(maze == NULL) {
    return 0;
  }

  if(cur.col < 0 || cur.col >= COL || \
     cur.row < 0 || cur.row >= ROW) {
    return 0;
  }

  if(maze->map[cur.row][cur.col] == 1) {
    return 1;
  }
  return 0;
}

void MarkStay(Maze* maze, Point cur)//标记落脚点
{
  if(maze == NULL) {
    return;
  }
  maze->map[cur.row][cur.col] = 2;
}

int isExit(Maze* maze, Point cur, Point entry)//判断是否是出口点
{
  if(maze == NULL) {
    return 0;
  }
  if((cur.row == 0 || cur.row == ROW - 1 || \
     cur.col == 0 || cur.col == COL - 1) && \
     (cur.col != entry.col || cur.row != entry.row)) {
    return 1;
  }
  return 0;
}
////////////////////////////////////////////////////////
//Plan A
////////////////////////////////////////////////////////
int _GetPathMaze(Maze* maze, Point cur, Point entry)
{
  printf("(%d,%d)\n",cur.row, cur.col);
  if(maze == NULL) {
    return 0;
  }
  //判断是否能落脚
  if(!CanStay(maze, cur)) {
    return 0;
  }
  //标记落脚点
  MarkStay(maze, cur);
  //判断是否是出口点
  if(isExit(maze, cur, entry)) {
    printf("找到一条路径\n");
    return 1;
  }
  //如果不是出口点那么就判断它的四周
  //预定顺序为上、右、下、左
  Point up = cur;  
  up.row -= 1;
  _GetPathMaze(maze, up, entry);

  Point right = cur;  
  right.col += 1;
  _GetPathMaze(maze, right, entry);

  Point down = cur;  
  down.row += 1;
  _GetPathMaze(maze, down, entry);

  Point left = cur;  
  left.col -= 1;
  _GetPathMaze(maze, left, entry);

  return 1;
}

void GetPathMaze(Maze* maze,Point entry)//查找路径
{
  if(maze == NULL) {
    return;
  }
  entry.row = 0;
  entry.col = 1;

  _GetPathMaze(maze, entry, entry);
}
////////////////////////////////////////////////////////
//Plan B
////////////////////////////////////////////////////////
int _GetPathMazeByMyStack(Maze* maze, Point entry) 
{
  if(maze == NULL) {
    return 0;
  }
  SeqStack stack;
  SeqStackInit(&stack);
  //首先判断是否能够落脚
  if(!(CanStay(maze, entry))) {
    return 0;
  }
  //如果能够落脚，那么这个时候就标记落脚点，并且入栈
  MarkStay(maze, entry);
  SeqStackPush(&stack, entry);
  //判断是否是出口，如果是出口就进行打印并标记
  //如果不是出口点，此时应该判断其四周的点，是否能够落脚
  //如果可以落脚就标记并入栈依次循环
  Point cur;
  while(SeqStackGetFront(&stack, &cur)) {
    if(isExit(maze, cur, entry)) {
      MarkStay(maze, cur);
      printf("找到一条路径\n");
      SeqStackPop(&stack);
      continue;
    }

    Point up = cur;
    up.row -= 1;
    if(CanStay(maze, up)) {
      MarkStay(maze, up);
      SeqStackPush(&stack, up);
      continue;
    }

    Point right = cur;
    right.col += 1;
    if(CanStay(maze, right)) {
      MarkStay(maze, right);
      SeqStackPush(&stack, right);
      continue;
    }

    Point down = cur;
    down.row += 1;
    if(CanStay(maze, down)) {
      MarkStay(maze, down);
      SeqStackPush(&stack, down);
      continue;
    }

    Point left = cur;
    left.col -= 1;
    if(CanStay(maze, left)) {
      MarkStay(maze, left);
      SeqStackPush(&stack, left);
      continue;
    }

    SeqStackPop(&stack);
  }
  return 1;
}

void GetPathMazeByMyStack(Maze* maze, Point entry) 
{
  if(maze == NULL) {
    return;
  }
  entry.row = 0;
  entry.col = 1;

  _GetPathMazeByMyStack(maze, entry);

  return;
}

////////////////////////////////////////////////////////
//ShortPath 
////////////////////////////////////////////////////////
int _GetShortPath(Maze* maze, Point cur, Point entry, SeqStack* cur_path, SeqStack* short_path)//获取最短路径
{
  if(maze == NULL) {
    return 0;
  }
  //判断是否能够落脚
  if(!CanStay(maze, cur)) {
    return 0;
  }

  //如果可以落脚，那么标记，并且对其进行入栈至cur_path
  MarkStay(maze, cur);
  SeqStackPush(cur_path, cur);
  //判断是否是出口，如果是出口，比较cur_path与short_path
  //比较两者size
  if(isExit(maze, cur, entry)) {
    printf("找到一条路径\n");
    SeqStackPrintShort(cur_path);
    if(cur_path->size < short_path->size || short_path->size == 0) {
      SeqStackAssign(cur_path, short_path);
    }
    SeqStackPop(cur_path);
    return 1;
  }
  //如果不是出口则探测其四周
  Point up = cur;  
  up.row -= 1;
  _GetShortPath(maze, up, entry, cur_path, short_path);

  Point right = cur;  
  right.col += 1;
  _GetShortPath(maze, right, entry, cur_path, short_path);

  Point down = cur;  
  down.row += 1;
  _GetShortPath(maze, down, entry, cur_path, short_path);

  Point left = cur;  
  left.col -= 1;
  _GetShortPath(maze, left, entry, cur_path, short_path);

  SeqStackPop(cur_path);

  return 1;
}

void GetShortPath(Maze* maze, Point entry)
{
  if(maze == NULL) {
    return;
  }

  SeqStack cur_path;
  SeqStack short_path;
  SeqStackInit(&cur_path);
  SeqStackInit(&short_path);

  entry.row = 0;
  entry.col = 1;

  _GetShortPath(maze, entry, entry, &cur_path, &short_path);
  printf("最短路径是\n");
  SeqStackPrintShort(&short_path);
  SeqStackPrintShort(&cur_path);
}
////////////////////////////////////////////////////
//ShortPathWithCycle
////////////////////////////////////////////////////

/////////////////////
// 
//    {0,2,0,0,0,0},
//    {0,3,1,1,0,0},
//    {0,1,0,1,1,1},
//    {1,1,1,1,0,0},
//    {0,0,1,0,0,0},
//    {0,0,1,0,0,0}

void MazeInitCycle(Maze* maze)
{
  if(maze == NULL) {
    return;
  }

  int map[ROW][COL] = {
    {0,1,0,0,0,0},
    {0,1,1,1,0,0},
    {0,1,0,1,1,1},
    {1,1,1,1,0,0},
    {0,0,1,0,0,0},
    {0,0,1,0,0,0}
  };

  size_t i = 0;
  size_t j = 0;
  for(; i < ROW; ++i) {
    for(j = 0; j < COL; ++j) {
      maze->map[i][j] = map[i][j];
    }
  }

  return;
}

int CanStayWithCycle(Maze* maze, Point cur, Point pre)//判断是否可以落脚
{
  if(maze == NULL) {
    return 0;
  }
  if(maze->map[cur.row][cur.col] == 1) {//如果落脚点的map值为1那么直接返回可以落脚
    return 1;
  }

  if(maze->map[pre.row][pre.col] + 1 < maze->map[cur.row][cur.col]) {
    return 1;
  }
  return 0;
}

void MarkStayWithCycle(Maze* maze, Point cur, Point pre)//标记为前一个点的下标+1
{
  if(maze == NULL) {
    return;
  }
  maze->map[cur.row][cur.col] = maze->map[pre.row][pre.col] + 1;
}

int _GetPathWithCycle(Maze* maze, Point cur, Point entry,
                      SeqStack* cur_path, SeqStack* short_path, Point pre)
{
//  printf("(%d, %d)\n",cur.row, cur.col);
  if(maze == NULL)
  {
    return 0;
  }
  //首先判断是否能落脚，这里判断是否能落脚时是跟前面不一样的
  //需要比较落脚地方与前面地方的值的大小
  if(!CanStayWithCycle(maze, cur, pre)) {
    return 0;
  }
  //如果可以落脚，那么就对落脚点进行标记，标记方式也与前面不同
  //并入栈
  MarkStayWithCycle(maze, cur, pre);//标记
  SeqStackPush(cur_path, cur);//入栈cur_path
  pre = cur;
  //如果是出口点，那么比较cur_path与short_path的size大小进行比较
  if(isExit(maze, cur, entry)) {
    printf("找到一条路径\n");
    if(cur_path->size < short_path->size || short_path->size == 0) {
      SeqStackAssign(cur_path, short_path);
    }
    SeqStackPop(cur_path);
    return 1;
  }
  //如果不是出口点，那么探寻上、右、下、左四点
  Point up = cur;
  up.row -= 1;
  _GetPathWithCycle(maze, up, entry, cur_path, short_path, pre);

  Point right = cur;
  right.col += 1;
  _GetPathWithCycle(maze, right, entry, cur_path, short_path, pre);

  Point down = cur;
  down.row += 1;
  _GetPathWithCycle(maze, down, entry, cur_path, short_path, pre);

  Point left = cur;
  left.col -= 1;
  _GetPathWithCycle(maze, left, entry, cur_path, short_path, pre);

  SeqStackPop(cur_path);
  return 1;
}

void GetPathWithCycle(Maze* maze, Point entry)//探寻带环路径
{
  if(maze == NULL) {
    return;
  }

  SeqStack cur_path;
  SeqStack short_path;
  SeqStackInit(&cur_path);
  SeqStackInit(&short_path);

  entry.row = 0;
  entry.col = 1;

  _GetPathWithCycle(maze, entry, entry, &cur_path, &short_path, entry);
  printf("找到一条最短路径\n");
  SeqStackPrintShort(&short_path);
}


////////////////////////////////////////////////////
//测试代码
////////////////////////////////////////////////////

void TestInit()
{
  HEAD;
  Maze maze;
  MazeInit(&maze);
  MazeMapPrint(&maze);
}

void TestGetPath()
{
  HEAD;
  Maze maze;
  Point entry;
  MazeInit(&maze);
  MazeMapPrint(&maze);
  GetPathMaze(&maze, entry);
  MazeMapPrint(&maze);
}

void TestGetPathByMyStack()
{
  HEAD;
  Maze maze;
  Point entry;
  MazeInit(&maze);
  MazeMapPrint(&maze);
  GetPathMazeByMyStack(&maze, entry);
  MazeMapPrint(&maze);
}

void TestGetPathWithCycle()
{
  HEAD;
  Maze maze;
  Point entry;
  MazeInitCycle(&maze);
  MazeMapPrint(&maze);
  GetPathWithCycle(&maze, entry);
  MazeMapPrint(&maze);
}

void TestGetShortPath()
{
  HEAD;
  Maze maze;
  Point entry;
  MazeInit(&maze);
  MazeMapPrint(&maze);
  GetShortPath(&maze, entry);
  MazeMapPrint(&maze);
}

int main()
{
  TestInit();
  TestGetPath();
  TestGetPathByMyStack();
  TestGetShortPath();
  TestGetPathWithCycle();

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  return 0;
}



