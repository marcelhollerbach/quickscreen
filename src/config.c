#include "e.h"
#include "quickscreen.h"

static Evas_Object *
_create(E_Config_Dialog *cfd, Evas *evas, E_Config_Dialog_Data *cfdata)
{
   Evas_Object *o = elm_label_add(cfd->dia->win);
   elm_object_text_set(o, "TODO");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);

   return o;
}

static int
_apply(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
  return 1;
}

static int
_check(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata EINA_UNUSED)
{
   return 1;
}

E_Config_Dialog*
quickscreen_settings(Evas_Object *parent, const char *params)
{
   E_Config_Dialog *cfd;
   E_Config_Dialog_View *v;

   if (e_config_dialog_find("E", "screen/screen_setup")) return NULL;
   if (!(v = E_NEW(E_Config_Dialog_View, 1))) return NULL;

   /* set dialog view functions & properties */
   v->basic.create_widgets = _create;
   v->basic.apply_cfdata   = _apply;
   v->basic.check_changed  = _check;
   quickscreen_advanced_setup(v);

   /* create new dialog */
   cfd = e_config_dialog_new(NULL, "Screen Setup",
                             "E", "screen/screen_setup2",
                             "preferences-system-screen-resolution",
                             0, v, (void *)params);
   return cfd;
}
