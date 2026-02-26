// My solution
class Solution {
public:
    int get(int i, int count){
        // int count = 10;
        if(i == 0) return 0;
        int ans = 1;
        while(i > 0){
            ans*=(count--);
            i--;
        }
        return ans;
    }
    int getUnseenCount(vector<bool>&seen, int limit){
        int val = 0;
        for(int i=0; i<limit;i++){
            if(!seen[i]) val++;
        }
        return val;
    }
    int numDupDigitsAtMostN(int n) {
        if(n < 10) return 0;
        int digits = floor(log10(n) + 1);
        string s = to_string(n);
        int non_repeated = 0;
        int add = 1;
        int count = 9;
        for(int i=1; i<digits;i++){
            if(i == 1){
                non_repeated += add;
                continue;
            }
            non_repeated += add*count;
            add *= count;count--;
        }
        non_repeated *= 9;
        vector<bool>seen(10, false);
        bool number_has_repeating_digits = false;
        int j = s.size();
        for(int i=0; i<s.size();i++){
            int val = s[i] - '0';
            if(i == 0){
                non_repeated += (val-1)*get(j-1-i, 9);
            }else if(i == s.size()-1){
                non_repeated += getUnseenCount(seen, val);
            }else{
                non_repeated += (getUnseenCount(seen, val))*get(j-1-i, 10-(i+1));
            }
            
            if(seen[val]){number_has_repeating_digits = true; break; }
            seen[val] = true;
        }
        return n - non_repeated + (number_has_repeating_digits ? 0 : -1);
    }
};
// Cleaner solution with chatgpt help
class Solution {
    public:
        int perm(int n, int r){
            int ans = 1;
            for(int i=0; i<r;i++){
                ans *= (n-i);
            }
            return ans;
        }
        int numDupDigitsAtMostN(int n) {
            if(n < 10) return 0;
            string s = to_string(n);
            int m = s.size();
            int non_repeated = 0;
            for(int i=1; i<m;i++){
                non_repeated += perm(9, i-1);
            }
            non_repeated *= 9;
            vector<bool>seen(10, false);
            bool number_has_repeating_digits = false;
            for(int i=0; i<s.size();i++){
                int digit = s[i] - '0';
                for(int d=(i==0 ? 1:0); d<digit;d++){
                    if(!seen[d]){
                        non_repeated += perm(9-i, m-i-1);
                    }
                }
                if(seen[digit]){return n - non_repeated; }
                seen[digit] = true;
            }
            return n - non_repeated -1;
        }
    };