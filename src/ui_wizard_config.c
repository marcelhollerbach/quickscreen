#include "config.h"
#include "e.h"
#include "quickscreen.h"
#include <string.h>

typedef struct
{

} Local_Data;

#define SCOPE_DATA(popup)                                                      \
  Local_Data* pd = evas_object_data_get(popup, "__data");

const char* device;
const char* pdevice;
const char* lid_id;
const char* id;
Evas_Object* popup;

Evas_Object*
_content_device(Evas_Object* parent);
Evas_Object*
_content_modes(Evas_Object* parent);
Evas_Object*
_content_expand(Evas_Object* parent);

void
_page_devices(void* data,
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
  E_Config_Randr2_Screen *cs, *cs2;

  printf("DNAME SET DATA: %s\n\n", id);
  // 	        if (!cs2->id) continue;
  cs = _screen_config_randr_id_find(id);
  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }
  if (cs->rel_to)
    eina_stringshare_del(cs->rel_to);
  cs->rel_to = NULL;
  //         printf("APPLY %s .... rel to %s\n", cs->id, cs2->rel_to);
  if (cs2->rel_to)
    cs->rel_to = eina_stringshare_add(lid_id);
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
  e_randr2_config_save();
  e_randr2_config_apply();
}


void
_set_extern_power_on(void* data EINA_UNUSED,
                  Evas_Object* obj EINA_UNUSED,
                  void* event_info EINA_UNUSED)
{

  E_Config_Randr2_Screen *cs, *cs2;

  
 
  cs = _screen_config_randr_id_find(id);

  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }

  if (cs->rel_to)
    eina_stringshare_del(cs->rel_to);
  
  cs->rel_to = NULL;
  cs->rel_to = eina_stringshare_add(lid_id);
  
  cs->rotation = 0;
	
  cs->priority = 100;
 
	cs->rel_mode = E_RANDR2_RELATIVE_NONE;
  
	cs->enabled = EINA_FALSE;
  
	 
  cs2 = _screen_config_randr_id_find(lid_id);

  if (!cs2) {
    cs2 = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs2->id = eina_stringshare_add(lid_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs2);
  }

  if (cs2->rel_to)
    eina_stringshare_del(cs2->rel_to);
  
  cs2->rel_to = NULL;
  cs2->rel_to = eina_stringshare_add(lid_id);
  
  cs2->rotation = 0;
	
  cs2->priority = 100;
  
	cs2->rel_mode = E_RANDR2_RELATIVE_CLONE;
  
	cs2->enabled = EINA_TRUE;
  
	
	
	
	
  e_randr2_config_save();
  e_randr2_config_apply();
}

void
_set_extern_power_off(void* data EINA_UNUSED,
                  Evas_Object* obj EINA_UNUSED,
                  void* event_info EINA_UNUSED)
{

  E_Config_Randr2_Screen *cs, *cs2;

  
 
  cs = _screen_config_randr_id_find(id);

  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }

  if (cs->rel_to)
    eina_stringshare_del(cs->rel_to);
  
  cs->rel_to = NULL;
  cs->rel_to = eina_stringshare_add(lid_id);
  
  cs->rotation = 0;
	
  cs->priority = 100;
  
		cs->rel_mode = E_RANDR2_RELATIVE_CLONE;
  
	cs->enabled = EINA_TRUE;
  
	 
  cs2 = _screen_config_randr_id_find(lid_id);

  if (!cs2) {
    cs2 = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs2->id = eina_stringshare_add(lid_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs2);
  }

  if (cs2->rel_to)
    eina_stringshare_del(cs2->rel_to);
  
  cs2->rel_to = NULL;
  cs2->rel_to = eina_stringshare_add(lid_id);
  
  cs2->rotation = 0;
	
  cs2->priority = 0;
  
	cs2->rel_mode = E_RANDR2_RELATIVE_NONE;
  
	cs2->enabled = EINA_FALSE;
  
	
	
	
	
  e_randr2_config_save();
  e_randr2_config_apply();
}

void
_focus_in_cb(void* data, Evas_Object* obj, void* event_info EINA_UNUSED)
{
  evas_object_color_set(obj, 51, 153, 255, 128);
}

