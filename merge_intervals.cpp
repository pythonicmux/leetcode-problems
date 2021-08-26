class Solution {
public:
    // Sort the intervals by starting time.
    // Then, start with the earliest interval and 
    // merge in all intervals that start before it ends. Once 
    // the next interval is disjoint, move on to that one, etc...
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>&b) {
            return a[0] < b[0];
        });
        
        if(intervals.size() == 0) return intervals;
        
        // We start with the first interval and merge intervals into it until there's 
        // a disjoint interval- then we push that disjoint interval onto the output vector 
        // and merge intervals into it.
        vector<vector<int>> out{intervals[0]};
        int candidateMerger = 1;
        
        while(candidateMerger < intervals.size()) {
            // If there's no more overlap then we move to the candidateMerger index as the 
            // new most recent interval.
            if(out[out.size() - 1][1] < intervals[candidateMerger][0]) {
                out.push_back(intervals[candidateMerger]);
            } else {
                // Otherwise, merge the interval into the most recent interval.
                out[out.size() - 1][1] = max(out[out.size() - 1][1], intervals[candidateMerger][1]);
            }
            
            candidateMerger++;
        }
        
        return out;
    }
};
