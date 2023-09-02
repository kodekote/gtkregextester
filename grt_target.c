
#include "grt_target.h"
#include <regex.h>

void grt_target_init(grt_ref *grt)
{
    GtkTextView *text_target = (GtkTextView *)gtk_builder_get_object( grt->builder, "text_target" );
    GtkTextBuffer *buf = gtk_text_view_get_buffer( text_target );
    gtk_text_buffer_create_tag( buf, "spacing", "letter-spacing", 1400, NULL );

    g_signal_connect( gtk_text_view_get_buffer(text_target), "changed", (GCallback)target_handle_changed, grt );
    g_signal_connect_after( text_target, "draw", (GCallback)target_handle_draw, grt );
}

//
//    HANDLER for signal 'CHANGED' for the GtkTextView 'text_target' (TARGET)
//
void target_handle_changed(GtkTextBuffer *buffer, gpointer data)
{
    grt_ref *grt = (grt_ref *)data;
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_bounds( buffer, &start, &end );
    gtk_text_buffer_apply_tag_by_name( buffer, "spacing", &start, &end );
    gtk_widget_queue_draw( (GtkWidget *)gtk_builder_get_object(grt->builder, "text_regex") );
}

gboolean target_handle_draw(GtkWidget *w, cairo_t *cr, gpointer data)
{
    grt_ref *grt = (grt_ref *)data;
    GtkTextBuffer *buf;
    GtkTextIter start;
    GtkTextIter end;

    gchar *regex = NULL;
    gchar *target = NULL;

    regex_t r;
    regmatch_t match[1];
    int offset;
    size_t offset_max;

    GdkRectangle rect;
    //  (left, top)
    //  |---------------|
    //  |               |
    //  |               |
    //  |---------------|
    //       (right, bot)
    gint left;
    gint top;
    gint right;
    gint bot;

    buf = gtk_text_view_get_buffer( (GtkTextView *)gtk_builder_get_object(grt->builder, "text_regex") );
    gtk_text_buffer_get_start_iter( buf, &start );
    gtk_text_buffer_get_end_iter( buf, &end );
    regex = gtk_text_buffer_get_text( buf, &start, &end, TRUE );
    if ( strlen(regex)>0 )
    {
        if ( regcomp(&r, regex, REG_EXTENDED) == 0 )
        {
            buf = gtk_text_view_get_buffer( (GtkTextView *)w );
            gtk_text_buffer_get_start_iter( buf, &start );
            gtk_text_buffer_get_end_iter( buf, &end );
            target = gtk_text_buffer_get_text( buf, &start, &end, TRUE );
            offset_max = strlen( target );

            offset = 0;
            while ( regexec(&r, target+offset, 1, match, 0) == 0 )
            {
                if ( match[0].rm_so == match[0].rm_eo )
                {
                    if ( ++offset > offset_max )
                    {
                        break;
                    }
                }
                else
                {
//                    printf( "from %d to %d\n", match[0].rm_so+offset, match[0].rm_eo+offset );
                    gtk_text_buffer_get_iter_at_offset( buf, &start, offset+match[0].rm_so );
                    /*
                     the match is from [a,b) or, equivalently, from [a,b-1]
                    */
                    gtk_text_buffer_get_iter_at_offset( buf, &end, offset+match[0].rm_eo-1 );
                    gtk_text_view_get_iter_location( (GtkTextView *)w, &start, &rect );
                    gtk_text_view_buffer_to_window_coords(
                            (GtkTextView *)w,
                            GTK_TEXT_WINDOW_TEXT,
                            rect.x,
                            rect.y,
                            &left,
                            &top);
                    gtk_text_view_get_iter_location( (GtkTextView *)w, &end, &rect );
                    gtk_text_view_buffer_to_window_coords(
                            (GtkTextView *)w,
                            GTK_TEXT_WINDOW_TEXT,
                            rect.x+rect.width,
                            rect.y+rect.height,
                            &right,
                            &bot);
                    cairo_set_source_rgba( cr, 0.0, 0.8, 0.0, 0.25 );
                    cairo_rectangle( cr, left+1, top, right-left-1, bot-top );
                    cairo_fill( cr );
                    cairo_set_source_rgba( cr, 0.0, 0.0, 1.0, 1.0 );
                    cairo_rectangle( cr, left+1, top, 1, bot-top );
                    cairo_fill( cr );
                    cairo_set_source_rgba( cr, 0.0, 0.0, 1.0, 1.0 );
                    cairo_rectangle( cr, right-2, top, 1, bot-top );
                    cairo_fill( cr );

                    offset += match[0].rm_eo;
                }
            }
        }
    }

    if ( regex != NULL )
    {
        g_free( regex );
    }
    if ( target != NULL )
    {
        g_free( target );
    }
    return FALSE;
}
