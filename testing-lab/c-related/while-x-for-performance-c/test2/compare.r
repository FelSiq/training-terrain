data.for1 <- read.csv("data/for.data", header=FALSE)$V1
data.for2 <- read.csv("data/for2.data", header=FALSE)$V1
data.while1 <- read.csv("data/while.data", header=FALSE)$V1
data.while2 <- read.csv("data/while2.data", header=FALSE)$V1

x.range <- 1:length(data.for1)
ylim <- c(min(data.for1, data.for2, data.while1, data.while2),
          max(data.for1, data.for2, data.while1, data.while2))

plot(x.range, data.for1, ylim=ylim, type="l")
lines(x.range, data.while2, col="green")

lines(x.range, data.for2, col="red")
lines(x.range, data.while1, col="blue")
