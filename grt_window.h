
#ifndef GRT_WINDOW_H
#define GRT_WINDOW_H

#include "main.h"
#include <gtk/gtk.h>

void grt_window_init(grt_ref *grt);
void handle_destroy(GtkWidget *window, gpointer data);

#endif
