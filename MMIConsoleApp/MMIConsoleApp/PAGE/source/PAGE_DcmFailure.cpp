
#include <../PAGE/header/PAGE_DcmFailure.h>

namespace PAGE {

    // Handle invalid OSB
    void DcmFailure::handleInvalidOsb(void)
    {
        invalidOsbCount++;
    }
}