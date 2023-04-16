#include "bsm.h"

BlackScholesModel::BlackScholesModel() :
    drift_(0.0), stock_price_(0.0), volatility_(0.0),
    risk_free_date_(0.0), date_(0.0) {}

BlackScholesModel::BlackScholesModel(double drift, double stock_price, double volatility, 
    double risk_free_rate, double date) :
    drift_(drift), stock_price_(stock_price), volatility_(volatility),
    risk_free_date_(risk_free_rate), date_(date) {}

std::vector<double> BlackScholesModel::GeneratePricePath(double to_date, int n_steps, double drift) const {
    std::vector<double> path(n_steps, 0.0);
    std::vector<double> eps = RandNormal(n_steps);
    
    double dt = (to_date - date_) / n_steps;

    double a = (drift - 0.5 * volatility_ * volatility_) * dt;
    double b = volatility_ * sqrt(dt);
    double current_log_s = log(stock_price_);

    for (size_t i = 0; i < n_steps; ++i) {
        double d_log_s = a + b * eps[i];
        double log_s = current_log_s + d_log_s;
        path[i] = exp(log_s);
        current_log_s = log_s; 
    }

    return path;
}