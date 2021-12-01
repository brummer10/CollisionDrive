
#define CONTROLS 7

#define GUI_ELEMENTS 0

#define TAB_ELEMENTS 0


#define PLUGIN_UI_URI "https://github.com/brummer10/CollisionDrive_Gui"


#include "lv2_plugin.h"


#include "xresources.h"

void set_costum_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 1.000},
        .bg =       { 0.100, 0.100, 0.100, 1.000},
        .base =     { 0.000, 0.000, 0.000, 1.000},
        .text =     { 0.900, 0.900, 0.900, 1.000},
        .shadow =   { 0.000, 0.000, 0.000, 0.200},
        .frame =    { 0.000, 0.000, 0.000, 1.000},
        .light =    { 0.100, 0.100, 0.100, 1.000}
    };

    main->color_scheme->prelight = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 1.000, 0.000, 1.000, 1.000},
        .bg =       { 0.250, 0.250, 0.250, 1.000},
        .base =     { 0.300, 0.300, 0.300, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.100, 0.100, 0.100, 0.400},
        .frame =    { 0.300, 0.300, 0.300, 1.000},
        .light =    { 0.300, 0.300, 0.300, 1.000}
    };

    main->color_scheme->selected = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.900, 0.900, 0.900, 1.000},
        .bg =       { 0.200, 0.200, 0.200, 1.000},
        .base =     { 0.500, 0.180, 0.180, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.800, 0.180, 0.180, 0.200},
        .frame =    { 0.500, 0.180, 0.180, 1.000},
        .light =    { 0.500, 0.180, 0.180, 1.000}
    };

    main->color_scheme->active = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.000, 1.000, 1.000, 1.000},
        .bg =       { 0.000, 0.000, 0.000, 1.000},
        .base =     { 0.180, 0.380, 0.380, 1.000},
        .text =     { 0.750, 0.750, 0.750, 1.000},
        .shadow =   { 0.180, 0.380, 0.380, 0.500},
        .frame =    { 0.180, 0.380, 0.380, 1.000},
        .light =    { 0.180, 0.380, 0.380, 1.000}
    };

    main->color_scheme->insensitive = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 0.500},
        .bg =       { 0.100, 0.100, 0.100, 0.500},
        .base =     { 0.000, 0.000, 0.000, 0.500},
        .text =     { 0.900, 0.900, 0.900, 0.500},
        .shadow =   { 0.000, 0.000, 0.000, 0.100},
        .frame =    { 0.000, 0.000, 0.000, 0.500},
        .light =    { 0.100, 0.100, 0.100, 0.500}
    };
}

#include "lv2_plugin.cc"

typedef struct {
    bool open;
    cairo_surface_t* closed_knob;
} X11_UI_Private_t;


static void show_my_label(Widget_t *w, int width, int height) {
    use_text_color_scheme(w, get_color_state(w));
    cairo_text_extents_t extents;
    /** show label below the knob**/
    cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
    cairo_text_extents(w->crb,w->label , &extents);
    cairo_move_to (w->crb, (width*0.5)-(extents.width/2), height-(extents.height/4));
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}

void draw_my_image_knob(Widget_t *w, int width_t, int height_t) {
    X11_UI* ui = (X11_UI*)w->parent_struct;
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double x = (double)width_t/(double)height;
    double y = (double)height/(double)width_t;
    double knobstate = adj_get_state(w->adj_y);
    int findex = (int)(((width/height)-1) * knobstate);
    cairo_scale(w->crb, x,x);
    //widget_set_scale(w);
    if (ps->open)
        cairo_set_source_surface (w->crb, w->image, -height*findex, 0);
    else
        cairo_set_source_surface (w->crb, ps->closed_knob, -height*findex, 0);
    cairo_rectangle(w->crb,0, 0, height, height);
    cairo_fill(w->crb);
    //widget_reset_scale(w);
    cairo_scale(w->crb, y,y);
}

