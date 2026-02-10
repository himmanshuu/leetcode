class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        unordered_map<int,int> even, odd;
        int result = 0;
        for(int i=0; i<nums.size();i++){
            even.clear(); odd.clear();
            if(nums[i] % 2){
                odd[nums[i]] +=1;
            }else{
                even[nums[i]] +=1;
            }
            for(int j = i+1; j<nums.size();j++){
                if(nums[j] % 2) odd[nums[j]]++;
                else even[nums[j]]++;
                if(odd.size() == even.size()) result = max(result, j-i+1);
            }

            
        }
        return result;
    }
};