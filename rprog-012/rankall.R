rankall <- function(outcome, num = "best") {
  oc <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
  oc[, 11] <- as.numeric(oc[, 11]) # Heart.Attack
  oc[, 17] <- as.numeric(oc[, 17]) # Heart.Failure
  oc[, 23] <- as.numeric(oc[, 23]) # Pneumonia
  oc[, 7] <- as.factor(oc[, 7])
  
  col_index <- if (outcome == "heart attack") 11
  else if (outcome == "heart failure") 17
  else if (outcome == "pneumonia") 23
  else stop("invalid outcome")
  
  oc <- oc[!is.na(oc[, col_index]),]
  
  find_rank <- function (x) {
    i <- if (num == "best") 1
    else if (num == "worst") nrow(x)
    else num
    x[order(x[,col_index], x[,2]),][i, 2]
  }
  
  h <- sapply(split(oc, oc$State), find_rank)
  data.frame(hospital = h, state = names(h))
}