# f = open("test.txt",'r',encoding="utf8")
# print(f.read())
# f = open("test.txt",'r',encoding="utf8")
# print(f.read())
# print(f.read(6))


with open("test.txt", 'r', encoding="utf8") as f:
    s = f.read()
    print(s)
    count = s.count("itheima")
    print(count)

