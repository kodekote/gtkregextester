
#ifndef GRT_BUTTON_H
#define GRT_BUTTON_H

#include "main.h"
#include <gtk/gtk.h>

void grt_button_init(grt_ref *grt);
void handle_clicked(GtkButton *btn, gpointer data);

#endif
