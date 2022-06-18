#include "lp_filter.h"

LpFilter::LpFilter() {
  this->alpha = DEFAULT_ALPHA;
  this->filtered_value = INITIAL_FILTER_VALUE;
}

LpFilter::LpFilter(double alpha) {
  this->alpha = alpha;
  this->filtered_value = INITIAL_FILTER_VALUE;
}

double LpFilter::get_filtered_value(double value) {
  this->filtered_value = this->alpha * value + (1 - this->alpha) * this->filtered_value;
  return this->filtered_value;
}
