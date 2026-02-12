class Solution {
    public:
        long long has_two_numbers(int a, int b){
            return ((long long)a << 32) | (unsigned int)b;
    
        }
        struct PairHash {
            size_t operator()(const pair<int,int>& p) const {
                size_t h1 = hash<int>()(p.first);
                size_t h2 = hash<int>()(p.second);
                return h1 ^ (h2 << 1);   // combine hashes
            }
        };
        int longestBalanced(string s) {
            int n = s.size();
            vector<char> chars = {'a','b','c'};
            unordered_map<pair<int,int>,int, PairHash> mp;
            int result = 1;
            int count = 1;
            int first_a =-1;
            int first_b = -1; 
            int first_c = -1;
            // one char scan;
            for(int i = 0; i<n;i++){
                while(i < n-1 && s[i] == s[i+1]){
                    count++;i++;
                }
                if(first_a == -1 && s[i] == 'a') first_a = 1;
                if(first_b == -1 && s[i] == 'b') first_b = 1;
                if(first_c == -1 && s[i] == 'c') first_c = 1;
    
                result = max(result, count);
                count = 1; 
            }
            if((first_a == -1 && first_b == -1) || (first_b == -1 && first_c == -1) || (first_c == -1 && first_a == -1)) return result;
            // two char scan;
            for(int i=0; i<3;i++){
                char x = chars[i % 3]; char y = chars[(i+1) % 3];
                int diff = 0;
                vector<int> first(2*n+1, n+1);
                int offset = n;
                int start = -1;
                first[offset] = -1;
                for(int j=0; j< n;j++){
                    // if(s[j] != x && s[j] != y){ mp.clear(); count_x=0; count_y=0; mp[0] = j;}
                    if(s[j] == x) diff++;
                    else if(s[j] == y) diff--;
                    else{
                        diff = 0;
                       start = j;
                        first[offset] = j;
                        continue;
                    }
                    if(first[offset + diff] != n+1 && first[offset+diff] >= start ){
                        result = max(result, j - first[offset + diff]);
                    }else{
                         first[offset + diff] = j;
                    }
                }
    
            }
            // cout<<result<<endl;
            if(first_a*first_b*first_c == -1) return result;
            // three char scan;
            int a=0,b=0,c=0;
            mp[{0,0}] = -1;
            for(int i=0; i<n;i++){
                if(s[i] == 'a') a++;
                if(s[i] == 'b') b++;
                if(s[i] == 'c') c++;
    
                // long long hash = has_two_numbers(a-b, b-c);
                if(mp.find({a-b,b-c}) != mp.end()){
                    result = max(result, i-mp[{a-b,b-c}]);
                }else{
                    mp[{a-b,b-c}] = i;
                }
            }
            return result;
        }
    };