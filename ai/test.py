#!/opt/anaconda3//bin/python3
from openai import OpenAI
import sys  # 导入 sys 模块以处理命令行参数

client = OpenAI(
  base_url = "https://integrate.api.nvidia.com/v1",
  api_key = "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"
)

# 获取命令行参数
if len(sys.argv) < 2:
    print("请提供要发送的消息。")
    sys.exit(1)

user_message = sys.argv[1]  # 从命令行获取用户消息

completion = client.chat.completions.create(
  model="deepseek-ai/deepseek-r1",
  messages=[{"role":"user","content": user_message}],  # 使用命令行输入的消息
  temperature=0.6,
  top_p=0.7,
  max_tokens=4096,
  stream=True
)

for chunk in completion:
  if chunk.choices[0].delta.content is not None:
    response = chunk.choices[0].delta.content
    # 去掉开头的 <think> 和 </think>
    response = response.replace("<think>", "").replace("</think>", "").strip()
    print(response, end="")


