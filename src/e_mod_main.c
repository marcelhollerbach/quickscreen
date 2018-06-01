#include "e.h"
#include "../config.h"/* module setup */

E_API E_Module_Api e_modapi =
{
   E_MODULE_API_VERSION,
     "YOUR MODULE"
};

E_API void *
e_modapi_init(E_Module *m)
{
  /* your code-init */

  return m;
}

E_API int
e_modapi_shutdown(E_Module *m EINA_UNUSED)
{
   /* your code-shutdown */

   return 1;
}

E_API int
e_modapi_save(E_Module *m EINA_UNUSED)
{
   /* your code-save */
   return 1;
}
