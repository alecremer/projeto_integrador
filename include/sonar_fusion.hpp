#ifndef SONAR_FUSION_HPP
#define SONAR_FUSION_HPP

#include <math.h>

using namespace std;

class SonarFusion {
public:

    SonarFusion(const double& delta_d, const double& d_max): delta_d(delta_d), d_max(d_max){}
    double fusion_distances(const double& d1, const double& d2){
        
        bool valid_delta = (abs(d1 - d2) <= delta_d);
        double d_fusion = (d1 + d2) / 2;
        bool valid_range = (d_fusion <= d_max);

        if(valid_delta && valid_range) return d_fusion;
        else return -1.00;

    }

private:
    int delta_d;
    int d_max;

};


#endif //SONAR_FUSION_HPP