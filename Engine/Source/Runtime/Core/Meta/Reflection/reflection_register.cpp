#include <assert.h>

#include "../json.h"
#include "reflection.h"
#include "reflection_register.h"
#include "../Serializer/serializer.h"




namespace Movan
{
    namespace Reflection
    {
        void TypeMetaRegister::Unregister() { TypeMetaRegisterinterface::unregisterAll(); }
    } // namespace Reflection
} // namespace Movan
