
#ifndef GRT_TARGET_H
#define GRT_TARGET_H

#include "main.h"
#include <gtk/gtk.h>

void grt_target_init(grt_ref *grt);
void target_handle_changed(GtkTextBuffer *buffer, gpointer data);
gboolean target_handle_draw(GtkWidget *w, cairo_t *cr, gpointer data);

#endif
