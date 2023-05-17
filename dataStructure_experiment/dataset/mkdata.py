import sys
import csv
import random

n = int(sys.argv[1])  # 원하는 행의 수를 설정

# 1~n까지의 수를 랜덤하게 배치
primary_keys = list(range(1, n+1))
random.shuffle(primary_keys)

# CSV 파일을 쓰기 모드로 열기
with open('./dataset/exdata.csv', 'w', newline='') as file:
    writer = csv.writer(file)

    # 각 행에 대해
    for i in range(n):
        # 1~100까지의 랜덤한 숫자 세 개를 생성
        random_numbers = [random.randint(1, 100) for _ in range(2)]

        # 기본키와 랜덤한 숫자를 합쳐서 행을 생성
        row = [f"A{primary_keys[i]:06d}"] + ["임시이름"] + random_numbers

        # 행을 CSV 파일에 작성
        writer.writerow(row)
