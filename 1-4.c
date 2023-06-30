#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Linknode{
    struct Linknode *next;
    float num;
    int power;
}L1;

typedef struct{
    L1 *head;
    L1 *tail;
}link;

void delete(char *a, int n){
    int len=strlen(a);
    for(int i=n; i<len; i++){
        a[i-1]=a[i];
    }
    a[len-1]=0;
}

float coef(char *t, int i){
    int flag;
    if(t[i]=='+') flag=1;
    else if(t[i]=='-') flag=-1;
    i++;
    float tmp=0;
    if(t[i]=='x') return flag;
    else{
        while(('0'<=t[i] && t[i]<='9') || t[i]=='.'){
            if(t[i]=='.'){
                tmp=tmp+(t[i+1]-'0')*0.1;
                break;
		    }
		    tmp=tmp*10+t[i++]-'0';
        }
        tmp=flag*tmp;
        return tmp;
    }
}

int expo(char *t, int i){
    int tmp=0, flag=1;
    if(t[i]=='x' && t[i+1]!='^') return 1;
    else{
        i+=2;
        if(t[i]=='-'){
            flag=-1;
            i++;
        }
        while('0'<=t[i] && t[i]<='9'){
		    tmp=tmp*10+t[i++]-'0';
        }
        tmp=tmp*flag;
        return tmp;
    }
}

link* Create(int len){
    link *p = (link*)malloc(sizeof(link*));
    L1 *headnode = (L1*)malloc(sizeof(L1*));
    p->head = headnode;
    p->head->next = p->tail = NULL;
    for(int i=0; i<len; i++){
        L1 *node = (L1*)malloc(sizeof(L1*));
        node->next = NULL;
        if(p->head->next == NULL){
            p->head->next = p->tail = node;
        }else{
            p->tail->next = node;
            p->tail = node;
        }
    }
    return p;
}

void AddData(link *p, float *a, int n){
    L1 *point = p->head->next;
    int i;
    for(i=0; i<n; i++){
        point->num = a[2*i];
        point->power = a[2*i+1];
        point = point->next;
    }
}

void Sort(link *p, int len){
    L1 *m, *n, *tail;
    int j;
    int num=len;
    for(int i=0; i<num-1; i++){
        j=num-1-i;
        m=p->head->next;
        n=m->next;
        tail=p->head;
        while(j--){
            if(m->power < n->power){
                m->next=n->next;
                n->next=m;
                tail->next=n;
            }
            tail=tail->next;
            m=tail->next;
            n=m->next;
        } 
    }
}

void ADD(link *p, link *q, link *result){
    L1 *p1=p->head->next, *p2=q->head->next, *p3=result->head->next;
    int sum=0;
    while(p1 && p2){
        if(p1->power == p2->power){
            sum=p1->num+p2->num;
            if(sum!=0){
                p3->num=sum;
                p3->power=p1->power;
                p1=p1->next;
                p2=p2->next;
                p3=p3->next;
            }else{
                p3->num=0;
                p1=p1->next;
                p2=p2->next;
            }
        }else if(p1->power < p2->power){
            p3->num=p2->num;
            p3->power=p2->power;
            p3=p3->next;
            p2=p2->next;
        }else{
            p3->num=p1->num;
            p3->power=p1->power;
            p3=p3->next;
            p1=p1->next;
        }
    }
    if(p1 == NULL){
        for(; p2; p2=p2->next){
            p3->num=p2->num;
            p3->power=p2->power;
            p3=p3->next;
        }
    }
    else{
        for(; p1; p1=p1->next){
            p3->num=p1->num;
            p3->power=p1->power;
            p3=p3->next;
        }
    }
    if(p3 && p3->next!=NULL) p3->next=NULL;
    p3=NULL;
}

