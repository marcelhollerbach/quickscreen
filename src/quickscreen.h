#ifndef QUICKSCREEN_H
#define QUICKSCREEN_H

extern int _quickscreen_log_domain;
#undef DBG
#undef INF
#undef WRN
#undef ERR
#undef CRIT
#define DBG(...) EINA_LOG_DOM_DBG(_quickscreen_log_domain, __VA_ARGS__)
#define INF(...) EINA_LOG_DOM_INF(_quickscreen_log_domain, __VA_ARGS__)
#define WRN(...) EINA_LOG_DOM_WARN(_quickscreen_log_domain, __VA_ARGS__)
#define ERR(...) EINA_LOG_DOM_ERR(_quickscreen_log_domain, __VA_ARGS__)
#define CRIT(...) EINA_LOG_DOM_CRIT(_quickscreen_log_domain, __VA_ARGS__)

E_Config_Dialog* quickscreen_settings(Evas_Object *parent, const char *params);

Evas_Object*     advanced_settings_create(Evas_Object *win);
void             advanced_settings_apply(Evas_Object *obj);
Evas_Object*     wizard_config_create(Evas_Object *win);
void             wizard_config_apply(Evas_Object *obj);
void             free_popup_screeninfo();
Eina_Strbuf*     find_relto_name(char *rel);
void             show_screeninfos();
void 				  qs_key(E_Object* obj EINA_UNUSED, const char* params EINA_UNUSED);

void      _block_clicked_cb(void* data EINA_UNUSED, Evas_Object* obj, void* event_info EINA_UNUSED);
#define _(a) a

#endif
