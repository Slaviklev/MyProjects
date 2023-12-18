#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "frequency_analysis.h"

GtkWidget *labelSucc;

char *textfile;
char *cryptfile;

void on_file_selected(GtkFileChooserButton *filechooserbutton, gpointer user_data) {
    const gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    textfile = (char *)filename;
}

void on_folder_selected(GtkFileChooserButton *filechooserbutton, gpointer user_data) {
    const gchar *foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    cryptfile = (char *)foldername;
}

static void programRunner(GtkWidget *widget, gpointer data) {
    if (textfile && cryptfile) {
        const char *sfile = "decrypted.txt";
        char dfile[strlen(cryptfile) + strlen(sfile)];
        strcpy(dfile, cryptfile);
        strcat(dfile, "/");
        strcat(dfile, sfile);
        unsigned int sizef = fsize(textfile);
        char ciphertext[sizef];
        cptext(ciphertext, sizef, textfile);
        frequencyAnalysis(ciphertext, dfile);
        gtk_label_set_markup(GTK_LABEL(labelSucc), "<span foreground='green'>Success</span>");
    } else {
        gtk_label_set_markup(GTK_LABEL(labelSucc), "<span foreground='red'>Unsuccess</span>");
    }
}

static void on_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    gtk_widget_destroy(window);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *file_chooser_button;
    GtkWidget *folder_chooser_button;
    GtkWidget *button, *button2;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Frequency_analyzer");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    labelSucc  = gtk_label_new(NULL); 

    file_chooser_button = gtk_file_chooser_button_new("Select a File", GTK_FILE_CHOOSER_ACTION_OPEN);
    g_signal_connect(file_chooser_button, "file-set", G_CALLBACK(on_file_selected), NULL);

    folder_chooser_button = gtk_file_chooser_button_new("Select a Folder", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    g_signal_connect(folder_chooser_button, "file-set", G_CALLBACK(on_folder_selected), NULL);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect(button, "clicked", G_CALLBACK(programRunner), window);

    button2 = gtk_button_new_with_label("Quit");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), file_chooser_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), folder_chooser_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), labelSucc, FALSE, FALSE, 5);

    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), button2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), button, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}