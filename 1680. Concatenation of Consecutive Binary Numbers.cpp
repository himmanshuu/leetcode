class Solution {
    public:
        static constexpr int MOD = 1e9 + 7;
        int concatenatedBinary(int n) {
            long long prev = 0;
            int curr = 1;
            int result = 0;
            int bits = 0;
            while(curr <= n){
                // int bits = 32 - __builtin_clz(curr);
                prev = ((prev<<bit_width((unsigned)curr)) | curr ) % MOD; 
                curr++;
            }
            return prev;
        }
    };

    class Solution {
        public:
            static constexpr int MOD = 1e9 + 7;
            int concatenatedBinary(int n) {
                long long prev = 0;
                int curr = 1;
                int result = 0;
                int bits = 0;
                while(curr <= n){
                    // int bits = 32 - __builtin_clz(curr);
                    if((curr&(curr-1)) == 0) bits++;
                    prev = ((prev<<bits) % MOD + curr ) % MOD; 
                    curr++;
                }
                return prev;
            }
        };