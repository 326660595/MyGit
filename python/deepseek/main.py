import os
from deepseek import DeepSeekClient

# os.environ["DEEPSEEK_API_KEY"] = "your_api_key_here"
client = DeepSeekClient(api_key="KFC-CRAZY-THURSDAY-VME50")



response = client.some_method(param1="value1", param2="value2")
print(response)


if response.status_code == 200:
    data = response.json()
    print(data)
else:
    print("Error:", response.status_code)


try:
    response = client.some_method(param1="value1", param2="value2")
    response.raise_for_status()
except Exception as e:
    print(f"An error occurred: {e}")
