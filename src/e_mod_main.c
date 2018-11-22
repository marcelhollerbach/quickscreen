#include "e.h"
#include "quickscreen.h"

static E_Action* act;

int _quickscreen_log_domain = -1;

/*List of Mirrored Popups*/
Eina_List *popups, *mirrors, *popups_screeninfo;
E_API E_Module_Api e_modapi = { E_MODULE_API_VERSION, "Quickscreen" };

static Evas_Object* popup;

Evas_Object* popup_screeninfo;

void
_block_clicked_cb(void* data EINA_UNUSED,
                  Evas_Object* obj,
                  void* event_info EINA_UNUSED)
{
  Evas_Object *pup, *mirror /*, *popup_screeninfo*/;

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

  free_popup_screeninfo();
}

void
free_popup_screeninfo()
{
  EINA_LIST_FREE(popups_screeninfo, popup_screeninfo)
  {
    evas_object_del(popup_screeninfo);
    popup_screeninfo = NULL;
  }
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
    Evas_Object *pup, *mirror;

    evas_object_del(popup);
    popup = NULL;

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
    EINA_LIST_FREE(popups_screeninfo, popup_screeninfo)
    {
      evas_object_del(popup_screeninfo);
      popup_screeninfo = NULL;
    }
    e_comp_ungrab_input(1, 1);

  }
}

static void
popup_resized(void* data,
              Evas* e EINA_UNUSED,
              Evas_Object* obj,
              void* event_data EINA_UNUSED)
{
  E_Zone* zone;
  Eina_List* l = NULL;
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
  int i = 0, h = 0, w = 0;

  EINA_LIST_FOREACH(e_comp->zones, l, zone)
  {
    if (i == 0) {
      /*center popup on first zone*/
      evas_object_resize(popup, zone->w, zone->h);
      e_comp_object_util_center_on_zone(popup, zone);
		
      evas_object_show(popup);
    } else {
      /*create mirror for each additional zone*/
      mirror = evas_object_image_filled_add(e_comp->evas);
      evas_object_image_source_set(mirror, obj);
      evas_object_image_source_events_set(mirror, EINA_TRUE);

      pup = elm_popup_add(e_comp->elm);

      evas_object_geometry_get(obj, 0, 0, &w, &h);
      evas_object_size_hint_min_set(mirror, w, h);

      elm_object_style_set(pup, "transparent");
      evas_object_layer_set(pup, E_LAYER_POPUP);

      evas_object_smart_callback_add(
        pup, "block,clicked", _block_clicked_cb, popup);

      elm_object_content_set(pup, mirror);

      evas_object_resize(pup, zone->w, zone->h);
      evas_object_geometry_get(pup, 0, 0, &w, &h);
      evas_object_move(pup,
                       zone->x + ((zone->w / 2) - (w / 2)),
                       zone->y + ((zone->h / 2) - (h / 2)));
      evas_object_show(mirror);
      evas_object_show(pup);

      /*append mirror to list of mirrors*/
      mirrors = eina_list_append(mirrors, mirror);
      /*append popup to list of mirrored popups*/
      popups = eina_list_append(popups, pup);

      if (!mirror)
        printf("Mirror is null\n");
    }
    i++;
  }
}

Eina_Strbuf*
find_relto_name(char* rel)
{
  Eina_List* l3;
  E_Randr2_Screen* s1;
  Eina_Strbuf* rel_to_name = NULL;
  rel_to_name = eina_strbuf_new();

  EINA_LIST_FOREACH(e_randr2->screens, l3, s1)
  {
    if (!strcmp(rel, s1->id)) {
      printf("TO DEVICES \t %s\n", s1->info.name);
      eina_strbuf_append_printf(
        rel_to_name, " %s [%s]", s1->info.screen, s1->info.name);
    }
  }
  return rel_to_name;
  eina_strbuf_free(rel_to_name);
}

