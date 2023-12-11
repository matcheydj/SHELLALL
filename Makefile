CC = gcc
CFLAGS = -Wall -Wextra -O2

# Define all object files
OBJECTS = shell_download.o shell_verify.o shell_build.o shell_install.o utils.o

# Define the program name
PROGRAM = shell_manager

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)

# Define individual object file compilation rules
shell_download.o: shell_download.c config.h curl/curl.h openssl/md5.h
	$(CC) $(CFLAGS) -c shell_download.c

shell_verify.o: shell_verify.c config.h
	$(CC) $(CFLAGS) -c shell_verify.c

shell_build.o: shell_build.c config.h
	$(CC) $(CFLAGS) -c shell_build.c

shell_install.o: shell_install.c config.h
	$(CC) $(CFLAGS) -c shell_install.c

utils.o: utils.c config.h
	$(CC) $(CFLAGS) -c utils.c

# Clean rule to remove object files and the program
clean:
	rm -f $(OBJECTS) $(PROGRAM)
