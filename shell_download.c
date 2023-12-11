#include <stdio.h>
#include <stdlib.h>

// Define directory for downloaded shells
#define DOWNLOAD_DIR "downloads"

// Structure to store shell information
typedef struct {
  char* name;
  char* download_url;
  char* install_path;
  int open_source;
} Shell;

// Function to check the current kernel version
void check_kernel_version() {
  system("uname -r");
}

// Function to download and build the latest kernel
void update_kernel() {
  system("wget https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.7-rc5.tar.gz");
  system("tar xvf linux-6.7-rc5.tar.gz");
  system("cd linux-6.7-rc5");
  system("make menuconfig");
  system("make");
  system("make modules_install");
  system("make install");
}

// Function to download and extract a shell archive
int download_shell(Shell shell) {
  // Create download directory if it doesn't exist
  system("mkdir -p " DOWNLOAD_DIR);

  // Define download command
  char command[256];
  sprintf(command, "wget -P " DOWNLOAD_DIR " %s", shell.download_url);

  // Download the shell archive
  if (system(command) != 0) {
    printf("Error: Failed to download %s.\n", shell.name);
    return 0;
  }

  // Extract the archive
  sprintf(command, "tar xvf " DOWNLOAD_DIR "/%s.tar.gz", shell.name);
  if (system(command) != 0) {
    printf("Error: Failed to extract %s.\n", shell.name);
    return 0;
  }

  return 1;
}

// Function to build and install a shell
int build_and_install_shell(Shell shell) {
  // Check if shell is open-source and skip build process if not
  if (!shell.open_source) {
    printf("%s is not open-source and will not be built.\n", shell.name);
    return 1;
  }

  // Change directory to extracted shell directory
  char command[256];
  sprintf(command, "cd " DOWNLOAD_DIR "/%s", shell.name);
  system(command);

  // Configure, build, and install the shell
  system("./configure");
  system("make");
  system("make install");

  // Check for errors
  if (system("make install") != 0) {
    printf("Error: Failed to install %s.\n", shell.name);
    return 0;
  }

  // Copy the executable to the desired install path
  sprintf(command, "cp %s %s", shell.install_path, shell.name);
  system(command);

  return 1;
}

int main() {
  check_kernel_version();
  update_kernel();

  // Define an array of shells to install
  Shell shells[] = {
    // Open-source shells
    {"bash", "http://ftp.gnu.org/gnu/bash/bash-5.1.tar.gz", "/bin/bash", 1},
    {"zsh", "https://www.zsh.org/pub/zsh-5.8.tar.gz", "/bin/zsh", 1},
    {"sh", "https://ftp.gnu.org/gnu/bash/sh-5.1.tar.gz", "/bin/sh", 1},
    {"ksh", "https://www.mirbsd.org/MirOS/dist/mirbsd/packages/All/ksh-2023-12-05.tar.gz", "/bin/ksh", 1},
    {"tcsh", "https://ftp.gnu.org/gnu/tcsh/tcsh-6.22.02.tar.gz", "/bin/tcsh", 1},
    {"fish", "https://fishshell.com/releases/3.5.1/fish-3.5.1.tar.xz", "/bin/fish", 1},
    {"dash", "https://deb.debian.org/debian/pool/main/d/dash/dash_0.5.11-1_amd64.deb", "/bin/dash", 1},
    {"ash", "https://ftp.gnu.org/gnu/bash/ash-4.4.23.tar.gz", "/bin/ash", 1},
    {"nu", "https://github.com/nu-shell/nu/releases/download/0.9.4/nu-linux-musl-0.9.4.tar.gz", "/bin/nu", 1},
    // Non-open-source shells (adjust URLs based on license terms)
    //{"cmd.exe", "", "", 0},
    //{"powershell", "", "", 0},
    //{"rc", "https://github.com/rcsh/rc/archive/refs/tags/rc-1.8.7.tar.gz", "", 0},
    //{"mksh", "https://ftp.mirbsd.org/mirbsd/mksh/mksh-61.0.tar.gz", "", 0},
    //{"busybox ash", "https://busybox.net/downloads/busybox-1.35.0.tar.bz2", "", 0},
  };

  // Download and install each shell
  for (int i = 0; i < sizeof(shells) / sizeof(shells[0]); i++) {
    Shell shell = shells[i];
    if (!download_shell(shell)) {
      continue;
    }
    if (!build_and_install_shell(shell)) {
      continue;
    }
    printf("%s installed successfully.\n", shell.name);
  }

  return 0;
}
