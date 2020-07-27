#ifndef Kassiopeia_KSMotionsMessage_h_
#define Kassiopeia_KSMotionsMessage_h_

#include "KMessage.h"

KMESSAGE_DECLARE(Kassiopeia, movmsg)

#ifdef Kassiopeia_ENABLE_DEBUG

#define movmsg_debug(xCONTENT) movmsg(eDebug) << xCONTENT;

#define movmsg_assert(xVARIABLE, xASSERTION)                                                                           \
    if (!(xVARIABLE xASSERTION))                                                                                       \
        fieldmsg(eError) << "Assertion failed: " << #xVARIABLE << " " << #xASSERTION << " but " << #xVARIABLE          \
                         << " is " << (xVARIABLE) << eom;

#endif

#ifndef movmsg_debug
#define movmsg_debug(xCONTENT)
#define movmsg_assert(xVARIABLE, xASSERTION)
#endif

#endif
