#ifndef SHELL_DOWNLOAD_VERIFY_H
#define SHELL_DOWNLOAD_VERIFY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/md5.h>

// Function to download a shell
int download_shell(char *shell_name, char *url);

// Function to extract a shell
int extract_shell(char *archive_filename);

// Function to handle cellular handover
int handle_cellular_handover(CURL *curl);

// Function to verify download integrity with checksum
int verify_download_integrity(char *filename, char *expected_checksum);

#endif // SHELL_DOWNLOAD_H
