#include <gtk/gtk.h>
#include "headers/GUI.h"

static void openTableResult(GtkWidget * widget,
                            gpointer user_data){
  if(user_data){
    g_print("%s\n", ((char *)user_data));
  }
  if(widget){
    for(int x = 0; x < 1; x++) continue;
  }

  //GtkWidget * tableResult = returnTableResult();

  //gtk_window_present(GTK_WINDOW(tableResult));

}

static void activate(GtkApplication * app,
                     gpointer user_data){
    
    if(user_data){
      g_print("%d\n", *((int *) user_data));
    }

    GtkWidget * window,
              * box,
              * button;
    
    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Menu");
    gtk_window_set_default_size(GTK_WINDOW(window), 650, 650);
    
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
    
    gtk_window_set_child (GTK_WINDOW (window), box);

    button = gtk_button_new_with_label("Enviar");
    
    g_signal_connect(button, "clicked", G_CALLBACK (openTableResult), NULL);

    gtk_box_append (GTK_BOX (box), button);


    gtk_window_present(GTK_WINDOW(window));
}

int run(int argc, char ** argv){
  GtkApplication * app;
  int status;
  
  app = gtk_application_new("calculo.tabela_logaritmo", G_APPLICATION_DEFAULT_FLAGS);
  
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  
  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return status;
}
