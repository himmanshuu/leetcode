class Solution {
    public:
        string reverseWords(string s) {
               reverse(s.begin(),s.end());
                stringstream ss(s);
                char del = ' ';
                string t;
                string result;
                while(getline(ss, t, del)){
                    if(t.empty()) continue;
                    reverse(t.begin(), t.end());
                    if(result.empty()){
                        result += t;
                    }else{
                        result += " " + t;
                    }
    
                }
                return result;
            reverse(s.begin(), s.end());
            int n = s.size();
            int write = 0;
            int read = 0;
            while(read < n){
                if(s[read] == ' '){
                    read++;
                    continue;
                }
                if(read >= n) break;
                if(write > 0) s[write++] = ' ';
                int start = write;
                while(read < n && s[read] != ' '){
                    s[write++] = s[read++];
                }
                reverse(s.begin() + start, s.begin() + write);
            }
            s.resize(write);
            return s;
        }
    };