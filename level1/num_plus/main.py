def solution(numbers):
    answer = 0
    arr = [-1] * 10
    for idx, val in enumerate(numbers):
        arr[val] = 1
    for idx, val in enumerate(arr):
        if arr[idx] == -1:
            answer += idx
    return answer

arr = [5, 8, 4, 0, 6, 7, 9]
print(solution(arr))
