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
// const char* lid_id;
const char* id;
const char* source_id;
const char* target_id;
Eina_List *expand_modes_obj_list = NULL;

int a = 0, r = 51, g = 153, b = 255;
int a1 = 0, r1 = 255, g1 = 255, b1 = 255;
int a2 = 255, r2 = 51, g2 = 153, b2 = 255;
int a3 = 255, r3 = 255, g3 = 255, b3 = 255;





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
_cb_settings_screen_setup(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
   _block_clicked_cb(NULL, NULL, NULL);
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

  printf("target_id SET DATA: %s\n\n", target_device);
  printf("source_id SET DATA: %s\n\n", source_device);
  // 	        if (!cs2->id) continue;
  cs = _screen_config_randr_id_find(target_id);
  if (!cs) {
    cs = calloc(1, sizeof(E_Config_Randr2_Screen));
    cs->id = eina_stringshare_add(target_id);
    e_randr2_cfg->screens = eina_list_append(e_randr2_cfg->screens, cs);
  }
  eina_stringshare_replace(&cs->rel_to, source_id);
  cs->rotation = 0;
  cs->rel_mode = data;
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
  
//   e_randr2_config_save();
//   e_randr2_config_apply();
//   _block_clicked_cb(NULL, NULL, NULL);

	// TODO REOPEN QUICKSCREEN
	//   sleep(5);
	//   qs_key(NULL, NULL);
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
_focus_in_cb(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  evas_object_color_set(data, r2, g2, b2, a2);
//   printf("FOCUS IN: %p\n", obj);
}

void
_focus_out_cb(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  evas_object_color_set(data, r3, g3, b3, a3);
}

static void
_on_keydown_expand(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
	
   if (strcmp(ev->key, "Return") == 0)
     {
		  _page_expand(data, NULL, NULL);
		  return;
	  }
}


static void
_on_key_expand_modes_obj(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
		
	Eina_List *expand_obj = data;
   Evas_Object *above = eina_list_nth(expand_obj, 0);
   Evas_Object *left_of = eina_list_nth(expand_obj, 1);
   Evas_Object *right_of = eina_list_nth(expand_obj, 2);
   Evas_Object *below = eina_list_nth(expand_obj, 3);
	
//   printf("KEY IN: %s\n", ev->key);
   if (strcmp(ev->key, "Up") == 0)
     {
		  elm_object_focus_set(above, EINA_TRUE);
		  return;
	  }
	  else if(strcmp(ev->key, "Left") == 0)
     {
		  elm_object_focus_set(left_of, EINA_TRUE);
		  return;
	  }else if(strcmp(ev->key, "Right") == 0)
     {
		  elm_object_focus_set(right_of, EINA_TRUE);
		  return;
	  }else if(strcmp(ev->key, "Down") == 0)
     {
		  elm_object_focus_set(below, EINA_TRUE);
		  return;
	  }
}

static void
_on_keydown_source(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
	
   if (strcmp(ev->key, "Return") == 0)
     {
		  _page_source_devices(data, NULL, NULL);
		  return;
	  }
}

static void
_on_keydown_page_modes(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
	
   if (strcmp(ev->key, "Return") == 0)
     {
		  _page_modes(data, NULL, NULL);
		  return;
	  }
}
/*
static void
_on_keydown_target(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
	
   if (strcmp(ev->key, "Return") == 0)
     {
		  _page_target_devices(data, NULL, NULL);
		  return;
	  }
}*/

static void
_on_keydown(void *data EINA_UNUSED,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
   if (strcmp(ev->key, "Return") == 0) /* print help */
     {
		  printf("ON KEY\n");
		  
		  if(strcmp((char*)data, "CLONE") == 0)
			{
// 				_set_relative((void*)E_RANDR2_RELATIVE_CLONE, NULL, NULL);
			}
		  if(strcmp((char*)data, "LEFT_OF") == 0)
		  {
			  _set_relative((void*)E_RANDR2_RELATIVE_TO_LEFT, NULL, NULL);
		  }/*
		  else if(strcmp((char*)data, "RIGHT_OF") == 0)
		  {
			  _set_relative((void*)E_RANDR2_RELATIVE_TO_RIGHT, NULL, NULL);
		  }
		  else if(strcmp((char*)data, "ABOVE") == 0)
		  {
			  _set_relative((void*)E_RANDR2_RELATIVE_TO_ABOVE, NULL, NULL);
		  }
		  else if(strcmp((char*)data, "BELOW") == 0)
		  {
			  _set_relative((void*)E_RANDR2_RELATIVE_TO_BELOW, NULL, NULL);
		  }
		  else if(strcmp((char*)data, "SOURCE_POWER_OFF") == 0)
		  {
			  _set_source_power_off(NULL, NULL, NULL);
		  }
		  else if(strcmp((char*)data, "TARGET_POWER_OFF") == 0)
		  {
			  _set_target_power_off(NULL, NULL, NULL);
		  }*/

		  return;
     }
}

Evas_Object*
_content_modes(Evas_Object* parent)
{
  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt_source_off, *bt_target_off, *bt_b, *bt_a, *bt_expand, *bt_clone;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];

  tb_m = elm_table_add(parent);
  elm_object_focus_allow_set(tb_m, EINA_FALSE);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r, g, b, a);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect,  r, g, b, a);
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
  elm_object_focus_allow_set(bt_b, EINA_FALSE);
  evas_object_color_set(bt_b, r3, g3, b3, a3);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_source_devices, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  elm_object_focus_allow_set(bt_a, EINA_FALSE);
  evas_object_color_set(bt_a, r3, g3, b3, a3);
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

  bt_clone = elm_button_add(parent);
  evas_object_color_set(bt_clone, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_clone, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_clone, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_clone, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_CLONE);
  evas_object_smart_callback_add(bt_clone, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_clone, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_clone, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_clone, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_clone, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "CLONE");
  elm_table_pack(tb_c, bt_clone, 0, 1, 1, 1);
  evas_object_show(bt_clone);

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

  bt_expand = elm_button_add(parent);
  evas_object_color_set(bt_expand, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_expand, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_expand, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_expand, "clicked", _page_expand, parent);
  evas_object_smart_callback_add(bt_expand, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_expand, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_expand, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_expand, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_expand, EVAS_CALLBACK_KEY_DOWN, _on_keydown_expand, parent);
  elm_table_pack(tb_c, bt_expand, 1, 1, 1, 1);
  evas_object_show(bt_expand);

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

  bt_target_off = elm_button_add(parent);
  evas_object_color_set(bt_target_off, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_target_off, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_target_off, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_target_off, "clicked", _set_target_power_off, NULL);
  evas_object_smart_callback_add(bt_target_off, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_target_off, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_target_off, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_target_off, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_target_off, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "TARGET_POWER_OFF");
  elm_table_pack(tb_c, bt_target_off, 0, 4, 1, 1);
  evas_object_show(bt_target_off);

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

  bt_source_off = elm_button_add(parent);
  evas_object_color_set(bt_source_off, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_source_off, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_source_off, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_source_off, "clicked", _set_source_power_off, NULL);
  evas_object_smart_callback_add(bt_source_off, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_source_off, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_source_off, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_source_off, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_source_off, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "SOURCE_POWER_OFF");
  elm_table_pack(tb_c, bt_source_off, 1, 4, 1, 1);
  evas_object_show(bt_source_off);

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
_set_target_id1(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
  target_id = (char*)data;
}

