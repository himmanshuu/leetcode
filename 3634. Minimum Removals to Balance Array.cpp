class Solution {
    public:
        int minRemoval(vector<int>& nums, int k) {
            int result = INT_MAX;
            int n = nums.size();
            sort(nums.begin(), nums.end());
            // for(int i=0; i<n;i++){
            //     int ub = upper_bound(nums.begin()+i, nums.end(), 1LL*k*nums[i])-nums.begin();
            //     result = min(result, i+n-ub);
            // }
            int start = 0;
            int end = 1;
            int pair = 1;
            while(end < n){
                if(start == end){
                    end++;
                    pair = 1;
                    continue;
                }
                if(1LL*k*nums[start] >= nums[end]){
                    pair++;
                    end++;
                    result = min(result, n-pair);
                }else{
                    start++;
                    pair--;
                }
                
            }
            return min(result, n-pair);
        }
    };