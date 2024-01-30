#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]
List SimpLinCpp(NumericVector x, NumericVector y) {
  
  mat data = join_rows(ones<vec>(x.size()), vec(x));
  
  vec response = vec(y.begin(), y.size(), false);
 
  vec coefficients = solve(data, response);
  vec residuals = response - data * coefficients;
  vec fitted_values = data * coefficients;
  
  double s2 = sum(square(residuals)) / (x.size() - 2);  
  mat cov_matrix = s2 * inv_sympd(trans(data) * data);
  vec se = sqrt(cov_matrix.diag());
  double t_critical = R::qt(0.975, x.size() - 2, true, false); 
  
  vec lower_ci = coefficients - t_critical * se;
  vec upper_ci = coefficients + t_critical * se;
  
  // Create a list with the results
  List result = List::create(
    _["coefficients"] = coefficients,
    _["standard_errors"] = se,
    _["confidence_intervals"] = DataFrame::create(
      _["lower"] = lower_ci,
      _["upper"] = upper_ci
    ),
    _["residuals"] = residuals,
    _["fitted_values"] = fitted_values
  );
  
  return result;
}


