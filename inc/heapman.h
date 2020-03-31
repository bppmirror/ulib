#pragma once

#include <stdlib.h>

namespace bpp
{
namespace ulib
{

class IHeapManager
{
public:

    //! Heap info structure
    typedef struct _SHeapState
    {
        _SHeapState():mMallocCount(0), mFreeCount(0), mFreeSpace(0), mCapacity(0){}
        int mMallocCount;  ///< Count of malloc() calls
        int mFreeCount;    ///< Count of free() calls
        long mFreeSpace;   ///< Free space in heap
        long mCapacity;    ///< Overall heap capacity
    }SHeapState;

    /** Allocate memory
     *
     * @param size - size of memory to allocate
     *
     * @return address or nullptr if was not succeed
     */
    virtual void* malloc(size_t size)=0;

    /** Free memory
     *
     * @param p - pointer to memory to free
     */
    virtual void  free(void* p)=0;

    /** Changes the size of the memory block
     *
     * @param p - pointer to memory block
     * @param new_size - new block size
     *
     * @return A pointer to the reallocated memory block or nullptr if was not succeees
     */
    virtual void* realloc(void* p, size_t new_size)=0;

    //! Get heap state
    virtual SHeapState state()=0;

public:
    virtual ~IHeapManager(){}
};

//! Get default heap manager
IHeapManager* defaultHM();

}} // namespace
