class Solution {
    public:
        long long dp[201][201][2];
        int MOD = 1e9 + 7;
        int numberOfStableArrays(int zero, int one, int limit) {
            int n = zero + one;
            memset(dp, 0, sizeof(dp));
            for(int i=0; i<=min(zero, limit);i++){
                dp[i][0][0] = 1;
            }
            for(int j=0; j<=min(one, limit);j++){
                dp[0][j][1] = 1;
            }
    
            for(int i=1; i <= zero; i++){
                for(int j=1; j <= one; j++){
                    if(i <= limit){
                        dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD;
                    }else{
                        dp[i][j][0] = ((dp[i-1][j][0] + dp[i-1][j][1] ) % MOD - dp[i-limit-1][j][1] + MOD) % MOD;
                    }
    
                    if(j <= limit){
                        dp[i][j][1] = (dp[i][j-1][0] + dp[i][j-1][1]) % MOD;
                    }else{
                        dp[i][j][1] =((dp[i][j-1][0] + dp[i][j-1][1]) % MOD - dp[i][j-limit-1][0] + MOD) % MOD;
                    }
                }
            }
            return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
        }
    };