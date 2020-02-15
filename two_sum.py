class array_element:
    def __init__(self, index, val):
        self._index = index
        self._value = val
        
    def getIndex(self):
        return self._index
    
    def getValue(self):
        return self._value
    
class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        
        new_nums = []
        
        # Convert the values to objects, so we can store their indices, also filter out any invalid values
        for old_idx, val in enumerate(nums):
                new_nums.append(array_element(old_idx, val))

        # Sort the numbers
        new_nums = sorted(new_nums, key=lambda ele: ele.getValue())
        
        # Optimization
        list_len = len(new_nums)
        if(list_len == 2):
            lower_idx = new_nums[0].getIndex()
            upper_idx = new_nums[1].getIndex()
            return [lower_idx, upper_idx]
        
        # Bad stuff happened
        assert(list_len >= 2)
        
        upper_idx = list_len - 1
        lower_idx = 0
        
        found = False
                
        while not found:
            sum = new_nums[lower_idx].getValue() + new_nums[upper_idx].getValue()
            
            # Lower index is too low, slide it right
            if sum < target:
                lower_idx += 1
            # Upper index is too high, slide it left
            elif sum > target:
                upper_idx -= 1
            else:
                lower_idx = new_nums[lower_idx].getIndex()
                upper_idx = new_nums[upper_idx].getIndex()
                return [lower_idx, upper_idx]
