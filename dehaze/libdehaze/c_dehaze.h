#ifndef _C_DEHAZE_H_
#define _C_DEHAZE_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

// only process yuv420p in data (stride = width)
int doDehaze(uint8_t *pData[], const int width, const int height);


#ifdef __cplusplus
}
#endif


#endif // _C_DEHAZE_H_
