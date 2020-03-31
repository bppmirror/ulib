#pragma once

#include "./mutex.h"
#include "./asrt.h"

namespace bpp
{
namespace ulib
{

class MutexLocker
{
public:
    /**
    * @brief MutexLocker - automatical mutex locker constructor
    *
    * @param pMutex - pointer to mutex
    * @param lockNow - true if start locked
    * @param MMode - mutex mode. If used in isr should be eMUTEX_ISR
    */
   MutexLocker(bpp::os::IMutex* pMutex, bool lockNow = true,
               bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL)
   {
       BPP_ASSERT(pMutex)
       mpMutex = pMutex;
       mMode = MMode;
       misLocked = false;
       if (lockNow)
       {
           this->lock();
           misLocked = true;
       }
   }

   /**
    * @brief Lock - lock mutex
    * @return
    */
   bool lock()
   {
       bool ret = mpMutex->lock(mMode);
       misLocked = true;
       return ret;
   }

   /**
    * @brief Lock - lock mutex
    * @return
    */
   bool unlock()
   {
       bool ret = mpMutex->unlock(mMode);
       misLocked = false;
       return ret;
   }


   /**
     * @brief Destructor - unlock mutex if locked
     */
   ~MutexLocker()
   {
       if (mpMutex && misLocked)
           mpMutex->unlock();
   }


private:
   bpp::os::IMutex* mpMutex;
   bool             misLocked;
   bpp::os::IMutex::EMode mMode;
};
}}
