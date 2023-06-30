#include <stdio.h>
#include <stdlib.h>

typedef struct Linknode{
    struct Linknode *next;
    struct Linknode *pre;
    int num;
    int power;
}L1;

typedef struct{
    L1 *stackbot;
    L1 *stacktop;
}link;

link* Create(){
    link *p = (link*)malloc(sizeof(link*));
    p->stackbot = p->stacktop = NULL;
    int i;
    for(i=0; i<5; i++){
        L1 *node = (L1*)malloc(sizeof(L1*));
        node->next = node->pre = NULL;
        if(p->stackbot == NULL){
            p->stackbot = p->stacktop = node;
        }else{
            p->stacktop->next = node;
            node->pre = p->stacktop;
            p->stacktop = node;
        }
    }
    return p;
}

void powerdecrease(link *stack1, link *stack2, int *numout, int len1, int len2){
    L1 *p1=stack1->stacktop, *p2=stack2->stacktop;
    while(!(p1->num)) p1=p1->pre;
    while(!(p2->num)) p2=p2->pre;
  
    int i;
    for(i=0; i<(len1+len2); i++){
        if(p1->power > p2->power){
            numout[2*i]=p1->num;
            numout[2*i+1]=p1->power;

            if(p1==stack1->stackbot){
                for(; ; p2=p2->pre){
                    i++;
                    numout[2*i]=p2->num;
                    numout[2*i+1]=p2->power;
                    if(p2==stack2->stackbot) break;
                }
            }

            p1=p1->pre;
        }else{
            numout[2*i]=p2->num;
            numout[2*i+1]=p2->power;

            if(p2==stack2->stackbot){
                for(; ; p1=p1->pre){
                    i++;
                    numout[2*i]=p1->num;
                    numout[2*i+1]=p1->power;
                    if(p1==stack1->stackbot) break;
                }
            }
            
            p2=p2->pre;
        }
    }
}

void push(link *p, int *a, int n){
    L1 *point = p->stackbot;
    int i;
    for(i=0; i<n; i++){
        point->num = a[2*i];
        point->power = a[2*i+1];
        point = point->next;
    }
    for(i=n; i<5; i++){
        point->num = point->power = 0;
        point = point->next;
    }
}

int main(){
    int a[10]={0}, b[10]={0};
    int i=0, j=0;
    int len1, len2;

    char c;
    int tmp=0;
    while(1){
		c = getchar();
		if(c==';'){
            len1 = i/2; 
            goto A;
        }
		if(c==' ') {
			a[i++]=tmp;
            tmp=0;
		}else{
            //if(c=='.') tmp=
			tmp=tmp*10+c-'0';
		}
	}
A:  getchar();
    while(1){
        c = getchar();
		if(c=='\n'){
            b[j++]=tmp;
            len2 = j/2; 
            break;
        }
		if(c==' ') {
			b[j++]=tmp;
			tmp =0;
		}else{
			tmp=tmp*10+c-'0';
		}
	}

    if(len1>5 ||len2>5){
        printf("Full!");
        return 0;
    }

    link *stack1, *stack2;
    int numout[20];
    stack1=Create();
    stack2=Create();
    push(stack1, a, len1);
    push(stack2, b, len2);
    powerdecrease(stack1, stack2, numout, len1, len2);

    for(i=0; i<(len1+len2)*2-1; i++){
        printf("%d ", numout[i]);
    }
    printf("%d", numout[i]);

    return 0; 
}