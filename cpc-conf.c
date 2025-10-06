#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024
#define MAX_LINE_LEN 256
#define VERSION "1.0.0"
#define PROGRAM_NAME "cpc-conf"

void show_version() {
    printf("\n%s version %s\n", PROGRAM_NAME, VERSION);
    printf("Copyright (C) 2025 Destroyer. All rights reserved.\n");
    printf("CPCReady Toolchain: INI configuration file management utility.\n\n");
}

void show_help(const char *program_name) {
    printf("\nCPCReady Toolchain INI Configuration Tool\n");
    printf("Copyright (C) 2025 Destroyer. All rights reserved.\n\n");
    
    printf("DESCRIPTION:\n");
    printf("    CPCReady Toolchain: Configuration file management utility.\n");
    printf("    This tool allows you to manage key-value pairs in INI format configuration files.\n");
    printf("    Supports sections, automatic file creation, and both reading and writing operations.\n\n");
    
    printf("USAGE:\n");
    printf("    %s get <filename> <section> <key>         Get a configuration value\n", program_name);
    printf("    %s set <filename> <section> <key> <value> Set or update a configuration value\n", program_name);
    printf("    %s [OPTIONS]                              Show help or version information\n\n", program_name);
    
    printf("COMMANDS:\n");
    printf("    get         Retrieve the value of a key from a specific section\n");
    printf("    set         Set or update a key-value pair in a specific section\n\n");
    
    printf("ARGUMENTS:\n");
    printf("    filename    Path to the INI configuration file\n");
    printf("    section     Section name in the INI file (without brackets)\n");
    printf("    key         Configuration key to get or set\n");
    printf("    value       Value to assign to the key (only for set command)\n\n");
    
    printf("OPTIONS:\n");
    printf("    -h, --help     Show this help message and exit\n");
    printf("    --version      Show version information and exit\n\n");
    
    printf("EXAMPLES:\n");
    printf("    %s set config.ini database host \"localhost\"\n", program_name);
    printf("    %s set config.ini database port 5432\n", program_name);
    printf("    %s get config.ini database host\n", program_name);
    printf("    %s get config.ini database port\n\n", program_name);
    
    printf("FILE FORMAT:\n");
    printf("    [section1]\n");
    printf("    key1=value1\n");
    printf("    key2=value2\n");
    printf("    \n");
    printf("    [section2]\n");
    printf("    key3=value3\n\n");
    
    printf("NOTES:\n");
    printf("    - If the file doesn't exist, it will be created automatically\n");
    printf("    - If the section doesn't exist, it will be created\n");
    printf("    - If the key already exists, its value will be updated\n");
    printf("    - If the key doesn't exist, it will be added to the specified section\n");
    printf("    - For 'get': Returns the value and exits with error if key/section not found\n");
    printf("    - Section names should not include brackets in the command line\n\n");
    
    printf("For more information, visit: https://github.com/CPCReady/cpc-conf\n\n");
}

