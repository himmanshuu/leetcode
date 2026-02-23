class Solution {
    public:
        bool hasAllCodes(string s, int k) {
            int n = s.size();
            if(n < k) return false;
            unordered_set<int> st;
            int mask = 0;
            for(int i=0; i<n;i++){
                mask = (mask << 1) & ((1<<k) - 1) | (s[i] - '0');
                if(i >= k-1) st.insert(mask);
            } 
            return st.size() == (1<<k);
        }
    };

    class Solution {
        public:
            bool hasAllCodes(string s, int k) {
                int n = s.size();
                int m = (1<<k);
                unordered_set<unsigned int> st;
                unsigned int curr = 0;
                int shift = 32 - k;
                for(int i=0;i<n;i++){
                    unsigned int bit = s[i] == '0' ? 0 : 1;
                    if(i < k){
                        curr |=(bit<<(31-i));
                        if(i == k-1) st.insert(curr);
                    }else{
                        curr = curr << 1;
                        curr |= (bit << (shift));
                        st.insert(curr);
                    }            
                }
                return st.size() == (1<<k);
            }
        };
        // Rolling Hash Solution
        class Solution {
            public:
                static constexpr long long BASE = 291;
                static constexpr long long MOD = 1e9 + 7;   
                bool hasAllCodes(string s, int k) {
                    int n = s.size();
                    unordered_set<long long> st;
                    vector<long long> pwr(n+1), h(n+1);
                    pwr[0] = 1;
                    for(int i = 0; i < n; i++) {
                        pwr[i+1] = (pwr[i] * BASE) % MOD;
                        h[i+1] = (h[i] * BASE + s[i]) % MOD;
                    }
                    auto getHash = [&](int l, int r){
                        return (h[r+1] - h[l] * pwr[r-l+1] % MOD + MOD) % MOD;
                    };
                    for(int i=k;i<=n;i++){
                        st.insert(getHash(i-k, i-1));         
                    }
                    return st.size() == (1<<k);
                }
            };