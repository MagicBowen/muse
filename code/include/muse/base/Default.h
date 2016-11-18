#ifndef H05B2224D_B926_4FC0_A936_77B52B8A98DB
#define H05B2224D_B926_4FC0_A936_77B52B8A98DB

#include <muse/muse.h>

MUSE_NS_BEGIN

namespace details
{
   template <typename T>
   struct DefaultValue
   {
      static T value()
      {
         return T();
      }
   };

   template <typename T>
   struct DefaultValue<T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <typename T>
   struct DefaultValue<const T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <>
   struct DefaultValue<void>
   {
      static void value()
      {
      }
   };
}

#define DEFAULT(type, method)  \
    virtual type method { return ::MUSE_NS::details::DefaultValue<type>::value(); }

MUSE_NS_END

#endif

