
#include "bench.h"
#include <stdlib.h>

#include <iostream>
#include "vectorial/vec4f.h"

#define NUM (81920)
#define ITER 100
using namespace vectorial;

vec4f* alloc_vec4f(size_t n) {
    void *ptr;
    int e = posix_memalign(&ptr, 16, n * sizeof(vec4f) );
//    if( e == EINVAL ) printf("EINVAL posix_memalign\n");
//    if( e == ENOMEM ) printf("ENOMEM posix_memalign\n");
    return static_cast<vec4f*>(ptr);
}



static vec4f * a;
static vec4f * b;
static vec4f * c;




void add_func() {
    
    vec4f* vectorial_restrict aa = a;
    vec4f* vectorial_restrict bb = b;
    vec4f* vectorial_restrict cc = c;
    
    for(size_t i = 0; i < NUM; ++i)
    {
        cc[i] = aa[i] + bb[i];
    }    
}

void add_bench() {

    a = alloc_vec4f(NUM);
    b = alloc_vec4f(NUM);
    c = alloc_vec4f(NUM);


    for(size_t i = 0; i < NUM; ++i)
    {
        a[i]=vec4f(i,i,i,i);
        b[i]=vec4f(NUM-i, NUM-i, NUM-i, NUM-i);
    }
        
    profile(add_func, ITER, NUM);

    free(a);
    free(b);
    free(c);


}
