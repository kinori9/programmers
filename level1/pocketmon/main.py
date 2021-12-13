def dfs(nums, i, now_try, can_try):
    if now_try < can_try:
        return ;
    print(nums[i])


def dfs_init(nums, i, now_try, can_try):
    nums_dic = nums.fromkeys(nums, False)
    ret = dfs(nums, i, now_try, can_try)
    return ret

def solution(nums):
    nums_len = len(nums)
    can_try = nums_len / 2
    nums_dic = {}
    for i in nums:
        string = str(i)
        nums_dic[i] = False
    dic_len = len(nums_dic)
    if dic_len < can_try:
        answer = dic_len
    else:
        answer = can_try
    return answer

#def solution(nums):
#    nums_len = len(nums)
#    can_try = nums_len / 2
#    i = 0;
#    ret_max = 0
#    ret = 0
#    for i in nums:
#        ret = dfs_init(nums, i, 0, can_try)
#        if ret_max < ret:
#            ret_max = ret
#        i += 1
#    answer = ret_max
#    return answer

nums = [3,1,2,3]
result = solution(nums)
#print(result)

#[3,1,2,3]	2
#[3,3,3,2,2,4]	3
#[3,3,3,2,2,2]	2
