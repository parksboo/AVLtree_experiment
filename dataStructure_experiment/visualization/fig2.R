
library(ggplot2)
library(reshape2)

# CSV 파일에서 데이터를 읽어옵니다.
# 아래의 "data.csv"는 실제 CSV 파일의 경로와 이름으로 대체해야 합니다.
df <- read.csv("~/Documents/data_structure_experiment/result/output2.csv")

df_long <- melt(df)

p <- ggplot(df_long, aes(x = variable, y = value)) +
    geom_boxplot(
        outlier.shape = 8, # 아웃라이어의 모양을 변경합니다.
        outlier.size = 2, # 아웃라이어의 크기를 변경합니다.
        notch = FALSE
    ) + # 노치를 추가하여 중앙값의 신뢰구간을 표시합니다.
    stat_boxplot(geom = "errorbar") + # 박스플롯에 에러바를 추가합니다.
    labs(x = "data structure", y = "time(sec)", title = "Figure 2. Execution time of stock market data") +
  scale_y_continuous(labels = function(x) format(x, scientific = FALSE))

# 그래프를 출력합니다.
print(p)
