//
// Created by 福井航大 on 2019/11/07.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  N 10

int main () {

    int i;

    srand((unsigned) time(NULL));

    double a[N];
    double b[N];
    double ans;

    for (i=0; i<N; i++) {
        a[i] =  (double)rand()/RAND_MAX;
        printf("%lf ",a[i]);
    }
    printf("\n");

    for (i=0; i<N; i++) {
        b[i] =  (double)rand()/RAND_MAX;
        printf("%lf ",b[i]);
    }

    for (i=0;i<N;i++){
        ans = ans+a[i]+b[i];
    }

    printf("%lf\n",ans);

    return 0;


}
