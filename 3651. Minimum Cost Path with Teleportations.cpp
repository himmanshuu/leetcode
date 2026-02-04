// Time complexity: O(m*n*k)
// Space complexity: O(m*n*k)
class Solution {
public:
    static const int N = 1e4 + 2;
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int max_val = INT_MIN;
        vector<int> suffx_min(N+1, INT_MAX);
        vector<vector<vector<int>>>dp(m, vector<vector<int>>(n, vector<int>(k+1, INT_MAX)));
        dp[0][0][0] = 0;
        // Base case with normal moves
        for(int i=0; i<m;i++){
            for(int j=0; j<n;j++){
                if(i > 0){
                    dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][0] + grid[i][j]);
                }
                if(j > 0){
                    dp[i][j][0] = min(dp[i][j][0], dp[i][j-1][0] + grid[i][j]);
                }
                suffx_min[grid[i][j]] = min(suffx_min[grid[i][j]], dp[i][j][0]);
                max_val = max(max_val, grid[i][j]);
            }
        }
        int curr_min = INT_MAX;
        // Suffix min array
        for(int i=max_val;i>=0;i--){
            suffx_min[i] = min(suffx_min[i], curr_min);
            curr_min = min(suffx_min[i], curr_min);
        }
        // Now with teleportations
        for(int t=1; t<=k;t++){
            vector<int> curr_suffx_min(max_val+1, INT_MAX);
            for(int i=0; i<m;i++){
                for(int j=0;j<n;j++){
                    // check cost with teleportations
                    dp[i][j][t] = min(dp[i][j][t-1], suffx_min[grid[i][j]]);
                    // Normal moves
                    if(i > 0){
                        dp[i][j][t] = min(dp[i][j][t], dp[i-1][j][t] + grid[i][j]);
                    }
                        if(j > 0){
                            dp[i][j][t] = min(dp[i][j][t], dp[i][j-1][t] + grid[i][j]);
                        }
                    
                    curr_suffx_min[grid[i][j]] = min(curr_suffx_min[grid[i][j]], dp[i][j][t]);
                }
            }
            curr_min = INT_MAX;
            for(int tx = max_val; tx>=0; tx--){
                curr_suffx_min[tx] = min(curr_suffx_min[tx], curr_min);
                curr_min = min(curr_min, curr_suffx_min[tx]);
                suffx_min[tx] = curr_min;
            }            
        }
        return dp[m-1][n-1][k];
    }
};

// Time complexity: O(m*n*k)
// Space complexity: O(m*n*k)
// 2d array approach
const int M=1e4+1, NN=6400;
const int INF=1e9+7;

//x_pos[x] consists in 1D indices of (i, j)  with grid value x
vector<int> xpos[M]; 

// dp[t][idx] with <= t teleports & idx(i,j)
unsigned dp[11][NN]; 

// Suffix Min
unsigned suffx_min[M]; 
class Solution {
public:
    static const int N = 1e4 + 1;
    const int INF = 1e9+7;
    static inline int idx(int i, int j, int c){ return i*c+j;}
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int max_val = INT_MIN;
        int N = m*n;

        //Initialize DP table
        for(int t=0; t<=k; t++)
            fill(dp[t], dp[t]+N, INF);        
        dp[0][0] = 0;
        // Base case with normal moves
        for(int i=0; i<m;i++){
            for(int j=0; j<n;j++){
                int pos = idx(i, j, n);
                if(i > 0){
                    dp[0][pos] = min(dp[0][pos], dp[0][idx(i-1,j,n)] + grid[i][j]);
                }
                if(j > 0){
                    dp[0][pos] = min(dp[0][pos], dp[0][idx(i,j-1,n)] + grid[i][j]);
                }
                // suffx_min[grid[i][j]] = min(suffx_min[grid[i][j]], dp[i][j][0]);
                xpos[grid[i][j]].push_back(pos);
                max_val = max(max_val, grid[i][j]);
            }
        }
        
        // Now with teleportations
        for(int t=1; t<=k;t++){
            unsigned curr_min = INF;
            // Suffix min array
            for(int x=max_val;x>=0;x--){
                for(auto idx: xpos[x]){
                    curr_min = min(dp[t-1][idx], curr_min);
                }    
                suffx_min[x] = curr_min;
            }
            for(int i=0; i<m;i++){
                for(int j=0;j<n;j++){
                    // check cost with teleportations
                    int pos = idx(i,j,n);
                    dp[t][pos]=min(dp[t-1][pos], suffx_min[grid[i][j]]);

                    if(i > 0){
                        dp[t][pos] = min(dp[t][pos], dp[t][idx(i-1,j,n)] + grid[i][j]);
                    }
                        if(j > 0){
                            dp[t][pos] = min(dp[t][pos], dp[t][idx(i,j-1,n)] + grid[i][j]);
                        }
                    
                }
            }          
        }
          // Reset for the next testcase
        for (int x=1; x<=max_val; x++)
            xpos[x].clear();
        return dp[k][idx(m-1,n-1,n)];
    }
};