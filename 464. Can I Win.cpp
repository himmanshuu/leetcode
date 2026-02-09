class Solution {
    public:
        // unordered_map<int, bool> memo;
        int memo[1<<20];
        bool canWin(int mask,int maxChoosableInteger, int desiredTotal){
            if(desiredTotal <= 0) return false;
            if(memo[mask] != -1) return memo[mask];
            for(int i=1; i<=maxChoosableInteger;i++){
                int x =  1 << (i-1);
                if(!(mask & x)){
                    if( i >= desiredTotal){
                        return memo[mask] = true;
                    } 
                    if(canWin(mask | x, maxChoosableInteger, desiredTotal - i) == false){
                        return memo[mask] = true;
                    }
                }
            }
            return memo[mask] = false;
        }
        bool canIWin(int maxChoosableInteger, int desiredTotal) {
            int total_possibility = (maxChoosableInteger)*(maxChoosableInteger + 1)/2 ;
            if(total_possibility < desiredTotal ) return false;
            if(desiredTotal <= 0) return true;
            memset(memo, -1, sizeof(memo));
            return canWin(0, maxChoosableInteger, desiredTotal);
    
        }
    };