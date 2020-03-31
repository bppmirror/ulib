/**
* MIT License
*
* Copyright (c) 2019- Yuriy Momotyuk (yurkis.bpp@gmail.com)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice (including the next
* paragraph) shall be included in all copies or substantial portions of the
* Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
* OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "./new.h"
#include "./mutex.h"
#include "./locker.h"
#include "./asrt.h"
#include "./log.h"

namespace bpp
{
namespace ulib
{

//! List container class
template <typename T> class List
{
private:

    //! Internal list entry data structure
    typedef struct _SListEntry
    {

        //! Constructor
        _SListEntry(const T& rtValue):mpPrevious(nullptr), mpNext(nullptr), mEntry(rtValue){}

        _SListEntry* mpPrevious; ///< Previous entry
        _SListEntry* mpNext;     ///< Next entry
        T            mEntry;     ///< Value
    }SListEntry;

    SListEntry* mpTop; ///< Top of the list (pointer to first element)
    SListEntry* mpEnd; ///< Bottom of the list (pointer to last element)
    bpp::os::IMutex* mpMutex; ///< Mutex

    ///////////////////////////////// iterator //////////////////
    //! Base iterator template
    template <typename R>
    struct _base_iterator
    {
        //! Constructor
        _base_iterator(SListEntry* pEntry = nullptr, List<T>* pList = nullptr):mpEntry(pEntry),mpList(pList)
        {}
        //////////////////
        R& operator*()  {BPP_ASSERT(mpEntry) return mpEntry->mEntry;}

        /////////////////
        R* operator->() {BPP_ASSERT(mpEntry) return &mpEntry->mEntry;}

        ////////////////
        _base_iterator<R> operator++()
            {if (mpEntry) {mpEntry = mpEntry->mpNext;}return *this;}
        /////////////////
        _base_iterator<R> operator--()
            { if (mpEntry) { mpEntry = mpEntry->mpPrevious;}
              else {if (mpList) mpEntry = mpList->last().mpEntry;}
             return *this;}

        /////////////////
        bool operator== (_base_iterator<R> oth) const { return mpEntry == oth.mpEntry;}

        /////////////////
        bool operator!= (_base_iterator<R> oth) const { return mpEntry != oth.mpEntry;}

        /////////////////
        _base_iterator<R> operator++(int)
            { _base_iterator<R> ret=*this;
              if (mpEntry){ mpEntry = mpEntry->mpNext;} return ret; }

        /////////////////
        _base_iterator<R> operator--(int)
            { _base_iterator<R> ret= _base_iterator<R>(mpEntry, mpList);
              if (mpEntry){ mpEntry = mpEntry->mpPrevious;}
              else {if (mpList) mpEntry = mpList->last().mpEntry;}
              return ret; }

        /////////////////
        void forward()
            {
                BPP_ASSERT(mpList)
                mpList->forward(*this);
            }

        /////////////////
        void backward()
            {
                BPP_ASSERT(mpList)
                mpList->backward(*this);
            }

        //! Return true if iterator points to valid value
        bool hasValidValue() {return mpEntry != nullptr;}

        //! Get pointer to list object
        List<T>* list(){return mpList;}

        private:
             SListEntry* mpEntry;
             List<T>*    mpList;

             friend bpp::ulib::List<T>;
    };
public:

    //! Constant iterator type
    typedef _base_iterator<const T> const_iterator;
    //! Iterator type
    typedef _base_iterator<T> iterator;


public:

    /** Constructor
     * If  isSynchronous param is set to true List will work in synchronous mode
     *
     * @param isSynchronous (true by default) - if true - list will work much slower but list will be thread safe
     */
    List(bool isSynchronous = true) {mpTop = nullptr; mpEnd= nullptr; if (isSynchronous) mpMutex = bpp::os::IMutex::instance(); else mpMutex = nullptr;}

    /** Add value to the end of the list
     *
     * @param Value - value to add
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return true is success
     */
    bool add(const T& Value, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Add value to the end of the list
     *
     * @param Value - value to add
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return true is success
     */
    bool pushBack(const T& Value, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL)
        {return add(Value, MMode);}


    /** Add value to the begining of the list
     *
     * @param Value - value to add
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return true is success
     */
    bool pushFront(const T& Value, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Insert value before iterator position
     *
     * @param it - iterator
     * @param val - value to insert
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return true is success
     */
    bool insert(iterator& it, const T& val,
                bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Insert value after iterator position
     *
     * @param it - iterator
     * @param val - value to insert
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return true is success
     */
    bool insertAfter(iterator& it, const T& val,
                     bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Adds element from C array
     *
     *  @param pArray - pointer to array
     *  @param Count - count of elements
     *  @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     *  @return true is success
     */
    bool addCArray(const T* pArray, size_t Count, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** List size
     *
     * @return list elements count
     *
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     */
    size_t size(bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Check is list empty
     *
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return treu is list is empty
     */
    bool empty() {return (mpTop == nullptr); }

    /** Find value
     * Find value in list from the begining
     *
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Iterator that point to just found value or to List.end() if not found
     */
    iterator find(const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Find value
     * Find value in list from the iterator position in forward direction
     *
     * @param it - iterator to start search
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Iterator that point to just found value or to List.end() if not found
     */
    iterator findNext(iterator it, const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Find value
     * Find value in list from the iterator position in backward direction
     *
     * @param it - iterator to start search
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Iterator that point to just found value or to List.end() if not found
     */
    iterator findPrevious(iterator it, const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Find value (constant iterator)
     * Find value in list from the begining with constant iterator
     *
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Constant iterator that point to just found value or to List.end() if not found
     */
    const_iterator constFind(const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Find value (constant iterator)
     * Find value in list from the iterator position in forward direction
     *
     * @param it - iterator to start search
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Constant iterator that point to just found value or to List.end() if not found
     */
    const_iterator findNext(const_iterator it, const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Find value (constant iterator)
     * Find value in list from the iterator position in backward direction
     *
     * @param it - iterator to start search
     * @param val - value to find
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return Constant iterator that point to just found value or to List.end() if not found
     */
    const_iterator findPrevious(const_iterator it, const T& val, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Check is list has some value
     *
     * @param val - value to check
     *
     * @return true if List has at least one entry with val value
     */
    bool has(const T& val) {return constFind(val) != this->constEnd();}

    /** Remove list element
     *
     * @param it - iterator that point to element to remove
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return next element after just removed
     */
    iterator erase(iterator& it, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Clear list
     *
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     */
    void clear(bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    //! Get iterator to the first element
    iterator begin() {return iterator(mpTop, this);}

    //! Get iterator after last list element
    iterator end()   {return iterator(nullptr, this);}

    //! Get iterator to last valid list element
    iterator last()  {return iterator(mpEnd, this);}

    //! Get constant iterator to the first element
    const_iterator constBegin() {return const_iterator(mpTop, this);}

    //! Get constant iterator after last list element
    const_iterator constEnd() {return const_iterator(nullptr, this);}

    //! Get constant iterator to last valid list element
    const_iterator constLast() {return const_iterator(mpEnd, this);}

    /** Get value in synchronous mode
     *
     * Function do the same as *it operation byt protected by mutex
     *
     * @param it - iterator that point to value
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return list element value reference
     */
    T& val(iterator it, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Get constant value in synchronous mode
     *
     * Function do the same as *it operation but protected by mutex
     *
     * @param it - iterator that point to value
     * @param MMode - if List is in synchrounous mode and you use this function from isr handler set this param to bpp::os::IMutex::eMUTEX_ISR
     *
     * @return list element value constant reference
     */
    const T& val(const_iterator it, bpp::os::IMutex::EMode MMode = bpp::os::IMutex::eMUTEX_NORMAL);

    /** Move iterator forward
     *
     * Function do the same as it++ but but protected by mutex
     *
     * @param [in][out] it - iterator
     */
    void forward(iterator& it){BPP_ASSERT(it.list() == this) if (!mpMutex){ it++;} else {bpp::ulib::MutexLocker locker(mpMutex); (void)locker; it++;}}

    /** Move constant iterator forward
     *
     * Function do the same as it++ but but protected by mutex
     *
     * @param [in][out] it - iterator
     */
    void forward(const_iterator& it){BPP_ASSERT(it.list() == this) if (!mpMutex){ it++;} else {bpp::ulib::MutexLocker locker(mpMutex); (void)locker; it++;}}

    /** Move iterator backward
     *
     * Function do the same as it-- but but protected by mutex
     *
     * @param [in][out] it - iterator
     */
    void backward(iterator& it){BPP_ASSERT(it.list() == this) if (!mpMutex){ it--;} else {bpp::ulib::MutexLocker locker(mpMutex); (void)locker; it--;}}

    /** Move constant iterator backward
     *
     * Function do the same as it-- but but protected by mutex
     *
     * @param [in][out] it - iterator
     */
    void backward(const_iterator& it){BPP_ASSERT(it.list() == this) if (!mpMutex){ it--;} else {bpp::ulib::MutexLocker locker(mpMutex); (void)locker; it--;}}

    //! Check if lists are equal
    bool operator==(List<T>& oth);

    //! Check if lists are not equal
    bool operator!=(List<T>& oth);

    //! Destructor
    ~List()
    {
        clear();
    }

#ifdef BPP_UNIT_TESTS
    //! Out sizes related information to log
    static void outSizes();
#endif
};
//////////////////////////////////////////////////////////////////////////////
template <typename T> bool List<T>::add(const T& Value, os::IMutex::EMode MMode)
{
    SListEntry* pEntry = new MY_HEAP_MANAGER List<T>::SListEntry(Value);
    BPP_ASSERT(pEntry)
    if (mpMutex) mpMutex->lock(MMode);
    if (!mpTop)
    {
        mpTop = pEntry;
        mpEnd = pEntry;
    }
    else
    {
        BPP_ASSERT(mpEnd)
        mpEnd->mpNext = pEntry;
        pEntry->mpPrevious = mpEnd;
        mpEnd = pEntry;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::pushFront(const T& Value, os::IMutex::EMode MMode)
{
    SListEntry* pEntry = new MY_HEAP_MANAGER List<T>::SListEntry(Value);
    BPP_ASSERT(pEntry)
    if (mpMutex) mpMutex->lock(MMode);
    if (!mpTop)
    {
        mpTop = pEntry;
        mpEnd = pEntry;
    }
    else
    {
        BPP_ASSERT(mpEnd)
        mpTop->mpPrevious = pEntry;
        pEntry->mpNext = mpTop;
        mpTop = pEntry;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::insert(iterator& it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    SListEntry* pEntry = new MY_HEAP_MANAGER List<T>::SListEntry(val);

    if (mpTop == nullptr)
    {
        BPP_ASSERT(mpEnd)
        if (mpMutex) mpMutex->lock(MMode);
        mpTop = pEntry;
        mpEnd = pEntry;
        if (mpMutex) mpMutex->unlock(MMode);
        return true;
    }
    // if not empty list

    SListEntry* pPrevEntry;// = it.mpEntry;
    if (it == this->end())
    {
        // if call insert when it = list::end() - insert BEFORE list::end()
        if (mpMutex) mpMutex->lock(MMode);
        pPrevEntry = mpEnd;
        mpEnd = pEntry;
        pPrevEntry->mpNext = pEntry;
        pEntry->mpPrevious = pPrevEntry;
    }
    else
    {
        if (mpMutex) mpMutex->lock(MMode);
        if (it.mpEntry->mpPrevious == nullptr)
        {
            //if call insert when it = list::begin() - insert BEFORE list::begin()
            pPrevEntry = mpTop;
            mpTop = pEntry;
            pEntry->mpNext = pPrevEntry;
        }
        else
        {
            BPP_ASSERT(mpEnd)
            pPrevEntry = it.mpEntry->mpPrevious;
            pEntry->mpNext = pPrevEntry->mpNext;
            pEntry->mpPrevious = pPrevEntry;
            pPrevEntry->mpNext = pEntry;
        }
    }
    if (mpMutex) mpMutex->unlock(MMode);

    return true;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::insertAfter(iterator& it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (!(it.hasValidValue()) && ((mpTop != nullptr)|| (mpEnd != nullptr)))
    {
        return false;
    }
    SListEntry* pEntry = new MY_HEAP_MANAGER List<T>::SListEntry(val);
    if (mpMutex) mpMutex->lock(MMode);
    if (!mpTop)
    {
        mpTop = pEntry;
        mpEnd = pEntry;
    }
    else
    {
        /*if (it == this->end())
        {
            it = this->last();
        }*/
        BPP_ASSERT(mpEnd)
        pEntry->mpNext = it.mpEntry->mpNext;
        pEntry->mpPrevious = it.mpEntry;
        it.mpEntry->mpNext = pEntry;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::addCArray(const T* pArray, size_t Count, bpp::os::IMutex::EMode MMode)
{
    bool ret = true;
    for (size_t i=0; i<Count; i++)
    {
        ret&= this->add(pArray[i], MMode);
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
size_t List<T>::size(bpp::os::IMutex::EMode MMode)
{
    if (mpMutex) mpMutex->lock(MMode);
    if ((!mpTop) || (!mpEnd))
    {
        if (mpMutex) mpMutex->unlock(MMode);
        return 0;
    }
    size_t cnt =0;
    iterator it = this->begin();
    while (it++!=this->end()){cnt++;}
    if (mpMutex) mpMutex->unlock(MMode);
    return cnt;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::iterator List<T>::find(const T& val, os::IMutex::EMode MMode)
{
    return this->findNext(this->begin(), val, MMode);

}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::iterator List<T>::findNext(List<T>::iterator it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (mpMutex) mpMutex->lock(MMode);
    while (it!=this->end())
    {
        if ((*it) == val) break;
        it++;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return it;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::iterator List<T>::findPrevious(List<T>::iterator it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (mpMutex) mpMutex->lock(MMode);
    it--;
    while (it!=this->end())
    {
        if ((*it) == val) break;
        it--;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return it;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::const_iterator List<T>::constFind(const T& val, bpp::os::IMutex::EMode MMode)
{
    return this->findNext(this->constBegin(), val, MMode);

}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::const_iterator List<T>::findNext(List<T>::const_iterator it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (mpMutex) mpMutex->lock(MMode);
    while (it!=this->constEnd())
    {
        if ((*it) == val) break;
        it++;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return it;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::const_iterator List<T>::findPrevious(List<T>::const_iterator it, const T& val, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (mpMutex) mpMutex->lock(MMode);
    it--;
    while (it!=this->constEnd())
    {
        if ((*it) == val) break;
        it--;
    }
    if (mpMutex) mpMutex->unlock(MMode);
    return it;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
typename List<T>::iterator List<T>::erase(iterator &it, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.hasValidValue()) //TODO: check!!! maybe better is to return List.end()
    BPP_ASSERT(it.list() == this)
    if (mpMutex) mpMutex->lock(MMode);
    if (it.mpEntry->mpNext != nullptr)
    {
        it.mpEntry->mpNext->mpPrevious = it.mpEntry->mpPrevious;
    }
    else
    {
        mpEnd = it.mpEntry->mpPrevious;
    }
    if (it.mpEntry->mpPrevious != nullptr)
    {
        it.mpEntry->mpPrevious->mpNext = it.mpEntry->mpNext;
    }
    else
    {
        mpTop = it.mpEntry->mpNext;
    }

    List<T>::iterator ret (it.mpEntry->mpNext, this);
    if (mpMutex) mpMutex->unlock(MMode);
    delete it.mpEntry;

    it.mpEntry = nullptr;             // I'M PARANOID AND I DONT BELEIVE IN PEOPLE

    return ret;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
void List<T>::clear(bpp::os::IMutex::EMode MMode)
{
    if (mpMutex) mpMutex->lock(MMode);

    SListEntry* pEntry = mpTop;
    while(pEntry)
    {
        SListEntry* pNext = pEntry->mpNext;
        delete pEntry;
        pEntry = pNext;
    }
    mpTop = nullptr;
    mpEnd = nullptr;

    if (mpMutex) mpMutex->unlock(MMode);
}

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T& List<T>::val(List::iterator it, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (!mpMutex)
    {
        return *it;
    }
    bpp::ulib::MutexLocker locker(mpMutex, true, MMode);
    (void)locker;
    return *it;
}

//////////////////////////////////////////////////////////////////////////////
template<typename T>
const T& List<T>::val(List::const_iterator it, bpp::os::IMutex::EMode MMode)
{
    BPP_ASSERT(it.list() == this)
    if (!mpMutex)
    {
        return *it;
    }
    bpp::ulib::MutexLocker locker(mpMutex, true, MMode);
    (void)locker;
    return *it;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::operator==(List<T>& oth)
{
    if (mpMutex) mpMutex->lock();
    List<T>::const_iterator my_it = this->constBegin();
    List<T>::const_iterator other_it = oth.constBegin();

    while ((my_it != this->constEnd()) && (other_it != oth.constEnd()))
    {
        if ((*my_it++) != (*other_it++))
        {
            if (mpMutex) mpMutex->unlock();
            return false;
        }
    }
    bool retVal = (my_it == this->constEnd()) && (other_it == oth.constEnd());
    if (mpMutex) mpMutex->unlock();
    return retVal;
}

//////////////////////////////////////////////////////////////////////////////
template <typename T>
bool List<T>::operator!=(List<T>& oth)
{
    if (mpMutex) mpMutex->lock();
    List<T>::const_iterator my_it = this->constBegin();
    List<T>::const_iterator other_it = oth.constBegin();

    while ((my_it != this->constEnd()) && (other_it != oth.constEnd()))
    {
        if ((*my_it++) != (*other_it++))
        {
            if (mpMutex) mpMutex->unlock();
            return true;
        }
    }
    bool retVal = (my_it != this->constEnd()) || (other_it != oth.constEnd());
    if (mpMutex) mpMutex->unlock();
    return retVal;
}

}}//namespace

namespace bpp
{
//! Operator that add ability to out list contains to log
template <class T>
bpp::LogOut& operator<<(bpp::LogOut& out, bpp::ulib::List<T>& val)
{
    out<<"["<<val.size()<<"] = {";
    typename bpp::ulib::List<T>::iterator it = val.begin();
    while (it != val.end())
    {
        out<<(*it++)<<" ;";
    }
    out<<"}\n";
    return out;
}
}

#ifdef BPP_UNIT_TESTS
#include "log.h"

template <typename T>
void bpp::ulib::List<T>::outSizes()
{
    MSG<<"List<size_t> instance : "<<sizeof(List<size_t>)<<"\n";
    MSG<<"List<size_t> entry    : "<<sizeof(List<size_t>::SListEntry)<<" ("<<(sizeof(List<size_t>::SListEntry) - sizeof(size_t))<<" + payload)\n";
    MSG<<"List<size_t>::iterator: "<<sizeof(List<size_t>::iterator)<<"\n";
}
#endif
