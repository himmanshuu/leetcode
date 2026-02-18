class TreeAncestor {
    static constexpr int LOG = 17;
    static constexpr int MAXN = 50001;
    int p[MAXN][LOG]; 
public:
    TreeAncestor(int n, vector<int>& parent) {
        // this->p.resize(n, vector<int>(17, -1));
        memset(p, -1, sizeof(p));

        for(int k=0; k<n;k++){p[k][0] = parent[k];}
        for(int j=1; j<LOG;j++){
            for(int i=0; i<n;i++){
                if(p[i][j-1] != -1){
                    p[i][j] = p[p[i][j-1]][j-1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for(int j=0; j<LOG;j++){
            if((k>>j) & 1){
                node = p[node][j];
                if(node == -1) return -1;
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */