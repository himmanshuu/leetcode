// Time complexity: O(n)
// Space complexity: O(n)
class Solution {
    public:
        using ll = long long;
        long long maxSumTrionic(vector<int>& nums) {
            int n = nums.size();
            vector<long long> prefix(n,0);
            prefix[0] = nums[0];
            for(int i = 1; i<n;i++){
                prefix [i] = prefix[i-1] + nums[i];
            } 
            int l = -1, r=-1, p=-1, q=-1;
            long long ans = LLONG_MIN;
            long long prev_edge_min = LLONG_MAX;
            long long curr_edge_min = LLONG_MAX;
            for(int i=0; i<n-1;i++){
                // reset if equal numbers;
                if(nums[i] == nums[i+1]){
                    l=-1;r=-1;p=-1;q=-1;prev_edge_min = LLONG_MAX;curr_edge_min = LLONG_MAX;
                }else{
                    
                    if(nums[i+1] > nums[i]){            
                        if(l == -1){
                            // starting of first edge
                            l = i;
                            prev_edge_min = i==0 ? 0 : prefix[i-1];
                        }
                        else if(p == -1){
                            // continue on first edge
                           prev_edge_min = min(prefix[i-1], prev_edge_min);
                        }else{
                            // third edge work
                            if(q == -1) q = i;
                            r = i+1;
                            curr_edge_min = min(curr_edge_min, prefix[r-2]);
                            ans = max(ans, prefix[r] - prev_edge_min);
                        }
                    }else{
                        if(l == -1) continue;
                        if(p == -1){
                            // starting of second edge 
                            p = i;
                        }else{
                            if(q != -1){
                                // recalibration of third edge as first edge
                                l = q;
                                p = i;
                                q=-1;
                                r=-1;
                                // update the edge min of the previous increasing to current increasing
                                prev_edge_min = curr_edge_min;
                                curr_edge_min = LLONG_MAX;
                            }
                            
                        }
                    }
                }
            }
            return ans;
        }
    };

    // Time complexity: O(n)
    // Space complexity: O(1)
    class Solution {
        public:
            using ll = long long;
            long long maxSumTrionic(vector<int>& nums) {
                int n = nums.size();
                int l =0, r=0, p=0,q=0;
                ll ans = LLONG_MIN;
        
                for(int i=0; i<n-1;i++){
                    ll sum = 0;
                    while(i < n-1 && nums[i] >= nums[i+1]){
                        i++;
                    }
                    while(i < n - 1 && nums[i] < nums[i+1]){
                        sum+= (nums[i] > 0) ? nums[i]:0;
                        i++;
                    }
                    p = i;
                    if(p == n-1 || nums[p] == nums[p+1]){
                        i = p;
                        continue;
                    } 
                    sum +=(nums[p-1] <0)?nums[p-1]:0; 
                    // sum += nums[p];
                    while(i < n-1 && nums[i] > nums[i+1]){
                        sum+= nums[i];i++;
                    }
                    q=i;
                    if(q == n-1 || nums[q] == nums[q+1]){
                        i = q;
                        continue;
                    } 
                    sum+=nums[q];
                    ll incr = 0;
                    ll max_incre = LLONG_MIN;
                    while(i < n-1 && nums[i] < nums[i+1]){
                        incr += nums[i+1];
                        max_incre = max(max_incre, incr);
                        i++;
                    }
                    ans = max(ans, sum + max_incre);
                    i = q-1;
                }
                return ans;
            }
        };

// Finite machine approach 
// Reference: https://leetcode.com/problems/trionic-array-ii/solutions/7550439/o1-space-solution-simplified-to-20-lines-c0eu/
class Solution {
    public:
        long long maxSumTrionic(const vector<int>& nums) {
            const long long INF = -1e17;
            long long result = INF, a = INF, b = INF, c = INF;
            long long prev = nums[0];
            for (size_t i = 1; i < nums.size(); i++) {
                long long curr = nums[i];
                auto na = INF, nb = INF, nc = INF;
                if (curr > prev) { // increasing, update first and third state
                    na = max(a, prev) + curr;
                    nc = max(b, c) + curr;
                } else if (curr < prev) { // decreasing, update second state
                    nb = max(a, b) + curr;
                }
                a = na, b = nb, c = nc;
                result = max(result, c);
                prev = curr;
            }
            return result;
        }
    };