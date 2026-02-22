class Solution {
    public:
        unordered_set<int> sieve(int n){
            vector<bool> isPrime(n+1, true);
            isPrime[0] = isPrime[1] = false;
            for(int i=2; i*i<=n;i++){
                if(isPrime[i]){
                    for(int j=i*i;j<=n;j+=i){
                        isPrime[j] = false;
                    }
                }
            }
            unordered_set<int>primes;
            for(int i=2; i<=n;i++){
                if(isPrime[i]) primes.insert(i);
            }
            return primes;
        }
        int countPrimeSetBits(int left, int right) {
            unordered_set<int>primes = {2,3,5,7,11,13,17,19,23,29,31};
            int count = 0;
            while(left <= right){
                int set = __builtin_popcount(left);
                if(primes.count(set)) count++;
                left++;
            }
            return count;
        }
    };