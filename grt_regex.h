
#ifndef GRT_REGEX_H
#define GRT_REGEX_H

#include "main.h"
#include <gtk/gtk.h>

void grt_regex_init(grt_ref *grt);
void regex_handle_changed(GtkTextBuffer *buffer, gpointer data);
gboolean regex_handle_draw(GtkWidget *w, cairo_t *cr, gpointer data);

#endif
