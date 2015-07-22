
#pragma once
#include <vector>
#include <iostream>

template <class T>
class CircularBuffer
{
public:
    // Lifetime
    CircularBuffer(size_t nWindowSize);
    
    // Access
    std::vector<T> getBuffer() { return m_aBuffer; };
    // @todo: getContiguousBuffer()
    
    void write(T aValue);
    T read();
    
    void hopWrite();
    void hopRead();
    
    inline void setAutoHopWrite(bool bAutoHop) { m_bAutoHopWrite = bAutoHop; };
    inline void setAutoHopRead(bool bAutoHop) { m_bAutoHopRead = bAutoHop; };
    inline void setOverlapAdd(bool bOverlapAdd) { m_bOverlapAdd = bOverlapAdd; };
    
    inline void setReadRate(float fReadRate) { m_fReadRate = fReadRate; };
    inline void setWindowSize(size_t nWindowSize);
    
    inline void setHopSize(size_t nHopSize);
    
    inline void setWriteOffset(size_t nOffset);
    inline void setReadOffset(size_t nOffset);
    
    inline void setHopRate(const size_t nHopRate);
    inline void setEnableDefaultHopRate(const bool bEnable) { m_bDefaultHopRate = bEnable; }
    
    void clear();
    
private:
    
    size_t m_nWindowSize;
    
    std::vector<T> m_aBuffer;
    std::vector<T> m_aContiguousBuffer;
    size_t m_nHopSize;
    
    size_t m_nWritePosition;
    size_t m_nReadPosition;
    size_t m_nHoppedWritePosition;
    size_t m_nHoppedReadPosition;
    
    bool m_bAutoHopWrite;
    bool m_bAutoHopRead;
    bool m_bOverlapAdd;
    
    size_t m_nWriteCounter;
    size_t m_nReadCounter;
    
    float m_fReadRate;
    float m_nHopRate;
    bool m_bDefaultHopRate;
    
    bool m_bDataHasChanged;
    
    // Helpers
    void incrementCursor(size_t& nCursor, const float fIncrement = 1);
};

//////////////////////////////////////////////////////////////////////////////////////////
// Lifetime
//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
CircularBuffer<T>::CircularBuffer(size_t nWindowSize)
:   m_nWindowSize(nWindowSize)
,   m_aBuffer(nWindowSize, 0)
,   m_aContiguousBuffer(nWindowSize, 0)
,   m_nHopSize(0)
,   m_nWritePosition(0)
,   m_nReadPosition(0)
,   m_nHoppedWritePosition(0)
,   m_nHoppedReadPosition(0)
,   m_bAutoHopWrite(false)
,   m_bAutoHopRead(false)
,   m_bOverlapAdd(false)
,   m_nWriteCounter(0)
,   m_nReadCounter(0)
,   m_fReadRate(1)
,   m_nHopRate(m_nWindowSize)
,   m_bDefaultHopRate(true)
,   m_bDataHasChanged(false)
{
}

//////////////////////////////////////////////////////////////////////////////////////////
// Access
//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::setHopRate(const size_t nHopRate)
{
    m_nHopRate = nHopRate;
    m_bDefaultHopRate = false;
}

//////////////////////////////////////////////////////////////////////////////////////////

template<class T>
void CircularBuffer<T>::setWindowSize(size_t nWindowSize)
{
    if (m_bDefaultHopRate)
    {
        m_nHopRate = m_nWindowSize;
    }
    
    m_bDataHasChanged = true;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::setHopSize(const size_t nHopSize)
{
    m_nHopSize = nHopSize;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::setWriteOffset(size_t nOffset)
{
    m_nWritePosition += nOffset;
    m_nWritePosition %= m_nWindowSize;
};

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::setReadOffset(size_t nOffset)
{
    m_nReadPosition += nOffset;
    m_nReadPosition %= m_nWindowSize;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Access
//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::write(T aValue)
{
    size_t nOverlapSize = m_nWindowSize - m_nHopSize;
    if (m_bOverlapAdd && m_nWriteCounter < nOverlapSize)
    {
        m_aBuffer[m_nWritePosition] += aValue;
    }
    else
    {
        m_aBuffer[m_nWritePosition] = aValue;
    }
        
    incrementCursor(m_nWritePosition);
    
    ++m_nWriteCounter;
    if(m_nWriteCounter == m_nWindowSize)
    {
        if (m_bAutoHopWrite)
        {
            hopWrite();
        }
        m_nWriteCounter = 0;
    }
    
    m_bDataHasChanged = true;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T CircularBuffer<T>::read()
{
    size_t nTmpReadPosition = m_nReadPosition;
    
    incrementCursor(m_nReadPosition, m_fReadRate);
    
    m_nReadCounter += m_fReadRate;
    if(m_nReadCounter >= m_nWindowSize)
    {
        if (m_bAutoHopRead)
        {
            hopRead();
        }
        m_nReadCounter %= m_nWindowSize;
    }
    
    return m_aBuffer[nTmpReadPosition];
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::hopWrite()
{
    m_nHoppedWritePosition += m_nHopSize;
    m_nHoppedWritePosition %= m_nWindowSize;
    
    m_nWritePosition = m_nHoppedWritePosition;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::hopRead()
{
    m_nHoppedReadPosition += m_nHopSize;
    m_nHoppedReadPosition %= m_nWindowSize;
    
    m_nReadPosition = m_nHoppedReadPosition;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::clear()
{
    m_aBuffer.clear();
    m_aContiguousBuffer.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void CircularBuffer<T>::incrementCursor(size_t& nCursor, float fIncrement)
{
    nCursor += fIncrement;
    
    if (nCursor >= m_nWindowSize)
    {
        nCursor %= m_nWindowSize;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

template class CircularBuffer<float>;
