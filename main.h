
#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>

typedef struct grt_ref
{
    GtkBuilder *builder;
    gchar *regex;
    gchar *target;
} grt_ref;

void _enable_css_styler();

#endif
