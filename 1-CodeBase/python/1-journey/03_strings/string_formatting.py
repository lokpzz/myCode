#股价计算小程序
name = "传智播客"
tock_price = float(19.99)
stock_code = "003032"
stock_price_daily_growth_factor = float(1.2)
growth_days = 7

print(f"公司：{name}，股票代码：{stock_code}，当前股价：{tock_price},\n"
      "每日增长系数是：%s,经过%d天的增长后，股价达到了：%f" % (stock_code,stock_price_daily_growth_factor,tock_price*(1.2 ** 7)))
