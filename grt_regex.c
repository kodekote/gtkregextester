
#include "grt_regex.h"
#include <regex.h>

#define STATUS_RECT_W 20
#define STATUS_RECT_H 20

void grt_regex_init(grt_ref *grt)
{
    GtkTextView *text_regex = (GtkTextView *)gtk_builder_get_object( grt->builder, "text_regex" );
    GtkTextBuffer *buf = gtk_text_view_get_buffer( text_regex );
    gtk_text_buffer_create_tag( buf, "spacing", "letter-spacing", 1400, NULL );

    g_object_set_data( (GObject *)text_regex, "draw-queued", (gpointer)FALSE );

    g_signal_connect( gtk_text_view_get_buffer( text_regex ), "changed", (GCallback)regex_handle_changed, grt );
    g_signal_connect_after( text_regex, "draw", (GCallback)regex_handle_draw, grt );
}

void regex_handle_changed(GtkTextBuffer *buffer, gpointer data)
{
    grt_ref *grt = (grt_ref *)data;
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_bounds( buffer, &start, &end );
    gtk_text_buffer_apply_tag_by_name( buffer, "spacing", &start, &end );
    gtk_widget_queue_draw( (GtkWidget *)gtk_builder_get_object(grt->builder, "text_target") );
}

gboolean regex_handle_draw(GtkWidget *w, cairo_t *cr, gpointer data)
{
    GtkTextBuffer *buf;
    GtkTextIter start;
    GtkTextIter end;
    gchar *str;
    regex_t r;
    gboolean is_valid;
    GdkRectangle rect;

//    printf( "regex_handle_draw\n" );

    buf = gtk_text_view_get_buffer( (GtkTextView *)w );
    gtk_text_buffer_get_start_iter( buf, &start );
    gtk_text_buffer_get_end_iter( buf, &end );
    str = gtk_text_buffer_get_text( buf, &start, &end, TRUE );

    if ( strlen(str) > 0 )
    {
        is_valid = ( regcomp(&r, str, REG_EXTENDED) == 0 );
        regfree( &r );
        if ( is_valid )
        {
            cairo_set_source_rgba( cr, 0.0, 1.0, 0.0, 0.5 );
        }
        else
        {
            cairo_set_source_rgba( cr, 1.0, 0.0, 0.0, 0.5 );
        }
    }
    else
    {
        cairo_set_source_rgba( cr, 1.0, 1.0, 0.0, 0.5 );
    }

    gtk_text_view_get_visible_rect( (GtkTextView *)w, &rect );

    if ( g_object_get_data((GObject *)w, "draw-queued") == FALSE )
    {
        g_object_set_data( (GObject *)w, "draw-queued", (gpointer)TRUE );
        gtk_widget_queue_draw_area( w, rect.width - STATUS_RECT_W - 5, 5, STATUS_RECT_W, STATUS_RECT_H );
    }
    else
    {
        g_object_set_data( (GObject *)w, "draw-queued", (gpointer)FALSE );
    }
    cairo_rectangle( cr, rect.width - STATUS_RECT_W - 5, 5, STATUS_RECT_W, STATUS_RECT_H );
    cairo_fill( cr );

    g_free( str );
    return FALSE;
}
