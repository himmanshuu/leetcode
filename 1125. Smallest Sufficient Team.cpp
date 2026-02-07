class Solution {
    public:
        vector<int> result;
        unordered_map<string,int> mp;
        // unordered_set<size_t> memo;
        unordered_map<int, vector<int>> memo;
        // set<pair<int,long long>> memo;
        // unordered_map<int,int>people_with_masks;
        unordered_set<int> all_masks;
        vector<pair<int,int>> people_with_masks;
    
        // bool memo[65635][60];
        size_t hash_two_numbers(int a, long long b) {
            return std::hash<int>{}(a) ^ (std::hash<long long>{}(b) << 1);
            // return ((a + b) * (a + b + 1)) / 2 + b;
            return (size_t)a ^ ((size_t)b << 1);
        };
        // size_t hash_value = ((int_val + long_val) * (int_val + long_val + 1)) / 2 + long_val;
    
        vector<int> dfs(int fullmask, int mask, int idx){
            // cout<<mask<<' '<<fullmask<<endl;
            if(fullmask == mask){
                // cout<<path.size()<<endl;
                // if(result.empty()) result = path;
                // if(result.size() > path.size()){
                //     result = path;
                // }
                return {};
            }
            if(idx == people_with_masks.size() ) return vector<int>(100);
            // long long key = 0;
            // for(int p=0; p<path.size();p++){
            //     key |= (1LL<<path[p]);
            // }
            int key = mask * 100 + idx;
            if(memo.count(key)) return memo[key];
            // if(memo.count(hash_two_numbers(mask,key))) return;
            // if(memo.count({mask,key})) return;
    
            // int idx = it->first;
            vector<int> take,skip;
            if((mask | people_with_masks[idx].second) > mask){      
                take = dfs( fullmask, mask | people_with_masks[idx].second, idx+1);
                take.push_back( people_with_masks[idx].first);
               
            }
            skip = dfs( fullmask, mask, idx+1);
            if(take.size() > 0 && take.size() < skip.size()) return memo[key] = take;
            return memo[key] = skip;
            // memo.insert(hash_two_numbers(mask,key));
            // memo.insert({mask, key});
        }
        vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
            // cout<<people.size()<<endl;
            int n = req_skills.size();
            int fullmask = (1<<req_skills.size()) - 1;
            for(int i=0; i<req_skills.size();i++){
                mp[req_skills[i]] = i;
            }
            for(int i=0; i<people.size();i++){
                int mask = 0;
                for(int j=0; j<people[i].size();j++){
                    mask |= (1<<mp[people[i][j]]);
                }
                if(mask > 0 && !all_masks.count(mask) ){
                    people_with_masks.push_back({i,mask});
                    all_masks.insert(mask);
                }
                
            }
            int m = people_with_masks.size();
            vector<bool> dominated(m, false);
            for(int i=0; i<m;i++){
                for(int j=i+1; j<m;j++){
                    int mask_i = people_with_masks[i].second;
                    int mask_j = people_with_masks[j].second;
                    if((mask_i & mask_j) == mask_i) dominated[i] = true;
                    else if((mask_i & mask_j) == mask_j) dominated[j] = true;
                }
            }
            vector<int> skillcount(n , 0);
            vector<int> skillowner(n, -1);
    
            for(int i=0;i<m;i++){
                if(dominated[i]) continue;
                for(int j=0; j<n;j++){
                    if((people_with_masks[i].second & (1<<mp[req_skills[j]]))){
                        skillcount[j]++;
                        if(skillcount[j] == 1){
                            skillowner[j] = i;
                        }else{
                            skillowner[j] = -1;
                        }
                    }
                }
            }
    
            int forced_mask = 0;
            vector<int> forced;
             for(int j=0; j<n;j++){
                if(skillowner[j] == -1) continue;
                int i = skillowner[j];
                if((forced_mask | people_with_masks[i].second) != forced_mask){
                     forced.push_back(people_with_masks[i].first);
                     forced_mask |= people_with_masks[i].second;
                }
               
                    
            }
            if(forced_mask == fullmask) return forced;
            int remaining = forced_mask ^ fullmask;
            for(int i=0; i<m;i++){
                if(dominated[i]) continue;
                if((people_with_masks[i].second & remaining) == remaining){
                    forced.push_back(people_with_masks[i].first);
                    return forced;
                }
            }
            vector<pair<int,int>> remaining_people;
            int j=0;
            for(int i=0; i<m;i++){
                if(dominated[i]) continue;
                if(j < forced.size() && forced[j] == people_with_masks[i].first){
                   j++; continue; 
                } 
                remaining_people.push_back(people_with_masks[i]);
            }
            // cout<<people_with_masks.size()<<' '<<remaining_people.size()<<endl;
            people_with_masks = remaining_people;
            vector<int> ans = dfs( fullmask, forced_mask, 0);
             forced.insert(forced.end(),ans.begin(),ans.end());
             return forced;
            // return result;
            vector<vector<int>>dp(fullmask+1);
            // dp[0] = {};
            dp[forced_mask] = forced;
    
            for(int mask = 0; mask <=fullmask;mask++){
                if(mask != forced_mask && dp[mask].empty()) continue;
                for(auto &pm: remaining_people){
                    if((mask | pm.second) <=mask) continue;
                    int new_mask = mask | pm.second;
                    if(dp[new_mask].empty() || dp[new_mask].size() > dp[mask].size() + 1){
                        dp[new_mask] = dp[mask];
                        dp[new_mask].push_back(pm.first);
                    }
                }
            }
            return dp[fullmask];
        }
    };