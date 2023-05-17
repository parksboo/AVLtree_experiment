
library(ggplot2)
library(reshape2)

# CSV 파일에서 데이터를 읽어옵니다.
# 아래의 "data.csv"는 실제 CSV 파일의 경로와 이름으로 대체해야 합니다.
df <- read.csv("~/Documents/data_structure_experiment/result/output1.csv")

# 데이터를 'long format'으로 변환합니다. 이렇게 해야 ggplot2에서 쉽게 처리할 수 있습니다.
df_long <- melt(df, id.vars = "data_size")

# 산점도를 그리고 추세선을 추가합니다.
p <- ggplot(df_long, aes(x = data_size, y = value, color = variable)) +
  geom_point() +
  geom_smooth(method = "loess", se = TRUE) +
  labs(y = "time(sec)", title = "Figure 1. Execution time of the program depending on data size", color = "Data Structure") 
# 그래프를 출력합니다.
print(p)