void
_focus_out_cb(void* data, Evas_Object* obj, void* event_info EINA_UNUSED)
{
  evas_object_color_set(obj, 255, 255, 255, 0);
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

  rect = evas_object_rectangle_add(parent);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(parent);
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
           device);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);

  bt_b = elm_button_add(parent);
  evas_object_color_set(bt_b, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_devices, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);
  
  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
//   evas_object_smart_callback_add(bt_a, "clicked", advanced_settings_create, popup);
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
    bt, "clicked", _set_relative, E_RANDR2_RELATIVE_CLONE);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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
  evas_object_smart_callback_add(bt, "clicked", _set_extern_power_on, NULL);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
  elm_table_pack(tb_c, bt, 0, 4, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  snprintf(buf, sizeof(buf), "%s<color=#ffffff> Off</color>", device);
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
  evas_object_smart_callback_add(bt, "clicked", _set_extern_power_off, NULL);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
  elm_table_pack(tb_c, bt, 1, 4, 1, 1);
  evas_object_show(bt);

  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0);
  snprintf(buf, sizeof(buf), "%s<color=#ffffff> Off</color>", pdevice);
  elm_object_text_set(lbl, buf);
  elm_table_pack(tb_c, lbl, 1, 5, 1, 1);
  evas_object_show(lbl);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}

void
_set_id(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  id = (char*)data;
}

void
_set_device_name(void* data,
                 Evas_Object* obj EINA_UNUSED,
                 void* event_info EINA_UNUSED)
{
  device = data;
  printf("DEVICE NAME: %s\n", device);
}

void
_page_modes(void* data,
            Evas_Object* obj EINA_UNUSED,
            void* event_info EINA_UNUSED)
{

  Evas_Object *content, *nf = data;
  Elm_Object_Item* it;

  content = _content_modes(nf);

  it = elm_naviframe_item_push(nf, "Select Mode", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
}

Evas_Object*
_content_device(Evas_Object* parent)
{
  Eina_List* l;
  E_Randr2_Screen* s;
  int x = 0;
  int i = 0;

  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object* bt, *bt_a;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];
  char *device_info;

  tb_m = elm_table_add(parent);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(parent);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(parent);
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
    "<color=#ffffff><bigger>Select Device</bigger><br>to configure</color>");
  elm_table_pack(tb_t, lbl, 0, 0, 1, 1);
  evas_object_show(lbl);

  bt_a = elm_button_add(parent);
  evas_object_color_set(bt_a, 255, 255, 255, 255);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
//   evas_object_smart_callback_add(bt_a, "clicked", advanced_settings_create, popup);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  /// SCROLLER
  Evas_Object* scroller = elm_scroller_add(box_c);
  evas_object_size_hint_weight_set(
    scroller, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);

  elm_box_pack_end(box_c, scroller);
  evas_object_show(scroller);

  tb_c = elm_table_add(box_c);
  elm_table_padding_set(tb_c, 10, 10);
  evas_object_size_hint_align_set(tb_c, 0.5, 0.5);
  //   evas_object_size_hint_weight_set(tb_c, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////

  EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {

    if (s->info.connected == EINA_TRUE && s->info.is_lid == EINA_TRUE)
	 {
      lid_id = s->id;
      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
		pdevice = strdup(buf);
	 }
    if (s->info.connected == EINA_TRUE && s->info.is_lid == EINA_FALSE) {

      ic = elm_icon_add(tb_c);
      snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
      elm_image_file_set(ic, buf, NULL);
      evas_object_size_hint_min_set(
        ic, ELM_SCALE_SIZE(235), ELM_SCALE_SIZE(189));
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
        bt, "clicked", _set_device_name, device_info);
      evas_object_smart_callback_add(bt, "clicked", _set_id, s->id);
      evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
      evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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
  if (i != 1) {
      ic = elm_icon_add(tb_c);
      snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
      elm_image_file_set(ic, buf, NULL);
      evas_object_size_hint_min_set(
        ic, ELM_SCALE_SIZE(235), ELM_SCALE_SIZE(189));
      evas_object_size_hint_weight_set(ic, 0, 0);
      evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(tb_c, ic, 0, 1, 1, 1);
      evas_object_show(ic);

    lbl = elm_label_add(tb_c);
      evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_object_text_set(lbl, "<color=#ffffff>NO EXTERNAL DEVICE FOUND</color>");
    elm_table_pack(tb_c, lbl, 0, 2, 1, 1);
    evas_object_show(lbl);
  }

  elm_object_content_set(scroller, tb_c);
  elm_scroller_bounce_set(scroller, EINA_TRUE, EINA_FALSE);
  elm_scroller_policy_set(
    scroller, ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_AUTO);
  elm_scroller_propagate_events_set(scroller, EINA_TRUE);
  elm_scroller_page_relative_set(scroller, 0, 1);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
}

