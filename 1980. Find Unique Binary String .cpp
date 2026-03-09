class Solution {
    public:
        string findDifferentBinaryString(vector<string>& nums) {
            unordered_set<unsigned long> st;
            for(auto &num:nums){
                unsigned long decimal = bitset<32>(num).to_ulong();
                st.insert(decimal);
            }
            int n = nums.size();
            for(int num =0; num<=n;num++){
                if(st.find(num)==st.end()){
                     string res = bitset<32>(num).to_string();
                     res.erase(0, 32-n);
                     return res;
                }
            }
           
            return "";
        }
    };