#pragma once

#include "./list.h"
#include "./new.h"
#include "./assert.h"

#define HAS_BPP_OBSERVERS(classname)

namespace bpp
{
namespace ulib
{

template <typename T>
class ObserverSubject
{
public:
    typedef List<T*> TObserverList;
    typedef typename TObserverList::iterator TObserverIterator;

    ObserverSubject()
    {
        TObserverList* mplObservers;
        observersList(mplObservers);
        mplObservers = new MY_HEAP_MANAGER TObserverList(true);
        BPP_ASSERT(mplObservers)
    }

    bool registerObserver(T* pObserver);
    bool unregisterObserver(T* pObserver);

protected:
    virtual void firstObserver(TObserverIterator& it){it = (mplObservers)->begin();}

private:
    TObserverList* mplObservers;
};

template <class T>
bool ObserverSubject<T>::registerObserver(T* pObserver)
{
    if ( mplObservers->find(pObserver).hasValidValue() )
    {
        return false;
    }
    mplObservers->add(pObserver);
    return true;
}

template <class T>
bool ObserverSubject<T>::unregisterObserver(T* pObserver)
{
    TObserverIterator it = mplObservers->find(pObserver);
    if ( ! it.hasValidValue() )
    {
        return false;
    }
    mplObservers->erase(it);
    return true;
}

#define HAS_OBSERVERS(observer)\
    private:\
        bpp::ulib::List<observer*>* get_##observer##_list(){static bpp::ulib::List<observer*>* lst = nullptr; if (lst == nullptr){ lst= new MY_HEAP_MANAGER bpp::ulib::List<observer*>(true); BPP_ASSERT(lst);} return lst; }\
    protected:\
        void firstObserver(bpp::ulib::List<observer*>::iterator& it){bpp::ulib::List<observer*>* lst = get_##observer##_list(); it = lst->begin();}\
        typedef bpp::ulib::List<observer*> TObserverList;\
        typedef typename TObserverList::iterator TObserverIterator;\
    public:\
        bool registerObserver(observer* pObserver){\
            bpp::ulib::List<observer*>* lst= get_##observer##_list();\
            if ( lst->find(pObserver).hasValidValue() ){ return false;}\
            lst->add(pObserver);\
            return true;\
            }\
        bool unregisterObserver(observer* pObserver)\
        {\
            bpp::ulib::List<observer*>* lst= get_##observer##_list();\
            bpp::ulib::List<observer*>::iterator it =  lst->find(pObserver);\
            if ( ! it.hasValidValue() )\
            {\
                return false;\
              }\
         lst->erase(it);\
        return true;\
        }\
        private:


#define NOTIFY_OBSERVERS(iface, method)\
{iface::TObserverIterator it; iface::firstObserver(it); while(it.hasValidValue()){(*it)->method; it.forward();}}

#define NOTIFY_OBSERVERS_FOR(pobj, iface, method)\
{iface::TObserverIterator it; pobj->iface::firstObserver(it); while(it.hasValidValue()){(*it)->method; it.forward();}}

}}// namespace
