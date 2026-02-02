02/02/2026 - POTD
class Solution {
    public:
        long long minimumCost(vector<int>& nums, int k, int dist) {
            int n = nums.size();
            multiset<int> selected;
            multiset<int> candidates;
            int left = 1;
            int right = 1 + dist;
            long long sum = LLONG_MAX;
            long long curr = 0;
            while(left <= right){
                // curr += nums[left];
                candidates.insert(nums[left]);
                left++;
            }
            while(selected.size() < k-1){
                auto it = candidates.begin();
                selected.insert(*it);
                curr += *it;
                candidates.erase(it);
                // cout<<selected.size()<<endl;
            }
            sum = min(sum, curr);
            left = 1;
            right = 2 + dist;
            while(right < n){
                auto it_remove = selected.find(nums[left]);
                // left is not in selected
                if(it_remove == selected.end()){
                    // remove from the candidates
                    candidates.erase(candidates.find(nums[left]));
                    int last_selected = *prev(selected.end());
                    // right can be inserted into selected
                    if(nums[right] < last_selected){
                        curr -= last_selected;
                        curr += nums[right];
                        // remove prev largest and insert in into canidates;
                        selected.erase(prev(selected.end()));
                        candidates.insert(last_selected);
                        selected.insert(nums[right]);
    
                    }else{
                        candidates.insert(nums[right]);
                    }
                }else{
                    // remove left from the selected
                    curr -= nums[left];
                    selected.erase(it_remove);
                    candidates.insert(nums[right]);
                    // move one elements into selected;
                     curr += *candidates.begin();
                     selected.insert(*candidates.begin());
                     candidates.erase(candidates.begin());
                    
                }
                sum = min(sum, curr);
                left++; right++;
            }
            return sum + nums[0];
        }
    };