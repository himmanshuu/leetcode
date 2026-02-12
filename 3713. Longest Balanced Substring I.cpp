class Solution {
    public:
        vector<int>count;
        int longestBalanced(string s) {
            int n = s.size();
            int result = 1;
            count.resize(26,0);
            for(int i=0; i<n;i++){
                count[s[i]-'a'] = 1;
                for(int j=i+1;j<n;j++){
                    count[s[j]-'a'] = count[s[j]-'a'] + 1;
                    int curr = -1;
                    bool balanced = true;
                    for(int k=0; k<26;k++){
                        if(count[k] == 0) continue;
                        if(curr == -1){
                            curr = count[k];
                        }else{
                            if(curr != count[k]){
                                balanced = false;
                            }
                        }
                    }
                    if(balanced) result = max(result, j-i+1);
                }
                for(int k=0; k<26;k++) count[k] = 0;
            }
            return result;
        }
    };