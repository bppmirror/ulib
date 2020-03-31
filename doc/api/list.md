# List

Class **List** is double linked list similar to std::list container.

Similar means that ulib::List **has no excactly the same behaviour** as std::list!

## Quick API guide

### Synchronous mode. Synchronous API

**List** object by default work in synchronous mode. That means that most of List API will be protected by mutex. 
**But iterators is not protected by itself!** You should use those API to work in synchronous mode:

* *value&* **val**( *iterator* ) or *const value&* **val**( *const_iterator* ) - access to value by reference or constant reference
* **forward**(*iterator*) or **forward**( *const_iterator* ) - move iterator forward
* **backward**(*iterator*) or **backward**( *const_iterator* ) - move iterator backward

Mode may be changed by setting boolean param of constructor:

```C++
    bpp::ulib::List ThreadSafeList(true); // Synchronous mode, thread safe
    bpp::ulib::List ThreadUnsafeList(false); // Much faster but thread unsafe
```


```C++

    bpp::ulib::List MyList(true); //make synchronous list

    // Walking though the list
    bpp::ulib::List<int>::iterator it = MyList.begin();
    while(it != MyList.end())
    {
        // accessing to the elements the same as in std::list::iterator
        MSG<<MyList.val(it))<<bpp::LogOut::ENDL;
        MyList.forward(it);
    }

```

If you have no any reference to **List** instance but only iterator you can gat pointer to list by call **iterator.list()** method:
```C++

    bpp::ulib::List mylist(true); //make synchronous list

    // Walking though the list
    bpp::ulib::List<int>::iterator it = mylist.begin();
    while(it != mylist.end())
    {
        // accessing to the elements the same as in std::list::iterator
        MSG<<it.list()->val(it))<<bpp::LogOut::ENDL;
        it.list()->forward(it);
    }

```


### API similar to std::list:

* **add()** / **pushBack()** - add element to the end of the list
* **pushFront()** - add element to the begining of the list
* **begin()** / **end()** - get iterator that point to the first element / to the next from last element if the list
* **constBegin()** / **constEnd()** -  get constant iterator that point to the first element / to the next from last element if the list 
* **erase()** - remove element from the list. Get iterator as a pointer to element, return iterator that point to the nex element
* **clear()** - clear list content 

**Basic example:**

```C++
#include "list.h"
#include "log.h"
void main()
{
    // instance
    bpp::ulib::List<int> MyList;

    // adding elements
    MyList.add(1);
    MyList.add(2);

    // get count of elements
    MSG<<"Size of list: "<<MyList.size()<<bpp::LogOut::ENDL;
    // list is able to be out using ulib log
    MSG<<"List contents: "<<MyList<<bpp::LogOut::ENDL;

    // Walking though the list
    bpp::ulib::List<int>::iterator it = MyList.begin();
    while(it != MyList.end())
    {
        // accessing to the elements the same as in std::list::iterator
        MSG<<(*it++)<<bpp::LogOut::ENDL;
    }

    // Walking reverse order
    it = list.end();
    while (--it != list.constEnd())
    {
        MSG<<(*it)<<bpp::LogOut::ENDL;
    }

    it = list.begin();
    it = list.earse(i); // Remove first element (1). it point to next element - (2)

    // clear the list
    list.clear(); 
}
```

### Own API:

#### Search:

* *iterator* **find**(*value*) , *const_iterator* **find**(*value*) - search element from the begining of the list by *value*
* *iterator* **findNext**(*iterator*, *value*), *const_iterator* **findNext**(*const_iterator*, *value*)  - search element from *iterator* by *value*
* *iterator* **findPrevious**(*iterator*, *value*), *const_iterator* **findPrevious**(*const_iterator*, *value*)  search element from *iterator* by *value* in reverse order

if value was not found functions above returnes iterator that point to **List.end()** or **List.constEnd()**

```C++
    // instance
    bpp::ulib::List<int> MyList;

    // adding elements
    MyList.add(1);
    MyList.add(2);

    bpp::ulib::List<int>::iterator it = List.find(1); // Found. Point to first list element
    bpp::ulib::List<int>::iterator it = List.findNext(it, 1); //Not found. Point to List.end()
    
```

#### Other

* **insertAfter**(*iterator* , *value*) -insert *value* after *iterator*
* **has**(*value*) - return true if list has at least one *value*
* **addCArray**(*array_ptr*, *count*) - adds to the end of the list C array. *array_ptr* points to array with *count* elements

## Memory footprint:

### amd64:

```
size_t     : 8
List<size_t> instance : 24
List<size_t> entry    : 24 (16 + payload)
List<size_t>::iterator: 16

```

### arm:

```
size_t     : 4
List<size_t> instance : 12
List<size_t> entry    : 12 (8 + payload)
List<size_t>::iterator: 8

```




