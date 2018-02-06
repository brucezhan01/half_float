#include <stdio.h>
#include "half.hpp"
#include "cpfp.hpp"

using half_float::half;
using half_float::half_cast;

#define LENGTH    1000
int main()
{
    float a[LENGTH];
    float b[LENGTH];
    float c[LENGTH];
    
    half ha[LENGTH];
    half hb[LENGTH];
    half hc[LENGTH];   
    
    cpfp ha_1[LENGTH];
    cpfp hb_1[LENGTH];
    cpfp hc_1[LENGTH];
    
    float min_error = 1e-4;
    long bigerr_cnt = 0;
    long bigerr1_cnt = 0;
    float err = 0.0f;
    float err_1 = 0.0f;
    
    for (int i = 0; i < LENGTH; ++i) {
        float r = static_cast<float>(rand())/static_cast<float>(RAND_MAX)*2.0f - 1.0f; // range: [-1, 1]
        a[i] = r;
        r = static_cast<float>(rand())/static_cast<float>(RAND_MAX)*2.0f - 1.0f;
        b[i] = r;
        c[i] = a[i]*b[i];
        
        ha[i] = half_cast<half, std::round_to_nearest>(a[i]);
        hb[i] = half_cast<half, std::round_to_nearest>(b[i]);
        hc[i] = ha[i]*hb[i];
        
        ha_1[i] = cpfp(a[i]);
        hb_1[i] = cpfp(b[i]);
        hc_1[i] = ha_1[i]*hb_1[i];

        err = fabs(c[i]-(float)hc[i]);
        err_1 = fabs(c[i]-(float)hc_1[i]);
        
        #if 0
        printf("==================== %d\n", i);
        printf("a=%.8f, b=%.8f, c=%.8f\n", a[i],b[i],c[i]);
        printf("ha=%.8f, hb=%.8f, hc=%.8f, hc_bin=0x%08x, hc_bin_hfloat=%.8f\n", (float)ha[i],(float)hb[i],(float)hc[i],hc[i].get_binary(),(float)half::from_binary(hc[i].get_binary()));
        printf("ha_1=%.8f, hb_1=%.8f, hc_1=%.8f\n", (float)ha_1[i],(float)hb_1[i],(float)hc_1[i]);
        printf("err=%.8f\n", err);
        printf("err_1=%.8f\n", err_1);
        printf("\n");
        #endif
        
        if (err > min_error) {
            ++bigerr_cnt;
            #if 0
            printf("Error (%.8f) is greater than %.8f\n", err, min_error);
            #endif
        }
        if (err_1 > min_error) {
            ++bigerr1_cnt;
            #if 0
            printf("Error-1 (%.8f) is greater than %.8f\n", err_1, min_error);
            #endif
        }
    }
    
    printf("(half impl) Total %ld count which error is bigger than %.8f\n", bigerr_cnt, min_error);
    printf("(cpfp impl) Total %ld count which error is bigger than %.8f\n", bigerr1_cnt, min_error);
    
    return 0;
}
