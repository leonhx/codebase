best <- function(state, outcome) {
  oc <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
  oc[, 11] <- as.numeric(oc[, 11]) # Heart.Attack
  oc[, 17] <- as.numeric(oc[, 17]) # Heart.Failure
  oc[, 23] <- as.numeric(oc[, 23]) # Pneumonia
  
  if (!is.element(state, oc$State))
    stop("invalid state")
  
  col_index <- if (outcome == "heart attack") 11
  else if (outcome == "heart failure") 17
  else if (outcome == "pneumonia") 23
  else stop("invalid outcome")
  
  oc <- oc[oc$State == state && !is.na(oc[, col_index]),]
  
  oc[with(oc, order(oc[,col_index], oc[,2])),][1, 2]
}