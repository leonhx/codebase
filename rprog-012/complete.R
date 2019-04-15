complete <- function(directory, id = 1:332) {
    nobs <- c()
    for (i in seq_along(id)) {
        filename <- sprintf("%s/%03d.csv", directory, id[i])
        pl <- read.csv(filename, header = T)
        c.cases <- complete.cases(pl$sulfate, pl$nitrate)
        nobs[i] <- length(c.cases[c.cases])
    }
    data.frame(id = id, nobs = nobs)
}