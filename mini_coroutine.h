/*
 * fork from https://www.chiark.greenend.org.uk/~sgtatham/coroutine.h
 *
 * To use these macros to define a coroutine, you need to write a
 * function that looks something like this.
 *
 * [Simple version using static variables (scr macros)]
 * #include "mini_coroutine.h"
 * int ascending (void) {
 *    static int i;     //can not use local variables
 *
 *    tick = getTimeMs();
 *
 *    __scrBegin(tick);
 *    for (i=0; i<10; i++) {
 *       __scrYield(i);
 *    }
 *    __scrFinishV;
 * }
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef __MINI_COROUTINE_H__
#define __MINI_COROUTINE_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



#define __scrBegin(tick)   \
    static unsigned int scrLine = 0, scrTick = 0, scrTargetTick = 0; scrTick = (tick); \
    switch(scrLine) { case 0:;
#define __scrGetPC(pScrLine) \
    (pScrLine) = &scrLine;
#define __scrReset(pScrLine) \
    if(NULL!=pScrLine){*(pScrLine)=0;}
#define __scrFinishV       } scrLine = 0; return
#define __scrFinish(z)       } scrLine = 0; return (z)
#define __scrYieldV       \
    do {\
        scrLine=__LINE__;\
    return; case __LINE__:;\
    } while (0)
#define __scrYield(z)       \
    do {\
        scrLine=__LINE__;\
    return (z); case __LINE__:;\
    } while (0)
#define __scrWaitV(tick) \
    do {\
        scrLine=__LINE__;\
        scrTargetTick = scrTick + (tick);\
    return; case __LINE__:\
        if(scrTargetTick > scrTick) return;\
        scrTargetTick=0;\
        ;\
    } while (0)
#define __scrWait(tick) \
    do {\
        scrLine=__LINE__;\
        scrTargetTick = scrTick + (tick);\
    return 6; case __LINE__:\
        if(scrTargetTick > scrTick) return 7;\
        scrTargetTick=0;\
        ;\
    } while (0)
#define __scrWaitUntil(condition,timeoutTick) \
    do {\
        scrLine=__LINE__;\
        scrTargetTick = scrTick + (timeoutTick);\
    return 6; case __LINE__:\
        if(scrTargetTick > scrTick && !(condition)) return 7;\
        scrTargetTick=0;\
        ;\
    } while (0)



#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__MINI_COROUTINE_H__
