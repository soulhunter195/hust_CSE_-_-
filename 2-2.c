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

static int roadnum[4]={4, 11, 16, 24};

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

void DeleteArc(graph *g, int pa, int pb){
	edge *p, *temp;
	p=g->L[pa].first;
	if(p->adj==pb){
        temp=p;
		free(temp);
		g->L[pa].first=p->next;
	}
	while(p->next!=NULL){
        if(p->next->adj==pb){
            temp=p->next;
			p->next=temp->next;	
			free(temp);
			break;
		}			
		p=p->next;
	}
	g->numedge--; 
}

void Insert(graph *g, int metro, float *length, char s[][20], int *sequence, char name[][20]){
    int i, cnt, cnt2;
    for(cnt=0; ;cnt++) if(metro==sequence[cnt]) break;
    if(metro==1) cnt2=0;
    else cnt2=roadnum[cnt-1];

    int p1, p2, tmp;
    edge *node1, *node2, *p, *q;
    if(s[0][0]!=0){
        p1=get_position(g, s[0]);
        p2=g->numvex-1;

        q=g->L[p1].first;
        if(q->seq >= roadnum[cnt]) q=q->next;
        tmp=q->adj;
        for(i=0; i<g->numvex; i++){
            p=g->L[i].first;
            for(; p!=NULL; p=p->next) if(p->seq > q->seq) p->seq+=1;
        }

        node1=(edge*)malloc(sizeof(edge*));
        node1->adj=p2;
        node1->len=length[0];
        node1->seq=q->seq;
        node1->next=g->L[p1].first;
        g->L[p1].first=node1;
        g->numedge++;

        strcpy(g->L[p2].name, name[p2]);
        node2=(edge*)malloc(sizeof(edge*));
        node2->adj=tmp;
        node2->len=length[1];
        node2->seq=node1->seq+1;
        node2->next=NULL;
        g->L[p2].first=node2;
        g->numedge++;

        DeleteArc(g, p1, tmp);
    }else{
        p2=g->numvex-1;
        for(i=0; i<g->numvex; i++){
            p=g->L[i].first;
            for(; p!=NULL; p=p->next){
                if(p->seq == cnt2) tmp=i;
                if(p->seq >= cnt2) p->seq+=1;
            }
        }
        strcpy(g->L[p2].name, name[p2]);
        node2=(edge*)malloc(sizeof(edge*));
        node2->adj=tmp;
        node2->len=length[1];
        node2->seq=cnt2;
        node2->next=NULL;
        g->L[p2].first=node2;
        g->numedge++;
    }
    for(i=cnt; i<4; i++) roadnum[i]++;
}

void Delete(graph *g, int metro, char *s, int *sequence){
    int i, cnt, cnt2;
    for(cnt=0; ;cnt++) if(metro==sequence[cnt]) break;
    if(metro==1) cnt2=0;
    else cnt2=roadnum[cnt-1];

    int p1, p2=50, adjtmp, lentmp1=0, lentmp2=0, seqtmp;
    edge *node1, *p, *q;
    p1=get_position(g, s);
    p=g->L[p1].first;
    for(; p!=NULL; p=p->next){
        if(p->seq<roadnum[cnt] && p->seq>=cnt2){
            adjtmp=p->adj;
            lentmp1=p->len;
            seqtmp=p->seq;
        }
    }
    for(i=0; i<g->numvex; i++){
        q=g->L[i].first;
        for(; q!=NULL; q=q->next){
            if(q->adj==p1 && q->seq<roadnum[cnt] && q->seq>=cnt2){
                lentmp2=q->len;
                p2=i;
            }
        }
        if(p2==i) break;
    }
    for(i=0; i<g->numvex; i++){
        q=g->L[i].first;
        for(; q!=NULL; q=q->next) if(q->seq > seqtmp) q->seq--;
    }

    node1=(edge*)malloc(sizeof(edge*));
    node1->adj=adjtmp;
    node1->len=lentmp1+lentmp2;
    node1->seq=seqtmp-1;
    node1->next=g->L[p2].first;
    g->L[p2].first=node1;
    g->numedge++;

    DeleteArc(g, p2, p1);
    DeleteArc(g, p1, adjtmp);
    for(i=cnt; i<4; i++) roadnum[i]--;
}

void PrintPart(graph *g, int *seq, int metro){
    int i, j, cnt, cnt2;
    for(cnt=0; ;cnt++) if(metro==seq[cnt]) break;
    if(metro==1) cnt2=0;
    else cnt2=roadnum[cnt-1];

    edge *p;
    int flag;
    for(i=cnt2; i<roadnum[cnt]; i++){
        flag=1;
        for(j=0; j<g->numvex; j++){
            p=g->L[j].first;
            for(; p!=NULL; p=p->next){
                if(p->seq==i && i==cnt2){
                    printf("%d %s %.2f %s", metro, g->L[j].name, p->len, g->L[p->adj].name);
                    flag=0;
                    break;
                }
                else if(p->seq==i){
                    printf(" %.2f %s", p->len, g->L[p->adj].name);
                    flag=0;
                    break;
                }
            }
            if(flag==0) break;
        }
    }
    printf("\n");
}


void Printgraph(graph g, int n, int *seq){
    int i, j, k=0;
    int flag;
    edge *p;
    
    for(i=0; i<n; i++){
        for(; k<roadnum[i]; k++){
            flag=1;
            for(j=0; j<g.numvex; j++){
                p=g.L[j].first;
                for(; p!=NULL; p=p->next){
                    if(p->seq==k && (k==0||k==roadnum[i-1])){
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
    Printgraph(g, n, seq);

    char jg[10]={0};
    int metro, flag;
    float length2[2]={0};
    char sta[2][20]={0};
    scanf("%s", jg);
    if(!strcmp(jg, "add")){
        scanf("%d%f%f ", &metro, &length2[0], &length2[1]);
        if(length2[0]==0) scanf("%s", sta[1]);
        else{
            scanf("%s", sta[0]);
            scanf("%s", sta[1]); 
        } 
    }else{
        scanf("%d ", &metro);
        scanf("%s", sta[0]);
    }
    for(i=0; name[i][0]!=0; i++){
        if(sta[0][0]==0) flag=0;
        if(!strcmp(sta[0], name[i])) flag=0;
    }
    if(flag != 0){
        if(!strcmp(jg, "add")) printf("增加失败，没有与输入的增加位置前一站点同名的站点\n");
        else printf("删除失败，没有同名站点\n");
    }else{
        if(!strcmp(jg, "add")){
            flag=1;
            for(i=0; name[i][0]!=0; i++){
                if(!strcmp(sta[1], name[i])) flag=0;
            }
            if(flag==0) printf("增加失败，已有同名站点\n");
            else{
                strcpy(name[cnt2], sta[1]);
                cnt2++;
                g.numvex++;
                Insert(&g, metro, length2, sta, seq, name);
                PrintPart(&g, seq, metro);
            }
        }else{
            Delete(&g, metro, sta[0], seq);
            PrintPart(&g, seq, metro);
        }
        
    }
    return 0;
}