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

void             quickscreen_advanced_setup(E_Config_Dialog_View *v);

#define _(a) a

#endif
