#include<stdio.h>
#include<math.h>
int main(){
    printf("%d\n",1+2);
    printf("%d\n",3-4);
    printf("%d\n",5*6);
    printf("%d\n",8/4);
    printf("%d\n",8/5);
    //整形转换
    printf("__________________________\n");
    printf("%lf\n",8/5);
    printf("%lf\n",8.0/5);
    printf("%lf\n",8/5.0);
    printf("%lf\n",8.0/5.0);
    printf("%d\n",8.0/5.0);
    //
    printf("__________________________\n");
    printf("%lf",sqrt(9));
    return 0;
}