void
_page_devices(void* data,
              Evas_Object* obj EINA_UNUSED,
              void* event_info EINA_UNUSED)
{

  Evas_Object *content, *nf = data;
  Elm_Object_Item* it;

  content = _content_device(nf);

  it = elm_naviframe_item_push(nf, "Select Mode", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
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

  rect = evas_object_rectangle_add(parent);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, 51, 153, 255, 255);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(parent);
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
    device);
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
//   evas_object_smart_callback_add(bt_a, "clicked", advanced_settings_create, popup);
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
    bt, "clicked", _set_relative, E_RANDR2_RELATIVE_TO_ABOVE);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
  elm_table_pack(tb_c, bt, 1, 0, 1, 1);
  evas_object_show(bt);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/left_off.png", PACKAGE_DATA_DIR);
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
    bt, "clicked", _set_relative, E_RANDR2_RELATIVE_TO_LEFT);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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

  bt = elm_button_add(parent);
  evas_object_color_set(bt, 255, 255, 255, 0);
  evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, bt, 1, 1, 1, 1);
  evas_object_show(bt);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/right_off.png", PACKAGE_DATA_DIR);
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
    bt, "clicked", _set_relative, E_RANDR2_RELATIVE_TO_RIGHT);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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
    bt, "clicked", _set_relative, E_RANDR2_RELATIVE_TO_BELOW);
  evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, NULL);
  evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, NULL);
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
  Evas_Object *content, *nf = data;
  Elm_Object_Item* it;

  content = _content_expand(nf);

  it = elm_naviframe_item_push(
    nf, "Select Expand Mode", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
}
/*
_exit_nf(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  if (popup) {
    evas_object_del(popup);
    popup = NULL;
  }
}*/

static void
_block_clicked_cb(void* data, Evas_Object* obj, void* event_info EINA_UNUSED)
{
  if (data) {
    evas_object_del(data);
    data = NULL;
  }
  evas_object_del(popup);
  popup = NULL;
}

Evas_Object*
wizard_config_create(Evas_Object* win)
{
  Local_Data* pd = E_NEW(Local_Data, 1);

  Evas_Object *nf, *content;
  Elm_Object_Item* it;

  if (popup) {
    evas_object_del(popup);
    popup = NULL;
    evas_object_del(nf);
    nf = NULL;
  } else {

    popup = elm_popup_add(win);
    elm_config_focus_highlight_enabled_set(EINA_TRUE);

    elm_object_style_set(popup, "transparent");
    evas_object_layer_set(popup, E_LAYER_CLIENT_ABOVE);

    nf = elm_naviframe_add(popup);
    evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(popup, nf);

    content = _content_device(nf);

    it =
      elm_naviframe_item_push(nf, "Select Device", NULL, NULL, content, NULL);
    elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
    evas_object_data_set(nf, "page1", it);

    evas_object_smart_callback_add(
      popup, "block,clicked", _block_clicked_cb, nf);

    elm_object_content_set(popup, nf);
    evas_object_show(popup);

    //////////////////
    // das muss sein :)
    evas_object_data_set(popup, "__data", pd);

    return popup;
  }

  return popup;
}

void
wizard_config_apply(Evas_Object* obj)
{
  SCOPE_DATA(obj);
}
