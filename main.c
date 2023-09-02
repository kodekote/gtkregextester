
#include "main.h"
#include "grt_window.h"
#include "grt_regex.h"
#include "grt_target.h"

int main(int argc, char *argv[]) {
    grt_ref grt = { NULL };

    gtk_init( &argc, &argv );
    _enable_css_styler();

    GtkBuilder *builder = gtk_builder_new_from_file( "gtkregextester.ui" );
    grt.builder = builder;

    grt_window_init( &grt );
    grt_regex_init( &grt );
    grt_target_init( &grt );

//    GtkLabel *label = (GtkLabel *)gtk_label_new( "Regular expressions" );
//    gtk_widget_set_margin_start( (GtkWidget *)label, 10 );
//    gtk_widget_set_margin_top( (GtkWidget *)label, 10 );
//    gtk_widget_set_margin_bottom( (GtkWidget *)label, 10 );
//    gtk_tree_view_column_set_widget(
//            (GtkTreeViewColumn *)gtk_builder_get_object(builder, "column1"),
//            (GtkWidget *)label );
//    gtk_widget_show( (GtkWidget *)label );

//    GtkListStore *list_store = (GtkListStore *)gtk_builder_get_object( builder, "list_store" );
//    GtkTreeIter iter;
//    gtk_list_store_append( list_store, &iter );
//    gtk_list_store_set( list_store, &iter, 0, "ab?", -1 );

//    gtk_widget_show_all( (GtkWidget *)gtk_builder_get_object(builder, "window") );

    gtk_main();
    return 0;
}

void _enable_css_styler()
{
    GtkCssProvider *styler = gtk_css_provider_new();

    gtk_css_provider_load_from_path( styler, "gtkregextester.css", NULL );
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        (GtkStyleProvider *)styler,
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref( styler );
}
