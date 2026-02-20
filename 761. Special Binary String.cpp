class Solution {
    public:
        string makeLargestSpecial(string s) {
            int n = s.size();
            if(s.empty()) return "";
            int sum = 0;
            int start = 0;
            vector<string> pieces;
            for(int i=0; i<n;i++){
                if(s[i] == '1') sum += 1;
                else sum -= 1;
                if(sum == 0){
                    string inside = s.substr(start + 1, (i-1) - (start + 1) + 1);
                    string recursed = makeLargestSpecial(inside);
                    pieces.push_back("1" + recursed + "0");
                    start = i + 1;
                }
            }
    
            sort(pieces.begin(), pieces.end(), greater<string>());
            string result;
            for(auto &p:pieces){
                result += p;
            }
            return result;
        }
    };