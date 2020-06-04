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
#include "shell.h"


/*
 *Funcion de datos de autor
 *
 * Input: N/A
 * Ouptu: Despliega Datos
 */
void mensajeInicio(){
    printf("\n****************************************************\n");
    printf("\nAutor: Jose Carlos Pacheco Sanchez - A01702828\n");
    printf("\nOjetivo: Desarrollo de un mini shell que pueda\nrealizar las operaciones basicas\n");
    printf("\n****************************************************\n\n\n");

}

/*
 *Funcion de datos de autor
 *
 * Input: N/A
 * Ouptu: concatenado de promt y mensaje de inicio
 */
void my_shell()
{
    char command_argv[BUFFER_MAX];
    char dir[PATH_MAX];

    mensajeInicio(); //INICIAL
    prompt();

    // En espera de nuevos comandos 
    while(fgets(command_argv,BUFFER_MAX, stdin)){
        if(command_argv[0] == '\n'){
            prompt();
            continue;
        }else if(strcmp(command_argv,"quit\n") == 0){
            break;
        }
        pipe_get_cmd(command_argv);
        prompt();
    }
    exit(0);
}

/*
 *Funcion para leer desde un archivo
 *
 * Input: nombe del archivo
 * Ouptu: Ejecucion de todos los comandos puestos 
 */
void file_execute(char *filepath){

    FILE *fp = fopen(filepath, "r");
    char buffer[BUFFER_MAX];

    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        if(strcmp(buffer,"quit\n") == 0){
            break;
        }
        
        fputs("\n\n<<COMANDOS : ",stdout);
        fputs(buffer,stdout);
        fputs("\n\n",stdout);
        pipe_get_cmd(buffer);
        fputs("\n\n",stdout);

        printf("\n\nTERMINA>>");

    }
    printf("\n\nFIN De ejecucion\n\n");
    fclose(fp);
    exit(0);
}


/*
 * MAIN Del programa 
 * Input: N/A o Nombre del archivo 
 * Output: Ejecucion de comandos en secuencia de procesos hijos y padres 
 * 
 */
int main(int argc, char *argv[]){
    int src = 0;
    struct stat statbuf;

    // Validaciones 
    if(argc > 2){
        printf("ERROR: %s [nombre]\n", argv[0]);
        return -1;

        //Si tenemos un archivo a leer ejecutar exec_file
    }else if(argc == 2){ 

        //printf("%s Argumentos, argv[1]");
        
        if((src = open(argv[1], O_RDONLY)) < 0){ //Existe?
            printf("%s: Archivo no encontrado\n",argv[1]);
            return -2;
        }

        stat(argv[1],&statbuf);
        if(S_ISREG(statbuf.st_mode)){
            file_execute(argv[1]);
        }else{
            printf("No se puede abrir el archivo: %s \n",argv[1]);
        }

    // En caso de ningun argumento, se ejecuta el SHELL 
    }else{
        my_shell();
    }
    return 0;
}