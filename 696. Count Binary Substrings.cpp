class Solution {
    public:
        int countBinarySubstrings(string s) {
            int n = s.size();
            int prev = 0;
            int curr = 1;
            int result = 0;
            for(int i=0; i<n-1;i++){
                if(s[i] == s[i+1]){
                    curr++;
                    continue;
                }
                result += min(prev, curr);
                prev = curr;
                curr = 1;
            }
            result += min(prev, curr);
            return result;
        }
    };