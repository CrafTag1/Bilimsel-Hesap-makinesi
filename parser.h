#ifndef PARSER_H
#define PARSER_H

// linked List düğümü tanımı
typedef struct CommandRecord {
    char command[20];
    long long args[4];
    int arg_count;
    char result[100];
    int is_error; 
    struct CommandRecord *next; // bir sonraki komutu tutacak pointer 
} CommandRecord;

void process_file(const char *giris_dosyasi, const char *cikis_dosyasi);

#endif