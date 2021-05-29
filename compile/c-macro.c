// gcc -E c-macro.c
#include <stdio.h>
#define Begin() static int state=0; switch(state) { case 0:
#define Yield(x) do { state=__LINE__; printf("line:%d\n", __LINE__); if(x>3) return x; } while (0)
#define End() }
int function (void) {
    return 0;
}

int main(void){
  static int i;
  Begin();
  for (i = 0; i < 10; i++)
    Yield(i);
  End();

  return 0;
}
