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

//variable transformation
double transformed_fxn(integrand fxn, double t) {
    double x = t / (1 - t * t);
    return fxn(x) * (1 + t * t) / ((1 - t * t) * (1 - t * t));
}

double integrateOverAllSpace(integrand fxn, double h) {
    double integral = 0.0;
    int n = static_cast<int>(2.0 / h); //number of intervals
    if (n % 2 != 0) {
        n++;
        h = 2.0 / n;  //recalculate h to ensure even intervals
    }

    int i = 0;
    #pragma omp parallel for private(i) reduction (+ : integral) //multithreading go even more brr
    for (i = 0; i <= n; ++i) {
        double t = -1.0 + i * h;
        if (!(std::abs(t) >= 1.0)) {
            double weight = (i == 0 || i == n) ? 1 : ((i % 2 == 0) ? 2 : 4);
            integral += weight * transformed_fxn(fxn, t);
        }
    }

    integral *= h / 3.0;
    return integral;
}

#endif // !INTEGRATE_H