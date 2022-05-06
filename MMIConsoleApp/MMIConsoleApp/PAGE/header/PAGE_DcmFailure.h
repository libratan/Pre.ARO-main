#ifndef PAGE_DCMFAILURE_H
#define PAGE_DCMFAILURE_H

namespace PAGE
{
    class DcmFailure
    {
    public:
        // Invalid OSB
        void handleInvalidOsb(void);

        //add other relevant functions here

    private:
        unsigned short int invalidOsbCount;
    };
}

#endif
