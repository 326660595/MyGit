import requests

# 设置 API Key 和端点
API_KEY = "KFC-CRAZY-THURSDAY-VME50"
API_URL = "https://api.deepseek.com/v1/endpoint"

# 设置请求头，包含 API Key
headers = {
    "Authorization": f"Bearer {API_KEY}",
    "Content-Type": "application/json"
}

# 设置请求参数
payload = {
    "param1": "value1",
    "param2": "value2"
}

# 发送 POST 请求
response = requests.post(API_URL, headers=headers, json=payload)

# 处理响应
if response.status_code == 200:
    data = response.json()
    print("API 调用成功，返回数据：", data)
else:
    print("API 调用失败，状态码：", response.status_code)
    print("错误信息：", response.text)