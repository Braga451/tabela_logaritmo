#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <mathCore.h>
#include <utils.h>
#include "headers/GUI.h"

typedef struct{
  GtkAdjustment * inferiorLimit;
  GtkAdjustment * superiorLimit;
  GtkAdjustment * base;
  GtkWidget * isLn;
}DATA_ADJUSTMENT;

void populateLimit(INTERVAL * interval, 
                   long double iteration,
                   long double inferiorLimit,
                   long double superiorLimit,
                   long double * base){
  long double numToReturn = 0.00,
              executionTime = 0.00,
              lnBase = ln(*base);
  for(long double x = inferiorLimit; x < (superiorLimit + iteration); x += iteration){
    timerFunctionHandler(&numToReturn, &executionTime, &x, base, &lnBase, &ln, &logN);
    pushInterval(interval, numToReturn);
    sumIntervalExecutionTime(interval, executionTime);
  }
}

void populateSecondAndThirdIntervalByOne(TABLE_DATA * tableData){
  INTERVAL * first = getIntervalFromTableData(tableData, 1), 
           * second =  getIntervalFromTableData(tableData, 2), 
           * third = getIntervalFromTableData(tableData, 3);
  long double * data = getIntervalData(first);
  int sizeofData = getIntervalSizeofData(first);
  for(int x = 0; x < sizeofData; x += 10){
    pushInterval(second, data[x]);
  }
  for(int x = 0; x < sizeofData; x += 20){
    pushInterval(third, data[x]);
  }
}

TABLE_DATA * returnPopulatedTableData(long double inferiorLimit, 
                                      long double superiorLimit, 
                                      long double * base){
  TABLE_DATA * tableData = returnTableData(*base);
  
  populateLimit(getIntervalFromTableData(tableData, 1), 0.01, inferiorLimit, superiorLimit, base);
  //populateLimit(getIntervalFromTableData(tableData, 2), 0.1, inferiorLimit, superiorLimit, base);
  //populateLimit(getIntervalFromTableData(tableData, 3), 0.2, inferiorLimit, superiorLimit, base);
  
  populateSecondAndThirdIntervalByOne(tableData);

  return tableData;
}

GtkWidget * returnTableText(char * text){
  char * formatedText = (char *) malloc(sizeof(char) * (strlen(text) + 59));

  sprintf(formatedText, "<span font-size=\"24pt\">%s</span>", text);

  GtkWidget * header = gtk_label_new(text);

  gtk_label_set_markup(GTK_LABEL(header), formatedText);

  return header;
}

void attachColumnToTable(GtkWidget * table, 
                         char * strLongDoubleBase){

}

GtkWidget * returnTable(TABLE_DATA * tableData){
  GtkWidget * table = gtk_grid_new(),
            * headerFirst = returnTableText("0.01"),
            * headerSecond = returnTableText("0.1"),
            * headerThird = returnTableText("0.2");
  
  INTERVAL * first = getIntervalFromTableData(tableData, 1), 
           * second =  getIntervalFromTableData(tableData, 2), 
           * third = getIntervalFromTableData(tableData, 3);
  
  
  long double * dataFirst = getIntervalData(first),
              * dataSecond = getIntervalData(second),
              * dataThird = getIntervalData(third);
  
  int sizeofDataFirst = getIntervalSizeofData(first), 
      sizeofDataSecond = getIntervalSizeofData(second),
      sizeofDataThird = getIntervalSizeofData(third);
  
  char * strLongDoubleBase = (char *) calloc(12, sizeof(char));
       snprintf(strLongDoubleBase, 11, "%Lf", returnTableDataBase(tableData)); // Todo: Discover how to put data in labels
       * strLongDoubleLogNumber = (char *) malloc(sizeof(char) * 12),
       * strLongDoubleResultNumber = (char *) malloc(sizeof(char) * 12),
       * finalResult = (char *) malloc(sizeof(char) * 42);

  gtk_grid_set_column_homogeneous ( GTK_GRID(table), true);
  gtk_grid_set_row_homogeneous(GTK_GRID(table), true);

  gtk_grid_attach(GTK_GRID(table), headerFirst, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(table), headerSecond, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(table), headerThird, 3, 1, 1, 1);
  
  for(int x = 2; x < sizeofDataFirst + 2; x++){
    gtk_grid_attach(GTK_GRID(table), returnTableText(dataFirst[x - 2]), 1, x, 1, 1);
  }
  
  for(int x = 2; x < sizeofDataSecond + 2; x++){
    gtk_grid_attach(GTK_GRID(table), returnTableText(dataSecond[x - 2]), 2, x, 1, 1);
  }

  for(int x = 2; x < sizeofDataThird + 2; x++){
    gtk_grid_attach(GTK_GRID(table), returnTableText(dataThird[x - 2]), 3, x, 1, 1);
  }

  return table;
}

