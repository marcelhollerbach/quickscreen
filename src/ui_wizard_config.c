#include "e.h"
#include "quickscreen.h"
#include <string.h>

typedef struct {

} Local_Data;

#define SCOPE_DATA(o) Local_Data *pd = evas_object_data_get(o, "__data");

Evas_Object*
wizard_config_create(Evas_Object *win)
{
   Local_Data *pd = E_NEW(Local_Data, 1);

   Evas_Object *o = elm_gengrid_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_data_set(o, "__data", pd);

   return o;
}

void
wizard_config_apply(Evas_Object *obj)
{
   SCOPE_DATA(obj);
}
