#include <time.h>
#include <stdio.h>

int main() {

    clock_t start,end;
    start = clock();

    // 何かの処理

    end = clock();

    printf("%lf秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}