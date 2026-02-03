class Solution {
    public:
        bool isTrionic(vector<int>& nums) {
           bool foundOnce = false, decreasing = false;
           int i = 1;
           for(; i<nums.size();i++){
               if(nums[i] - nums[i-1] > 0){
                if(decreasing) foundOnce = true;
                continue;
               }
               if(i>1 && nums[i] - nums[i-1] < 0){
                    if(foundOnce) return false;
                    decreasing = true;
                    continue;
               }  
               break;
           }
           return i == (int)nums.size() && decreasing && foundOnce; 
        }
    };