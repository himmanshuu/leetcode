class Solution {
    public:
        int helper(vector<int>&student, vector<int>&mentor){
            int score = 0;
            for(int i=0; i<student.size();i++){
                if(student[i] == mentor[i]) score += 1;
            }
            return score;
        }
        int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
            int m = students.size(); int n = students[0].size();
            vector<vector<int>> compt(m, vector<int>(m,0));
    
            for(int i=0; i<m;i++){
                for(int j=0; j<m;j++){
                    compt[i][j] = helper(students[i], mentors[j]);
                }
            }
    
            // vector<vector<int>>dp(m+1, vector<int>(1<<m, INT_MIN));
            vector<int>dp(1<<m, INT_MIN);
            dp[0] = 0;
            // for(int i=0; i<m;i++){
                for(int mask = 0; mask < (1<<m); mask++){
                    if(dp[mask] == INT_MIN) continue;
                    int studentIdx = __builtin_popcount(mask);
                    if(studentIdx >= m) continue;
                    for(int j=0; j<m;j++){
                        if((mask & (1<<j))) continue;
                        int new_mask = mask | (1<<j);
                        dp[new_mask] = max(dp[new_mask], dp[mask] + compt[studentIdx][j]);
                    }
                }
            // }
            return dp[(1<<m)-1];
        }
    };