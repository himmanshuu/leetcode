// Two approaches -> 1. Normal Approach O(NMLog(NM)) and 2. Bucket Sort O(NM + MaxDistance)
class Solution {
    public:
        vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
            int n = workers.size();
            int m = bikes.size();
    
            vector<tuple<int,int, int>> distance;
            vector<pair<int,int>> distBucket[1999];
            int minDis = INT_MAX;
            for(int i=0; i<n;i++){
                for(int j=0;j<m;j++){
                    int dist = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                    distBucket[dist].push_back({i,j});
                    // distance.push_back({dist,i,j});
                    minDis = min(minDis, dist);
                }
            }
            // sort(distance.begin(), distance.end(), [](const tuple<int,int,int>&a, const tuple<int,int,int>&b){
            //    if(get<0>(a) == get<0>(b)){
            //     if(get<1>(a) == get<1>(b)){
            //         return get<2>(a) < get<2>(b);
            //     }
            //     return get<1>(a) < get<1>(b);
            //    } 
            //    return get<0>(a) < get<0>(b);
            // }); 
    
            vector<int> workers_assigned(n, -1);
            vector<int> bikes_used(m, false);
            int currDis = minDis;
            // vector<int> answers(n);
            int assigned_workers = 0;
            while(assigned_workers != n){
                for(auto &[i,j]: distBucket[currDis]){
                    if(workers_assigned[i] == -1 && !bikes_used[j]){
                        workers_assigned[i] = j;
                        bikes_used[j] = true;
                        assigned_workers++;
                    }
                }
                currDis++;
            }
            return workers_assigned;
            // for(auto &[d,i,j] : distance){
            //     if(workers_assigned[i] || bikes_used[j]) continue;
            //     answers[i] = j;
            //     workers_assigned[i] =true;
            //     bikes_used[j]=true;
            // }
            // return answers;
        }
    };