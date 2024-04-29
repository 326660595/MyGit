import re

# 给定的字符串
input_string = 'get_log_json:line-1939-:            "Message": "[2, \"5186178\", \"StopTransaction\", {\"meterStop\": 41, \"idTag\": "TACW2241822G1488", "timestamp": "2023-09-18T03:22:04.000Z", "transactionId": 394918, "reason": "EVDisconnected"}]"'

# 使用正则表达式匹配
match = re.search(r'"transactionId":\s*(\d+)', input_string)

if match:
    # 提取匹配的值
    transaction_id = match.group(1)
    print("Transaction ID:", transaction_id)
else:
    print("Transaction ID not found.")

    # get_log_json:line-1939-:            "Message": "[2, \"5186178\", \"StopTransaction\", {\"meterStop\": 41, \"idTag\": \"TACW2241822G1488\", \"timestamp\": \"2023-09-18T03:22:04.000Z\",
    # \"transactionId\": 394918, \"reason\": \"EVDisconnected\"}]",
