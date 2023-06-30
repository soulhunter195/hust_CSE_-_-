#include <stdio.h>
#include <stdlib.h>

typedef struct Linknode{
    struct Linknode *next;
    float num;
    int power;
}L1;

typedef struct{
    L1 *head;
    L1 *tail;
}link;

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

int main(){
    char t[60];
    float a[20]={0}, b[20]={0};
    int i=0, j=0, c=1, flag=0;
    int len1, len2;
    char symbol;
    float tmp=0;

    gets(t);
    while(1){
		if((t[i]=='+' || t[i]=='-') && t[i+1]==' '){
			symbol=t[i];
			len1=j/2;
			goto A;
		}
		if(t[i]==' '){
			a[j++]=c*tmp;
            c=1;
			tmp=0;
            i++;
            continue;
		}
		if(t[i]=='-') c=-1;
		if(t[i]=='.'){
			tmp=tmp+(t[i+1]-'0')*0.1;
			i+=2;
			continue;
		}
		if('0'<=t[i]&&t[i]<='9') tmp=tmp*10+t[i++]-'0';
		else i++;
	}
A:	j=0;
	i+=2;
	while(1){
		if(t[i]=='\n' || t[i]=='\0'){
			b[j++]=c*tmp;
			len2=j/2;
			break;
		}
		if(t[i]==' '){
			b[j++]=c*tmp;
			tmp=0;
            c=1;
			i++;
            continue;
		}
		if(t[i]=='-') c=-1;
		if(t[i]=='.'){
			tmp=tmp+(t[i+1]-'0')*0.1;
			i+=2;
			continue;
		}
		if('0'<=t[i]&&t[i]<='9')  tmp=tmp*10+t[i++]-'0';
		else i++;
	}

    if(symbol == '+') flag=1;
    else flag=2;

    link *poly1, *poly2, *result;
    poly1=Create(len1);
    poly2=Create(len2);
    result=Create(len1+len2);

    AddData(poly1, a, len1);
    AddData(poly2, b, len2);
    Sort(poly1, len1);
    Sort(poly2, len2);

    if(flag == 1) ADD(poly1, poly2, result);
    else SUB(poly1, poly2, result);

    L1 *m=result->head->next;
    if(m->next==NULL) printf("0 0");
    while(m!=NULL){
        if(m->num == 0){
            m=m->next;
            continue;
        }
        printf("%g ", m->num);
        printf("%d ", m->power);
        m=m->next;
    }
    
    return 0;
}