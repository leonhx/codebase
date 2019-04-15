pollutantmean <- function(directory, pollutant, id = 1:332) {
    sum <- 0
    count <- 0
    
    for (i in id) {
        filename <- sprintf("%s/%03d.csv", directory, i)
        pl <- read.csv(filename, header = T)[[pollutant]]
        pl <- pl[!is.na(pl)]
        count <- count + length(pl)
        sum <- sum + sum(pl)
    }
    
    sum / count
}