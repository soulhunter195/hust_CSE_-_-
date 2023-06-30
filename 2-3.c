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

static int visited[50];//标记节点是否被访问过
static int path_next[50];//记录节点在路径中的下一个节点
static int path_record[50];//记录路径
static int rec=0;

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

int MIN(float *a){
	int i, tmp2=0;
	float tmp1=a[0];
	for(i=0; a[i]!=0; i++){
		if(a[i] < tmp1){
			tmp1=a[i];
			tmp2=i;
		}
	}
	return tmp2;
}

void FreeGraph(graph *g){
    int i;
    edge *p, *q;
    for(i=0; i<g->numvex; i++){
        p = g->L[i].first;
        while(p){
            q = p->next;
            free(p);
            p = q;
        }
    }
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

edge* neighbour(graph *g, int record){
	edge *p;
	p=g->L[record].first;
	while(p!=NULL){
		if(visited[p->adj]==1) p=p->next;
		else{
			if(path_next[record]==-1){
				while(p!=NULL && visited[p->adj]==1) p=p->next;
				return p;
			}else if(path_next[record] == p->adj){
				p=p->next;
				while(p!=NULL && visited[p->adj]==1) p=p->next;
				return p;
			}else p=p->next;
		}
	}
}

void path(graph *g, char *s1, char *s2, char name[][20]){
	int start, end;
	start=get_position(g, s1);
	end=get_position(g, s2);

	int i, curvex, cnt=0;
	int record1[5], pathrec[5][20];
	float len[5][10], lensum[5];
	edge *p, *q;
	memset(lensum, 0, sizeof(lensum));

	path_record[rec]=start;
	visited[start]=1;
	while(rec>=0){
		curvex=path_record[rec];
		if(curvex == end){
            for(i=0; i<rec; i++){
				q=g->L[path_record[i]].first;
				while(q->adj!=path_record[i+1]) q=q->next;
				len[cnt][i]=q->len;
            }
			for(i=0; i<rec; i++) lensum[cnt]+=len[cnt][i];
			for(i=0; i<=rec; i++) pathrec[cnt][i]=path_record[i];
			
			record1[cnt]=rec;
			visited[end]=0;
			path_next[end]=-1;
			path_record[rec]=-1;
			rec--;
			cnt++;
		}else{
			p=neighbour(g, curvex);
			if(p!=NULL){
				path_next[curvex]=p->adj;
				rec++;
				path_record[rec]=p->adj;
				visited[p->adj]=1;
			}else{
				visited[curvex]=0;
				path_record[rec]=-1;
				path_next[curvex]=-1;
				rec--;
			}
		}
	}

	int cnt2=MIN(lensum);
	for(i=0; i<=record1[cnt2]; i++){
		if(i == 0) printf("%.2f %s %.2f", lensum[cnt2], name[pathrec[cnt2][i]], len[cnt2][i]);
		else if(i == record1[cnt2]) printf(" %s", name[pathrec[cnt2][i]]);
		else printf(" %s %.2f", name[pathrec[cnt2][i]], len[cnt2][i]);
	}
	printf("\n");
}

int main(){
    int n, route;
	scanf("%d", &n);
	float len;
	char c;
	int i, j, k;
    int seq[n];
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

	char start[20], end[20];
	for(i=0; i<g.numvex; i++){
        visited[i] = 0;
        path_next[i] = -1;
        path_record[i] = -1;
    }
	scanf("%s%s", start, end);
	path(&g, start, end, name);

	FreeGraph(&g);
    return 0;
}