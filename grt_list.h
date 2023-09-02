
#ifndef GRT_LIST_H
#define GRT_LIST_H

#include "main.h"
#include <gtk/gtk.h>

void grt_list_init(grt_ref *grt);
gboolean handle_focus_out(GtkWidget *w, GdkEventFocus event, gpointer data);
void handle_changed(GtkTreeSelection *sel, gpointer data);

#endif
