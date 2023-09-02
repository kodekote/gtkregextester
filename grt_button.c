
#include "grt_button.h"

void grt_button_init(grt_ref *grt)
{
    g_signal_connect(
            gtk_builder_get_object(grt->builder, "button_save"),
            "clicked",
            (GCallback)handle_clicked,
            grt);
    g_signal_connect(
            gtk_builder_get_object(grt->builder, "button_pop"),
            "clicked",
            (GCallback)handle_clicked,
            grt);
    g_signal_connect(
            gtk_builder_get_object(grt->builder, "button_push"),
            "clicked",
            (GCallback)handle_clicked,
            grt);
}

void handle_clicked(GtkButton *btn, gpointer data)
{
    grt_ref *grt = (grt_ref *)data;

    GtkTextBuffer *buf;
    GtkTextIter start;
    GtkTextIter end;
    gchar *str = NULL;

    if ( btn == (GtkButton *)gtk_builder_get_object(grt->builder, "button_save") )
    {
        printf( "saving...\n" );
    }
    else if ( btn == (GtkButton *)gtk_builder_get_object(grt->builder, "button_pop") )
    {

    }
    else if ( btn == (GtkButton *)gtk_builder_get_object(grt->builder, "button_push") )
    {
        buf = gtk_text_view_get_buffer( (GtkTextView *)gtk_builder_get_object(grt->builder, "text_regex") );
        gtk_text_buffer_get_start_iter( buf, &start );
        gtk_text_buffer_get_end_iter( buf, &end );
        str = gtk_text_buffer_get_text( buf, &start, &end, TRUE );
        gtk_text_buffer_set_text( buf, "", -1 );

        gtk_list_store_append( (GtkListStore *)gtk_builder_get_object(grt->builder, "list_store"), &start);
        gtk_list_store_set(  (GtkListStore *)gtk_builder_get_object(grt->builder, "list_store"), &start, 0, str, -1 );
    }
    else
    {
        printf( "unknown button pressed: %s\n", gtk_button_get_label(btn) );
    }

    if ( str != NULL )
    {
        g_free( str );
    }
}
