class Solution {
    public:
        const int INF = INT_MAX;
        string shortestSuperstring(vector<string>& words) {
            int n = words.size();
            int fullmask = (1<<n) - 1;
            int full = fullmask + 1;
            vector<vector<int>> dp(full, vector<int>(n,INF));
            vector<vector<int>>cost(n, vector<int>(n, 0));
            vector<vector<int>> overlap(n, vector<int>(n,0));
            vector<vector<int>> parent(full, vector<int>(n,-1));
            
            vector<int>path;
            string res;
    
            for(int i=0; i<n;i++){
                for(int j=0; j<n;j++){
                    if(i == j){
                        continue;
                    }
                    int max_overlap = 0;
                    for(int k=1; k<=min(words[i].size(), words[j].size()); k++){
                        if(words[i].substr(words[i].size() - k) == words[j].substr(0,k)){
                            max_overlap = k;
                        }
                    }
                    overlap[i][j] = max_overlap;
                    cost[i][j] = words[j].size() - max_overlap;
                }
            }
            for(int i=0; i<n;i++) dp[(1<<i)][i] = words[i].length();
            for(int mask = 1; mask < fullmask;mask++){
                for(int last = 0; last < n; last++){
                    if(!(mask & (1<<last))) continue;
                    if(dp[mask][last] == INF) continue;
                    for(int next = 0; next < n; next++){
                        if(mask & (1<<next)) continue;
                        int new_mask = mask | (1<<next);
                        int new_cost = dp[mask][last] + cost[last][next];
                        if(new_cost < dp[new_mask][next]){
                            dp[new_mask][next] = new_cost;
                            parent[new_mask][next] = last;
                        }
                    }
                }
            }
            int min_cost = INF;
            int curr = -1;
            for(int i=0; i<n;i++){
                if(dp[fullmask][i] < min_cost){
                    min_cost = dp[fullmask][i];
                    curr = i;
                }
            }
            int mask = fullmask;
            while(curr != -1){
                path.push_back(curr);
                int prev = parent[mask][curr];
                 if(prev != -1) {
                    mask ^= (1 << curr);  // Remove curr from mask
                }
                curr = prev;
            }
            reverse(path.begin(), path.end());
            res = words[path[0]];
            for(int i=1; i<path.size();i++){
                int prev_word = path[i-1];
                int curr_word = path[i];
                res += words[curr_word].substr(overlap[prev_word][curr_word]);
            }
            return res;
        }
    };