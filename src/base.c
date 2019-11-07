#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#define  N 10


double a[N];
double b[N];


void data_create(){
    int i;
    srand((unsigned) time(NULL));

    double ans;

    for (i=0; i<N; i++) {
        a[i] =  (double)rand()/RAND_MAX;
    }
    for (i=0; i<N; i++) {
        b[i] =  (double)rand()/RAND_MAX;
    }
}


double calc(){
    double ans = 0;
    int i;
    for (i=0;i<N;i++) {
        ans = ans + a[i] + b[i];
    }
    return ans;
}


int check(double target){
    double ans=0;
    int i;
    for (i=0;i<N;i++){
        ans = ans+a[i]+b[i];
    }

    if (fabs(ans - target) <= DBL_EPSILON * fmax(1, fmax(fabs(ans), fabs(target)))) {
        return 1;
    }
    else
        return 0;

}

int main() {
    double ans;

    data_create();

    clock_t start,end;

    start = clock();
    ans = calc();
    end = clock();
    printf("%lf 秒かかりました\n",(double)(end-start)/CLOCKS_PER_SEC);
    if(check(ans))
        printf("OK\n");
    else
        printf("NG\n");

    return 0;
}