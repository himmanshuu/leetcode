class Solution {
    public:
        string P = "11";
        string bits;
        int m;
        static const int MAX_STATE = 3;
        int next[MAX_STATE][2];
        int memo[32][MAX_STATE][2];
        vector<int>preCompute(){
            int n = P.size();
            vector<int> lps(n, 0);
            int len = 0;
            for(int i=1; i<n;i++){
                while(len > 0 && P[i] != P[len]){
                    len = lps[len - 1];
                }
                if(P[i] == P[len]) len++;
                lps[i] = len;
            }
            return lps;
        }
        void buildNextState(){
            vector<int> lps = preCompute();
            for(int state = 0; state < MAX_STATE; state++){
                for(int bit = 0; bit<=1; bit++){
                    if(state == MAX_STATE - 1){
                        next[state][bit] = state;
                        continue;
                    }
                    int curr = state;
                    while(curr > 0 && P[curr] != (bit + '0')){
                        curr = lps[curr-1];
                    }
                    if(P[curr] == bit + '0') curr++;
                    next[state][bit] = curr;
                }
            }
        }
        int dfs(int pos, int state, int tight){
            if(state == MAX_STATE - 1) return 0;
            if(pos == bits.size()) return 1;
            if(memo[pos][state][tight] != -1) return memo[pos][state][tight];
            int limit = tight ? bits[pos] - '0' : 1;
            int ans = 0;
            for(int bit = 0; bit<=limit; bit++){
                int nextState = next[state][bit];
                int nextTight = tight && (bit == limit);
                ans += dfs(pos + 1, nextState, nextTight);
            }
            return memo[pos][state][tight] = ans;
    
        }
        int findIntegers(int n) {
            // bitset<32>bn(n);
            // bits = bn.to_string();
            // bits.erase(0, bits.find_first_not_of('0'));
            // buildNextState();
            // memset(memo, -1, sizeof(memo));
            // return dfs(0, 0, 1);
            vector<int>dp(32, 0);
            dp[0] = 1;
            dp[1] = 2;
            for(int i=2; i<32;i++) dp[i] = dp[i-1] + dp[i-2];
            int result = 0;
            int prev_bit = -1;
            for(int i=31; i>=0;i--){
                if(n & (1<<i)){
                    result += dp[i]; // this is when bit i is flipped to 0.
                    if(prev_bit == 1){
                        return result; //pattern matched
                    }
                    prev_bit = 1;
                }else{
                    prev_bit = 0;
                }
            }
            return result + 1;
        }
    };