# str = "hello world"
# print(str)
# str[0] = 'a'
# print(str)
"""报错！确实不可修改"""

s = "万过薪月，员序程马黑来，nohtyP学"
result1 = s[9:4:-1]
print(result1)

result2 = s.split('，')
print(result2)
result3 = s.split("，")[1].replace("来","")[::-1]
print(result3)

