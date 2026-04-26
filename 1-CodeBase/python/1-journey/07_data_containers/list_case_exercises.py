
my_list1 = [21,25,21,23,22,20]
my_list2 = list([1,2,3])

print(my_list1)
print(my_list2)

my_list1.append(31)

print(my_list1)

my_list2.extend([2,3,4,5,2])

print(my_list2)

print(my_list1[0])

print(my_list2[len(my_list2)-1])

print(my_list1.index(31))


print("_________________")
index = 0
print("while")
while index < len(my_list2):
    print(my_list2[index])
    index += 1

index = 0
print("for")
for num in my_list2:
    print(num)
    index += 1

