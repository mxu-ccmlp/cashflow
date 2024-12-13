#pragma once
#define invalid_staticsmm -999.0
#include <cmath>
#include <iostream>
namespace cf_funcs {
    int binarySearch(const double* x, int size, double new_x) {
        int left = 0, right = size / 2 - 1; // size / 2 because x is interleaved with y
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (x[mid * 2] == new_x) {
                return mid*2; // Found exact match
            }
            else if (x[mid * 2] < new_x) {
                left = mid + 1; // Move right
            }
            else {
                right = mid - 1; // Move left
            }
        }
        return (right+1)*2; // Return index of the largest x[i] <= new_x
    }
    double interp(double* x, double new_x, int shape0){
        //x,y needs to be sorted
        int nx = shape0 *2;
        int steps=0;
        if (new_x<=x[0])
            return x[1];
        else if (new_x>=x[nx-2])
            return x[nx-1];
        //else if (new_x<=x[0])
        //    return (new_x - x[0])*(x[1]-x[3])/(x[0] - x[2]) + x[1];
        //else if (new_x>=x[nx-2])
        //    return (new_x - x[nx-2])*(x[nx-1] - x[nx-3])/(x[nx-2] - x[nx-4]) + x[nx-1];
        else{
            //int steps = 0;
            //while (new_x>x[steps])
            //    steps += 2;
            steps = binarySearch(x, nx, new_x);
            //if (oldsteps != steps) {
            //    std::cout << oldsteps << ":" << steps << std::endl;
            //}
            return (new_x - x[steps-2])*(x[steps+1] - x[steps-1])/(x[steps] - x[steps-2]) + x[steps-1];
        }
    }
    double scurve(double rate_incentive, double a, double b, double c, double d){
        return a + b/(1.0+exp(-1.0*c*(rate_incentive-d)));
    }
    double interp2(double* x, double* y, double new_x, int shape0){
        //x,y needs to be sorted
        int nx = shape0 *4;
        int steps=0;

        if (new_x<x[0])
            return y[0];
        else if (new_x>x[nx-4])
            return y[nx-4];
        else if (new_x<=x[0])
            return (new_x - x[0])*(y[0]-y[4])/(x[0] - x[4]) + y[0];
        else if (new_x>=x[nx-4])
            return (new_x - x[nx-4])*(y[nx-4] - y[nx-8])/(x[nx-4] - x[nx-8]) + y[nx-4];
        else{
            while (new_x>x[steps])
                steps += 4;
            return (new_x - x[steps-4])*(y[steps] - y[steps-4])/(x[steps] - x[steps-4]) + y[steps-4];
        }
    }
    double genSeverity(double orig_bal, double curr_bal, int isMH, int wala){
        double disc, resale_exp, other_exp, int_exp, sev;
        double recovery;
        if (isMH == 1){
            disc = 0.30;
            resale_exp = 0.05;
            other_exp = 0.105;
            int_exp = 0.025;
        }else{
            disc = 0.08;
            resale_exp = 0.0075;
            other_exp = 0.048;
            int_exp = 0.025;
        }
        disc = 1.0 * disc * (0.6 - (wala - 233) * (0.6- 0.3)/120.0);
        recovery = orig_bal * (disc- other_exp) * ( 1.0- resale_exp) - curr_bal * int_exp;
        sev = 1.0 - recovery / curr_bal *1.0;
        if (sev<=0.50)
            sev = 0.50;
        else if (sev>=1.05)
            sev = 1.05;
        return sev;
    }
    double genSeverityX(double orig_bal, double curr_bal, double wala){
        double disc, sev;
        if (orig_bal>=40000.0)
            disc = 0.25;
        else if (orig_bal>=20000.0)
            disc = 0.20;
        else if (orig_bal>=10000.0)
            disc = 0.15;
        else
            disc =0.10;
        if (wala<=120)
            disc = disc * 1.0;
        else if (wala<=180)
            disc = disc * 0.5;
        else if (wala>=240)
            disc = disc * 0.25;
        sev = 1.0 - (orig_bal*disc - 2000.0)/curr_bal;
        if (sev<=0.15)
            sev = 0.15;
        if (sev>=1.05)
            sev = 1.05;
        return sev;
    }
}