import json

# 给定的字符串
input_string = "Message: [2, \"5186178\", \"StopTransaction\", {\"meterStop\": 41, \"idTag\": \"TACW2241822G1488\", \"timestamp\": \"2023-09-18T03:22:04.000Z\", \"transactionId\": 394918, \"reason\": \"EVDisconnected\"}]"

# 提取 JSON 部分，即大括号内的内容
json_start = input_string.find("{")
json_end = input_string.rfind("}") + 1
json_data = input_string[json_start:json_end]

# 解析 JSON 数据
data = json.loads(json_data)

# 访问所需的值
meterStop = data["meterStop"]
idTag = data["idTag"]
timestamp = data["timestamp"]
transactionId = data["transactionId"]
reason = data["reason"]

# 打印结果
print("meterStop:", meterStop)
print("idTag:", idTag)
print("timestamp:", timestamp)
print("transactionId:", transactionId)
print("reason:", reason)
