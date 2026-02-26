class Solution {
    public:
        static constexpr long long INF = -1e15;
        long long memo[501][501];
        vector<int> nums1, nums2;
        int n,m;
        long long dfs(int i, int j){
            if(i == n || j == m){
                return memo[i][j] = INF;
            }
            if(memo[i][j] != LLONG_MIN) return memo[i][j];
            long long ans = INF;
            long long a = dfs(i+1, j+1);
            long long b = dfs(i,j+1);
            long long c = dfs(i+1, j);
            if(a != INF){
                ans = max({ans, a, a + nums1[i]*nums2[j],1LL*nums1[i]*nums2[j] });
            }else{
                ans = max(ans, 1LL*nums1[i]*nums2[j]);
            }
            if(b != INF){
                ans = max(ans, b);
            }
            if(c != INF){
                ans = max(ans, c);
            }
            return memo[i][j] = ans;
        }
        int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
            // this->nums1 = nums1;
            // this->nums2 = nums2;
            this->n = nums1.size();
            this->m = nums2.size();
            // fill(&memo[0][0], &memo[0][0] + 501*501, LLONG_MIN);
            // return dfs(0,0);
    
            vector<vector<long long>> dp(n+1, vector<long long>(m+1, INF));
    
            for(int i=n-1; i>=0; i--){
                for(int j=m-1; j>=0; j--){
                    long long take = 1LL * nums1[i] * nums2[j];
                    // long long extend = take + max(0LL, dp[i+1][j+1]);
                    dp[i][j] = max({
                        take,
                        take + dp[i+1][j+1],
                        dp[i+1][j],
                        dp[i][j+1]
                    });
                }
            }
    
            return dp[0][0];
        }
    };