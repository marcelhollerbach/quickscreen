#include "config.h"
#include "e.h"
#include "quickscreen.h"
#include <string.h>

typedef struct
{

} Local_Data;

#define SCOPE_DATA(popup)                                                      \
  Local_Data* pd = evas_object_data_get(popup, "__data");


char* source_device;
char* target_device;
const char* lid_id;
const char* id;
const char* source_id;
const char* target_id;
int count = 0;


Evas_Object*
_content_source_devices(Evas_Object* parent);
Evas_Object*
_content_target_devices(Evas_Object* parent);
Evas_Object*
_content_modes(Evas_Object* parent);
Evas_Object*
_content_expand(Evas_Object* parent);

void
_page_source_devices(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED);
void
_page_target_devices(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED);
void
_page_modes(void* data,
            Evas_Object* obj EINA_UNUSED,
            void* event_info EINA_UNUSED);
void
_page_expand(void* data,
             Evas_Object* obj EINA_UNUSED,
             void* event_info EINA_UNUSED);

void
_focus_in_cb(void* data,
             Evas_Object* obj EINA_UNUSED,
             void* event_info EINA_UNUSED);
void
_focus_out_cb(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED);

static void
_cb_settings_screen_setup(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   e_configure_registry_call("screen/screen_setup", NULL, NULL);
}

static E_Config_Randr2_Screen*
_screen_config_randr_id_find(const char* id)
{
  Eina_List* l;
  E_Config_Randr2_Screen* cs;

  if (!id)
    return NULL;
  EINA_LIST_FOREACH(e_randr2_cfg->screens, l, cs)
  {
    if (!cs->id)
      continue;
    if (!strcmp(cs->id, id))
      return cs;
  }
  return NULL;
}


void
_set_relative(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED)
{
  E_Config_Randr2_Screen *cs, *cs_source;

  printf("DNAME SET DATA: %s\n\n", target_id);
  // 	        if (!cs2->id) continue;
  cs = _screen_config_randr_id_find(target_id);
  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(target_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }
  eina_stringshare_replace(&cs->rel_to, source_id);
  //         cs->rel_align = cs2->rel_align;
  //         cs->mode_w = cs2->mode_w;
  //         cs->mode_h = cs2->mode_h;
  //         cs->mode_refresh = cs2->mode_refresh;
  cs->rotation = 0;
  //         cs->priority = cs2->priority;
  // 		  		 cs->rel_to =
  // eina_stringshare_add("LVDS-1/00ffffffffffff00367f2500000000002d0c010490241400eaa8e099574b92251c505400000001010101010101010101010101010101403880b4703840403c3c550068c810000018403880807138aa408080880068c810000018000000fc004e76696469612044656661756c000000fc007420466c61742050616e656c00001f");
  
  cs->rel_mode = data;
  //         if (cs->profile) eina_stringshare_del(cs->profile);
  //         cs->profile = NULL;
  //         if (cs2->profile) cs->profile = eina_stringshare_add(cs2->profile);
  //         cs->scale_multiplier = cs2->scale_multiplier;
  //         printf("APPLY %s .... rel mode %i\n", cs->id, cs->rel_mode);
  //         cs->enabled = cs2->enabled;
  cs->enabled = EINA_TRUE;
  

  // enable source if off
  cs_source = _screen_config_randr_id_find(source_id);
  if (!cs_source) {
    cs_source = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs_source->id = eina_stringshare_add(source_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs_source);
  }
  if(cs_source->enabled == EINA_FALSE)
  {
	eina_stringshare_replace(&cs_source->rel_to, source_id);
	cs_source->rotation = 0;
	cs_source->rel_mode = E_RANDR2_RELATIVE_NONE;
	cs_source->enabled = EINA_TRUE;
  }
  
  e_randr2_config_save();
  e_randr2_config_apply();
  _block_clicked_cb(NULL, NULL, NULL);
}

void
_set_target_power_off(void* data EINA_UNUSED,
                     Evas_Object* obj EINA_UNUSED,
                     void* event_info EINA_UNUSED)
{

  E_Config_Randr2_Screen *cs, *cs2;

  cs = _screen_config_randr_id_find(target_id);

  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(target_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }

  eina_stringshare_replace(&cs->rel_to, target_id);

  cs->rotation = 0;

  cs->priority = 0;

  cs->rel_mode = E_RANDR2_RELATIVE_NONE;

  cs->enabled = EINA_FALSE;

  
  
  cs2 = _screen_config_randr_id_find(source_id);

  if (!cs2) {
    cs2 = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs2->id = eina_stringshare_add(source_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs2);
  }

  eina_stringshare_replace(&cs2->rel_to, source_id);

  cs2->rotation = 0;

  cs2->priority = 100;

  cs2->rel_mode = E_RANDR2_RELATIVE_NONE;

  cs2->enabled = EINA_TRUE;

  e_randr2_config_save();
  e_randr2_config_apply();
  _block_clicked_cb(NULL, NULL, NULL);
}

