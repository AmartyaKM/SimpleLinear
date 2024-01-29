

set.seed(123)
x <- rnorm(100)
y <- 2 * x + 1 + rnorm(100)

SimpLinR <- function(x, y) {
  if (!is.numeric(x) || !is.numeric(y) || length(x) != length(y)) {
    stop("Input vectors x and y must be numeric vectors of the same length.")
  }
  # Call the C++ function
  return(SimpLinCpp(x, y))
}

# Call the R function
result <- SimpLinR(x, y)

# Print the result
print(result)
