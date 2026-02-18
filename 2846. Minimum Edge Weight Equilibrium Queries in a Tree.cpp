// Binary lifting + lca - similar to 3841 - https://leetcode.com/problems/palindromic-path-queries-in-a-tree/description/
class Solution {
    static constexpr int LOG = 15;
    static constexpr int MAXN = 1e4+1;
    int n;
    int parent[MAXN][LOG];
    int depth[MAXN];
    int prefixEdge[MAXN][27];
    vector<pair<int,int>> graph[MAXN];
public:
    void dfs(int node,int p, int d, vector<int>&count){
        parent[node][0] = p;
        depth[node] = d;
        if(p != -1){
            for(int i=1; i<27;i++) prefixEdge[node][i] = count[i];
        }
        for(auto &[neighbour, weight]: graph[node]){
            if(neighbour != p){
                count[weight]++;
                dfs(neighbour, node, d+1, count);
                count[weight]--;
            }
        }
    }

    void build_binary_lifting(){
        for(int j=1; j<LOG;j++){
            for(int node =0; node < n; node++){
                if(parent[node][j-1] != -1){
                    parent[node][j] = parent[parent[node][j-1]][j-1];
                }else{
                    parent[node][j] = -1;
                }
            }
        }
    }

    int getlca(int u, int v){
        if(depth[u] < depth[v]){
            swap(u,v);
        }

        int diff = depth[u] - depth[v];
        for(int j=0; j< LOG;j++){
            if((diff >> j) & 1){
                u = parent[u][j];
                
            }
        }   
        if(u == v){
            return u;
        } 

        for(int j=LOG-1; j>=0; j--){
            if(parent[u][j] != parent[v][j]){
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        return parent[u][0];
    }
    int getMinimumChanges(int node1[27], int node2[27], int lca[27]){
        int nonzero = 0;
        int max_freq = 0;
        int count = 0;
        for(int i=1; i<27;i++){
            count = node1[i] - lca[i] + node2[i] - lca[i];
            nonzero += count;
            max_freq = max(max_freq, count);
            count = 0;
        }
        return nonzero - max_freq;
    }
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        this->n = n;
        memset(parent, -1, sizeof(parent));
        memset(prefixEdge, 0, sizeof(prefixEdge));

        for(auto &e:edges){
            int u = e[0], v=e[1],w=e[2];
            graph[u].push_back({v,w});
            graph[v].push_back({u,w});
        }

        vector<int>count(27,0);
        dfs(0,-1,0, count);
        build_binary_lifting();
        vector<int> answer;
        for(auto &q: queries){
            int u = q[0], v=q[1];
            int lca = getlca(u,v);
            answer.push_back(getMinimumChanges(prefixEdge[u], prefixEdge[v], prefixEdge[lca]));
        }
        return answer;
    }
};