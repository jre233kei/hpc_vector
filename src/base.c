#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <omp.h>

#define  N 100000000


double a[N];
double b[N];


void data_create() {
    int i;
    srand((unsigned) time(NULL));

    double ans;

    for (i = 0; i < N; i++) {
        a[i] = (double) rand() / RAND_MAX;
    }
    for (i = 0; i < N; i++) {
        b[i] = (double) rand() / RAND_MAX;
    }
}

/* 通常のプログラム */
/*
double calc(){
    double ans = 0;
    int i;
    for (i=0;i<N;i++) {
        ans = ans + a[i] * b[i];
    }
    return ans;
}
*/

/* open mp */
/*
double calc() {
    double ans = 0;
    int i;
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        ans = ans + a[i] * b[i];
    }
    return ans;
}
*/

/* 正しくなるよう工夫 */
/*
double calc() {
    double ans = 0;
    int i;
    double *tmp = malloc(N* sizeof(double));

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        tmp[i] = a[i] * b[i];
    }

    for (i = 0; i < N; i++) {
        ans += tmp[i];
    }
    return ans;
}
 */


/* 加算部分を分割 */
/*
double calc() {
    double ans = 0;
    int i;
    double tmp[4];

    for (i = 0; i < N; i+=4) {
        tmp[0] = tmp[0] + a[i] * b[i];
        tmp[1] = tmp[1] + a[i+1] * b[i+1];
        tmp[2] = tmp[2] + a[i+2] * b[i+2];
        tmp[3] = tmp[3] + a[i+3] * b[i+3];
    }

    for (i = 0; i < 4; i++) {
        ans += tmp[i];
    }
    return ans;
}
*/

/* 加算部分を分割 */
/*
double calc() {
    double ans = 0;
    int i;
    double tmp[8];
    for (i = 0; i < N; i+=8) {
        tmp[0] = tmp[0] + a[i] * b[i];
        tmp[1] = tmp[1] + a[i+1] * b[i+1];
        tmp[2] = tmp[2] + a[i+2] * b[i+2];
        tmp[3] = tmp[3] + a[i+3] * b[i+3];
        tmp[4] = tmp[4] + a[i+4] * b[i+4];
        tmp[5] = tmp[5] + a[i+5] * b[i+5];
        tmp[6] = tmp[6] + a[i+6] * b[i+6];
        tmp[7] = tmp[7] + a[i+7] * b[i+7];
    }

    for (i = 0; i < 8; i++) {
        ans += tmp[i];
    }
    return ans;
}
 */

double calc() {
    double ans = 0;
    int i;
    double tmp[2];
    for (i = 0; i < N; i+=2) {
        tmp[0] = tmp[0] + a[i] * b[i];
        tmp[1] = tmp[1] + a[i+1] * b[i+1];
    }

    for (i = 0; i < 2; i++) {
        ans += tmp[i];
    }
    return ans;
}

int check(double target) {
    double ans = 0;
    int i;
    for (i = 0; i < N; i++) {
        ans = ans + a[i] * b[i];
    }

    if (fabs(ans - target) <= 1e-7 * fmax(1, fmax(fabs(ans), fabs(target)))) {
        return 1;
    } else
        return 0;
}

int main() {
    double ans;
    int i;

    double time = 0.0;

    /* ウォームアップ */
    data_create();
    ans = calc();
    if (check(ans))
        printf("OK\n");
    else
        printf("NG\n");

    /* 計測開始 */
    clock_t start, end;

    for (i = 0; i < 5; i++) {

        data_create();

        start = clock();
        ans = calc();
        end = clock();

        double t = (double) (end - start) / CLOCKS_PER_SEC;
        time += t;
        printf("%lf 秒かかりました\n", t);
        if (check(ans))
            printf("OK\n");
        else
            printf("NG\n");
    }

    printf("%lf\n",time/5);

    return 0;
}