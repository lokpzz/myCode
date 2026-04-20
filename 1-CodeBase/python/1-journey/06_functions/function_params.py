def check_temperature (temperature):
    if temperature <= 37.5:
        print(f"欢迎来到黑马程序员！请出示您的健康码以及72小时核酸证明，并配合测量体温！\n体温测量中，您的体温是：{temperature}度，体温正常请进！")
    else:
        print(f"欢迎来到黑马程序员！请出示您的健康码以及72小时核酸证明，并配合测量体温! \n中，您的体温是：{temperature}度，需要隔离！")
    return 0
temperature = float(input("你的体温： "))
check_temperature(temperature)