#ifndef INTEGRATE_H
#define INTEGRATE_H
#include <functional>
#include <omp.h>

using integrand = std::function<double(double/*x*/)>;

//simple implementation of Simpson's rule
double integrate(integrand fxn, double x0, double xEnd, double h) {
    //ensure the number of intervals (n) is even
    int n = static_cast<int>((xEnd - x0) / h);
    if (n % 2 != 0) {
        n++;
        h = (xEnd - x0) / n;  //recalculate h to ensure even intervals
    }

	double integral = fxn(x0);

    int i = 0;
    #pragma omp parallel for private(i) reduction (+ : integral) //multithreading go brr
    for (i = 0; i < n; i++) {
        if (i % 2 == 0)
            integral += 2 * fxn(x0 + i * h);
        else
            integral += 4 * fxn(x0 + i * h);
    }

    integral += fxn(xEnd);
    integral *= h/3.0;

    return integral;
}

double integrateOverAllSpace(integrand fxn, double h) {
    double x0 = std::numeric_limits<double>::min();
    double xEnd = std::numeric_limits<double>::max();
    //ensure the number of intervals (n) is even
    int n = static_cast<int>((xEnd - x0) / h);
    if (n % 2 != 0) {
        n++;
        h = (xEnd - x0) / n;  //recalculate h to ensure even intervals
    }

	double integral = fxn(x0);

    int i = 0;
    #pragma omp parallel for private(i) reduction (+ : integral) //multithreading go brr
    for (i = 0; i < n; i++) {
        if (i % 2 == 0)
            integral += 2 * fxn(x0 + i * h);
        else
            integral += 4 * fxn(x0 + i * h);
    }

    integral += fxn(xEnd);
    integral *= h/3.0;

    return integral;
}

#endif // !INTEGRATE_H