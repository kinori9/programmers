from itertools import combinations
from collections import Counter
import operator

def solution(orders, course):
    answer = []
    for cour in course:
        temp = []
        for order in orders:
            order = ''.join(sorted(order))
            combi = combinations(order, cour)
            temp += combi
        counte_result = Counter(temp) 
        sorted_result = sorted(counte_result.items(), key=operator.itemgetter(1), reverse=True)
        max = 0
        for ret in sorted_result:
            if ret[1] >= max and ret[1] > 1:
                max = ret[1]
                ret = ''.join(sorted(ret[0]))
                answer.append(ret)
    answer.sort()
    return answer

orders = ["ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH"]
#orders = ["ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD"]
#orders = ["XYZ", "XWY", "WXA"]
course = [2,3,4]
print(solution(orders, course))

