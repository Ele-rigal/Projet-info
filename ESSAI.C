#include <stdlib.h>

#include <stdio.h>

#include <time.h>

/* pour compiler ce fichier:  gcc –o cocotte cocotte.c libgraphique.c –lglut –lGLU –lGL –lm */















/* indispensable pour compiler un programme utilisant la bibliothèque graphique: */



#include "libgraphique.h"



#include "libgraphique_fonts.h"



#include "libgraphique.c"



#include <unistd.h>



#include <stdio.h>



#ifdef __unix__



# include <unistd.h>



#elif defined _WIN32



# include <windows.h>



#define sleep(x) Sleep(1000 * x)



#endif



#define COTE_MIN (WINDOW_WIDTH < WINDOW_HEIGHT ? WINDOW_WIDTH : WINDOW_HEIGHT)
int main(void)
{
int n,t,finli,finco,li,co,x1,y1,x2,y2,x;
int i,m,xn1,yn1,xn2,yn2,xm1,ym1,xm2,ym2;
char rep[100];
printf("entrez le nom du fichier à ouvrir:  ");
scanf("%s",rep);
FILE* fic=fopen(rep,"r");
start_graphics();
set_drawing_color(color_BLACK);
fscanf(fic,"%d %d %d %d",&n,&t,&finli,&finco);
m=n;
//calcul pour centrer la grille
int marge_c=(WINDOW_WIDTH-(t*n))/2;
int marge_h=(WINDOW_HEIGHT-(t*m))/2;
xn1=marge_c;
yn1=marge_h;
xm1=marge_c;
ym1=marge_h;
for(i=1;i<=n+1;i++){
//dessin des lignes
    xn2=xn1+(m)*t;
    yn2=yn1;
    draw_line(xn1, yn1, xn2, yn2);
		/*if (i<=n){
            char *c=i-'0';
            draw_string(xn1-t,yn1+(t/2),&c);
        } essai de l'index mais ne fonctionne pas*/
    yn1=yn1+t;
}
for(i=1;i<=m+1;i++){
//dessin des colonnes
    ym2=ym1+(n)*t;
    xm2=xm1;
    draw_line(xm1, ym1, xm2, ym2);
    /*if (i<=m){
        draw_string(xm1+(t/2),ym1-t,&i);
    }*/
    xm1=xm1+t;
}
do{	set_drawing_color(color_WHITE);
	x=fscanf(fic,"%d %d %d %d",&x1,&y1,&x2,&y2);
	draw_line(x1,y1,x2,y2);
	update_graphics();
}
while(x==4);
set_drawing_color(color_WHITE);
draw_line(x2,y2,finco,finli);
update_graphics();
fclose(fic);
        sleep(10);
        stop_graphics();
get_key();
return 0;
}