void draw_my_knob(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int width = attrs.width-2;
    int height = attrs.height-2;

    /** get values for the knob **/

    int knobx1 = width* 0.5;

    int knoby1 = height * 0.5;
    if (w->image) 
        draw_my_image_knob(w, width, height);
    use_text_color_scheme(w, get_color_state(w));
    cairo_text_extents_t extents;
    /** show value on the kob**/
    if (w->state) {
        char s[64];
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        float value = adj_get_value(w->adj);
        if (fabs(w->adj->step)>0.99) {
            snprintf(s, 63,"%d",  (int) value);
        } else if (fabs(w->adj->step)>0.09) {
            snprintf(s, 63, format[1-1], value);
        } else {
            snprintf(s, 63, format[2-1], value);
        }
        cairo_set_font_size (w->crb, w->app->small_font/w->scale.ascale);
        cairo_text_extents(w->crb, s, &extents);
        cairo_move_to (w->crb, knobx1-extents.width/2, knoby1+extents.height*2);
        cairo_show_text(w->crb, s);
        cairo_new_path (w->crb);
    }

    show_my_label(w, width, height);
}


void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
    if (index == 2) adj_set_value(ui->widget[6]->adj, adj_get_value(ui->widget[0]->adj));
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri, float scale) {
    (*w) = 300 * scale; //set initial width of main window
    (*h) = 381 * scale; //set initial height of main window
}

const char* plugin_set_name() {
    return "CollisionDrive"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri, float scale) {
    X11_UI_Private_t *ps =(X11_UI_Private_t*)malloc(sizeof(X11_UI_Private_t));
    ui->private_ptr = ps;
    ps->open = false;
    set_costum_theme(&ui->main);
    ui->widget[0] = add_lv2_image_toggle (ui->widget[0], ui->win, 2, "", ui, 120,  270, 60 * scale, 60 * scale);
    widget_get_png(ui->widget[0], LDVAR(footsw_png));

    ui->widget[1] = add_lv2_knob (ui->widget[1], ui->win, 3, "BRIGHT", ui, 165,  30, 60 * scale, 80 * scale);
    widget_get_png(ui->widget[1], LDVAR(knob_black_1__png));
    set_adjustment(ui->widget[1]->adj, 0.500, 0.500, 0.000, 1.000, 0.010, CL_CONTINUOS);

    ui->widget[2] = add_lv2_knob (ui->widget[2], ui->win, 4, "GATE", ui, 120,  135, 60 * scale, 80 * scale);
    widget_get_png(ui->widget[2], LDVAR(tune_png));
    ps->closed_knob = surface_get_png(ui->widget[2], ps->closed_knob, LDVAR(tune_blue_png));
    ui->widget[2]->func.expose_callback = draw_my_knob;
    set_adjustment(ui->widget[2]->adj, -15.000, -15.000, -30.000, -10.000, 0.400, CL_CONTINUOS);

    ui->widget[3] = add_lv2_knob (ui->widget[3], ui->win, 5, "ATTACK", ui, 30,  120, 60 * scale, 80 * scale);
    widget_get_surface_ptr(ui->widget[3], ui->widget[1]);
    set_adjustment(ui->widget[3]->adj, 3.000, 3.000, 0.000, 5.000, 1.000, CL_CONTINUOS);

    ui->widget[4] = add_lv2_knob (ui->widget[4], ui->win, 6, "DRIVE", ui, 210,  120, 60 * scale, 80 * scale);
    widget_get_surface_ptr(ui->widget[4], ui->widget[1]);
    set_adjustment(ui->widget[4]->adj, 0.100, 0.100, 0.000, 1.000, 0.010, CL_CONTINUOS);

    ui->widget[5] = add_lv2_knob (ui->widget[5], ui->win, 7, "LEVEL", ui, 75,  30, 60 * scale, 80 * scale);
    widget_get_surface_ptr(ui->widget[5], ui->widget[1]);
    set_adjustment(ui->widget[5]->adj, -6.000, -6.000, -20.000, 4.000, 0.240, CL_CONTINUOS);

    ui->widget[6] = add_lv2_image_toggle (ui->widget[6], ui->win, 2, "", ui, 128,  225, 44 * scale, 44 * scale);
    widget_get_png(ui->widget[6], LDVAR(led_red_png));

}

void plugin_cleanup(X11_UI *ui) {
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    cairo_surface_destroy(ps->closed_knob);    
    free(ps);
    ui->private_ptr = NULL;
    // clean up used sources when needed
}


void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    float value = *(float*)buffer;
    X11_UI_Private_t *ps = (X11_UI_Private_t*)ui->private_ptr;
    if (port_index == 8) {
        ps->open = value > 0.0001 ? true : false;
        expose_widget(ui->widget[2]);
    }
    // port value change message from host
    // do special stuff when needed
}