int main(int argc, char* argv[]) {
    // Check for help and version arguments
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            show_help(argv[0]);
            return 0;
        }
        if (strcmp(argv[1], "--version") == 0) {
            show_version();
            return 0;
        }
    }

    if(argc < 4) {
        fprintf(stderr, "\nError: Insufficient arguments provided.\n\n");
        printf("Usage: %s get <filename> <section> <key>\n", argv[0]);
        printf("       %s set <filename> <section> <key> <value>\n", argv[0]);
        printf("       %s -h|--help for detailed help\n", argv[0]);
        printf("       %s --version for version information\n\n", argv[0]);
        return 1;
    }

    const char* cmd = argv[1];
    const char* filename = argv[2];
    const char* section = argv[3];
    const char* key = argv[4];
    const char* value = (argc > 5) ? argv[5] : NULL;

    char* lines[MAX_LINES];
    int num_lines = 0;
    char line[MAX_LINE_LEN];
    char current_section[MAX_LINE_LEN] = "";
    int section_found = 0;
    int key_found = 0;

    FILE* file = fopen(filename, "r");
    if(file) {
        while(fgets(line, sizeof(line), file) && num_lines < MAX_LINES) {
            lines[num_lines] = strdup(line);
            num_lines++;
        }
        fclose(file);
    } else if(strcmp(cmd, "get") == 0) {
        fprintf(stderr, "\nError: Configuration file '%s' not found.\n\n", filename);
        return 1;
    } else if(strcmp(cmd, "set") == 0) {
        // File will be created when we write it (silent mode)
    }

    if(strcmp(cmd, "get") == 0) {
        // Leer valor
        for(int i=0; i<num_lines; i++) {
            char* l = lines[i];
            if(l[0] == '[') {
                sscanf(l, "[%255[^]]]", current_section);
            } else {
                char k[MAX_LINE_LEN], v[MAX_LINE_LEN];
                if(sscanf(l, "%255[^=]=%255[^\n]", k, v) == 2) {
                    while(k[0]==' ') memmove(k,k+1,strlen(k));
                    while(v[0]==' ') memmove(v,v+1,strlen(v));
                    if(strcmp(current_section, section) == 0 && strcmp(k, key) == 0) {
                        printf("%s\n", v);
                        for(int j=0; j<num_lines; j++) free(lines[j]);
                        return 0;
                    }
                }
            }
        }
        fprintf(stderr, "\nError: Key '%s' not found in section '[%s]' of file '%s'.\n\n", key, section, filename);
        for(int j=0; j<num_lines; j++) free(lines[j]);
        return 1;
    }

    else if(strcmp(cmd, "set") == 0) {
        if (!value) {
            fprintf(stderr, "\nError: Value parameter is required for 'set' command.\n\n");
            printf("Usage: %s set <filename> <section> <key> <value>\n", argv[0]);
            printf("       %s -h|--help for detailed help\n\n", argv[0]);
            return 1;
        }
        
        // Modificar o crear
        for(int i=0; i<num_lines; i++) {
            char* l = lines[i];
            if(l[0] == '[') {
                sscanf(l, "[%255[^]]]", current_section);
                if(strcmp(current_section, section) == 0) section_found = 1;
            } else {
                char k[MAX_LINE_LEN], v[MAX_LINE_LEN];
                if(sscanf(l, "%255[^=]=%255[^\n]", k, v) == 2) {
                    while(k[0]==' ') memmove(k,k+1,strlen(k));
                    while(v[0]==' ') memmove(v,v+1,strlen(v));
                    if(strcmp(current_section, section) == 0 && strcmp(k, key) == 0) {
                        snprintf(line, sizeof(line), "%s=%s\n", k, value);
                        free(lines[i]);
                        lines[i] = strdup(line);
                        key_found = 1;
                    }
                }
            }
        }

        if(!section_found) {
            if(num_lines > 0) {
                snprintf(line, sizeof(line), "\n[%s]\n%s=%s\n", section, key, value);
            } else {
                snprintf(line, sizeof(line), "[%s]\n%s=%s\n", section, key, value);
            }
            lines[num_lines++] = strdup(line);
        } else if(section_found && !key_found) {
            int insert_at = num_lines;
            for(int i=0; i<num_lines; i++) {
                if(lines[i][0] == '[') {
                    char sec[MAX_LINE_LEN];
                    sscanf(lines[i], "[%255[^]]]", sec);
                    if(strcmp(sec, section) == 0) {
                        insert_at = i+1;
                        break;
                    }
                }
            }
            snprintf(line, sizeof(line), "%s=%s\n", key, value);
            for(int j=num_lines; j>insert_at; j--) lines[j] = lines[j-1];
            lines[insert_at] = strdup(line);
            num_lines++;
        }

        // Guardar
        file = fopen(filename, "w");
        if(!file) {
            fprintf(stderr, "\nError: Could not create or write to file '%s'.\n\n", filename);
            for(int j=0; j<num_lines; j++) free(lines[j]);
            return 1;
        }
        for(int i=0; i<num_lines; i++) {
            fputs(lines[i], file);
            free(lines[i]);
        }
        fclose(file);
        
        // Silent success - no output on successful operations
        return 0;
    }

    // Invalid command
    else {
        fprintf(stderr, "\nError: Unknown command '%s'.\n\n", cmd);
        printf("Valid commands: get, set\n");
        printf("Usage: %s get <filename> <section> <key>\n", argv[0]);
        printf("       %s set <filename> <section> <key> <value>\n", argv[0]);
        printf("       %s -h|--help for detailed help\n\n", argv[0]);
        return 1;
    }
}