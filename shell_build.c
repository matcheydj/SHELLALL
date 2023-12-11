#include <stdio.h>
#include <stdlib.h>

// Function to run the build script for the specific shell
int build_shell(char *dir_path, char *archive_filename) {
    char command[256];

    // Change to the directory
    sprintf(command, "cd %s", dir_path);
    system(command);

    // Extract the archive
    sprintf(command, "tar xvf %s", archive_filename);
    system(command);

    // Run the build script
    system("./configure");
    int make_status = system("make");

    // Check for errors
    if (make_status != 0) {
        printf("Error: Build failed.\n");
        return 0;
    }

    printf("Build completed successfully.\n");
    return 1;
}

int main() {
    char *dir_path = "<directory path>";
    char *archive_filename = "<archive filename>";

    int build_status = build_shell(dir_path, archive_filename);

    return 0;
}
