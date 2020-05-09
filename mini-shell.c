/*
 =======================================================================================================================
 Name        : mini-shell.c
 Author      : Jose Carlos Pacheco
 ID          : A01702828
 Version     : v1.0
 Description : Mini shell para materia de programacion avanzada , requerimientos en el ./info/proyecto.pdf
 =======================================================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


// Metodos



/* Main
 *
 * Input: minimo 1 argumento maximo ?
 * Input type: debera validar comandos existentes o un archivo .txt.bat.bin
 *
 * Output: La ejecucion de los comandos ingresados o en el caso la ejecucion de los comandos de archvio
 *
 */
int main(int argc, char* argv[]) {

    if( argc <= 1){
        printf("usage: %s hacen falta argumentos\n", argv[0]);
        return -1;
    }

    exit(0);

}