

SimpLinR <- function(x, y) {
  if (!is.numeric(x) || !is.numeric(y) || length(x) != length(y)) {
    stop("Input vectors x and y must be numeric vectors of the same length.")
  }
  # Call the C++ function
  return(SimpLinCpp(x, y))
}