void
_set_source_power_off(void* data EINA_UNUSED,
                      Evas_Object* obj EINA_UNUSED,
                      void* event_info EINA_UNUSED)
{

  E_Config_Randr2_Screen *cs, *cs2;

  cs = _screen_config_randr_id_find(target_id);

  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }

  eina_stringshare_replace(&cs->rel_to, target_id);

  cs->rotation = 0;

  cs->priority = 100;

  cs->rel_mode = E_RANDR2_RELATIVE_NONE;

  cs->enabled = EINA_TRUE;

  cs2 = _screen_config_randr_id_find(source_id);

  if (!cs2) {
    cs2 = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs2->id = eina_stringshare_add(source_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs2);
  }

  eina_stringshare_replace(&cs2->rel_to, source_id);

  cs2->rotation = 0;

  cs2->priority = 0;

  cs2->rel_mode = E_RANDR2_RELATIVE_NONE;

  cs2->enabled = EINA_FALSE;

  e_randr2_config_save();
  e_randr2_config_apply();
  _block_clicked_cb(NULL, NULL, NULL);
}

void
_focus_in_cb(void* data, Evas_Object* obj, void* event_info EINA_UNUSED)
{
  evas_object_color_set(data, 51, 153, 255, 255);
  printf("FOCUS IN\n");
}

void
_focus_out_cb(void* data, Evas_Object* obj, void* event_info EINA_UNUSED)
{
  evas_object_color_set(data, 255, 255, 255, 255);
  printf("FOCUS OUT\n");
}

Evas_Object*
_content_modes(Evas_Object* parent)
{
  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt, *bt_b, *bt_a;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];

  tb_m = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 0);
  elm_table_pack(tb_m, rect, 0, 0, 1, 2);
  evas_object_size_hint_min_set(rect, 500, 300);
  evas_object_show(rect);

  tb_t = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_t, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //   evas_object_size_hint_weight_set(tb_t, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, tb_t, 0, 0, 1, 1);
  evas_object_show(tb_t);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, 0.5, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0.5);
  snprintf(buf,
           sizeof(buf),
           "<color=#ffffff><bigger>Select Mode</bigger><br>for %s</color>",
           target_device);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);

  bt_b = elm_button_add(parent);
  evas_object_color_set(bt_b, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_source_devices, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
    evas_object_smart_callback_add(bt_a, "clicked", _cb_settings_screen_setup,
    NULL);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  tb_c = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_box_pack_end(box_c, tb_c);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////
  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/clone.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 0, 1, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //     evas_object_smart_callback_add(bt, "clicked", _set_clone,
  evas_object_smart_callback_add(
    bt, "clicked", _set_relative,  (void*)E_RANDR2_RELATIVE_CLONE);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 0, 1, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, 0.5, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  elm_object_text_set(lbl, "<color=#ffffff><b>Clone</b></color>");
  elm_table_pack(tb_c, lbl, 0, 2, 1, 1);
  evas_object_show(lbl);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/expand.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 1, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt, "clicked", _page_expand, parent);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 1, 1, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  elm_object_text_set(lbl, "<color=#ffffff><b>Expand</b></color>");
  elm_table_pack(tb_c, lbl, 1, 2, 1, 1);
  evas_object_show(lbl);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/left.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 0, 4, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt, "clicked", _set_target_power_off, NULL);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 0, 4, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  snprintf(buf, sizeof(buf), "%s<color=#ffffff> Off</color>", target_device);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_c, lbl, 0, 5, 1, 1);
  evas_object_show(lbl);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/right.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 4, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt, "clicked", _set_source_power_off, NULL);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 1, 4, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  snprintf(buf, sizeof(buf), "%s<color=#ffffff> Off</color>", source_device);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_c, lbl, 1, 5, 1, 1);
  evas_object_show(lbl);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}

void
_set_target_id(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  target_id = (char*)data;
}

void
_set_source_id(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  source_id = (char*)data;
}

