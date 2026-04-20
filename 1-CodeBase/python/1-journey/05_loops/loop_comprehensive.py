import random

account_balance = 10000
for i in range(1,21):
    employee_performance = random.randint(1, 10)
    if employee_performance > 5:
        if account_balance == 0:
            break
        account_balance -= 1000
        print(f"向员工{i},绩效分{employee_performance},发放工资1000元，账户余额还剩余{account_balance}元")
    else:
        print(f"员工{i}，绩效分{employee_performance}，低于5，不发工资，下一位。")
if account_balance == 0:
    print("工资发完了，下个月领取吧。")
else:
    print(f"工资还剩{account_balance}")

