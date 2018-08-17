#include "e.h"
#include "quickscreen.h"

static E_Action* act;

int _quickscreen_log_domain = -1;

E_API E_Module_Api e_modapi = { E_MODULE_API_VERSION, "Quickscreen" };

static Evas_Object* popup;

static void
_block_clicked_cb(void* data EINA_UNUSED,
                  Evas_Object* obj,
                  void* event_info EINA_UNUSED)
{
  evas_object_del(popup);
  popup = NULL;

  e_comp_ungrab_input(1, 1);
}

void
key_down(void* data EINA_UNUSED,
         Evas* e EINA_UNUSED,
         Evas_Object* obj EINA_UNUSED,
         void* event_info)
{
  Evas_Event_Key_Down* ev = event_info;
  const char* k = ev->keyname;

  if (!strcmp(k, "Escape")) {
    if (popup) {
      evas_object_del(popup);
      popup = NULL;
      e_comp_ungrab_input(1, 1);
    }
  }
}

static void
display_popup(Evas_Object* content)
{
  if (popup) {
    evas_object_del(popup);
    popup = NULL;
    e_comp_ungrab_input(1, 1);
  }

  elm_config_focus_highlight_enabled_set(EINA_TRUE);
  
  popup = elm_popup_add(e_comp->elm);
  e_comp_grab_input(1, 1);

  elm_object_style_set(popup, "transparent");
  //     evas_object_layer_set(popup, E_LAYER_CLIENT_ABOVE);
  evas_object_layer_set(popup, E_LAYER_POPUP);

  evas_object_smart_callback_add(
    popup, "block,clicked", _block_clicked_cb, popup);

  evas_object_event_callback_add(
    popup, EVAS_CALLBACK_KEY_DOWN, key_down, popup);

  elm_object_content_set(popup, content);
  evas_object_show(popup);

  //////////////////

  // das muss sein :)
  evas_object_data_set(popup, "__data", NULL);
}

static void
qs_key(E_Object* obj EINA_UNUSED, const char* params EINA_UNUSED)
{
  Evas_Object* content;

  content = wizard_config_create(e_comp->elm);
  display_popup(content);

  printf("QUICKSCREEN\n");
}

E_API void*
e_modapi_init(E_Module* m)
{
  _quickscreen_log_domain = eina_log_domain_register("quickscreen", "red");

  act = e_action_add("qs_key");
  e_action_predef_name_set(
    "Quickscreen", "Show Quickscreen Popup", "qs_key", NULL, NULL, 0);
  act->func.go = qs_key;

  e_configure_registry_item_add("extensions/quickscreen",
                                0,
                                "Quickscreen",
                                NULL,
                                "preferences-system-screen-resolution",
                                quickscreen_settings);

  return m;
}

E_API int
e_modapi_shutdown(E_Module* m EINA_UNUSED)
{
  /* your code-shutdown */

  E_FREE_FUNC(act, e_action_del);
  e_action_predef_name_del("Quickscreen", "qs_key");

  e_configure_registry_item_del("extensions/quickscreen");

  return 1;
}

E_API int
e_modapi_save(E_Module* m EINA_UNUSED)
{
  /* your code-save */
  return 1;
}
