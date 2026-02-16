class Solution {
    public:
        int reverseBits(int n) {
            // int result =0;
            // for(int i=0; i<32; i++){
            //     if(n & (1<<i)){
            //          result |= (1<<(31-i));
            //     } 
            // }
            // return result;
            uint32_t m = n;
              m = ((m & 0xaaaaaaaa) >> 1) | ((m & 0x55555555) << 1);
              m = ((m & 0xcccccccc) >> 2) | ((m & 0x33333333) << 2);  
              m = ((m & 0xf0f0f0f0) >> 4) | ((m & 0x0f0f0f0f) << 4);  
              m = ((m & 0xff00ff00) >> 8) | ((m & 0x00ff00ff) << 8);  
              m = (m >> 16) | (m << 16);
        
        return m;
        }
    };