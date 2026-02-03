// Solution with rolling hash - flyod Warshal
class Solution {
public:
    static const int MOD = 1e9 + 7;
    static const int BASE = 241;
    long long hashString(string &s ){
        long long h = 0;
        for(auto &c:s){
            h = (h*BASE + c) % MOD;
        }
        return h;
    }
    void flyoddMarshal(unordered_map<long long,int> &mp,vector<vector<int>> &g, vector<string>& original, vector<string>& changed, vector<int>& cost ){
        for(int i=0; i<original.size();i++){
            long long ho = hashString(original[i]);
            long long hc = hashString(changed[i]);
            int x = mp[ho]; int y = mp[hc];
            g[x][y] = min(g[x][y], cost[i]);    
        }
        for(int i=0; i<g.size();i++) g[i][i] = 0;
        for(int k=0; k<g.size();k++){
            for(int i=0; i<g.size();i++){
                for(int j=0; j<g.size();j++){
                    if(g[i][k] == INT_MAX || g[k][j] == INT_MAX) continue;
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        int n = source.size();
        vector<long long> hS(n+1), hT(n+1), pwr(n+1);
        pwr[0] = 1; 
        for(int i=0; i<n;i++){
            pwr[i+1] = (pwr[i]*BASE) % MOD;
            hS[i+1] = (hS[i]*BASE + source[i]) % MOD;
            hT[i+1] = (hT[i]*BASE + target[i]) % MOD;
        }
        auto getHash = [&](vector<long long> &h,int l, int r){
            return (h[r+1] - h[l]*pwr[r-l+1] % MOD + MOD) % MOD;
        };
        vector<int> len;
        int node_index = -1;
        unordered_map<long long, int> mp;
        for(int i=0; i<original.size();i++){
            long long ho = hashString(original[i]);
            long long hc = hashString(changed[i]);

            if(!mp.count(ho)) mp[ho] = ++node_index;
            if(!mp.count(hc)) mp[hc] = ++node_index;
            len.push_back(original[i].size());
        }
        sort(len.begin(), len.end());
        len.erase(unique(len.begin(), len.end()), len.end());
        vector<vector<int>> g(node_index + 1, vector<int>(node_index+1, INT_MAX));
        flyoddMarshal(mp, g, original, changed,cost);
        vector<long long>dp(n, LLONG_MAX);
        if(source[0] == target[0]) dp[0] = 0;
        for(int i=0; i<n;i++){
            if(i > 0 && source[i] == target[i] && dp[i-1] != LLONG_MAX){
                dp[i] = min(dp[i], dp[i-1]);
            }
            for(auto &l:len){
                int j = i - l;
                if(j < -1) break;
                if(j >=0 && dp[j] == LLONG_MAX) continue;
                long long sub_src = getHash(hS, j+1, i);
                long long sub_tgt = getHash(hT, j+1, i);

                if(mp.count(sub_src) && mp.count(sub_tgt)){
                    int x = mp[sub_src]; int y = mp[sub_tgt];
                    if(g[x][y] != INT_MAX){
                        if(j == -1){
                        dp[i] = min(dp[i], 1ll*g[x][y]);
                        }else{
                            dp[i] = min(dp[i], dp[j] + g[x][y]);
                        }
                    }
                    
                }
            }
        }
        return dp[n-1] == LLONG_MAX ? -1 : dp[n-1];
    }
};

// Without rolling hash simply pruning
class Solution {
    public:
        void flyodMarshal(vector<vector<int>> &g, unordered_map<string,int> &mp,vector<string>& original, vector<string>& changed, vector<int>& cost){
            for(int i=0; i<original.size();i++){
                int x = mp[original[i]];
                int y = mp[changed[i]];
                g[x][y] = min(g[x][y], cost[i]);
            }
            for(int i=0; i<g.size();i++) g[i][i] = 0;
             // Floyd-Warshall: k must be the outermost loop
            for(int k=0; k<g.size(); k++){           // Changed: k outside
                for(int i=0; i<g.size(); i++){       // Changed: i middle
                    for(int j=0; j<g.size(); j++){   // Changed: j inside
                        if(g[i][k] == INT_MAX || g[k][j] == INT_MAX) continue;
                        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                    }
                }
            }
        }
        long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
            unordered_map<string,int> mp;
            map<int, vector<int>> indices_by_len;
            int node_index = -1;
            int max_len = 0;
            for(int i = 0; i < original.size();i++){
                if(mp.find(original[i]) == mp.end()){
                    node_index++;
                    mp[original[i]] = node_index;
                } 
                if(mp.find(changed[i]) == mp.end()){
                    node_index++;
                    mp[changed[i]] = node_index;
                }
                indices_by_len[original[i].size()].push_back(i);
                max_len = max({max_len, (int) original[i].size()});
            }
            vector<vector<int>> g(node_index+1, vector<int>(node_index+1, INT_MAX));
            flyodMarshal(g,mp,original, changed, cost);
            vector<long long> dp(source.size(),LLONG_MAX);
            if(source[0] == target[0]) dp[0] = 0;
            for(int i=0; i<source.size();i++){
                if(i>0 && source[i] == target[i] && dp[i-1] != LLONG_MAX){
                    dp[i] = min(dp[i],dp[i-1]);
                }
              
                for(auto &[len, rules]: indices_by_len){
                    int j = i - len;
                    if(j < -1) break;
                    if(j >= 0 && dp[j] == LLONG_MAX) continue;
                    string source_sub = source.substr(j+1,len);
                        string target_sub = target.substr(j+1,len);
                        if(mp.count(source_sub) && mp.count(target_sub)){
                        int x = mp[source_sub]; int y = mp[target_sub];
                      
                            if(g[x][y] != INT_MAX){
    
                                if(j == -1){
                                    dp[i] = min(dp[i], 1ll*g[x][y]);
                                }else{
                                    dp[i] = min(dp[i], dp[j] + g[x][y]);
                                }
                            }
                        
                        }
    
                }
            }
            return dp[(int)source.size() - 1] == LLONG_MAX ? -1 : dp[(int)source.size() - 1];
        }
    };