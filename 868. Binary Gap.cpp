class Solution {
    public:
        int binaryGap(int n) {
            bitset<32> bn(n);
            int prev = 31 - __builtin_clz(n);
            int result = 0;
            for(int i=prev; i>=0;i--){
                if(bn[i]){
                    result = max(result, prev - i);
                    prev = i;
                }
            }
            return result;
        }
    };