# uLib API documentation

## Init and configuration

At first you should perform uLib init. **Right now** it is optional step but in future this behaviour **may be changed**

To init uLib you should include ***ulib.h*** header and call ***bpp::init()*** function.
You should pass pointer to ***bpp::ulib::SuLibSettings*** structure. If don't whant to fill it you can call ***bpp::ulib::autoSettings()*** to get default values depend on platform.

For simpliest case you should perform:
```C++
#include "ulib.h"

...
if ( !bpp::ulib::init( bpp::ulib::autoSettings ) )
{
	// something goes wrong
}

```

### bpp::ulib::SuLibSettings structure

By this structure you can customize many aspects of uLib work. Take a look at structure members:

* ***mASSERTCallback*** - callback that will be called on failed assertion

* ***mOutputHandler*** - logger output handler (you can add another one or remove this by bpp::Log API)

* ***mStdFn*** - structure stores pointers to standard C memory related function (like memcpy) implementation

## uLib API
**General:**

* [**Memory management**](./mem.md)
* [**Logger**](./log.md)
* [**Assertions**](./assert.md)

**Basic containers:**

* [**List**](./list.md)
* [**String**](./string.md)

**Utils**

* [**AutoPtr**](./autoptr.md)
* [**MutexLocker**](./mutexlocker.md)