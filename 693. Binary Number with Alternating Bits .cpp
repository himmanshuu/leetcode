class Solution {
    public:
        bool hasAlternatingBits(int n) {
            return (n & (n>>1)) == 0 && (n | (n>>2)) == n;
            unsigned int x = n;
            // if(n & 1){
            //     x = (n ^ 0x55555555);
            // }else{
            //     x = (n^0xaaaaaaaa);
            // }
            x = (x>>1) + x;
            
            return (x & (x+1)) == 0; 
        }
    };