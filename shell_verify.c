#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get the version of the shell source code
char* get_shell_version(char *shell_name) {
  char command[256];
  sprintf(command, "%s --version", shell_name);

  // Execute the command and capture the output using a pipe
  FILE* pipe = popen(command, "r");
  if (!pipe) return NULL;

  // Read the first line of output as the version
  char version[64];
  fgets(version, sizeof(version), pipe);
  pclose(pipe);

  // Strip trailing newline character
  version[strcspn(version, "\n")] = '\0';

  return strdup(version);
}

// Function to get the latest version of the shell from the web
char* get_latest_version(char *shell_name) {
  char command[256];
  sprintf(command, "curl -s https://www.kernel.org/pub/linux/utils/%s", shell_name);

  // Execute the command and capture the output using a pipe
  FILE* pipe = popen(command, "r");
  if (!pipe) return NULL;

  // Extract version number from the downloaded HTML content
  char version[64];
  while (fgets(version, sizeof(version), pipe)) {
    // Search for a line containing "Latest version"
    if (strstr(version, "Latest version")) {
      // Extract the version number following ": "
      char* version_start = strstr(version, ": ") + 2;
      strncpy(version, version_start, strcspn(version_start, "<"));
      break;
    }
  }
  pclose(pipe);

  // Strip trailing newline character
  version[strcspn(version, "\n")] = '\0';

  return strdup(version);
}

// Function to compare two versions
int is_latest_version(char *version1, char *version2) {
  int result = strcmp(version1, version2);
  return result == 0;
}
