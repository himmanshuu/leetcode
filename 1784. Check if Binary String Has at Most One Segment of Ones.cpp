class Solution {
public:
    bool checkOnesSegment(string s) {
        int ones_segment = 0;
        int n = s.size();
        int i = 0;
        while(i < n){
            int cnt = 0;
            int j = i;
            while(j < n && s[j] == '1'){cnt++;j++;} 
            if(cnt > 0) ones_segment++;
            i = j +( j > i ? 0 : 1);
        }
        return ones_segment == 1;
    }
};