void
_set_source_id(void* data, Evas_Object* obj EINA_UNUSED, void* event_info EINA_UNUSED)
{
  source_id = (char*)data;
}

void
_set_source_id1(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
  source_id = (char*)data;
}

void
_set_target_device_name(void* data,
                 Evas_Object* obj EINA_UNUSED,
                 void* event_info EINA_UNUSED)
{
  target_device = data;
//   printf("TARGET DEVICE NAME: %s\n", target_device);
}


void
_set_target_device_name1(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
  target_device = data;
//   printf("TARGET DEVICE NAME: %s\n", target_device);
}

void
_set_source_device_name(void* data,
                 Evas_Object* obj EINA_UNUSED,
                 void* event_info EINA_UNUSED)
{
  source_device = data;
//   printf("SOURCE DEVICE NAME: %s\n", source_device);
}

void
_set_source_device_name1(void *data,
            Evas *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void *einfo)
{
  source_device = data;
//   printf("SOURCE DEVICE NAME: %s\n", source_device);
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

//////////TEST DND///////////////
/*
static void
_cleanup_cb(void *data, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{  
   Evas_Coord mx, my, cx, cy, cw, ch, nx, ny, lx, ly, lw, lh, mx1, my1;

				evas_pointer_canvas_xy_get(evas_object_evas_get(data), &mx, &my);
				evas_object_geometry_get(obj, &cx, &cy, &cw, &ch);
// 				evas_object_geometry_get(ec->layout, &lx, &ly, &lw, &lh);
				printf("MOUSE X:%i Y:%i\n", mx, my);
				printf("OBJ GEO X:%i Y:%i\n", cx, cy);

 int button_mask;

 button_mask = evas_pointer_button_down_mask_get(evas_object_evas_get(data));
 
        if (button_mask == 1)
        {
				evas_object_move(obj, mx - (cw/2),  my - (ch/2));
// 				printf("NEW OBJ GEO X:%i Y:%i\n", mx - cx,  my - cy);
        }
}*/

/*
Evas_Object*
_content_dnd(Evas_Object* parent)
{
  Eina_List* l *tmp;
  E_Randr2_Screen* s;
  Evas_Object *rect, *gd, *lbl;
  char buf[PATH_MAX];
  
   gd = elm_grid_add(parent);
   elm_grid_size_set(gd, 500, 300);
   evas_object_size_hint_weight_set(gd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(gd, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_min_set(gd, 500, 300);
//   evas_object_color_set(gd, 1, 153, 255, 255);
int i = 0;
   EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {
	  if (s->info.connected == EINA_TRUE) {
  rect = evas_object_rectangle_add(gd);
//   evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
//   evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  
//   evas_object_size_hint_min_set(rect, 100, 75);
//   evas_object_size_hint_max_set(rect, 100, 75);
  evas_object_color_set(rect, 51, 153, 255, 128);
  evas_object_show(rect);
  
  lbl = elm_label_add(gd);
//   evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.0, 0.0);
  
      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
  elm_object_text_set(lbl, buf);
  evas_object_color_set(lbl, r3, g3, b3, a3);
  evas_object_show(lbl);
  
   elm_grid_pack(gd, lbl, i, i, s->config.mode.w/10, s->config.mode.h/10);
   elm_grid_pack(gd, rect, i, i, s->config.mode.w/10, s->config.mode.h/10);
	
  
  evas_object_event_callback_add(rect, EVAS_CALLBACK_MOUSE_MOVE , _cleanup_cb, gd);
//   evas_object_event_callback_add(lbl, EVAS_CALLBACK_MOUSE_MOVE , _cleanup_cb, gd);
//   elm_box_pack_end(box, rect);
	i=i+100;
	  }
  }


  
  evas_object_show(gd);
  
  
  return gd;
}*/

//////////END TEST DND ////////////////


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
  elm_object_focus_allow_set(tb_m, EINA_FALSE);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
//   elm_object_focus_allow_set(rect, EINA_FALSE);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r2, g2, b2, a2);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
//   elm_object_focus_allow_set(rect, EINA_FALSE);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r, g, b, a);
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
  elm_object_focus_allow_set(bt_a, EINA_FALSE); // If enable first focus with keyboard is broken
  evas_object_color_set(bt_a, r3, g3, b3, a3);
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
		evas_object_color_set(bt, r1, g1, b1, a1);
      evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
      evas_object_smart_callback_add(bt, "clicked", _page_source_devices, parent);

      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
      device_info = strdup(buf);
      evas_object_smart_callback_add(bt, "clicked", _set_target_device_name, device_info);
      evas_object_smart_callback_add(bt, "clicked", _set_target_id, s->id);
      evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
      evas_object_smart_callback_add(bt, "unpressed", _focus_out_cb, ic);
		evas_object_smart_callback_add(bt, "focused", _focus_in_cb, ic);
		evas_object_smart_callback_add(bt, "unfocused", _focus_out_cb, ic);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _on_keydown_source, parent);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _set_target_id1, s->id);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _set_target_device_name1, device_info);
      elm_table_pack(tb_c, bt, x, 1, 1, 2);
      evas_object_show(bt);

		if(x == 0)
			elm_object_focus_set(bt, EINA_TRUE);
		
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
      "<color=#ffffff>NO EXTERNAL DEVICES FOUND<br><br>plugin a device<br>or restart 'E' using "
      "strg+alt+end to detect analog devices</color>");
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

  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt, *bt_a, *bt_b;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];
  char* device_info;

  tb_m = elm_table_add(parent);
  elm_object_focus_allow_set(tb_m, EINA_FALSE);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r2, g2, b2, a2);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r, g, b, a);
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
  elm_object_focus_allow_set(bt_b, EINA_FALSE);
  evas_object_color_set(bt_b, r3, g3, b3, a3);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_target_devices, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  elm_object_focus_allow_set(bt_a, EINA_FALSE);
  evas_object_color_set(bt_a, r3, g3, b3, a3);
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
      evas_object_color_set(bt, r1, g1, b1, a1);
      evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
      evas_object_smart_callback_add(bt, "clicked", _page_modes, parent);

      snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
      device_info = strdup(buf);
      evas_object_smart_callback_add(bt, "clicked", _set_source_device_name, device_info);
      evas_object_smart_callback_add(bt, "clicked", _set_source_id, s->id);
      evas_object_smart_callback_add(bt, "pressed", _focus_in_cb, ic);
		evas_object_smart_callback_add(bt, "focused", _focus_in_cb, ic);
		evas_object_smart_callback_add(bt, "unfocused", _focus_out_cb, ic);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _on_keydown_page_modes, parent);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _set_source_id1, s->id);
		evas_object_event_callback_add(bt, EVAS_CALLBACK_KEY_DOWN, _set_source_device_name1, device_info);
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

      x++;
    }
  }