void
_set_target_device_name(void* data,
                 Evas_Object* obj EINA_UNUSED,
                 void* event_info EINA_UNUSED)
{
  target_device = data;
  printf("TARGET DEVICE NAME: %s\n", target_device);
}

void
_set_source_device_name(void* data,
                 Evas_Object* obj EINA_UNUSED,
                 void* event_info EINA_UNUSED)
{
  source_device = data;
  printf("SOURCE DEVICE NAME: %s\n", source_device);
}

void
_page_modes(void* data,
            Evas_Object* obj EINA_UNUSED,
            void* event_info EINA_UNUSED)
{
  Evas_Object *nf = NULL;;
  Evas_Object *content = NULL;
  nf = data;
  Elm_Object_Item* it;

  content = _content_modes(nf);

  it = elm_naviframe_item_push(nf, "Select Mode", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
}

Evas_Object*
_content_target_devices(Evas_Object* parent)
{
  Eina_List* l;
  E_Randr2_Screen* s;
  int x = 0;
  int i = 0;

  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt, *bt_a;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];
  char* device_info;

  tb_m = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 0);
  elm_table_pack(tb_m, rect, 0, 0, 1, 2);
  evas_object_size_hint_min_set(rect, 500, 300);
  evas_object_show(rect);

  tb_t = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_t, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //   evas_object_size_hint_weight_set(tb_t, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, tb_t, 0, 0, 1, 1);
  evas_object_show(tb_t);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0.5);
  elm_object_text_set(
    lbl,
    "<color=#ffffff><bigger>Select Target Device</bigger><br>to configure</color>");
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);

  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
    evas_object_smart_callback_add(bt_a, "clicked", _cb_settings_screen_setup,
    NULL);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  /// SCROLLER
//   Evas_Object* scroller = elm_scroller_add(box_c);
//   evas_object_size_hint_weight_set(
//     scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//   evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);

//   elm_box_pack_end(box_c, scroller);
//   evas_object_show(scroller);

  tb_c = elm_table_add(box_c);
  elm_table_padding_set(tb_c, 10, 10);
  evas_object_size_hint_align_set(tb_c, 0.5, 0.5);
  //   evas_object_size_hint_weight_set(tb_c, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////

  EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {

//     if (s->info.connected == EINA_TRUE && s->info.is_lid == EINA_TRUE) {
//       lid_id = s->id;
//       snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
//       pdevice = strdup(buf);
//     }
    if (s->info.connected == EINA_TRUE && s->info.is_lid == EINA_FALSE) {

      ic = elm_icon_add(tb_c);
      snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
      elm_image_file_set(ic, buf, NULL);
      evas_object_size_hint_min_set(
        ic, ELM_SCALE_SIZE(156), ELM_SCALE_SIZE(126));
      evas_object_size_hint_weight_set(ic, 0, 0);
      evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(tb_c, ic, x, 1, 1, 1);
      evas_object_show(ic);

      bt = elm_button_add(tb_c);
      evas_object_color_set(bt, 255, 255, 255, 0);
      evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
      evas_object_smart_callback_add(bt, "clicked", _page_source_devices, parent);

      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
      device_info = strdup(buf);
      evas_object_smart_callback_add(
        bt, "clicked", _set_target_device_name, device_info);
      evas_object_smart_callback_add(bt, "clicked", _set_target_id, s->id);
      evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
      evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
      elm_object_signal_callback_add(bt, "focused", "*", _focus_in_cb, NULL);
      elm_object_signal_callback_add(bt, "unfocused", "*", _focus_out_cb, NULL);
      elm_table_pack(tb_c, bt, x, 1, 1, 2);
      evas_object_show(bt);

      lbl = elm_label_add(tb_c);
      snprintf(buf,
               sizeof(buf),
               "<color=#ffffff>%s<br>%s</color>",
               s->info.screen,
               s->info.name);
      elm_object_text_set(lbl, buf);
      elm_table_pack(tb_c, lbl, x, 2, 1, 1);
      evas_object_show(lbl);

      i = 1;
      x++;
    }
  }
  if (i == 0) {
    ic = elm_icon_add(tb_c);
    snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
    elm_image_file_set(ic, buf, NULL);
    evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(156), ELM_SCALE_SIZE(126));
    evas_object_size_hint_weight_set(ic, 0, 0);
    evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(tb_c, ic, 0, 1, 1, 1);
    evas_object_show(ic);

    lbl = elm_label_add(tb_c);
    evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(
      lbl,
      "<color=#ffffff>NO EXTERNAL DEVICES FOUND<br><small>plugin a device<br>or restart 'E' using "
      "strg+alt+end to detect analog devices</small></color>");
    elm_table_pack(tb_c, lbl, 0, 2, 1, 1);
    evas_object_show(lbl);
  }

  elm_box_pack_end(box_c,  tb_c);
