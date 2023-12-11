#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_download.h"

// Function to display usage information
void show_usage(char *program_name) {
  printf("Usage: %s [options] <shell_name>...\n", program_name);
  printf("Options:\n");
  printf("  -h, --help   Display this help message\n");
  printf("  -l, --list   List available shells\n");
}

// Function to check if a shell is available
// int is_shell_available(char *shell_name) {
  // ... implement logic to check if the shell is included in the supported list ...
//  return 1; // replace placeholder with actual check
// }

// List of supported shells
char *supported_shells[] = {
    "cmd.exe",
    "PowerShell",
    "WSL",
    "bash",
    "zsh",
    "sh",
    "ksh",
    "tcsh",
    "fish",
    "dash",
    "ash",
    "rc",
    "mksh",
    "busybox ash",
    "nu shell"
};

// Function to check if a shell is available and included in the supported list
int is_shell_supported(char *shell_name) {
    // Check if the shell is available
    char command[256];
    sprintf(command, "which %s > /dev/null 2>&1", shell_name);
    int shell_available = system(command) == 0;

    // Check if the shell is included in the supported list
    int shell_supported = 0;
    for (int i = 0; i < sizeof(supported_shells) / sizeof(char*); i++) {
        if (strcmp(shell_name, supported_shells[i]) == 0) {
            shell_supported = 1;
            break;
        }
    }

    return shell_available && shell_supported;
}

int main() {
    char *shell_name = "<shell name>";

    int shell_supported = is_shell_supported(shell_name);

    if (shell_supported) {
        printf("%s is available and supported.\n", shell_name);
    } else {
        printf("%s is not available or not supported.\n", shell_name);
    }

    return 0;
}

// Function to download and install a shell
int install_shell(char *shell_name) {
  // Check if the shell is available
  if (!is_shell_available(shell_name)) {
    printf("Error: Shell '%s' is not available.\n", shell_name);
    return 0;
  }

  // Get information about the shell
  Shell shell = get_shell_by_name(shell_name);

  // Download and install the shell
  if (!download_shell(shell)) {
    return 0;
  }
  if (!build_and_install_shell(shell)) {
    return 0;
  }
  printf("%s installed successfully.\n", shell.name);

  return 1;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    show_usage(argv[0]);
    return 0;
  }

  int success = 0;

  for (int i = 1; i < argc; i++) {
    char *argument = argv[i];

    // Handle options
    if (strcmp(argument, "-h") == 0 || strcmp(argument, "--help") == 0) {
      show_usage(argv[0]);
      return 0;
    } else if (strcmp(argument, "-l") == 0 || strcmp(argument, "--list") == 0) {
      list_available_shells();
      return 0;
    }

    // Install the specified shell
    if (install_shell(argument)) {
      success = 1;
    }
  }

  return success ? 0 : 1;
}

// This program uses the system function to execute shell commands from within the C program. The is_shell_supported function takes the name of a shell as input, checks if the shell is available on the system by using the which command, and checks if the shell is included in the supported list. It returns a boolean indicating whether the shell is available and supported.

