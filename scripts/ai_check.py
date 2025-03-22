import os
import requests
import json
import argparse

# Конфигурация DeepSeek API
DEEPSEEK_API_URL = "https://api.deepseek.com/v1/analyze"
DEEPSEEK_API_KEY = os.getenv("DEEPSEEK_API_KEY")  # API ключ из переменных окружения

def analyze_code(code_dir, include_dir):
    # Сбор всех файлов с кодом
    code_files = []
    for root, _, files in os.walk(code_dir):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                code_files.append(os.path.join(root, file))
    for root, _, files in os.walk(include_dir):
        for file in files:
            if file.endswith(".h"):
                code_files.append(os.path.join(root, file))

    # Чтение кода
    code_content = ""
    for file in code_files:
        with open(file, "r") as f:
            code_content += f"File: {file}\n\n{f.read()}\n\n"

    # Отправка запроса к DeepSeek API
    headers = {
        "Authorization": f"Bearer {DEEPSEEK_API_KEY}",
        "Content-Type": "application/json",
    }
    data = {
        "code": code_content,
        "language": "cpp",
        "task": "code_review",
    }
    response = requests.post(DEEPSEEK_API_URL, headers=headers, json=data)

    if response.status_code != 200:
        print(f"Ошибка: {response.status_code} - {response.text}")
        return 1, 0  # Возвращаем ошибку и оценку 0

    # Обработка результата
    result = response.json()
    feedback = result.get("feedback", "Нет обратной связи.")
    grade = result.get("grade", 0)  # Оценка от нейросети (0-100)

    print(f"Обратная связь от нейросети:\n{feedback}")
    print(f"Оценка от нейросети: {grade}/100")

    return 0, grade  # Успех и оценка

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Анализ кода с помощью DeepSeek.")
    parser.add_argument("--code-dir", required=True, help="Директория с кодом студента.")
    parser.add_argument("--include-dir", required=True, help="Директория с заголовочными файлами.")
    args = parser.parse_args()

    exit_code, grade = analyze_code(args.code_dir, args.include_dir)
    exit(exit_code)
