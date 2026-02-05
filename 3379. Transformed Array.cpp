class Solution {
    public:
        static inline int positive_mod(int a, int n) {
        return ((a % n) + n) % n;
        }
        vector<int> constructTransformedArray(vector<int>& nums) {
            int n = nums.size();
            vector<int> result(n,0);
            for(int i=0; i<n;i++){
                result[i] = nums[positive_mod(i + nums[i], n)];
            }
            return result;    
        }
    };