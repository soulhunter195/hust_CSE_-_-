#include <stdio.h>
#include <stdlib.h>

typedef struct Linknode{
    struct Linknode *next;
    int num;
}L1;

typedef struct{
    L1 *head;
    L1 *tail;
}queue;

queue* Create(){
    queue *p = (queue*)malloc(sizeof(queue*));
    p->head = p->tail = NULL;
    for(int i=0; i<8; i++){
        L1 *node = (L1*)malloc(sizeof(L1*));
        node->next = NULL;
        if(p->head == NULL){
            p->head = p->tail = node;
        }else{
            p->tail->next = node;
            p->tail = node;
        }
    }
    p->tail->next = p->head;
    p->tail = p->head;
    return p;
}

void adddata(queue *p, int *a, int n, int i){
    L1 *point = p->head;
    for(int k=0; k<i; k++) point = point->next;
    for(int k=0; k<n; k++){
        if(k > 7) break;
        if(point->next == p->head){
            point->num = a[k];
            point = p->head;
        }else{
            point->num = a[k];
            point = point->next;
        }
    }
}

int main(){
    queue *p = Create();
    int n, i, k;

    scanf("%d", &n);
    if(n == 0){
        printf("Empty!");
        return 0;
    }

    scanf("%d%d", &i, &k);
    if(k > 8){
        printf("Error");
        return 0;
    }else if(k > n){
        printf("Fault");
        return 0;
    }

    int a[100];
    for(int m=0; m<n; m++) scanf("%d", &a[m]);

    adddata(p, a, n, i);

    if(n > 8) printf("Full ");

    L1 *point = p->head;
    for(int m=0; m<i; m++) point = point->next;
    for(int m=0; m<k; m++){
        printf("%d ", point->num);
        point=point->next;
    }

    return 0;
}