//   elm_object_content_set(scroller, tb_c);
//   elm_scroller_bounce_set(scroller, EINA_TRUE, EINA_FALSE);
//   elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
//   elm_scroller_propagate_events_set(scroller, EINA_TRUE);
//   elm_scroller_page_relative_set(scroller, 0, 1);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}


Evas_Object*
_content_source_devices(Evas_Object* parent)
{
  Eina_List* l;
  E_Randr2_Screen* s;
  int x = 0;
  int i = 0;

  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt, *bt_a, *bt_b;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];
  char* device_info;

  tb_m = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 0);
  elm_table_pack(tb_m, rect, 0, 0, 1, 2);
  evas_object_size_hint_min_set(rect, 500, 300);
  evas_object_show(rect);

  tb_t = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_t, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //   evas_object_size_hint_weight_set(tb_t, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, tb_t, 0, 0, 1, 1);
  evas_object_show(tb_t);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0.5);
  elm_object_text_set(
    lbl,
    "<color=#ffffff><bigger>Select Source Device</bigger><br>to use</color>");
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);
  
	bt_b = elm_button_add(parent);
  evas_object_color_set(bt_b, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_target_devices, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
    evas_object_smart_callback_add(bt_a, "clicked", _cb_settings_screen_setup,
    NULL);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  /// SCROLLER
//   Evas_Object* scroller = elm_scroller_add(box_c);
//   evas_object_size_hint_weight_set(
//     scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//   evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);

//   elm_box_pack_end(box_c, scroller);
//   evas_object_show(scroller);

  tb_c = elm_table_add(box_c);
  elm_table_padding_set(tb_c, 10, 10);
  evas_object_size_hint_align_set(tb_c, 0.5, 0.5);
  //   evas_object_size_hint_weight_set(tb_c, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////

  EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {

//     if (s->info.connected == EINA_TRUE && s->info.is_lid == EINA_TRUE) {
//       lid_id = s->id;
//       snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
//       pdevice = strdup(buf);
//     }
    if (s->info.connected == EINA_TRUE  && s->id != target_id/*&& s->info.is_lid == EINA_FALSE*/) {

      ic = elm_icon_add(tb_c);
      snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
      elm_image_file_set(ic, buf, NULL);
      evas_object_size_hint_min_set(
        ic, ELM_SCALE_SIZE(156), ELM_SCALE_SIZE(126));
      evas_object_size_hint_weight_set(ic, 0, 0);
      evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(tb_c, ic, x, 1, 1, 1);
      evas_object_show(ic);

      bt = elm_button_add(tb_c);
      evas_object_color_set(bt, 255, 255, 255, 0);
      evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
      evas_object_smart_callback_add(bt, "clicked", _page_modes, parent);

      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
      device_info = strdup(buf);
      evas_object_smart_callback_add(
        bt, "clicked", _set_source_device_name, device_info);
      evas_object_smart_callback_add(bt, "clicked", _set_source_id, s->id);
      evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
      evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
//       elm_object_signal_callback_add(bt, "focused", "*", _focus_in_cb, NULL);
//       elm_object_signal_callback_add(bt, "unfocused", "*", _focus_out_cb, NULL);
      elm_table_pack(tb_c, bt, x, 1, 1, 2);
      evas_object_show(bt);

      lbl = elm_label_add(tb_c);
      snprintf(buf,
               sizeof(buf),
               "<color=#ffffff>%s<br>%s</color>",
               s->info.screen,
               s->info.name);
      elm_object_text_set(lbl, buf);
      elm_table_pack(tb_c, lbl, x, 2, 1, 1);
      evas_object_show(lbl);

      i = 1;
      x++;
    }
  }
  if (x == 1) {
// 	  elm_obj_naviframe_item_pop();
  }
// 
  elm_box_pack_end(box_c, tb_c);
//   elm_object_content_set(scroller, tb_c);
//   elm_scroller_bounce_set(scroller, EINA_TRUE, EINA_FALSE);
//   elm_scroller_policy_set(
//     scroller, ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
//   elm_scroller_propagate_events_set(scroller, EINA_TRUE);
//   elm_scroller_page_relative_set(scroller, 0, 1);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}

void
_page_target_devices(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED)
{

  Evas_Object *content = NULL;
  Evas_Object *nf = NULL;;
  nf = data;
  Elm_Object_Item* it;

  content = _content_target_devices(nf);

  it = elm_naviframe_item_push(nf, "Select Target Device", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
}

void
_page_source_devices(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED)
{

  Evas_Object *content = NULL;
  Evas_Object *nf = NULL;
  nf = data;
  Elm_Object_Item* it;

  content = _content_source_devices(nf);

  it = elm_naviframe_item_push(nf, "Select Souce device", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
  evas_object_data_set(nf, "page1", it);
}


Evas_Object*
_content_expand(Evas_Object* parent)
{
  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt, *bt_b, *bt_a;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];

  tb_m = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 0);
  elm_table_pack(tb_m, rect, 0, 0, 1, 2);
  evas_object_size_hint_min_set(rect, 500, 300);
  evas_object_show(rect);

  tb_t = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_t, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //   evas_object_size_hint_weight_set(tb_t, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, tb_t, 0, 0, 1, 1);
  evas_object_show(tb_t);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, 0.5, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0.5);
  snprintf(
    buf,
    sizeof(buf),
    "<color=#ffffff><bigger>Select Expand Mode</bigger><br>for %s</color>",
    target_device);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);

  bt_b = elm_button_add(parent);
  evas_object_color_set(bt_b, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_modes, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
    evas_object_smart_callback_add(bt_a, "clicked", _cb_settings_screen_setup,
    NULL);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  tb_c = elm_table_add(parent);
  elm_table_homogeneous_set(tb_c, EINA_TRUE);
  elm_table_padding_set(tb_c, 1, 1);
  evas_object_size_hint_align_set(tb_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_c, 0, EVAS_HINT_EXPAND);
  elm_box_pack_end(box_c, tb_c);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////
  ///
  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/above.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 0, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(
    bt, "clicked", _set_relative,  (void*)E_RANDR2_RELATIVE_TO_ABOVE);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 1, 0, 1, 1);
  evas_object_show(bt);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/left_of.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, 1, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 0, 1, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(
    bt, "clicked", _set_relative,  (void*)E_RANDR2_RELATIVE_TO_LEFT);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 0, 1, 1, 1);
  evas_object_show(bt);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/monitor.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 1, 1, 1);
  evas_object_show(ic);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/right_of.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, 0, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 2, 1, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(
    bt, "clicked", _set_relative,  (void*)E_RANDR2_RELATIVE_TO_RIGHT);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 2, 1, 1, 1);
  evas_object_show(bt);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/below.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 2, 1, 1);
  evas_object_show(ic);

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(
    bt, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_TO_BELOW);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
  elm_table_pack(tb_c, bt, 1, 2, 1, 1);
  evas_object_show(bt);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}

