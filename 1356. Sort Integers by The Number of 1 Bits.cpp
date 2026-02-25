class Solution {
    public:
        int brianKernighan(int n){
            int count = 0;
            while(n > 0){
                n &= n-1;
                count++;
            }
            return count;
        }
        vector<int> sortByBits(vector<int>& arr) {
            vector<int> buckets[32];
            for(auto &a:arr){
                buckets[brianKernighan(a)].push_back(a);
            }
    
            vector<int> ans;
            for(int i=0; i<32;i++){
                sort(buckets[i].begin(), buckets[i].end());
                for(auto &b: buckets[i]) ans.push_back(b);
            }
            return ans;
        }
    };