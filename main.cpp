#include <stdio.h>
#include "half.hpp"

using half_float::half;
using half_float::half_cast;

#define LENGTH    16
int main()
{
    float a[LENGTH];
    float b[LENGTH];
    float c[LENGTH];
    
    half ha[LENGTH];
    half hb[LENGTH];
    half hc[LENGTH];   
    
    for (int i = 0; i < LENGTH; ++i) {
        float r = static_cast<float>(rand())/static_cast<float>(RAND_MAX)*2.0f - 1.0f; // range: [-1, 1]
        a[i] = r;
        r = static_cast<float>(rand())/static_cast<float>(RAND_MAX)*2.0f - 1.0f;
        b[i] = r;
        c[i] = a[i]*b[i];
        
        ha[i] = half_cast<half, std::round_to_nearest>(a[i]);
        hb[i] = half_cast<half, std::round_to_nearest>(b[i]);
        hc[i] = ha[i]*hb[i];
        
        printf("%d:diff=%.8f, a=%.8f, b=%.8f, c=%.8f, ha=%.8f, hb=%.8f, hc=%.8f, hc_bin=0x%08x, hc_bin_hfloat=%.8f\n", i,fabs(c[i]-(float)hc[i]),a[i],b[i],c[i],(float)ha[i],(float)hb[i],(float)hc[i],hc[i].get_binary(),(float)half::from_binary(hc[i].get_binary()));
    }
    
    return 0;
}
