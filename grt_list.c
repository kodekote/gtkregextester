
#include "grt_list.h"

void grt_list_init(grt_ref *grt)
{
    GtkLabel *label = (GtkLabel *)gtk_label_new( "Regular expressions" );
    GtkTreeViewColumn *col = (GtkTreeViewColumn *)gtk_builder_get_object(grt->builder, "column1");

    gtk_widget_set_margin_start( (GtkWidget *)label, 10 );
    gtk_widget_set_margin_top( (GtkWidget *)label, 10 );
    gtk_widget_set_margin_bottom( (GtkWidget *)label, 10 );
    gtk_tree_view_column_set_widget( col, (GtkWidget *)label );
    gtk_widget_show( (GtkWidget *)label );

    g_signal_connect(
            gtk_builder_get_object(grt->builder, "tree_view"),
            "focus-out-event",
            (GCallback)handle_focus_out,
            grt);
}

gboolean handle_focus_out(GtkWidget *w, GdkEventFocus event, gpointer data)
{
    GtkTreeSelection *sel = gtk_tree_view_get_selection( (GtkTreeView *)w );
    gtk_tree_selection_unselect_all( sel );

    return FALSE;
}
