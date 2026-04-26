# fr = open("case_test.txt","r",encoding = "utf8")
# fw = open("bill.txt.bak","w",encoding="utf8")
#
# sflist = fr.readlines()
# for line in sflist:
#     if "测试" in line :
#         continue
#     fw.write(line)
# fw.flush()
# fr.close()
# fw.close()

# 改进
# 同时打开两个文件，自动管理关闭
with open("case_test.txt", "r", encoding="utf8") as fr, \
     open("bill.txt.bak", "w", encoding="utf8") as fw:
    # 逐行读取原文件
    for line in fr:
        # 跳过包含"测试"的行
        if "测试" in line:
            continue
        # 非测试行写入备份文件
        fw.write(line)

print("文件备份完成，已过滤掉测试数据行")