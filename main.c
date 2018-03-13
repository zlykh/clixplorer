#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>

#define cygdrive "/cygdrive/"

void indent_writer(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
        printf("  ");
    }
}

int print_dir(char *current_path, int indent_level) {
    DIR *dir = opendir(current_path);

    if (dir != NULL) {
        struct dirent *dir_entry = readdir(dir);

        while (dir_entry) {
            if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
                indent_writer(indent_level);
                char *isFolder = dir_entry->d_type == DT_DIR ? "[+]" : "   ";
                printf("%s %s\n", isFolder, dir_entry->d_name);
            }

            dir_entry = readdir(dir);
        }

        closedir(dir);
        printf(")>'.')>: type . (dot) to go up \n");

        return 0;
    } else {
        return 1;
    }
}

void step_back(int *indent_level_ref, char *last_segment, char **current_path_ref) {
    for (int i = 0; i < strlen(last_segment); i++) {
        (*current_path_ref)[strlen(*current_path_ref) - 1] = NULL;
    }
    *indent_level_ref -= 1;
    printf("<(0.o)>: Folder not found!\n");
}

int main() {
    printf("^('.')^: Clixplorer - cli-explorer\n");
    printf("^('.')^: Type local disk symbol (C,D,..)\n");

    char *input_str = calloc(20, sizeof(char));
    char *current_path = calloc(200, sizeof(char));
    char *last_segment = calloc(20, sizeof(char));
    int indent_level = 0;

    strcpy(current_path, cygdrive);

    while (1) {
        gets(input_str);

        if (strcmp(input_str, "q") == 0) {
            printf("(._.'): exit...\n");
            break;
        }

        if (strcmp(input_str, ".") == 0) {
            if (indent_level == 0) {
                printf("\\(*.*)/: You are at the top level!\n");
                print_dir(current_path, indent_level);
                continue;
            }
            step_back(&indent_level, last_segment, &current_path);

        } else {
            input_str = strcat(input_str, "/");
            last_segment = strcpy(last_segment, input_str);
            current_path = strcat(current_path, input_str);
            indent_level += 1;
        }


        printf(")>'.')>: %s\n", current_path);

        int error = print_dir(current_path, indent_level);
        if (error) {
            step_back(&indent_level, last_segment, &current_path);
        }

    }

    free(input_str);
    free(current_path);
    free(last_segment);

    return 0;
}