void
_page_expand(void* data,
             Evas_Object* obj EINA_UNUSED,
             void* event_info EINA_UNUSED)
{
  Evas_Object *content = NULL;
  Evas_Object *nf = NULL;;
  nf = data;
  Elm_Object_Item* it;

  content = _content_expand(nf);

  it = elm_naviframe_item_push(
    nf, "Select Expand Mode", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
}

Evas_Object*
wizard_config_create(Evas_Object* win)
{
  Local_Data* pd = E_NEW(Local_Data, 1);

  Evas_Object *nf = NULL, *content;
  Elm_Object_Item* it;

  nf = elm_naviframe_add(win);
  evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

  E_Randr2_Screen* s;
  Eina_List* l;
  char buf[PATH_MAX];
  count = 0;


  EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {
    if (s->info.connected == EINA_TRUE) {
      if (s->info.is_lid == EINA_FALSE) {
        snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
        target_device = strdup(buf);

        _set_target_id(s->id, NULL, NULL);
        count++;
      } else {
        lid_id = s->id;
        snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
        target_device = strdup(buf);
      }
    }
  }

//   if (count == 1) {
//     content = _content_modes(nf);
//   } else
    content = _content_target_devices(nf);

  it = elm_naviframe_item_push(nf, "Select Target Device", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
  evas_object_data_set(nf, "page1", it);

  // das muss sein :)
  evas_object_data_set(nf, "__data", pd);

  return nf;
}

void
wizard_config_apply(Evas_Object* obj)
{
  SCOPE_DATA(obj);
}
