#include <stdio.h>
#include <stdlib.h>
#include "hijo.c"
#include "padre.c"
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char * argv[]) {
    char input[30] = "datos_juegos_1000.csv";
    char output[30] = "output.txt";
    float min_price = 0;
    int min_year = -1;
    int flag = 0;
    if(validate(argc,argv,input,output,&min_price,&min_year,&flag)){
        if(flag){
            printf("Archivo de entrada: %s\n",input);
            printf("Archivo de salida : %s\n",output);
            printf("Ano de inicio: %d\n",min_year);
            printf("Precio minimo: %f\n",min_price);
            printf("Flag: %d\n",flag);
        }
        int fd[2];
        int fd2[2];
        int pid;
        long buffer = 41;
        int totalYears;
        int status;
        char * string = (char *) malloc(sizeof (char)*1000);
        if(pipe(fd) == -1){
            printf("error\n");
            exit(-1);
        }
        if(pipe(fd2) == -1){
            printf("error\n");
            exit(-1);
        }
        TDAlista  ** hash = leerCSV(input,min_year,min_price);
        totalYears = crearArchivo(hash,"intermedio.txt",fd,flag,min_year);
        //abrimos el archivo 
        FILE * fp;
        fp = fopen("intermedio.txt","r");
        int flag2 = 0;
        FILE * fr = fopen(output,"r");
        if(fr!=NULL){
            flag2 = 1;
        }
        fclose(fr);
        for (int i = 0; i < totalYears; i++) {
            pid = fork();//creamos n hijos
            if(pid>0){
                if(flag2 == 1 && i==0){
                    FILE * ar = fopen(output,"w");
                    fclose(ar);
                }
                FILE * archivoSalida = fopen(output,"a");
                char * string2 = (char *) malloc(sizeof (char)*1000);
                //espera el estatus de dicho hijo para recien crear al sgte hijo
                wait(NULL);
                read(fd2[0],string2,sizeof(char)*1000);
                fprintf(archivoSalida,"%s\n",string2);
                free(string2);
                fclose(archivoSalida);
            }
            if(pid == 0){//si es hijo
                close(fd[1]);//comunicacion del pipe
                close(fd2[0]);
                read(fd[0],&buffer,sizeof(buffer));//leemos y guardamos donde le corresponde del archivo
                gamelist * list;
                list=crearListaVaciaGame();
                leerArchivo(fp,buffer,list);//trabajamos con dicha info CREAR LIST
                buscarTopAndBottom(string,list);
                calcularPromedios(string,list);
                juegosFree(string,list);
                write(fd2[1],string, sizeof(char) * 1000);
                //aqui debe ir un 
                //exit(1); //para que el padre rompa su espera 
                exit(1);//mientras con eso nos aseguramos que los hijos no se reproduzcan
            }
        }
        fclose(fp);
    }else {
        printf("Por favor ingrese una entrada correcta\n");
        printf("Utilice -h para ver las indicaciones de ayuda\n");
    }

    return 0;
}