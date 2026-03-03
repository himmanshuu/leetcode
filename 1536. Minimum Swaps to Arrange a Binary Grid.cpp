class Solution {
    public:
        void helper(vector<int>& arr, int low, int high){
           
            for(int i = high; i>low;i--){
                swap(arr[i],arr[i-1]);
            }
          
        }
        int minSwaps(vector<vector<int>>& grid) {
            int n = grid.size();
            if(n==1) return 0;
            vector<int> arr(n,-1);
            // vector<bool> placed(n, false);
            for(int i=0; i<n;i++){
                for(int j=n-1;j>=0;j--){
                    if(grid[i][j] == 1){
                       arr[i] = j;
                       break;
                    }
                }
            }
    
            int cnt = 0;
            int i = 0;
            while(i < n){
                if(arr[i] <= i){ i++; continue;}
                int j = i + 1;
                while(j < n && arr[j] > i){
                    j++;
                }
    
                if(j == n) return -1;
                cnt += (j-i);
                helper(arr, i, j);
            }
            return cnt;
        }
    };