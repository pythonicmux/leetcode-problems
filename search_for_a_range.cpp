class Solution {
public:
    // Return an index of the target integer within the array nums or -1 if target isn't in nums.
    int find(vector<int>& nums, int target, int lo, int hi) {
        if(nums.size() == 0) return -1;
        
        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if(nums[mid] > target) hi = mid - 1;
            else if(nums[mid] < target) lo = mid + 1;
            else return mid;
        }
        
        return (lo == hi && nums[lo] == target)?lo:-1;
    }
    
    // First find one index in nums where target is at.
    // Then, keep searching to the left of target and to the right of target 
    // until the target is not found in the subarray to get the bounds.
    vector<int> searchRange(vector<int>& nums, int target) {
        int initialIndex = find(nums, target, 0, nums.size() - 1);
        if(initialIndex < 0) return vector<int>{-1, -1};
        
        // Get the leftmost instance of target in nums.
        int lastLeftmostIndex = initialIndex;
        int leftmostIndex = find(nums, target, 0, initialIndex - 1);
        while(leftmostIndex != -1 && leftmostIndex != lastLeftmostIndex) {
            lastLeftmostIndex = leftmostIndex;
            leftmostIndex = find(nums, target, 0, leftmostIndex - 1);
        }
        
        // Get the rightmost instance of target in nums.
        int lastRightmostIndex = initialIndex;
        int rightmostIndex = find(nums, target, initialIndex + 1, nums.size() - 1);
        while(rightmostIndex != -1 && rightmostIndex != lastRightmostIndex) {
            lastRightmostIndex = rightmostIndex;
            rightmostIndex = find(nums, target, rightmostIndex + 1, nums.size() - 1);
        }
        
        return std::vector<int>{lastLeftmostIndex, lastRightmostIndex};
    }
};
