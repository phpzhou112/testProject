#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

       int
       main(int argc, char *argv[])
       {
           struct stat sb;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (stat(argv[1], &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
           }

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFREG:  printf("normal file\n");               break;
	  }
	}



