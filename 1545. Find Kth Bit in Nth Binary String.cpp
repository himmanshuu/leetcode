class Solution {
    public:
        char findKthBit(int n, int k) {
            if(n == 1 && k == 1) return '0';
            int mid = (1<<(n-1));
            if(k == mid) return '1';
            else if(k > mid) return findKthBit(n-1, (1<<n)-k) & 1 ? '0' : '1';
            else return findKthBit(n-1, k);
        }
    };