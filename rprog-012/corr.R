corr <- function(directory, threshold = 0) {
    cr <- c(); i <- 1
    files <- list.files(directory)
    for (file in files) {
        fullname <- paste(directory, file, sep = "/")
        pl <- read.csv(fullname, header = T)
        pl <- pl[complete.cases(pl$nitrate, pl$sulfate),]
        if (nrow(pl) > threshold) {
            cr[i] <- cor(pl$nitrate, pl$sulfate)
            i <- i + 1
        }
    }
    cr
}