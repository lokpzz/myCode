#定义一个列表list
list1 = [1,2,3,4,5]
print(list1)
print(list1[0])
print(type(list1))
#定义一个嵌套的列表
list2 = [[1,2,3],[4,5,6]]
print(list2)
print(list2[0])
print(type(list2))
#通过下标索引取出对应位置的数据
print(list2[1][1])
#通过下标索引取出数据（倒序取出）
for item in list2[0]:
    print(item)
#取出嵌套列表的元素
for item in list2[1]:
    print(item)