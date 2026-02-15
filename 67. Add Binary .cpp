class Solution {
    public:
        string addBinary(string a, string b) {
            if(b.size() > a.size()) return addBinary(b,a);
            string res(a.size() + 1,'1');
            int i = a.size() - 1;
            int k = res.size() - 1;
            int carry = 0;
            for(int j=b.size()-1; j>=0;j--,i--){
                int x = a[i] - '0'; int y = b[j] - '0';
                res[k--] =  (x^y^carry) + '0';
                carry = (x&y) | ((x^y) & carry);        
            }
            for(;i>=0;i--){
                int x = a[i] - '0';
                res[k--] = (x^carry) + '0';
                carry = x&carry;
            }
            if(carry & 1) return res;
            return res.substr(1);
        }
    };