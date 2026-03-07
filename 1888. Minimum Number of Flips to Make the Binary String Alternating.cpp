class Solution {
    public:
        int minFlips(string s) {
            int result = INT_MAX;
            int ops[2] = {0,0};
            int n = s.size();
    
            for(int i=0; i<n;i++){
                ops[(s[i] ^ i) & 1]++;
            }
            result = min(ops[0],ops[1]);
            for(int i=0;i<n;i++){
                ops[(s[i] ^ i) & 1]--;
                ops[(s[i]^(n+i)) & 1]++;
                result = min({result, ops[0],ops[1]});
            }
            return result;
        }
    };

    class Solution {
        public:
            int minFlips(string s) {
                string ss = s+s;
                int parity1 = 1;
                int parity2 = 0;
                int cnt1 = 0, cnt2=0;
                int result = INT_MAX;
                int k = 0, j = s.size() - 1;
                for(int i=0; i<s.size();i++){
                    if((ss[i] & 1) != (parity1^(i&1))) cnt1++;
                    if((ss[i] & 1) != (parity2^(i&1))) cnt2++;
                }
                // cout<<cnt1<<' '<<cnt2<<endl;
                result = min(cnt1, cnt2);
                for(int i=s.size(); i<ss.size();i++,k++){     
                    if((ss[k] & 1) != (parity1^(k&1))) cnt1--;
                    if((ss[k] & 1) != (parity2^(k&1))) cnt2--;
                    if((ss[i] & 1) != (parity1^(i&1))) cnt1++;
                    if((ss[i] & 1) != (parity2^(i&1))) cnt2++;
                    result = min({result, cnt1, cnt2});
                }        
                return result;
            }
        };  