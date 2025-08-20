#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

#define CLINE_TOK_BUFSIZE 64
#define CLINE_TOK_DELIM " \t\r\n\a"

char **split_line(char *line) {
    int bufsize = CLINE_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    if (!tokens) {
        fprintf(stderr, "cline: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, CLINE_TOK_DELIM);
    while (token != NULL) {
        tokens[position++] = token;
        if (position >= bufsize) {
            bufsize += CLINE_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "cline: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, CLINE_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int launch(char **args) {
    if (args[0] == NULL) return 1;

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cline: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cline");
            }
        }
        return 1;
    }
    
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    if (strcmp(args[0], "pwd") == 0) {

        char cwd[1030];
        if(getcwd(cwd, sizeof(cwd))!=NULL){
            fprintf(stdout, "current working dir: '%s'", cwd);
        }
        else{
            perror("getcwd() error");
        }
        return 0;
    }

    if(strcmp(args[0], "clear") == 0 || strcmp(args[0], "cls") == 0){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        return 1;
    }

    if (strcmp(args[0], "camera") == 0) {
        #ifdef _WIN32
            
            system("start microsoft.windows.camera:");
        #else
            fprintf(stderr, "cline: The 'camera' command is only available on Windows.\n");
        #endif
        return 1; 
    }

    if (strcmp(args[0], "start") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cline: expected argument to \"start\"\n");
        }
        else if(strcmp(args[1],"camera")==0){
            #ifdef _WIN32
            system("start microsoft.windows.camera:");
        #else
            fprintf(stderr, "cline: The 'camera' command is only available on Windows.\n");
        #endif
        return 1;
        } else {
            #ifdef _WIN32
                char command[256];
                
                snprintf(command, sizeof(command), "start %s", args[1]);
                system(command);
            #else
                fprintf(stderr, "cline: The 'start' command is only available on Windows.\n");
            #endif
        }
        return 1; 
    }

    if(strcmp(args[0],"Kill")==0){
        #ifdef _WIN32
            
            system("shutdown /s /t 0");
        #else
            system("shutdown now");
        #endif
         return 1;
    }

    if(strcmp(args[0],"reboot")==0){
        #ifdef _WIN32
            system("shutdown /r /t 0");
        #else
            system("reboot");
        #endif
         return 1;
    }

    if(strcmp(args[0],"lock")==0){
        #ifdef _WIN32
            system("rundll32.exe user32.dll,LockWorkStation");
        #else
            fprintf(stderr, "cline: 'lock' is not universally supported on Linux.\n");
        #endif
         return 1;
    }

    if (strcmp(args[0], "sleep") == 0) {
        #ifdef _WIN32
            system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
        #else
            system("systemctl suspend");
        #endif
        return 1;
    }

    if (strcmp(args[0], "help") == 0) {
        printf("--- Cline Shell Help ---\n");
        printf("These are the built-in commands:\n");
        printf("  cd [dir]       - Change the current directory.\n");
        printf("  pwd            - Print the current working directory.\n");
        printf("  clear / cls    - Clear the terminal screen.\n");
        printf("  start [app]    - (Windows only) Launch an application.\n");
        printf("  camera         - (Windows only) Launch the camera app.\n");
        printf("  shutdown       - Shuts down the computer.\n");
        printf("  restart        - Restarts the computer.\n");
        printf("  sleep          - Puts the computer to sleep.\n");
        printf("  lock           - (Windows only) Locks the computer.\n");
        printf("  exit           - Exit the shell.\n");
        printf("------------------------\n");
        return 1;
    }
    

#ifdef _WIN32
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    char cmdline[1024] = "cmd.exe /c ";
    for (int i = 0; args[i] != NULL; i++) {
        strcat(cmdline, args[i]);
        strcat(cmdline, " ");
    }
    if (!CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "cline: Error creating process on Windows (code: %lu)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#else
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) perror("cline");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("cline");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
#endif

    return 1;
}

void shell_loop(void) {
    char *line;
    char **args;
    int status;
    char prompt[1030];
    char cwd[1024];

    do {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            
            snprintf(prompt, sizeof(prompt), "%s> ", cwd);
        } else {
            perror("getcwd() error");
            strcpy(prompt, "> ");
        }

        line = readline(prompt);

        if (line == NULL) {
            printf("\nexit\n");
            break;
        }

        if (line && *line) {
            add_history(line);
        }

        args = split_line(line);
        status = launch(args);
        
        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    printf("Welcome to Cline Shell!\n");
    printf("Type 'help' to see a list of built-in commands.\n\n");

    shell_loop();
    return EXIT_SUCCESS;
}