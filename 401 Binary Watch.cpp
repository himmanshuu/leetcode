class Solution {
    public:
    vector<string>result;

    void backtrack(int mask, int turnedOn, int start) {
        if (__builtin_popcount(mask) == turnedOn) {
            int hours   = mask >> 6;         // top 4 bits
            int minutes = mask & 0b111111;   // bottom 6 bits
            if (hours < 12 && minutes < 60)
                result.push_back(to_string(hours) + ":" + (minutes < 10 ? "0" : "") + to_string(minutes));
            return;
    }

    for (int i = start; i < 10; i++) {
        backtrack(mask | (1 << i), turnedOn, i + 1);
    }
}
        vector<string> readBinaryWatch(int turnedOn) {
            int hrs = min(3,turnedOn);
            vector<string>res;
            for(int hrsmask = 0; hrsmask < 12; hrsmask++){
                for(int minmask = 0; minmask < 60; minmask++){
                    int hrs_digit = __builtin_popcount(hrsmask);
                    int min_digit = __builtin_popcount(minmask);
    
                    if(hrs_digit + min_digit == turnedOn){
                        res.push_back(to_string(hrsmask) + ":" + (minmask < 10 ? "0" : "") + to_string(minmask));
                    }
                }
            }
            return res;
        }
    };