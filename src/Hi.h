#ifndef HI_H
#define HI_H

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
std::vector<double> xHI;
std::vector<double> y1HI;
std::vector<double> y2HI;

void writeH(){
	double xVar = -2;

	while (xVar <= 2){
		y1HI.push_back((double) std::sqrt(1-(std::abs(xVar)-1)*(std::abs(xVar)-1)));
		y2HI.push_back((double) std::acos(1-std::abs(xVar)) - 3.1415926535);
		xHI.push_back((double) xVar);
		xVar += 0.01;
	}
}

void plotH() {
    writeH();

    plt::plot(xHI, y1HI);
    plt::plot(xHI, y2HI);

    plt::title("Hi Lana :)");
    plt::save("../saves/Hi.png");
}

#endif