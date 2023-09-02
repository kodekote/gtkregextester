gboolean sig_row_activated(GtkTreeView *view, GdkEventButton *event, void *data)
{
    static gint64 last_sig = 0;

    gint64 time_delta = g_get_monotonic_time() - last_sig;
    last_sig = g_get_monotonic_time();

    GtkTreeSelection *sel = gtk_tree_view_get_selection( view );
    GtkTreePath *path;

    if ( time_delta < 500000 )
    {
        printf( "double click\n" );
        return FALSE;
    }
    if ( event->type != GDK_BUTTON_PRESS || event->button != 1 )
    {
        return TRUE;
    }
    if ( !gtk_tree_view_get_path_at_pos(view, (int)event->x, (int)event->y, &path, NULL, NULL, NULL) )
    {
        gtk_tree_selection_unselect_all( sel );
    }
    else if ( gtk_tree_selection_path_is_selected(sel, path) )
    {
        gtk_tree_selection_unselect_path( sel, path );
    }
    else
    {
        gtk_tree_selection_select_path( sel, path );
    }
    return TRUE;
}
