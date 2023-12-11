#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/md5.h> // Include OpenSSL library for MD5 checksum

// Function to download a shell
int download_shell(char *shell_name, char *url) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "curl_easy_init() failed.\n");
    return 1;
  }

  // Set download options
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); // Use a custom write callback for progress and error handling
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "Shell Downloader/1.0"); // Set user agent for identification
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

  // Enable SSL verification for secure connection
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

  // Perform the download
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    curl_easy_cleanup(curl);
    return 1;
  }

  // Always clean up
  curl_easy_cleanup(curl);
  return 0;
}

// Function to extract a shell
int extract_shell(char *archive_filename) {
  char command[256];
  int system_ret;

  // Check file extension
  if (strstr(archive_filename, ".tar.gz") == NULL) {
    fprintf(stderr, "Unsupported archive format: %s\n", archive_filename);
    return 1;
  }

  sprintf(command, "tar xvf %s", archive_filename);
  system_ret = system(command);
  if (system_ret != 0) {
    fprintf(stderr, "Failed to extract archive: %s\n", archive_filename);
    return 1;
  }

  return 0;
}

// Function to handle cellular handover (not implemented)
int handle_cellular_handover(CURL *curl) {
  // Implement platform-specific code to monitor network changes and pause/resume download
  return 0; // Replace with actual implementation
}

// Function to verify download integrity with checksum
int verify_download_integrity(char *filename, char *expected_checksum) {
  unsigned char md5[MD5_DIGEST_LENGTH];
  FILE *file = fopen(filename, "rb");
  MD5_CTX context;

  if (!file) {
    fprintf(stderr, "Failed to open file: %s\n", filename);
    return 1;
  }

  // Calculate MD5 checksum of the downloaded file
  MD5_Init(&context);
  MD5_Update(&context, file_buffer, file_size);
  MD5_Final(md5, &context);
  fclose(file);

  // Compare calculated checksum with expected checksum
  if (memcmp(md5, expected_checksum, MD5_DIGEST_LENGTH) != 0) {
    fprintf(stderr, "Checksum mismatch. Downloaded file is corrupted.\n");
    return 1;
  }

  return 0;
}
