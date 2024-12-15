#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

inline ll read(){
    char ch = getchar();
	ll x = 0, f = 1;
    while(ch < '0' || ch > '9') {
       if(ch == '-') f = -1;
      	  ch = getchar();
    }
    while(ch <= '9' && ch >= '0') {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
    return x * f;
}

int s, t;
int n, m, e;

int head[6020202], to[6020202], nxt[6020202], from[2020202];
ll w[6020202];
int tot = 1;
int matcha[202020], matchb[202020];

void add(int x, int y, ll z){
    tot++;
    to[tot] = y;
    w[tot] = z;
    from[tot] = x;
    nxt[tot] = head[x];
    head[x] = tot;
}

int table[2020][2020];
int deep[6020202];

bool bfs(){
    memset(deep, -1, sizeof(deep));
    deep[s] = 0;
    queue<int>q;
    q.push(s);
    while(q.size()){
        int x = q.front();
        q.pop();
        for(int i = head[x]; i; i = nxt[i]){
            int y = to[i];
            if(deep[y] < 0 && w[i]){
                deep[y] = deep[x] + 1;
                q.push(y); 
            }
        }
    }
    if(deep[t] != -1) return 1;
    return 0;
}

ll dfs(int x, ll v){
    ll used = 0, res = 0;
    if(x == t) return v;
    for(int i = head[x]; i; i = nxt[i]){
        int y = to[i];
        if(w[i] && deep[y] == deep[x]+1){
            res = dfs(y, min(v - used, w[i]));
            w[i] -= res;
            w[i ^ 1] += res;
            used += res;
            if(i != s && y != t){
            	matcha[i] = y;
			}
            if(used == v) return v;
        }
    }
    if(used == 0) deep[x] = -1;
    return used;
}

void dinic(){
    ll ans = 0;
    while(bfs()){
        ll res = 0;
        while(res = dfs(s, 0x7fffffff)){
            ans += res;
        }
    }
    printf("共能进行 %d 人次排班\n", ans);
    for(int i = 2 * (1 + m + n); i <= tot; i += 2){
    	if(w[i] == 0){
    		printf("第 %d 个人去第 %d 个时间段\n", from[i], to[i] - n);
    		table[to[i] - n][0]++;
    		table[to[i] - n][table[to[i] - n][0]] = from[i];
    	}
	}
	for(int i = 1;i <= m; i++){
		printf("第 %d 个时间段的人有：",i);
		for(int j = 1; j <= table[i][0]; j++){
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
}
 
int main(){
	printf("请分别输入，人数，时间数，边数\n");
	n = read(), m = read(), e = read(); 
    s = 0,t = n + m + n + 1;
    for(int i = 1; i <= n; i++){
        add(s, i, 1);
        add(i, s, 0);
    }
    printf("请输入每个时间段需要的人数（相等）\n");
    int d = read(); 
    for(int i = 1; i <= m; i++){
        add(i + n, t, d);
        add(t, i + n, 0);
    }
    printf("请输入第几个人在第几个时间段有空，共 %d 行\n",e);
    for(int i = 1; i <= e; i++){
        int x = read(), y = read();
        add(x, y + n, 1);
        add(y + n, x, 0);
    }
    dinic();
    return 0;
}

