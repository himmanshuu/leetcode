// M Workers N Bikes -> Each worker can be assigned to only one bike -> Assign bikes to workers such that the total distance is minimized
// One to One formulation -> where number of bikes > number of workers -> We need to use a mask to keep track of the bikes that have been assigned to the worker
class Solution {
    public:
        int mem[1<<11];
        int dfs(vector<vector<int>> &adj, int m,int n, int mask){
            if(mem[mask] != -1) return mem[mask];
            int assigned = __builtin_popcount(mask);
            if(assigned == m){
                return 0;
            }
            int ans = INT_MAX;
            for(int j=0; j<n;j++){
                if(mask &(1<<j)) continue;
                ans = min(ans, adj[assigned][j] + dfs(adj, m, n, mask | (1<<j)));
            }
            return mem[mask] = ans;
        }    
        int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
            int m = workers.size(); int n = bikes.size();
            vector<vector<int>> adj(m, vector<int>(n, 0));
            for(int i=0; i<m;i++){
                for(int j=0; j<n;j++){
                    adj[i][j] = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
    
                }
            }
            memset(mem, -1, sizeof(mem));
            return dfs(adj, m, n ,0);
            vector<int>dp(1<<n, INT_MAX);
            dp[0] = 0;
            int result = INT_MAX;
            for(int mask =0; mask < (1<<n);mask++){
                if(dp[mask] == INT_MAX) continue;
                int wIdx = __builtin_popcount(mask);
                if(wIdx >= m){
                    result = min(result, dp[mask]);
                    continue;
                } 
                for(int j=0; j<n;j++){
                    if(mask & (1<<j)) continue;
                    int new_mask = mask | (1<<j);
                    dp[new_mask] = min(dp[new_mask], dp[mask] + adj[wIdx][j]);
                }
            }
            return result;
        }
    };