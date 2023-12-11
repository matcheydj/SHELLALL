#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sha3.h>

// Configuration variables
#define DEFAULT_SHELL_DOWNLOAD_DIR "/path/to/download/directory"
#define SYSTEM_PATH "/path/to/system"
#define INSTALLATION_ENVIRONMENT "installation environment"
#define USER "user"
#define DATE_TIME time(NULL)
#define PERMISSIONS "permissions"
#define AVAILABLE_STORAGE "available storage"

// Function to encrypt a string using SHA3-384
char* encrypt_string(char *str) {
  // Allocate memory for the encrypted string
  char *encrypted_str = malloc(SHA3_384_DIGEST_SIZE);

  // Create a SHA3-384 context
  SHA3_384_CTX ctx;
  sha3_384_Init(&ctx);

  // Update the context with the string
  sha3_384_Update(&ctx, (uint8_t*) str, strlen(str));

  // Finalize the context and get the digest
  sha3_384_Final(&ctx, (uint8_t*) encrypted_str);

  return encrypted_str;
}

// Declare variables as pointers to store actual values
char *default_shell_download_dir_ptr = DEFAULT_SHELL_DOWNLOAD_DIR;
char *system_path_ptr = SYSTEM_PATH;
char *installation_environment_ptr = INSTALLATION_ENVIRONMENT;
char *user_ptr = USER;
time_t *date_time_ptr = &DATE_TIME;
char *permissions_ptr = PERMISSIONS;
char *available_storage_ptr = AVAILABLE_STORAGE;

#endif // CONFIG_H
