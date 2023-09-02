
#include "grt_window.h"

void grt_window_init(grt_ref *grt)
{
    g_signal_connect( gtk_builder_get_object(grt->builder, "window"), "destroy", (GCallback)handle_destroy, grt );
}

void handle_destroy(GtkWidget *w, gpointer data)
{
    grt_ref *grt = (grt_ref *)data;

    if ( (void *)w == gtk_builder_get_object(grt->builder, "window") )
    {
        gtk_main_quit();
    }
    else
    {
        printf( "signal 'destroy' sent to unknown widget: %ld\n", (long)w );
    }
}
