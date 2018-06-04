#include "e.h"
#include "quickscreen.h"
#include "config.h"
#include <string.h>

typedef struct {

} Local_Data;

#define SCOPE_DATA(popup) Local_Data *pd = evas_object_data_get(popup, "__data");


Evas_Object *popup;


Evas_Object *
_content_device(Evas_Object *parent)
{
  Evas_Object *tb;
  Evas_Object *lbl;
  Evas_Object *ic;
  Evas_Object *bt;
  Evas_Object *rect;
  
  char buf[PATH_MAX];
	
  tb = elm_table_add(parent);
  elm_table_padding_set(tb, 10, 10);
  evas_object_size_hint_min_set(tb, 500, 400);
  evas_object_size_hint_align_set(tb, EVAS_HINT_FILL, EVAS_HINT_FILL);
  evas_object_size_hint_weight_set(tb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);


  rect = evas_object_rectangle_add(parent);
  evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_color_set(rect, 51, 153, 255, 255);
	elm_table_pack(tb, rect, 0, 0, 1, 2);
	evas_object_show(rect);
	
	
	ic = elm_icon_add(parent);
	snprintf(buf, sizeof(buf), "%s/images/beamer.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 0, 0, 1, 1);
	evas_object_show(ic);
		
	lbl = elm_label_add(parent);
	elm_object_text_set(lbl, "<color=#ffffff>BEAMER HDMI-1</color>");
	elm_table_pack(tb, lbl, 0, 1, 1, 1);
	evas_object_show(lbl);

	bt = elm_button_add(parent);
	evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);		
	elm_object_text_set(bt, "BEAMER HDMI-1");
	elm_table_pack(tb, bt, 1, 0, 1, 2);
	
	elm_object_focus_set(bt, EINA_TRUE);
	evas_object_show(bt);
		
	ic = elm_icon_add(parent);
	snprintf(buf, sizeof(buf), "%s/images/monitor.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 1, 0, 1, 1);
	evas_object_show(ic);
		
	lbl = elm_label_add(parent);
	elm_object_text_set(lbl, "<color=#ffffff>MONITOR DVI-0</color>");
	elm_table_pack(tb, lbl, 1, 1, 1, 1);
	evas_object_show(lbl);
   evas_object_show(tb);
  
   return tb;
}

Evas_Object *
_content_modes(Evas_Object *parent)
{
	Evas_Object *tb;
	Evas_Object *lbl;
	Evas_Object *ic;
	Evas_Object *bt;
	Evas_Object *rect;
   char buf[PATH_MAX];
  		
	tb = elm_table_add(popup);
	elm_table_padding_set(tb, 10, 10);
		
	rect = evas_object_rectangle_add(popup);
	evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_color_set(rect, 51, 153, 255, 255);
	elm_table_pack(tb, rect, 0, 0, 1, 2);
	evas_object_show(rect);

	lbl = elm_label_add(popup);
	elm_object_text_set(lbl, "<color=#ffffff>Clone</color>");
	elm_table_pack(tb, lbl, 0, 0, 1, 1);
	evas_object_show(lbl);
		
	ic = elm_icon_add(popup);
	snprintf(buf, sizeof(buf), "%s/images/clone.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 0, 1, 1, 1);
	evas_object_show(ic);
		
	lbl = elm_label_add(popup);
	elm_object_text_set(lbl, "<color=#ffffff>Extend</color>");
	elm_table_pack(tb, lbl, 1, 0, 1, 1);
	evas_object_show(lbl);
		
	ic = elm_icon_add(popup);
	snprintf(buf, sizeof(buf), "%s/images/extend.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 1, 1, 1, 1);
	evas_object_show(ic);
		
		
	lbl = elm_label_add(popup);
	elm_object_text_set(lbl, "Extern ON");
	elm_table_pack(tb, lbl, 0, 2, 1, 1);
	evas_object_show(lbl);
		
	ic = elm_icon_add(popup);
	snprintf(buf, sizeof(buf), "%s/images/left.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 0, 3, 1, 1);
	evas_object_show(ic);
		
	lbl = elm_label_add(popup);
	elm_object_text_set(lbl, "<color=#ffffff>Intern ON</color>");
	elm_table_pack(tb, lbl, 1, 2, 1, 1);
	evas_object_show(lbl);
		
	ic = elm_icon_add(popup);
	snprintf(buf, sizeof(buf), "%s/images/right.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_min_set(ic, ELM_SCALE_SIZE(321), ELM_SCALE_SIZE(124));
	evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, ic, 1, 3, 1, 1);
	evas_object_show(ic);
		
	bt = elm_button_add(popup);
	elm_object_text_set(bt, "Advanced Settings");
	elm_table_pack(tb, bt, 0, 4, 2, 1);
	evas_object_show(bt);
			
	evas_object_show(tb);
	
	return tb;
}


void
_page_modes(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	
   Evas_Object *btn, *content, *ic1, *nf = data;
//    Elm_Object_Item *it;

   btn = elm_button_add(nf);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
//    evas_object_smart_callback_add(bt, "clicked", _page3, nf);

   ic1 = elm_icon_add(nf);
   elm_icon_standard_set(ic1, "arrow_right");
   evas_object_size_hint_aspect_set(ic1, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   elm_layout_content_set(btn, "icon", ic1);

   content = _content_modes(nf);

   elm_naviframe_item_push(nf, "Select Mode",
                                NULL, btn, content,  NULL);
//    elm_object_item_part_text_set(it, "subtitle", "Here is sub-title part!");
}

void
_exit_nf(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	if(popup)
   {
        evas_object_del(popup);
        popup = NULL;
	}
}

static void
_block_clicked_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   if (data)
     evas_object_del(data);
   evas_object_del(obj);
}


Evas_Object*
wizard_config_create(Evas_Object *win)
{
	Local_Data *pd = E_NEW(Local_Data, 1);

   if(popup)
   {
        evas_object_del(popup);
        popup = NULL;
        return;
	}
	
	popup = elm_popup_add(win);
   evas_object_layer_set(popup, E_LAYER_POPUP);
	
   evas_object_smart_callback_add(popup, "block,clicked", _block_clicked_cb,
                                  NULL);
	
	
	elm_object_focus_set(popup, EINA_TRUE);
	Evas_Object *nf, *btn, *btn1, *content;
   Elm_Object_Item *it;

   nf = elm_naviframe_add(popup);
   evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(popup, nf);
   evas_object_show(nf);
	
//    evas_object_smart_callback_add(nf, "title,clicked", _title_clicked, 0);
//    evas_object_smart_callback_add(nf, "item,activated", _item_activated, NULL);

   btn = elm_button_add(nf);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(btn, "clicked", _page_modes, nf);
	elm_object_text_set(btn, "Mode");
   evas_object_show(btn);
	
   btn1 = elm_button_add(nf);
   evas_object_size_hint_align_set(btn1, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(btn1, "clicked", _exit_nf, NULL);
	elm_object_text_set(btn1, "Exit");
   evas_object_show(btn1);

   content = _content_device(nf);
   it = elm_naviframe_item_push(nf, "Select Device", btn1, btn, content, NULL);
   evas_object_data_set(nf, "page1", it);
	
	
   elm_object_content_set(popup, nf);
	evas_object_show(popup);
	
	//das muss sein :)
   evas_object_data_set(popup, "__data", pd);

   return popup;
}

void
wizard_config_apply(Evas_Object *obj)
{
   SCOPE_DATA(obj);
}