//   if (x == 1) {
// 	  elm_obj_naviframe_item_pop();
//   }
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

  it = elm_naviframe_item_push(nf, "Select Source device", NULL, NULL, content, NULL);
  elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
  evas_object_data_set(nf, "page1", it);
}


Evas_Object*
_content_expand(Evas_Object* parent)
{
  Evas_Object *tb_c, *tb_m, *tb_t;
  Evas_Object* lbl;
  Evas_Object* ic;
  Evas_Object *bt_above, *bt_below, *bt_leftof, *bt_rightof, *bt_b, *bt_a;
  Evas_Object* rect;
  Evas_Object* box_c;

  char buf[PATH_MAX];

  tb_m = elm_table_add(parent);
  elm_object_focus_allow_set(tb_m, EINA_FALSE);
  evas_object_size_hint_align_set(tb_m, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb_m, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_show(tb_m);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  elm_object_focus_allow_set(rect, EINA_FALSE);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r2, g2, b2, a2);
  elm_table_pack(tb_m, rect, 0, 0, 1, 1);
  evas_object_show(rect);

  rect = evas_object_rectangle_add(evas_object_evas_get(parent));
  elm_object_focus_allow_set(rect, EINA_FALSE);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_color_set(rect, r, g, b, a);
  elm_table_pack(tb_m, rect, 0, 0, 1, 2);
  evas_object_size_hint_min_set(rect, 500, 300);
  evas_object_show(rect);

  tb_t = elm_table_add(parent);
  elm_object_focus_allow_set(tb_t, EINA_FALSE);
  evas_object_size_hint_align_set(tb_t, EVAS_HINT_FILL, EVAS_HINT_FILL);
  //   evas_object_size_hint_weight_set(tb_t, EVAS_HINT_EXPAND,
  //   EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, tb_t, 0, 0, 1, 1);
  evas_object_show(tb_t);

  lbl = elm_label_add(parent);
  elm_object_focus_allow_set(lbl, EINA_FALSE);
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
  elm_object_focus_allow_set(bt_b, EINA_FALSE);
  evas_object_color_set(bt_b, r3, g3, b3, a3);
  evas_object_size_hint_weight_set(bt_b, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_b, 0, 0.5);
  elm_object_text_set(bt_b, "Back");
  evas_object_smart_callback_add(bt_b, "clicked", _page_modes, parent);
  elm_table_pack(tb_t, bt_b, 0, 0, 1, 1);
  evas_object_show(bt_b);

  bt_a = elm_button_add(parent);
  elm_object_focus_allow_set(bt_a, EINA_FALSE);
  evas_object_color_set(bt_a, r3, g3, b3, a3);
  evas_object_size_hint_weight_set(bt_a, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_a, 1, 0.5);
  elm_object_text_set(bt_a, "Advanced");
    evas_object_smart_callback_add(bt_a, "clicked", _cb_settings_screen_setup,
    NULL);
  elm_table_pack(tb_t, bt_a, 0, 0, 1, 1);
  evas_object_show(bt_a);

  box_c = elm_box_add(parent);
  elm_object_focus_allow_set(box_c, EINA_FALSE);
  evas_object_size_hint_align_set(box_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(box_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_table_pack(tb_m, box_c, 0, 1, 1, 1);
  evas_object_show(box_c);

  tb_c = elm_table_add(parent);
  elm_object_focus_allow_set(tb_c, EINA_FALSE);
  elm_table_homogeneous_set(tb_c, EINA_TRUE);
  elm_table_padding_set(tb_c, 1, 1);
  evas_object_size_hint_weight_set(tb_c, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(tb_c, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_box_pack_end(box_c, tb_c);
  evas_object_show(tb_c);

  ////////////// START INHALT TABLE CONTENT ////
  ///
  ic = elm_image_add(parent);
  elm_object_focus_allow_set(ic, EINA_FALSE);
  snprintf(buf, sizeof(buf), "%s/images/above.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 0, 1, 1);
  evas_object_show(ic);

  bt_above = elm_button_add(parent);
  evas_object_color_set(bt_above, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_above, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_above, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_above, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_TO_ABOVE);
  evas_object_smart_callback_add(bt_above, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_above, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_above, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_above, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_above, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "ABOVE");
  elm_table_pack(tb_c, bt_above, 1, 0, 1, 1);
  evas_object_show(bt_above);

  ///////////

  ic = elm_image_add(parent);
  elm_object_focus_allow_set(ic, EINA_FALSE);
  snprintf(buf, sizeof(buf), "%s/images/left_of.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, 1, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 0, 1, 1, 1);
  evas_object_show(ic);

  bt_leftof = elm_button_add(parent);
  evas_object_color_set(bt_leftof, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_leftof, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_leftof, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_leftof, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_TO_LEFT);
  evas_object_smart_callback_add(bt_leftof, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_leftof, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_leftof, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_leftof, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_leftof, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "LEFT_OF");
  elm_table_pack(tb_c, bt_leftof, 0, 1, 1, 1);
  evas_object_show(bt_leftof);

  ///////////

  ic = elm_image_add(parent);
  elm_object_focus_allow_set(ic, EINA_FALSE);
  snprintf(buf, sizeof(buf), "%s/images/monitor.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 1, 1, 1);
  evas_object_show(ic);
  
//   rect = evas_object_rectangle_add(evas_object_evas_get(parent));
//   elm_object_focus_allow_set(rect, EINA_FALSE);
// //   evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
// //   evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//   evas_object_color_set(rect, r2, g2, b2, a2);
//   elm_table_pack(tb_c, rect, 1, 1, 1, 1);
//   evas_object_show(rect);
  
  lbl = elm_label_add(parent);
  evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(lbl, 0.5, 0.5);
  elm_object_text_set(lbl, target_device);
  elm_table_pack(tb_c, lbl, 1, 1, 1, 1);
  evas_object_show(lbl);

  ///////////

  ic = elm_image_add(parent);
  snprintf(buf, sizeof(buf), "%s/images/right_of.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, 0, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 2, 1, 1, 1);
  evas_object_show(ic);

  bt_rightof = elm_button_add(parent);
  evas_object_color_set(bt_rightof, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_rightof, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_rightof, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_rightof, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_TO_RIGHT);
  evas_object_smart_callback_add(bt_rightof, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_rightof, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_rightof, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_rightof, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_rightof, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "RIGHT_OF");
  elm_table_pack(tb_c, bt_rightof, 2, 1, 1, 1);
  evas_object_show(bt_rightof);
  elm_object_focus_set(bt_rightof, EINA_TRUE);

  ///////////

  ic = elm_image_add(parent);
  elm_object_focus_allow_set(ic, EINA_FALSE);
  snprintf(buf, sizeof(buf), "%s/images/below.png", PACKAGE_DATA_DIR);
  elm_image_file_set(ic, buf, NULL);
  evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(165), ELM_SCALE_SIZE(62));
  evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_table_pack(tb_c, ic, 1, 2, 1, 1);
  evas_object_show(ic);

  bt_below = elm_button_add(parent);
  evas_object_color_set(bt_below, r1, g1, b1, a1);
  evas_object_size_hint_weight_set(bt_below, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(bt_below, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_smart_callback_add(bt_below, "clicked", _set_relative, (void*)E_RANDR2_RELATIVE_TO_BELOW);
  evas_object_smart_callback_add(bt_below, "pressed", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_below, "unpressed", _focus_out_cb, ic);
  evas_object_smart_callback_add(bt_below, "focused", _focus_in_cb, ic);
  evas_object_smart_callback_add(bt_below, "unfocused", _focus_out_cb, ic);
  evas_object_event_callback_add(bt_below, EVAS_CALLBACK_KEY_DOWN, _on_keydown, "BELOW");
  elm_table_pack(tb_c, bt_below, 1, 2, 1, 1);
  evas_object_show(bt_below);

  ////////////// END INHALT TABLE CONTENT ////

  return tb_m;
  
  expand_modes_obj_list = eina_list_append(expand_modes_obj_list, bt_above);
  expand_modes_obj_list = eina_list_append(expand_modes_obj_list, bt_leftof);
  expand_modes_obj_list = eina_list_append(expand_modes_obj_list, bt_rightof);
  expand_modes_obj_list = eina_list_append(expand_modes_obj_list, bt_below);
  
  
  
  evas_object_event_callback_add(bt_above, EVAS_CALLBACK_KEY_DOWN, _on_key_expand_modes_obj, expand_modes_obj_list);
  evas_object_event_callback_add(bt_leftof, EVAS_CALLBACK_KEY_DOWN, _on_key_expand_modes_obj, expand_modes_obj_list);
  evas_object_event_callback_add(bt_rightof, EVAS_CALLBACK_KEY_DOWN, _on_key_expand_modes_obj, expand_modes_obj_list);
  evas_object_event_callback_add(bt_below, EVAS_CALLBACK_KEY_DOWN, _on_key_expand_modes_obj, expand_modes_obj_list);
  
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

  evas_color_argb_premul(a, &r, &g, &b);
  evas_color_argb_premul(a1, &r1, &g1, &b1);
  evas_color_argb_premul(a2, &r2, &g2, &b2);
  evas_color_argb_premul(a3, &r, &g3, &b3);
  
  nf = elm_naviframe_add(win);
  evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

  E_Randr2_Screen* s;
  Eina_List* l;
  char buf[PATH_MAX];
  int count_lid = 0;
  int count_device = 0;


  EINA_LIST_FOREACH(e_randr2->screens, l, s)
  {
    if (s->info.connected == EINA_TRUE) {
      if (s->info.is_lid == EINA_FALSE) {
        snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
        target_device = strdup(buf);
        _set_target_id(s->id, NULL, NULL);
        count_device++;
      } else {
//         lid_id = s->id;
		  _set_source_id(s->id, NULL, NULL);
        snprintf(buf, sizeof(buf), "%s - [%s]", s->info.screen, s->info.name);
        source_device = strdup(buf);
		  count_lid++;
      }
    }
  }
// content = _content_dnd(nf);

if(count_lid == 1 && count_device == 1)
{
    content = _content_target_devices(nf);
	 it = elm_naviframe_item_push(nf, "Select Target Device", NULL, NULL, content, NULL);
	
	 elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);
  
    content = _content_modes(nf);
	 it = elm_naviframe_item_push(nf, "Select Mode", NULL, NULL, content, NULL);
}
else
{
    content = _content_target_devices(nf);
		 it = elm_naviframe_item_push(nf, "Select Target Device", NULL, NULL, content, NULL);
}

//     content = _content_target_devices(nf);
// 		 it = elm_naviframe_item_push(nf, "Select Target Device", NULL, NULL, content, NULL);
		 
		 
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
