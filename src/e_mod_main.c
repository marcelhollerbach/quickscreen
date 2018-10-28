#include "e.h"
#include "quickscreen.h"

static E_Action* act;

int _quickscreen_log_domain = -1;

/*List of Mirrored Popups*/
Eina_List *popups, *mirrors, *popups1;
E_API E_Module_Api e_modapi = { E_MODULE_API_VERSION, "Quickscreen" };

static Evas_Object* popup;

Evas_Object *popup1;

void
_block_clicked_cb(void* data EINA_UNUSED,
                  Evas_Object* obj,
                  void* event_info EINA_UNUSED)
{
  Evas_Object *pup, *mirror, *popup1;

  evas_object_del(popup);
  popup = NULL;
//   
//   evas_object_del(popup1);
//   popup1 = NULL;
 
  e_comp_ungrab_input(1, 1);
     EINA_LIST_FREE(mirrors, mirror)
   {
      evas_object_del(mirror);
      mirror = NULL;
   }
  EINA_LIST_FREE(popups, pup)
  {
     evas_object_del(pup);
     pup = NULL;
  }
	EINA_LIST_FREE(popups1, popup1)
	{
		evas_object_del(popup1);
		popup1 = NULL;
	}
}
/*
static void
_block_clicked_cb1(void* data EINA_UNUSED,
                  Evas_Object* obj,
                  void* event_info EINA_UNUSED)
{

  evas_object_del(obj);
//   popup = NULL;

}*/

void
key_down(void* data EINA_UNUSED,
         Evas* e EINA_UNUSED,
         Evas_Object* obj EINA_UNUSED,
         void* event_info)
{
  Evas_Event_Key_Down* ev = event_info;
  const char* k = ev->keyname;
//   Evas_Object *pup;
	
  if (!strcmp(k, "Escape")) {
    if (popup) {
/*		 
      evas_object_del(popup);
      popup = NULL;
      e_comp_ungrab_input(1, 1);
      EINA_LIST_FREE(popups, pup)
      {
         evas_object_del(pup);
         pup = NULL;
      }
      */
  Evas_Object *pup, *mirror;

  evas_object_del(popup);
  popup = NULL;

  e_comp_ungrab_input(1, 1);
     EINA_LIST_FREE(mirrors, mirror)
   {
      evas_object_del(mirror);
      mirror = NULL;
   }
  EINA_LIST_FREE(popups, pup)
  {
     evas_object_del(pup);
     pup = NULL;
  }
    }
    
  }
}

static void
popup_resized(void *data, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_data EINA_UNUSED)
{
   E_Zone *zone; Eina_List *l = NULL;
   Evas_Object *popup = data, *pup, *mirror;
   /*Remove previous mirrors*/
   EINA_LIST_FREE(mirrors, mirror)
   {
      evas_object_del(mirror);
      mirror = NULL;
   }
   /*Remove previous mirrored popups*/
   EINA_LIST_FREE(popups, pup)
   {
      evas_object_del(pup);
      pup = NULL;
   }
//    printf("POPUP RESIZE\n");
		
   int i = 0;
   int h = 0;
   int w = 0;
	
   EINA_LIST_FOREACH(e_comp->zones, l, zone) 
   {
      if (i == 0) 
	{
           /*center popup on first zone*/
           e_comp_object_util_center_on_zone(popup, zone);
           evas_object_show(popup);
        }
      else 
        {
           /*create mirror for each additional zone*/
           mirror = evas_object_image_filled_add(e_comp->evas);
           evas_object_image_source_set(mirror, obj);
           evas_object_image_source_events_set(mirror, EINA_TRUE);

           pup = elm_popup_add(e_comp->elm);
			  
// 			  Evas_Object *scroller = elm_scroller_add(pup);
// 			  evas_object_size_hint_min_set(scroller, zone->w / 4, zone->h / 3);
// 			  elm_object_content_set(popup, scroller);
	
           evas_object_geometry_get(obj, 0, 0, &w, &h);
           evas_object_size_hint_min_set(mirror, w, h);
			  
// 			  printf("SIZE POPUP: %i %i\n\n", w, h);
           elm_object_style_set(pup, "transparent");
           evas_object_layer_set(pup, E_LAYER_CLIENT_ABOVE);
           evas_object_layer_set(pup, E_LAYER_POPUP);

           evas_object_smart_callback_add(
           pup, "block,clicked", _block_clicked_cb, popup);
				
           elm_object_content_set(pup, mirror); 
//            elm_object_content_set(scroller, mirror); 

           e_comp_object_util_center_on_zone(pup, zone);
           evas_object_show(mirror);
           evas_object_show(pup);

           /*append mirror to list of mirrors*/
           mirrors = eina_list_append(mirrors, mirror);
           /*append popup to list of mirrored popups*/
           popups = eina_list_append(popups, pup);


           if (!mirror) printf("Mirror is null\n");
        } 
      i++;
   }
}

