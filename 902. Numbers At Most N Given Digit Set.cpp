class Solution {
    public:
        int binarySearch(vector<string>& digits,int num){
            int start = 0; int end = digits.size();
            while(start < end){
                int mid = (start + end) >> 1;
                int val = digits[mid][0] - '0';
                if(val >= num) end = mid;
                else start = mid + 1;
            }
            return start;
        }
        int atMostNGivenDigitSet(vector<string>& digits, int n) {
            int len = digits.size();
            string num = to_string(n);
            int digits_in_n = num.size();
            vector<int> pwr;
            int ans = 0;
            int curr = 1;
            pwr.push_back(1);
            for(int i=1; i<digits_in_n;i++){
                curr *= len;
                ans += curr;
                pwr.push_back(curr);
            }
            bool allDigitsFound = true;
            for(int i=0; i<digits_in_n;i++){
                // int lb = binarySearch(digits, num[i] - '0');
                int lb = lower_bound( digits.begin(),digits.end(),string(1, num[i])) - digits.begin();
                ans += (lb)*pwr[digits_in_n - i-1];
                if(lb == digits.size() || digits[lb][0] != num[i] ) return ans;
            }
            return allDigitsFound ? ans + 1 : ans;
        }
    };