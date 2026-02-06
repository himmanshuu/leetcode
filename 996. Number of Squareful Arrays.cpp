class Solution {
    public:
        int result = 0;
        int connections[12][12];
        unordered_map<int,int> memo;
        bool isPerfectSquare(int n) {
            if (n < 0) return false;
            int sqrtN = (int)sqrt(n);
            return sqrtN * sqrtN == n;
        }
    
        bool hasIsolatedNode(int mask, int n){
            int forced = 0;
            for(int i=0; i<n;i++){
                if(mask & (1<<i)) continue;
                int connect = 0; 
                 for(int j=0; j<n;j++){
                    if((mask & (1<<j)) || i==j) continue;
                    if(connections[i][j]) connect++;
                }
                if(connect == 0) return true;
                if(connect == 1) forced++;
                if(forced > 2) return true;       
            }
            return false;
        }
         // Find forced moves: nodes with degree 1 in remaining graph
        int findForcedNode(int mask, int n, int last){
            for(int i=0; i<n; i++){
                if(mask & (1<<i)) continue;  // Skip used
                
                int degree = 0;
                int connectsTo = -1;
                
                for(int j=0; j<n; j++){
                    if((mask & (1<<j)) || i==j) continue;
                    if(connections[i][j]){
                        degree++;
                        connectsTo = j;
                    }
                }
                
                // If this node has degree 1 and connects to 'last', it's forced
                if(degree == 1 && last != -1 && connectsTo == last){
                    return i;  // Must pick this node next!
                }
            }
            return -1;  // No forced node
        }
        // dp bitmask solution
        int helper(vector<int>&nums, int mask, int fullmask, int last){
            if(mask == fullmask){
                // result++;
                return 1;
            }
            int key = (mask << 4) | (last+1);
            if(memo.count(key)) return memo[key];
            if(last != -1 &&  hasIsolatedNode(mask^(1<<last), (int)nums.size())){
                return memo[key]=0;
            } 
            int forcedMoves = findForcedNode(mask, nums.size(), last);
            if(forcedMoves!=-1){
                return memo[key] = helper(nums, mask | (1<<forcedMoves), nums.size(), forcedMoves);
            }
            
            unordered_set<int> last_used;
            int count = 0;
            for(int i=0; i<nums.size();i++){
                if((mask & (1<<i)) || last_used.count(nums[i])) continue;
               
                if(last == -1 || connections[last][i]){
                    last_used.insert(nums[i]);
                   count += helper(nums, mask | (1<<i), fullmask,i);
                    // visited[i] = false;
                }
            }
            return memo[key] = count;
        }
        // backtrack solution
        void backtrack(vector<int>&nums, vector<bool>&visited, int last, int count){
            if(count == nums.size()){
                result++;
                return;
            }
            int last_used = -1;
            for(int i=0; i<nums.size();i++){
                if(visited[i] || last_used == nums[i]) continue;
               
                if(last == -1 || isPerfectSquare(nums[i]+nums[last])){
                    visited[i] = true;
                    last_used = nums[i];
                    backtrack(nums, visited, i, count+1);
                    visited[i] = false;
                }
            }
        }
        int numSquarefulPerms(vector<int>& nums) {
            // vector<bool> visited(nums.size(), false);
        
            int n = nums.size();
            for(int i=0; i<n;i++){
                for(int j=0;j<n;j++){
                    if(i != j && isPerfectSquare(nums[i] + nums[j])){
                        connections[i][j] = true;
                    }
                }
            }
            int fullmask = (1<<nums.size()) - 1;
            // return helper(nums, 0, fullmask, -1);
            // return result;
           // dp iterative solution;
           vector<vector<int>> dp(fullmask + 1, vector<int>(n,0));
           for(int i=0; i<n;i++){
            for(int j=0;j<n;j++){
                if(connections[i][j]){
                    dp[(1<<i) | (1<<j)][j] = 1;
                }
            }
           }
            for(int mask = 1; mask <= fullmask;mask++){
                unordered_set<int> last_used;
                for(int last =0; last<n;last++){
                    if(!(mask&(1<<last)) || last_used.count(nums[last])) continue;
                    for(int next=0; next<n;next++){
                        if(last ==next || (mask & (1<<next))) continue;
                        if(connections[last][next]){
                            last_used.insert(nums[last]);
                            dp[mask | (1<<next)][next] += dp[mask][last];
                        }
                    }
                }
            }
            unordered_set<int> used;
            for(int i=0;i<n;i++){
                if(!used.count(nums[i])){
                    used.insert(nums[i]);
                    result += dp[fullmask][i];
                }
            }
            return result;
        }
    };