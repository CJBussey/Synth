//
//  WavetableBufferTest.cpp
//  Synthuck
//
//  Created by Carl Bussey on 23/07/2015.
//
//

#include "WavetableBufferTest.h"
#include "../Source/WavetableBuffer.h"

int main()
{
    FWavetableBuffer aWavetableBuffer(10, 3);
    
    for (size_t nIndex = 0; nIndex < 10; ++nIndex)
    {
        aWavetableBuffer[nIndex] = nIndex;
    }
    
    for (size_t nIndex = 0; nIndex < 10; ++nIndex)
    {
        std::cout << aWavetableBuffer() << std::endl;
    }
}