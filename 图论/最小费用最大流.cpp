#include<bits/stdc++.h>
using namespace std;
const int INF=0X3f3f3f3f;
const int MAXN=2e4+3;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

struct min_cost{
	typedef pair <int,int> P;
	struct edge{ int to,cap,cost,rev;};
	int V;
	int max_flow=0;
	vector <edge> G[MAXN];
	int h[MAXN],dist[MAXN];
	int prevv[MAXN],preve[MAXN];
	
	void add_edge(int from,int to,int cap,int cost){
		G[from].push_back((edge){to,cap,cost,G[to].size()});
		G[to].push_back((edge){from,0,-cost,G[from].size()-1});
	}
	int min_cost_flow(int s,int t,int f){
		int res=0;
		memset(h,0,sizeof h);
		while (f>0){
			priority_queue<P,vector<P>,greater<P>> que;
		
			memset(dist,INF,sizeof dist);
			dist[s]=0;
			que.push(P(0,s));
			while (!que.empty()){
				P p=que.top();que.pop();
				int v=p.second;
				if (dist[v]<p.first) continue;
				for (int i=0;i<G[v].size();i++){
					edge &e=G[v][i];
					if (e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
						dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
						prevv[e.to]=v;
						preve[e.to]=i;
						que.push(P(dist[e.to],e.to));
					}
				}
			}
			if (dist[t]==INF) break;
			for (int v=1;v<=V;v++) h[v]+=dist[v];
			
			int d=f;
			for (int v=t;v!=s;v=prevv[v]){
				d=min(d,G[prevv[v]][preve[v]].cap);
			}
			f-=d;
			max_flow+=d;
			res+=d*h[t];
			for (int v=t;v!=s;v=prevv[v]){
				edge &e=G[prevv[v]][preve[v]];
				e.cap-=d;
				G[v][e.rev].cap+=d;
			}
		}
		return res;
	}
}mcost;

int n,m,s,t;
int main(){
	cin>>n>>m>>s>>t;
	mcost.V=n;
	for (int i=1,u,v,w,c;i<=m;i++){
		u=read(), v=read(),w=read(),c=read();
		mcost.add_edge(u,v,w,c);
	}
	int ans=mcost.min_cost_flow(s,t,INF);
	cout<<mcost.max_flow<<" "<<ans;
	return 0;
}
		

		
