#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+3;

struct Tree_centroid{
	struct edge {int to,length; };
	bool centroid[MAXN];
	int subtree_size[MAXN];
	vector <edge> G[MAXN];
	
	int compute_subtree_size(int v,int p){
		int c=1;
		for (int i=0;i<G[v].size();i++) {
			int w=G[v][i].to;
			if ( w==p || centroid[w]) continue;
			c+=compute_subtree_size(G[v][i].to,v);
		}
		subtree_size[v]=c;
		return c;
	}
	
	pair <int,int> search_centroid(int v,int p,int t){
		pair<int,int> res=make_pair(INT_MAX,-1);
		int s=1,m=0;
		for (int i=0;i<G[v].size();i++){
			int w=G[v][i].to;
			if (w==p || centroid[w]) continue;
			res=min(res,search_centroid(w,v,t));
			m=max(m,subtree_size[w]);
			s+=subtree_size[w];
		}
		m=max(m,t-s);
		res=min(res,make_pair(m,v));
		return res;
	}
}get_centroid;

int main(){
	return 0;
}
