#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	FILE *da1, *da2;
        int dato1, dato2, a, b, c, d, x, y;
        int p1[2], p2[2];

        pipe (p1);
        pipe (p2);

        int hijo=fork();


      	if(hijo==0){       // Codigo el proceso hijo
                // Escucha al padre   
                close(p1[1]);
                da1 = fdopen(p1[0], "r");
                fscanf(da1,"%d %d", &a, &b );
                c = a + b;
                d = a * b;
                printf("%d %d \n", c, d );
                // le habla al padre
                close (p2[0]);
                da2 = fdopen(p2[1],"w" );
                fprintf(da2, "%d %d ", c, d);
	}
        else { //Codigo del proceso padre
                dato1 = atoi(argv[1]);
                dato2 = atoi(argv[2]);
                close(p1[0]); //cierra la lectura
                da2=fdopen(p1[1],"w");
                fprintf(da2, "%d %d", dato1, dato2);
               close(p2[1]);
                da1 = fdopen(p2[0], "r");
                fscanf (da1, "%d %d",&x, &y);
                printf ("Suma: %d\n", x );
                printf ("Multiplica: %d\n", y );
              
        }

   return 0;

}