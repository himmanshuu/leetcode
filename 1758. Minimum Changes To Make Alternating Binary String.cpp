class Solution {
public:
    int minOperations(string s) {
        int cnt1 = 0, cnt2=0;
        char seq1 = '1';
        char seq2 = '0';

        for(auto &c:s){
            if(c != seq1) cnt1++;
            if(c != seq2) cnt2++;
            seq1 = seq1 & 1 ? '0':'1';
            seq2 = seq2 & 1 ? '0':'1';
        }
        return min(cnt1, cnt2);
    }
};