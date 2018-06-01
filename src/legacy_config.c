#include "e.h"
#include "quickscreen.h"

struct _E_Config_Dialog_Data {
   Evas_Object *advanced;
   Evas_Object *wizard;
};

static void
_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   e_config_dialog_changed_set(data, EINA_TRUE);
}

static Evas_Object *
_basic_create(E_Config_Dialog *cfd, Evas *evas, E_Config_Dialog_Data *cfdata)
{
   e_dialog_resizable_set(cfd->dia, 1);

   cfdata->wizard = wizard_config_create(cfd->dia->win);
   evas_object_smart_callback_add(cfdata->wizard, "changed", _changed_cb, cfd);

   return cfdata->wizard;
}

static int
_basic_apply(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
  wizard_config_apply(cfdata->wizard);
  return 1;
}

static int
_basic_check(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata EINA_UNUSED)
{
   return 1;
}


static Evas_Object *
_advanced_create(E_Config_Dialog *cfd, Evas *evas EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
   e_dialog_resizable_set(cfd->dia, 1);

   cfdata->advanced = advanced_settings_create(cfd->dia->win);
   evas_object_smart_callback_add(cfdata->advanced, "changed", _changed_cb, cfd);

   return cfdata->advanced;
}

static int
_advanced_apply(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
  advanced_settings_apply(cfdata->advanced);
  return 1;
}

static int
_advanced_check(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
  return 1;
}

static void *
_create_data(E_Config_Dialog *cfd EINA_UNUSED)
{
   return E_NEW(E_Config_Dialog, 1);
}

static void
_free_data(E_Config_Dialog *cfd EINA_UNUSED, E_Config_Dialog_Data *cfdata)
{
   free(cfdata);
}

E_Config_Dialog*
quickscreen_settings(Evas_Object *parent, const char *params)
{
   E_Config_Dialog *cfd;
   E_Config_Dialog_View *v;

   if (e_config_dialog_find("E", "screen/screen_setup")) return NULL;
   if (!(v = E_NEW(E_Config_Dialog_View, 1))) return NULL;

   /* set dialog view functions & properties */
   v->create_cfdata = _create_data;
   v->free_cfdata = _free_data;
   v->basic.create_widgets = _basic_create;
   v->basic.apply_cfdata   = _basic_apply;
   v->basic.check_changed  = _basic_check;
   v->advanced.create_widgets = _advanced_create;
   v->advanced.apply_cfdata = _advanced_apply;
   v->advanced.check_changed = _advanced_check;

   /* create new dialog */
   cfd = e_config_dialog_new(NULL, "Screen Setup",
                             "E", "screen/screen_setup2",
                             "preferences-system-screen-resolution",
                             0, v, (void *)params);
   return cfd;
}
