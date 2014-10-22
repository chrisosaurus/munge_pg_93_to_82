#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
    if( argc != 2 ){
        puts("ERROR! expected exactly 1 argument");
        exit(1);
    }

    printf("Opening file '%s'\n", argv[1]);
    FILE *f = fopen(argv[1], "r+b");
    if( ! f ){
        printf("Failed to open file\n");
        exit(1);
    }

    char read[100];

    // Replace line
    //      SET lock_timeout = 0;
    // With
    //      --T lock_timeout = 0;
    if( fseek(f, 62, SEEK_SET) ){
        printf("First seek failed\n");
        exit(1);
    }

    // check line before destroying
    char *exp1 = "SET lock_timeout = 0;";

    if( fread(read, 1, 21, f) != 21 ){
        printf("First read failed\n");
        exit(1);
    }
    if( strncmp(exp1, read, 21) ){
        printf("First strncmp failed\n");
        exit(1);
    }
    if( fseek(f, 62, SEEK_SET) ){
        printf("First re-seek failed\n");
        exit(1);
    }

    // comment out line
    if( fwrite("--", 1, 2, f) != 2 ){
        printf("First write failed\n");
        exit(1);
    }

    if( fseek(f, 406, SEEK_SET) ){
        printf("Second seek failed\n");
        exit(1);
    }

    // Replace line
    char * exp2 = "CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;";
    // With
    char * line = "CREATE PROCEDURAL LANGUAGE plpgsql;---------------------------";

    if( fread(read, 1, 62, f) != 62 ){
        printf("Second read failed\n");
        exit(1);
    }
    if( strncmp(exp2, read, 62) ){
        printf("Second strncmp failed\n");
        read[62] = '\0';
        printf("Expected '%s'\n", exp2);
        printf("Got      '%s'\n", read);
        exit(1);
    }

    if( fseek(f, 406, SEEK_SET) ){
        printf("Second re-seek failed\n");
        exit(1);
    }


    // comment out line
    if( fwrite(line, 1, 62, f) != 62 ){
        printf("Second write failed\n");
        exit(1);
    }

    puts("Success");
    fclose(f);

}
