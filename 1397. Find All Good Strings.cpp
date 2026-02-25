class Solution {
    public:
        static const int MOD = 1e9 + 7;
        string P;
        int n;
        int m;
        vector<vector<int>> next;
        int memo[501][51][2];
        string s1, s2;
        vector<int>precompute(){
            // int n = P.size();
            vector<int> lps(m, 0);
            int len = 0;
            for(int i=1;i<m;i++){
                while(len > 0 && P[i] != P[len]) len = lps[len-1];
                if(P[i] == P[len]) len++;
                lps[i] = len;
            }
            return lps;
        }
        vector<vector<int>> buildNextState(){
            // int m = P.size();
            vector<vector<int>> next(m+1, vector<int>(26, 0));
            vector<int> lps = precompute();
            for(int state =0; state<=m;state++){
                for(int c=0;c<26;c++){
                    if(state == m){
                        next[state][c] = m;
                        continue;
                    }
                    int curr = state;
                    while(curr > 0 && P[curr] != 'a' + c) curr = lps[curr-1];
                    if(P[curr] == 'a' + c) curr++;
                    next[state][c] = curr;
                }
            }
            return next;
        }
        int dfs(int pos,int state, int tightLow, int tightHigh){
            if(state == m) return 0;
            if(pos == n) return 1;
            if(memo[pos][state][tightLow][tightHigh] != -1) return memo[pos][state][tightLow][tightHigh];
    
            int low = tightLow ? s1[pos] - 'a' : 0;
            int high = tightHigh ? s2[pos] - 'a' : 25;
            long long ans = 0;
            for(int c=low;c<=high;c++){
                int nextState = next[state][c];
                int nextTightLow = tightLow && (c == s1[pos] - 'a');
                int nextTightHigh = tightHigh && (c == s2[pos] - 'a');
    
                ans += dfs(pos + 1, nextState, nextTightLow, nextTightHigh);
                ans %= MOD;
            }
            return memo[pos][state][tightLow][tightHigh] = ans;
        }
        // dfs for prefix solution count[s2] - count[prev(s1)]; 
        int dfs(int pos,int state, int tight, string &s){
            if(state == m) return 0;
            if(pos == n) return 1;
            if(memo[pos][state][tight] != -1) return memo[pos][state][tight];
    
            int limit = tight ? s[pos] - 'a' : 25;
            long long ans = 0;
            for(int c=0;c<=limit;c++){
                int nextState = next[state][c];
                int nextTight = tight && (c == s[pos] - 'a');
    
                ans += dfs(pos + 1, nextState, nextTight,s);
                ans %= MOD;
            }
            return memo[pos][state][tight] = ans;
        }
        // find prev string;
        string getPrev(string s) {
    
            int n = s.size();
    
            for(int i = n - 1; i >= 0; i--) {
    
                if(s[i] > 'a') {
                    s[i]--;  // decrease this position
                    return s;
                }
    
                // if 'a', borrow
                s[i] = 'z';
            }
    
            // if we reach here, all were 'a'
            return "";  // means no previous string
        }
        int findGoodStrings(int n, string s1, string s2, string evil) {
            this->n = n; this->s1 = s1; this->s2= s2; this->P = evil; m = P.size();
            memset(memo, -1, sizeof(memo));
            next = buildNextState();
            string prev = getPrev(s1);
            int count = dfs(0,0,1,s2);
            if(prev == "") return count;
            memset(memo, -1, sizeof(memo));
            return (count - dfs(0,0,1,prev) + MOD) % MOD;
            // return dfs(0, 0, 1, 1);
        }
    };