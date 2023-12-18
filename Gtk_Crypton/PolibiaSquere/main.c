#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "squerePolibia.h"

GtkWidget *labelSucc;
GtkWidget *entry;
GtkWidget *radio_button1, *radio_button2;

bool  encryptFlag;
bool  decryptFlag;
char *textfile;
char *cryptfile;
char *alfabe;

void on_radio_button1_toggled(GtkToggleButton *button, gpointer user_data) {
    gboolean state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button1));
    encryptFlag = state;
}

void on_radio_button2_toggled(GtkToggleButton *button, gpointer user_data) {
    gboolean state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button2));
    decryptFlag = state;
}

void on_file_selected(GtkFileChooserButton *filechooserbutton, gpointer user_data) {
    const gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    textfile = (char *)filename;
}

void on_folder_selected(GtkFileChooserButton *filechooserbutton, gpointer user_data) {
    const gchar *foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    cryptfile = (char *)foldername;
}

void alfabet(char *alfabe) {
    for (unsigned int i=0, c=32; c < 127; c++, i++) {
        alfabe[i] = c;
    }
}

static void programRunner(GtkWidget *widget, gpointer data) {
    const gchar *key = gtk_entry_get_text(GTK_ENTRY(entry));
    unsigned int row = 2;
    unsigned int col = strlen(key);
    unsigned int matrix[row][col];

    if ((textfile && cryptfile) && strcmp(key, "") && (encryptFlag || decryptFlag)) {
        char alfabe[127-32];
        alfabet(alfabe);
        const unsigned int row = calc_rows(key, alfabe);
        const unsigned int col = 4;
        char matrix[row][col];
        memset(matrix, 0, sizeof(matrix));
        squere(alfabe, key, row, col, matrix);

        if (encryptFlag) {
            const char *sfile = "encrypted.txt";
            char efile[strlen(cryptfile) + strlen(sfile)];
            strcpy(efile, cryptfile);
            strcat(efile, "/");
            strcat(efile, sfile);
            
            encrypt(row, col, matrix, textfile, efile);

            gtk_label_set_markup(GTK_LABEL(labelSucc), "<span foreground='green'>Success</span>");
        }
        if (decryptFlag) {
            const char *sfile = "decrypted.txt";
            char dfile[strlen(cryptfile) + strlen(sfile)];
            strcpy(dfile, cryptfile);
            strcat(dfile, "/");
            strcat(dfile, sfile);
            
            decrypt(row, col, matrix, textfile, dfile);

            gtk_label_set_markup(GTK_LABEL(labelSucc), "<span foreground='green'>Success</span>");

        }
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
    gtk_window_set_title(GTK_WINDOW(window), "PolibiaSquere");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    labelSucc  = gtk_label_new(NULL);
    

    radio_button1 = gtk_radio_button_new_with_label(NULL, "Encrypt");
    g_signal_connect(radio_button1, "toggled", G_CALLBACK(on_radio_button1_toggled), "Encrypt");
    radio_button2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button1), "Decrypt");
    g_signal_connect(radio_button2, "toggled", G_CALLBACK(on_radio_button2_toggled), "Decrypt");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button2), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button1), TRUE);
 

    file_chooser_button = gtk_file_chooser_button_new("Select a File", GTK_FILE_CHOOSER_ACTION_OPEN);
    g_signal_connect(file_chooser_button, "file-set", G_CALLBACK(on_file_selected), NULL);

    folder_chooser_button = gtk_file_chooser_button_new("Select a Folder", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    g_signal_connect(folder_chooser_button, "file-set", G_CALLBACK(on_folder_selected), NULL);

    button = gtk_button_new_with_label("Ok");
    g_signal_connect(button, "clicked", G_CALLBACK(programRunner), window);

    button2 = gtk_button_new_with_label("Quit");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), window);

    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter key");


    GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), radio_button1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), radio_button2, FALSE, FALSE, 5);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), file_chooser_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), folder_chooser_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 5);
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