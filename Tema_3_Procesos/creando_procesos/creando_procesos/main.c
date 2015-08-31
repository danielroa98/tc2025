//
//  main.c
//  creando_procesos
//
//  Created by Vicente Cubells Nonell on 31/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    int pid;
    int estado;
    
    pid = fork();
    
    if (pid == -1)
    {
        printf("Error al crear el proceso hijo \n");
    }
    else if (pid == 0)
    {
        // Estamos en el hijo
        printf("Estamos en el proceso hijo con PID = %d y su padre es PPID = %d \n", \
               getpid(), getppid());
        exit(8);
    }
    else {
        // Estamos en el padre
        printf("Estamos en el proceso padre con PID = %d y su padre es PPID = %d \n", \
               getpid(), getppid());
        
        // Popner al padre a esperar que el hijo termine
        if (waitpid(pid, &estado, 0) != -1)
        {
            if (WIFEXITED(estado))
                printf("Ya terminó el hijo con PID %d con valor de retorno %d \n", pid, WEXITSTATUS(estado));
        }
        
        printf("Después del wait");
        
    }
    
    return 0;
}
