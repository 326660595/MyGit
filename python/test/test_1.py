import re

# 输入的 JSON 字符串
json_str = '{"connectorId":1,"transactionId":418025,"meterValue":{"timestamp":"2023-10-11T10:37:27.000Z","sampledValue":{"value":"227.30","context":"Transaction.End","format":"Raw","measurand":"Voltage","phase":"L1-N","unit":"V"},{"value":"0.18","context":"Transaction.End","format":"Raw","measurand":"Current.Import","phase":"L1","unit":"A"},{"value":"41","context":"Transaction.End","format":"Raw","measurand":"Power.Active.Import","phase":"L1","unit":"W"},{"value":"0","context":"Transaction.End","format":"Raw","measurand":"Energy.Active.Import.Register","unit":"Wh"},{"value":"16","context":"Transaction.End","format":"Raw","measurand":"Current.Offered","unit":"A"}}}'
# 使用正则表达式查找所有"value"值
values = re.findall(r'"value":"(.*?)"', json_str)
# values = re.findall(r'"connectorId":(.*?),', json_str)
print(len(values))

# 打印所有"value"值
for value in values:
    print(value)
