#include <stdio.h>
int judge(int a, int b, int c){
    int tmp, flag;
    int mask=0x80;
    for(int i=0; i<=7; i++){
        tmp = c<<(i) & mask;
        if(tmp == mask){
            flag = (a<<(i) & mask) ^ (b<<(i) & mask);
        }
    }
    return flag;
}
int main(){
    int xa, xb, xc, xd, ya, yb, yc, yd;
    printf("请输入两个IPv4地址：\n");
    scanf("%d.%d.%d.%d", &xa, &xb, &xc, &xd);
    scanf("%d.%d.%d.%d", &ya, &yb, &yc, &yd);
    printf("请输入子网掩码：\n");
    int za, zb, zc, zd;
    scanf("%d.%d.%d.%d", &za, &zb, &zc, &zd);
    if(judge(xa, ya, za) == 0 && judge(xb, yb, zb) == 0 && judge(xc, yc, zc) == 0 && judge(xd, yd, zd) == 0) printf("true");
    else printf("false");
    return 0;
}