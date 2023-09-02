
#include "main.h"
#include "grt_window.h"
#include "grt_regex.h"
#include "grt_target.h"
#include "grt_list.h"
#include "grt_button.h"

//  [a-z]\s*\+\s*[a-z]\s*\=\s*[0-9]+

int main(int argc, char *argv[]) {
    grt_ref grt = { NULL };

    gtk_init( &argc, &argv );
    _enable_css_styler();

    GtkBuilder *builder = gtk_builder_new_from_file( "gtkregextester.ui" );
    grt.builder = builder;

    grt_window_init( &grt );
    grt_regex_init( &grt );
    grt_target_init( &grt );
    grt_list_init( &grt );
    grt_button_init( &grt );

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
