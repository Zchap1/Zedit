#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
static GtkWidget *txt;
static GtkWidget *filetitle;
static GtkWidget  *nameinfo;
static GtkTextBuffer *block;
static GtkTextIter start,end;
void do_calculate(GtkWidget *calculate, gpointer data) {
    char buffer[128];
    const gchar* filename = gtk_entry_get_text(GTK_ENTRY(filetitle));
    FILE * fp;
    fp = fopen (filename,"w");



    block = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt));
    gtk_text_buffer_get_start_iter(block,&start);
    gtk_text_buffer_get_end_iter(block,&end);
    


    fprintf (fp,gtk_text_buffer_get_text(block,&start,&end,0));
    fclose (fp);
    snprintf(buffer, sizeof(buffer), "Successfully wrote to file %s",filename);
    
    gtk_label_set_text(GTK_LABEL(nameinfo), buffer);
}

// gcc 007_gtk.c -o 007_gtk `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
    GtkWidget *window, *grid, *calculate;
    gtk_init(&argc, &argv);
//window stuff
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "Zedit");
    gtk_widget_set_size_request (window, 640, 480);

//end of window stuff
//create grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
//add grid to window




    txt = gtk_text_view_new();
    





filetitle = gtk_entry_new();



//two entries
    gtk_widget_set_size_request(txt,640,480);//set it a decent size
//button stuff
    calculate = gtk_button_new_with_label("Save");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
//connect button to calculate function    
    nameinfo = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid),nameinfo,0,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),filetitle,0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),calculate,0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),txt,0,2,1,1);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

