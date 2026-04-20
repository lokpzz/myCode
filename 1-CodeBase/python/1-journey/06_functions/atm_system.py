def check_balance (name):
    print("------------------查询余额-------------------")
    print(f"{name}，您好，您的余额剩余：<unk>元")
    return 0
def deposit (name, amount):
    print("--------------------存款--------------------")
    print(f"{name}，您好，您存款<UNK>元成功")
    print(f"{name}，您好，您的余额剩余：<UNK> + {amount}元")
    return 0
def withdrawal(name, amount):
    print("--------------------取款--------------------")
    print(f"{name}，您好，您取款{amount}元成功")
    print(f"{name}，您好，您的余额剩余：<UNK> - {amount}元")
    return 0
def mainMenu(name):
    while True:
        print("-------------------主菜单-------------------")
        print(f"{name}，您好，欢迎来到黑马银行ATM。请选择操作：")
        print("查询余额\t[输入1]")
        print("存款\t\t[输入2]")
        print("取款\t\t[输入3]")
        print("退出\t\t[输入4]")
        print("请输入您的选择：", end="")
        choice = input()
        match choice:
            case "1":
                check_balance(name)
            case "2":
                amount = float(input("{name}，您好，您想存入多少钱："))
                deposit(name, amount)
            case "3":
                amount = float(input("{name}，您好，您想取出多少钱："))
                withdrawal(name, amount)
            case "4":
                break
            case _:  # 相当于 default
                print("输入错误")
        choice = input("请按任意键进行下一步")

account_name = input("请输入您的账户姓名：")
# 调用函数，打印菜单
mainMenu(account_name)
print("已退出登录")