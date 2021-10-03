/*
http://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html
Shell (command line interface - CLI) faz interface com o SO (kernel): vai invocar 
diretamente sys calls

Hierarquia: shell>sys calls>SO>hardware

O shell (um programa em C) recebe da linha de comando instrucao para executar 
um programa (novo processo)

manpages
fork(2) > duplica o processo atual
execve(2) > carrega executavel (imagem) para execucao *on success, execve() does not return; error = -1*
wait(2) > espera processo finalizar
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> //maior parte das chamadas de sistemas esta aqui
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define READ_END 0 //controle pipe entrada
#define WRITE_END 1 //controle pipe saida

int main(int argc, char *argv[]) {

    int fd1[2], fd2[2];
    int status, pid;

//    char *argv[] = {"", NULL};
    char *envp[] = {"", NULL};
    bool executing;
    char str[101];
    char *command;
    char *param;
    const char *strs_syscall[99];

    pid_t pid_filho;
    printf("Welcome to the miniature-shell\n");

    //loop infinito do shell
    executing = true;
    while (executing) {

        //leitura entrada usuario
        fgets(str, 100, stdin);

        //copia str para quebrar
        char *paramstr = calloc(1, strlen(str)+1);
        strcpy(paramstr, str);

        //quebrar string em pipe
        int cmd_count = 0;
        while ((command = strsep(&paramstr, "|"))) {
            //printf("\tComando %d:\n", cmd_count++);
            strs_syscall[cmd_count] = command;
            printf("strs_syscall[%d]> %s\n", cmd_count, strs_syscall[cmd_count]);
            cmd_count++;

//            while((param = strsep(&command, " "))) {
//                printf("\t\t%s\n", param);
//            }

        }

    }

    //printf("PPID: %d \n", getpid());
    //getchar();

    pid_filho = fork();
    printf("pid_filho: %d \n", pid_filho);
    //getchar();

    /* substituir a imagem de execucao */
    int ret = execve("hello", argv, envp); //se execve funcionar, nao ha retorno
    if (ret == -1) {
        perror("execve error\n");
        return 1;
    }

    return 0;

}

