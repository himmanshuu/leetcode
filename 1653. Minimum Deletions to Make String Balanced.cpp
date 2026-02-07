struct last{
    int idx;
    int val;
};
class Solution {
public:
    int minimumDeletions(string s) {
        last a, b;
        a.idx = s[0] == 'a' ? 0: -1; a.val = 0;
        b.idx = s[0] == 'b' ? 0: -1; b.val = 0;

        for(int i=1; i<s.size();i++){
            if(s[i] == s[i-1]){
                a.idx += s[i] == 'a' ? 1:0;
                b.idx += s[i] == 'b' ? 1:0;
            }
            else if(s[i] == 'a'){
                a.val += (i - a.idx - 1);
                a.idx = i;
            }else{
                b.val = min(b.val + (i-b.idx-1), a.val + (i-a.idx-1));
                b.idx = i;
            }
        }
        return min(a.val + s.size() - a.idx - 1, b.val + s.size() - b.idx - 1);
    }
};