#include <stdio.h>
#include "seqstack.h"

int str_instack(SeqStack* s, char* str1, char* str2, int len)
{
  if(str1 == NULL || str2 == NULL) {
    return -1;
  }

  SeqStackType top;
  SeqStackInit(s);
  int i = 0;

  for(; i < len; ++i) {
    SeqStackPush(s, *str1);
    SeqStackGetFront(s, &top);

    while(top == *str2) {
      SeqStackPop(s);
      SeqStackGetFront(s, &top);
      str2++;
    }
    if(*str2 == '\0') {
      return 1;
    }
    str1++;
  }
  return -1;
}

int main()
{
  SeqStack s;
  int ret;
  char str1[5] = {'a', 'b', 'c', 'd', 'e'};
  char str2[5] = {'a', 'c', 'd', 'e', 'b'};
  char str3[5] = {'a', 'd', 'b', 'e', 'c'};
  int len = sizeof(str1)/sizeof(str1[0]);

  ret = str_instack(&s, str1, str2, len);
  printf("expected ret 1,actual ret %d\n",ret);

  ret = str_instack(&s, str1, str3, len);
  printf("expected ret -1,actual ret %d\n",ret);

  return 0;
}






