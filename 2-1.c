#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Edgenode{
    int adj;
    float len;
    int seq;
    struct Edgenode *next;
}edge;

typedef struct Vertexnode{
    char name[20];
    edge *first;
}vertex, list[50];

typedef struct{
    list L;
    int numvex, numedge;
}graph;


int compare(char a[][20], char b[]){
    int len=0;
    while(a[len][0] != 0) len++;
    for(int i=0; i<len; i++){
        if(!(strcmp(a[i], b))){
			return 0;
		}
    }
    return 1;
}

int get_position(graph *g, char* c){
    int i;
    for(i=0; i<g->numvex; i++)
        if(strcmp(g->L[i].name, c) == 0) return i;
    return -1;
}

void Create(graph *g, char n[][20], char a[][2][20], float way[], int seq[], int vexnum, int arcnum){
    int i;
    memset(g, 0, sizeof(graph));
    g->numedge = arcnum;
    g->numvex = vexnum;

    for(i=0; i<vexnum; i++){
        strcpy(g->L[i].name, n[i]);
        g->L[i].first=NULL;
    }

    char c1[20], c2[20];
    int p1, p2;
    for(i=0; i<arcnum; i++){
        strcpy(c1, a[i][0]);
        strcpy(c2, a[i][1]);

        p1=get_position(g, c1);
        p2=get_position(g, c2);

        edge *node1=(edge*)malloc(sizeof(edge*));
        node1->adj = p2;
        node1->len = way[i];
        node1->seq=i;

        node1->next=g->L[p1].first;
        g->L[p1].first=node1;

    }
}

void Printgraph(graph g, int n, int *seq, int *road){
    int i, j, k=0;
    int flag;
    edge *p;
    // for(i=0; p->next!=NULL; i++){
    //     printf("%d\n", p->seq);
    // }
    for(i=0; i<n; i++){
        for(; k<road[i]; k++){
            flag=1;
            for(j=0; j<g.numvex; j++){
                p=g.L[j].first;
                for(; p!=NULL; p=p->next){
                    if(p->seq==k && (k==0||k==road[i-1])){
                        printf("%d %s %.2f %s", seq[i], g.L[j].name, p->len, g.L[p->adj].name);
                        flag=0;
                        break;
                    }
                    else if(p->seq==k){
                        printf(" %.2f %s", p->len, g.L[p->adj].name);
                        flag=0;
                        break;
                    }
                }
                if(flag==0) break;
            } 
        }   
       printf("\n");
    }
}

int main(){
    int n, route;
	scanf("%d", &n);
	float len;
	char c;
	int i, j, k;
    int seq[n], roadnum[4]={4, 11, 16, 24};
	char tmpname[30][20]={0}, name[30][20]={0};
	char line[50][2][20]={0};
	float tmplength[n][20], length[50]={0};
	int cnt1=0, cnt2=0, cnt3=0;
	
	for(i=0; i<n; i++){
		scanf("%d ", &route);
        seq[i]=route;
		len=1;
		for(k=0; len!=0; k++){
			if(c==' ' && k!=0) getchar();
			for(j=0; (c=getchar()) != ' ';j++) tmpname[k][j]=c;
			scanf("%f", &len);
			tmplength[i][k]=len;
			if(len==0) break;
		}
		for(j=0; tmplength[i][j]!=0; j++){
			strcpy(line[cnt1][0], tmpname[j]);
			strcpy(line[cnt1][1], tmpname[j+1]);
			cnt1++;       
		}
		j=0;
        do{
			if(compare(name, tmpname[j])==1) strcpy(name[cnt2++], tmpname[j]);
		}while(tmplength[i][j++]!=0);
			
        for(j=0; tmplength[i][j]!=0; j++) length[cnt3++] = tmplength[i][j];
		memset(tmpname, 0, sizeof(tmpname));
	}

    int arcnum=cnt3, vexnum=cnt2;
    graph g;
    Create(&g, name, line, length, seq, vexnum, arcnum);
    Printgraph(g, n, seq, roadnum);
    return 0;
}