static void
qs_key(E_Object* obj EINA_UNUSED, const char* params EINA_UNUSED)
{ 
   Evas_Object* content;
   E_Zone *zone; Eina_List *l = NULL; 
  
   content = wizard_config_create(e_comp->elm);
//   display_popup(content);
   popup = elm_popup_add(e_comp->elm);
// 	Evas_Object *scroller = elm_scroller_add(popup);
// 	evas_object_size_hint_min_set(scroller, zone->w / 4, zone->h / 3);
// 	elm_object_content_set(popup, scroller);
// 	elm_object_content_set(scroller, content);
	
	
   e_comp_grab_input(1, 1);

   elm_object_style_set(popup, "transparent");
   evas_object_layer_set(popup, E_LAYER_CLIENT_ABOVE);
   evas_object_layer_set(popup, E_LAYER_POPUP);

   evas_object_smart_callback_add(
   popup, "block,clicked", _block_clicked_cb, popup);

   evas_object_event_callback_add(
   popup, EVAS_CALLBACK_KEY_DOWN, key_down, popup);

   /*add resize callback for popup*/
   evas_object_event_callback_add(content, EVAS_CALLBACK_RESIZE, popup_resized, popup);
					
   elm_object_content_set(popup, content);
// 	elm_object_content_set(scroller, content);
					
   int i = 0;
	
   EINA_LIST_FOREACH(e_comp->zones, l, zone) 
     {
        if (i == 0) 
          {
             e_comp_object_util_center_on_zone(popup, zone); 
             evas_object_show(popup);
          }
        else 
          {
             Evas_Object *mirror = evas_object_image_filled_add(e_comp->evas);
             evas_object_image_source_set(mirror, content);
             evas_object_image_source_events_set(mirror, EINA_TRUE);

             Evas_Object *pup = elm_popup_add(e_comp->elm);
				 
// 				 Evas_Object *scroller = elm_scroller_add(pup);
// 				 evas_object_size_hint_min_set(scroller, zone->w / 4, zone->h / 3);
// 				 elm_object_content_set(popup, scroller);
				 
				 elm_object_style_set(pup, "transparent");
			    evas_object_layer_set(pup, E_LAYER_CLIENT_ABOVE);
			    evas_object_layer_set(pup, E_LAYER_POPUP);

			   	evas_object_smart_callback_add(
						pup, "block,clicked", _block_clicked_cb, popup);
					
             elm_object_content_set(pup, mirror); 
//              elm_object_content_set(scroller, mirror); 

             e_comp_object_util_center_on_zone(pup, zone);
             evas_object_show(mirror);
             evas_object_show(pup);

             /*append mirror to list of mirrors*/
             mirrors = eina_list_append(mirrors, mirror);
             /*append popup to list of mirrored popups*/
             popups = eina_list_append(popups, pup);
             printf("QUICKSCREEN MIRROR\n");
          } 
        i++;
     }

/////////// SCREEN INFOS
   E_Zone *zone1; 
	Eina_List *l1 = NULL; 
	Eina_List* l2 = NULL;
	Eina_List* l3 = NULL;
	E_Randr2_Screen* s;
	E_Randr2_Screen* s1;
	char buf[PATH_MAX];
   int x, y, w, h, ow, oh;
// 	char mode[PATH_MAX];
  
  EINA_LIST_FOREACH(e_randr2->screens, l2, s)
  {				
			
			popup1 = elm_popup_add(e_comp->elm);
// 			evas_object_smart_callback_add(popup1, "block,clicked", _block_clicked_cb1, popup1);
			elm_object_style_set(popup1, "transparent");
			evas_object_layer_set(popup1, E_LAYER_CLIENT_ABOVE);
			evas_object_layer_set(popup1, E_LAYER_POPUP);
			
// 			popup1 = elm_popup_add(e_comp->elm);
// 			popup1 = e_comp_object_util_add(popup1, E_COMP_OBJECT_TYPE_NONE);
// 			elm_object_style_set(popup1, "transparent");
// 			evas_object_layer_set(popup1, E_LAYER_POPUP);
// 			evas_object_layer_set(popup1, E_LAYER_CLIENT_ABOVE);
			
			EINA_LIST_FOREACH(e_comp->zones, l1, zone1)
				{
				if (!strcmp(s->id, zone1->randr2_id)) {
						
						Evas_Object *lbl;
						lbl = elm_entry_add(popup1);
						elm_entry_editable_set(lbl, EINA_FALSE);
						Eina_Strbuf *test = NULL;
						test = eina_strbuf_new();
						switch (s->config.relative.mode)
                    {
                     case E_RANDR2_RELATIVE_UNKNOWN:
									 eina_strbuf_append(test, "Unknown");
                       break;
                     case E_RANDR2_RELATIVE_NONE:
									 eina_strbuf_append(test, "Primary");
                       break;
                     case E_RANDR2_RELATIVE_CLONE:
								  eina_strbuf_append(test, "Clone<br>of:");
								  EINA_LIST_FOREACH(e_randr2->screens, l3, s1) // FIND ALL CLONE DEVICES
									{
										if(s1->config.enabled == EINA_TRUE && s1->info.connected == EINA_TRUE)
										{
											if(s1->config.relative.mode == 1 || s1->config.relative.mode == 2)
											{
												printf("CLONE DEVICES \t %s\n", s1->info.name);
												eina_strbuf_append_printf(test," [%s]" ,s1->info.name);
											}
										}
									}
                       break;
                     case E_RANDR2_RELATIVE_TO_LEFT:
									 eina_strbuf_append(test, "Left Of");
								break;
                     case E_RANDR2_RELATIVE_TO_RIGHT:
									 eina_strbuf_append(test, "Right Of");
								break;
                     case E_RANDR2_RELATIVE_TO_ABOVE:
									 eina_strbuf_append(test, "Above");
								break;
                     case E_RANDR2_RELATIVE_TO_BELOW:
									 eina_strbuf_append(test, "Below");
								break;
                    }
									
						snprintf(buf, sizeof(buf), "%s - [%s] - %s", s->info.screen, s->info.name, eina_strbuf_string_get(test));
						eina_strbuf_free(test);
						elm_object_text_set(lbl, buf);
			         evas_object_show(lbl);
					
						elm_object_content_set(popup1, lbl);
						
						
					   evas_object_geometry_get(lbl, NULL, NULL, &ow, &oh);
// 						evas_object_resize(popup1, ow, oh);
						evas_object_resize(popup1, 150, 50);
						e_zone_useful_geometry_get(zone1, &x, &y, &w, &h);
						evas_object_move(popup1, zone1->x + 100, zone1->y);
						evas_object_show(popup1);
						
							
						printf("%s XY: %i x %i w:%i h:%i\n", zone1->name, zone1->x, zone1->y, zone1->w, zone1->h);
					}
				}

             popups1 = eina_list_append(popups1, popup1);
				 
// 						printf("CLONE DEVICE \t %i\n", s->config.relative.mode);
  }
///////////
	
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
