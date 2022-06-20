#ifndef LP_FILTER_H
#define LP_FILTER_H

#define DEFAULT_ALPHA 0.1
#define INITIAL_FILTER_VALUE 0.0

class LpFilter {
private:
    double alpha;
    double filtered_value;
public:
    LpFilter();
    LpFilter(double alpha);
    double get_filtered_value(double value);
};

#endif // LP_FILTER_H
