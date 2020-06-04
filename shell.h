/*
 =======================================================================================================================
 Name        : mini-shell.c
 Author      : Jose Carlos Pacheco
 ID          : A01702828
 Version     : v1.2
 Description : Mini shell para materia de programacion avanzada , requerimientos en el ./info/proyecto.pdf
 =======================================================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

#define BUFFER_MAX 512

struct command_t {
        char *name;
        int argc;
        char *argv[100];
};


struct command_t command_dir;

/*
 *Funcion que despliega el promt 
 *
 * Input: N/A
 * Ouptu: Nombre del shell
 */
void prompt()
{
    char dir[PATH_MAX];

    if(getcwd(dir, sizeof(dir)) != NULL){
        printf("mini-shell >> ");
    }

}
/*
 *Funcion de ejecucion de moviemiento entre directorios  
 * Input: N/A
 * Ouptu: cambio en Directorio
 * 
 
void changeDir() {
	if (command_dir.argv[1] == NULL) {
		chdir(getenv("HOME"));
	} else {
		if (chdir(command_dir.argv[1]) == -1) {
			printf(" %s: no such directory\n", command_dir.argv[1]);
		}
	}
}

*/



/*
 *Funcion de ejecucion de comando 
 *
 * Input: comandos
 * Ouptu: en caso de exito -> 0 , 
 * Ejecucion de con execvp 
 */
int execute_command(char *command_argv) {

    char *args[100], *args_exec;
    int contador = 0;

    args_exec = strtok(command_argv," ");
    if(args_exec == NULL){
        printf("\n!!No dejes comandos en blanco!!\n");
    }else{
        while(args_exec != NULL){
            args[contador] = args_exec;
            contador++;
            args_exec = strtok(NULL, " ");
        }
        args[contador] = NULL;

        //Ejecucion de comandos
        if (execvp(args[0], args) == -1) {
            perror("Execution error");
            return -1;
        }
    }

    return 0;
}


/*
 *Funcion que nos permite concatenar serie de comandos
 *
 * Input: comandos
 * Ouptu: Ejecucion de comandos en serie
 */
void pipe_get_cmd(char *command_argv)
{
    char *command;
    int contador = 0, pid = 0;

    
    command = strtok(command_argv,"\n");
    command = strtok(command_argv,";"); // Uso de PIPES pero con ; 

    while(command != NULL){
        if((pid = fork()) == 0){
            execute_command(command);
            //printf("Fin de comando");
            exit(0); 
            
        }else{
            contador++;
            command = strtok(NULL, ";");
        }
    }
    
    while(contador-- > 0){
        wait(NULL);
    }
}