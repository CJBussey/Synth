
#pragma once

#include <vector>

///////////////////////////////////////////////////////////////////////////////

template <class T>
class WavetableBuffer
{
public:
    WavetableBuffer(const size_t nSize = 0, const float fPhaseInc = 1.);
    size_t size();
    void setIncrement(const float fPhaseInc);
    
    T& operator()();
    T& operator[](const size_t nIndex);
    void operator++();
    
private:
    // Members
    std::vector<T> m_aBuffer;
    float m_fPhaseInc;
    float m_fReadIndex;
};

///////////////////////////////////////////////////////////////////////////////

template<class T>
WavetableBuffer<T>::WavetableBuffer(const size_t nSize, const float fPhaseInc)
:   m_aBuffer(nSize, 0)
,   m_fPhaseInc(fPhaseInc)
{
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
inline size_t WavetableBuffer<T>::size()
{
    return m_aBuffer.size();
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
inline void WavetableBuffer<T>::setIncrement(const float fPhaseInc)
{
    m_fPhaseInc = fPhaseInc;
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
T& WavetableBuffer<T>::operator[](const size_t nIndex)
{
    return m_aBuffer[nIndex];
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
T& WavetableBuffer<T>::operator()()
{
    float fTmpReadIndex = m_fReadIndex;
    operator++();
    // todo: interpolation
    return m_aBuffer[static_cast<size_t>(fTmpReadIndex)];
}

///////////////////////////////////////////////////////////////////////////////

template <class T>
void WavetableBuffer<T>::operator++()
{
    m_fReadIndex += m_fPhaseInc;
    if (m_fReadIndex >= m_aBuffer.size())
    {
        m_fReadIndex -= m_aBuffer.size();
    }
}

///////////////////////////////////////////////////////////////////////////////

typedef WavetableBuffer<float> FWavetableBuffer;
