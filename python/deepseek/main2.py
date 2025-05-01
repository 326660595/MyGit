# Please install OpenAI SDK first: `pip3 install openai`

from openai import OpenAI

russell_api_key = "sk-9e2055b35eaf40b083838dff780a2140"

client = OpenAI(api_key=russell_api_key, base_url="https://api.deepseek.com")

response = client.chat.completions.create(
    model="deepseek-chat",
    messages=[
        {"role": "system", "content": "You are a helpful assistant"},
        {"role": "user", "content": "介绍一下yocto"},
    ],
    stream=False
)

print(response.choices[0].message.content)