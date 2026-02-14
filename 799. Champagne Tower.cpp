class Solution {
    public:
        void helper(vector<double>&current, vector<double> &next, int curr_idx, int next_idx, double &remaining){
            if(curr_idx == -1){
                next[next_idx] = remaining;
                remaining -= 1;
                return;
            }
            if(current[curr_idx] >= 1){
                next[next_idx] += (current[curr_idx] - 1)/2;
                remaining -=0.5;
            }else{
                remaining -= current[curr_idx];
            }
            // return remaining;
        }
        double champagneTower(int poured, int query_row, int query_glass) {
            vector<double> curr;
    
        //    curr.push_back(poured);
           vector<double> next = curr;
           double remaining = poured;
           int row = -1;
           while(remaining > 0 && row < query_row ){
            row++;
              for(int j=0; j<curr.size();j++){
                next[j] = 0;
                if(j == 0){
                    helper(curr, next, 0,0, remaining);
                    
                }else{     
                     helper(curr, next, j-1,j, remaining);  
                     helper(curr, next, j,j, remaining);
     
                }
              }
               next.push_back(0);
               helper(curr, next, curr.size()-1,next.size()-1, remaining);
    
              curr = next;  
           }
           if(query_row > row) return 0.0;
           return curr[query_glass] > 1 ? 1.0 : curr[query_glass];
        }
    };