void
show_screeninfos()
{
  E_Zone* zone;
  Eina_List* l1 = NULL;
  Eina_List* l2 = NULL;
  Eina_List* l3 = NULL;
  E_Randr2_Screen *s, *s1;
  char buf[PATH_MAX];

  EINA_LIST_FOREACH(e_randr2->screens, l1, s)
  {

    popup_screeninfo = elm_popup_add(e_comp->elm);
    elm_object_style_set(popup_screeninfo, "transparent");
    evas_object_layer_set(popup_screeninfo, E_LAYER_POPUP);
    evas_object_event_callback_add(
      popup_screeninfo, EVAS_CALLBACK_KEY_DOWN, key_down, popup_screeninfo);

    EINA_LIST_FOREACH(e_comp->zones, l2, zone)
    {
      if (!strcmp(s->id, zone->randr2_id)) {

        Evas_Object* lbl;
        Eina_Strbuf* buffer = NULL;
        Eina_Strbuf* rel_to_name = NULL;
        buffer = eina_strbuf_new();
        rel_to_name = eina_strbuf_new();

        lbl = elm_entry_add(popup_screeninfo);
        elm_entry_editable_set(lbl, EINA_FALSE);
        switch (s->config.relative.mode) {
          case E_RANDR2_RELATIVE_UNKNOWN:
            eina_strbuf_append(buffer, "Unknown");
            break;
          case E_RANDR2_RELATIVE_NONE:
            eina_strbuf_append(buffer, "Primary");
            break;
          case E_RANDR2_RELATIVE_CLONE:
            eina_strbuf_append(buffer, "<b>Clone of:</b>");
            EINA_LIST_FOREACH(
              e_randr2->screens, l3, s1) // find all CLONE devices
            {
              if (s1->config.enabled == EINA_TRUE &&
                  s1->info.connected == EINA_TRUE) {
                if (s1->config.relative.mode == 1 ||
                    s1->config.relative.mode == 2)
                  eina_strbuf_append_printf(buffer, " [%s]", s1->info.name);
              }
            }
            break;
          case E_RANDR2_RELATIVE_TO_LEFT:
            eina_strbuf_append(buffer, "<b>Left Of<b>");
            eina_strbuf_append_buffer(buffer,
                                      find_relto_name(s->config.relative.to));
            break;
          case E_RANDR2_RELATIVE_TO_RIGHT:
            eina_strbuf_append(buffer, "<b>Right Of</b>");
            eina_strbuf_append_buffer(buffer,
                                      find_relto_name(s->config.relative.to));

            break;
          case E_RANDR2_RELATIVE_TO_ABOVE:
            eina_strbuf_append(buffer, "<b>Above</b>");
            eina_strbuf_append_buffer(buffer,
                                      find_relto_name(s->config.relative.to));
            break;
          case E_RANDR2_RELATIVE_TO_BELOW:
            eina_strbuf_append(buffer, "<b>Below</b>");
            eina_strbuf_append_buffer(buffer,
                                      find_relto_name(s->config.relative.to));
            break;
        }

        snprintf(buf,
                 sizeof(buf),
                 "<custom align=center><b>%s - [%s]</b><br>%s</custom>",
                 s->info.screen,
                 s->info.name,
                 eina_strbuf_string_get(buffer));
        eina_strbuf_free(buffer);
        eina_strbuf_free(rel_to_name);
        elm_object_text_set(lbl, buf);
        evas_object_show(lbl);

        elm_object_content_set(popup_screeninfo, lbl);

        evas_object_resize(popup_screeninfo, 150, 50);
        evas_object_move(popup_screeninfo, zone->x + 75, zone->y + 25);
        evas_object_show(popup_screeninfo);
      }
    }

    popups_screeninfo = eina_list_append(popups_screeninfo, popup_screeninfo);
  }
}

void
qs_key(E_Object* obj EINA_UNUSED, const char* params EINA_UNUSED)
{
  Evas_Object* content;
  E_Zone* zone;
  Eina_List* l = NULL;
  int w = 0, h = 0;
  content = wizard_config_create(e_comp->elm);

  popup = elm_popup_add(e_comp->elm);

  e_comp_grab_input(1, 1);

  elm_object_style_set(popup, "transparent");
  evas_object_layer_set(popup, E_LAYER_POPUP);

  evas_object_smart_callback_add(
    popup, "block,clicked", _block_clicked_cb, popup);

  evas_object_event_callback_add(
    popup, EVAS_CALLBACK_KEY_DOWN, key_down, popup);

  /*add resize callback for popup*/
  evas_object_event_callback_add(
    content, EVAS_CALLBACK_RESIZE, popup_resized, popup);

  elm_object_content_set(popup, content);

  int i = 0;

  EINA_LIST_FOREACH(e_comp->zones, l, zone)
  {
    if (i == 0) {
      evas_object_resize(popup, zone->w, zone->h);
      e_comp_object_util_center_on_zone(popup, zone);
		
      printf("OBJ SIZE W %i  H %i\n", w, h);
      printf("1 ZONE %s %i ZONE H %i\n", zone->name, zone->w / 2, zone->h / 2);
		
      evas_object_show(popup);
    } else {
      Evas_Object* mirror = evas_object_image_filled_add(e_comp->evas);
      evas_object_image_source_set(mirror, content);
      evas_object_image_source_events_set(mirror, EINA_TRUE);

      Evas_Object* pup = elm_popup_add(e_comp->elm);

      elm_object_style_set(pup, "transparent");
      evas_object_layer_set(pup, E_LAYER_POPUP);

      evas_object_smart_callback_add(
        pup, "block,clicked", _block_clicked_cb, mirror);

      elm_object_content_set(pup, mirror);

      evas_object_resize(pup, zone->w, zone->h);
      e_comp_object_util_center_on_zone(pup, zone);
		
      printf("OBJ SIZE W %i  H %i\n", w, h);
      evas_object_show(mirror);
      evas_object_show(pup);

      // append mirror to list of mirrors
      mirrors = eina_list_append(mirrors, mirror);
      // append popup to list of mirrored popups
      popups = eina_list_append(popups, pup);
      printf("QUICKSCREEN MIRROR\n");
    }
    i++;
    printf("ZONE %s x=%i y=%i w=%i h=%i\n",
           zone->name,
           zone->x,
           zone->y,
           zone->w,
           zone->h);
  }

  show_screeninfos();
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
