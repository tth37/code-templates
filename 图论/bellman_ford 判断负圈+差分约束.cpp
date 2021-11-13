#include<bits/stdc++.h>
using namespace std;
const int MAXN=2E4+3;
struct edge{
	int from,to,cost;
};
edge e[4*MAXN];
int d[MAXN],n,m,tot_edge;

int bellman_ford(int st,int V){
	const int INF=0X3fffffff;
	int negative_loop=0;
	memset(d,0x3f,sizeof(d));
	d[st]=0;
	
	for (int i=0;i<=V;i++)
		for (int j=1;j<=tot_edge;j++){
			edge ed=e[j];
			if (d[ed.from]!=INF && d[ed.to]>d[ed.from]+ed.cost){
				if (i==V) negative_loop=1;
				d[ed.to]=d[ed.from]+ed.cost;
			}
		}
	return negative_loop;
}

int main(){
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		++tot_edge;
		e[tot_edge].from=v,e[tot_edge].to=u,e[tot_edge].cost=w;
	}
	for (int i=1;i<=n;i++){
		++tot_edge;
		e[tot_edge].from=0,e[tot_edge].to=i,e[tot_edge].cost=0;
	}
	if (bellman_ford(0,n)) cout<<"NO";
	else{
		for (int i=1;i<=n;i++) printf("%d ",d[i]);
	}





	return 0;
}