void SUB(link *p, link *q, link *result){
    L1 *p1=p->head->next, *p2=q->head->next, *p3=result->head->next;
    int sum=0;
    while(p1 && p2){
        if(p1->power == p2->power){
            sum=p1->num-p2->num;
            if(sum!=0){
                p3->num=sum;
                p3->power=p1->power;
                p1=p1->next;
                p2=p2->next;
                p3=p3->next;
            }else{
                p3->num=0;
                p1=p1->next;
                p2=p2->next;
            }
        }else if(p1->power < p2->power){
            p3->num=(-1)*p2->num;
            p3->power=p2->power;
            p3=p3->next;
            p2=p2->next;
        }else{
            p3->num=p1->num;
            p3->power=p1->power;
            p3=p3->next;
            p1=p1->next;
        }
    }
    if(p1 == NULL){
        for(; p2; p2=p2->next){
            p3->num=(-1)*p2->num;
            p3->power=p2->power;
            p3=p3->next;
        }
    }
    else{
        for(; p1; p1=p1->next){
            p3->num=p1->num;
            p3->power=p1->power;
            p3=p3->next;
        }
    }
    
    if(p3->next && p3->next!=NULL) p3->next=NULL;
    p3->num=0;
}

void output(L1 *p){
    if(p->num==1){
        if(p->power==1) printf("x");
        else if(p->power==0) printf("1");
        else printf("x^%d", p->power);
        if(p->next!=NULL && p->next->num>0) printf("+");
    }else if(p->num==-1){
        if(p->power==1) printf("-x");
        else if(p->power==0) printf("-1");
        else printf("-x^%d", p->power);
        if(p->next!=NULL && p->next->num>0) printf("+");
    }else{
        if(p->power==1) printf("%gx", p->num);
        else if(p->power==0) printf("%g", p->num);
        else printf("%gx^%d", p->num, p->power);
        if(p->next!=NULL && p->next->num>0) printf("+");
    }
}

int main(){
    char t[80];
    float a[20]={0}, b[20]={0};
    int i=0, j=0, flag;
    int len1, len2;

    gets(t);
    if(t[1]!='-') t[0]='+';
    else delete(t, 1);

    while(t[i]!=')'){
        a[j++]=coef(t, i);
        i++;
        while(t[i]!='x' && t[i]!='+' && t[i]!='-'){
            if(t[i]==')'){
                a[j++]=0;
                goto A;
            }
            i++;
        }
        if(t[i]!='x') a[j++]=0;
        else a[j++]=expo(t, i);
        while(t[i]!=')' && t[i]!='+' && t[i]!='-') i++;
        if(t[i-1]=='^'){
            i++;
            while(t[i]!=')' && t[i]!='+' && t[i]!='-') i++;
        }
    }
A:  len1=j/2;
    j=0;
    if(t[++i] == '+') flag=1;
    else flag=2;
    i++;
    if(t[i+1]!='-') t[i]='+';
    else delete(t, i+1);
    while(t[i]!=')'){
        b[j++]=coef(t, i);
        i++;
        while(t[i]!='x' && t[i]!='+' && t[i]!='-'){
            if(t[i]==')'){
                a[j++]=0;
                goto B;
            }
            i++;
        }
        if(t[i]!='x') b[j++]=0;
        else b[j++]=expo(t, i);
        while(t[i]!=')' && t[i]!='+' && t[i]!='-' ) i++;
        if(t[i-1]=='^'){
            i+=2;
            while(t[i]!=')' && t[i]!='+' && t[i]!='-') i++;
        }
    }
B:  len2=j/2;

    link *poly1, *poly2, *result;
    poly1=Create(len1);
    poly2=Create(len2);
    result=Create(len1+len2);

    AddData(poly1, a, len1);
    AddData(poly2, b, len2);
    Sort(poly1, len1);
    Sort(poly2, len2);

    L1 *p=poly1->head->next;
    L1 *q=poly2->head->next;
    if(p->num==0 && p->power==0){
        while(q!=NULL){
            if(q->num == 0){
                q=q->next;
                continue;
            }
        output(q);
        q=q->next;
        }
        return 0;
    }

    if(flag == 1) ADD(poly1, poly2, result);
    else SUB(poly1, poly2, result);

    L1 *m=result->head->next;
    if(m->next==NULL) printf("0");
    while(m!=NULL){
        if(m->num == 0){
            m=m->next;
            continue;
        }
        if(m->next && m->power==m->next->power){
            m->num=m->num+m->next->num;
            m->next=m->next->next;
        }
        output(m);
        m=m->next;
    }
    
    return 0;
}