static void presentLogTable(GtkWidget * widget,
                            gpointer user_data){
  if(user_data && widget){
    long double 
      inferiorLimit = gtk_adjustment_get_value(((DATA_ADJUSTMENT *) user_data)->inferiorLimit),
      superiorLimit = gtk_adjustment_get_value(((DATA_ADJUSTMENT *) user_data)->superiorLimit),
      base = gtk_adjustment_get_value(((DATA_ADJUSTMENT *) user_data)->base);
    if(base == 1){
      return;
    }
    gboolean isLn = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(((DATA_ADJUSTMENT *)user_data)->isLn)); 
    
    g_print("%Lf\n", inferiorLimit);
    g_print("%Lf\n", superiorLimit);
    g_print("%Lf\n", base);
    g_print("%d\n\n", isLn);

    GtkWidget * window = gtk_window_new();

    gtk_window_set_child(GTK_WINDOW(window), returnTable(returnPopulatedTableData(inferiorLimit, superiorLimit, isLn ? NULL : &base)));

    gtk_window_present(GTK_WINDOW(window));
  }
}

static void activate(GtkApplication * app,
                     gpointer user_data){
    
    if(user_data){
      g_print("%d\n", *((int *) user_data));
    }
    
    DATA_ADJUSTMENT * data = (DATA_ADJUSTMENT *) malloc(sizeof(DATA_ADJUSTMENT));

    GtkWidget * window,
              * box,
              * button,
              * inferiorLimitInput,
              * superiorLimitInput,
              * baseInput,
              * inferiorLimitLabel,
              * superiorLimitLabel,
              * baseLabel,
              * toggleButtonNaturalLog;
    
    GtkAdjustment * inferiorLimitAdjustment,
                  * superiorLimitAdjustment,
                  * baseAdjustment;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Menu");
    gtk_window_set_default_size(GTK_WINDOW(window), 650, 650);
    
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
    
    inferiorLimitLabel = gtk_label_new("Limite inferior");
    inferiorLimitAdjustment =  gtk_adjustment_new (0.00, 1.0, 1000000.00, 1, 0.1, 0.0);
    inferiorLimitInput = gtk_spin_button_new(inferiorLimitAdjustment, 1.0, 4);
    
    superiorLimitLabel = gtk_label_new("Limite superior");
    superiorLimitAdjustment =  gtk_adjustment_new (0.00, 1.0, 1000000.00, 1, 0.1, 0.0);
    superiorLimitInput = gtk_spin_button_new(superiorLimitAdjustment, 1.0, 4);
    
    baseLabel = gtk_label_new("Base");
    baseAdjustment =  gtk_adjustment_new (0.00, 1.0, 1000000.00, 1, 0.1, 0.0);
    baseInput = gtk_spin_button_new(baseAdjustment, 1.0, 4);
    
    toggleButtonNaturalLog = gtk_toggle_button_new_with_label("Logaritmo natural");

    gtk_window_set_child (GTK_WINDOW (window), box);

    button = gtk_button_new_with_label("Enviar");
    
    gtk_box_append(GTK_BOX(box), inferiorLimitLabel);
    gtk_box_append(GTK_BOX(box), inferiorLimitInput);
    
    gtk_box_append(GTK_BOX(box), superiorLimitLabel);
    gtk_box_append(GTK_BOX(box), superiorLimitInput);
    
    gtk_box_append(GTK_BOX(box), baseLabel);
    gtk_box_append(GTK_BOX(box), baseInput);
    gtk_box_append(GTK_BOX(box), toggleButtonNaturalLog);

    data->inferiorLimit = inferiorLimitAdjustment;
    data->superiorLimit = superiorLimitAdjustment;
    data->base = baseAdjustment;
    data->isLn = toggleButtonNaturalLog;

    g_signal_connect(button, "clicked", G_CALLBACK (presentLogTable), data);
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
