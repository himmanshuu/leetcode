class Solution {
    public:
        int numSteps(string s) {
            int consecutive = 0;
            int steps = 0;
            int i = s.size() - 1;
            for(;s[i]!='1';i--) steps++; // find first one;
            for(;i>=0;i--){
                if(s[i] == '1') consecutive++; // keep track of current cluster of ones
                else{
                    steps += consecutive + 1; // in case of zero bit, to move it to right most will take consecutive + 1 steps;
                    consecutive = 1; // reset consecutive and now there is only one 1 bit.
                }
            }
            return consecutive > 1 ? steps + consecutive + 1: steps;
        }
    };

    class Solution {
        public:
            int numSteps(string s) {
                int carry = 0;
                int steps = 0;
        
                for(int i=s.size()-1;i>0;i--){
                    int bit = s[i] & 1;
                    steps += (bit^carry) + 1;
                    carry |= bit;
                }
                return steps + carry;
            }
        };