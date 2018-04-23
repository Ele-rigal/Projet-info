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
#include "lib.h"
//partie des fonctions utiles au programme

int main(void){

    srand(time(NULL)); //init la fonction rand()
    int i,n,m,t,xn1,yn1,xn2,yn2,xm1,ym1,xm2,ym2;
    printf("entrez la taille du cote du carre:");
    scanf("%d",&n);
    m=n;
    printf("entrez la taille des cases:");
    scanf("%d",&t);
//calcul pour centrer la grille
int marge_c=(WINDOW_WIDTH-(t*n))/2;
int marge_h=(WINDOW_HEIGHT-(t*m))/2;
//début de l'interface graphique
ini_graph();
//coordonnées des marges à prendre pour centrer
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
//coordonnées du curseur départ
int li=xn1+(t/2);
int co=yn1-(1.5*t);
//coordonnées de la fin
int finli=xm1-(1.5*t);
int finco=ym1+(t/2);update_graphics();
int r=t/6; //rayon
draw_circle_full(li,co,r); //création du curseur
update_graphics();
int touche;
touche=dir();
int g=factorielle(n)-n*n;
int d=factorielle(n)-n*n;
int h=factorielle(n)-n*n;
int b=factorielle(n)-n*n;
sup_g(li,co,t);
set_drawing_color(color_BLACK);
while((li<=finli)&&(co>=finco))
{
//int touche=get_key();
//printf("%d",touche); mouchar pour vérifier que le rand marchait bien
    if(((touche==key_LEFT)&&(li>(xn1+(t/2))))&&(g>0))
    {   li=li-t;
        draw_circle_full(li,co,r);
        sup_g(li+t,co,t);
        draw_circle_full(li+t,co,r);
        set_drawing_color(color_BLACK);
        g--;
    }
    else if(((touche==key_RIGHT)&&(li<xn2-(t/2)))&&(d>1))
    {   li=li+t;
        draw_circle_full(li,co,r);
        sup_d(li-t,co,t);
        draw_circle_full(li-t,co,r);
        set_drawing_color(color_BLACK);
        touche=dir();
        d--;
    }
    else if(((touche==key_DOWN)&&(co>finco))&&(b>1))
    {   co=co-t;
        draw_circle_full(li,co,r);
        sup_bas(li,co+t,t);
        draw_circle_full(li,co+t,r);
        set_drawing_color(color_BLACK);
        b--;
    }
    else if(((touche==key_UP)&&(co<yn1-(1.5*t)))&&(h>0))
    {   co=co+t;
        draw_circle_full(li,co,r);
        sup_haut(li,co-t,t);
        draw_circle_full(li,co-t,r);
        set_drawing_color(color_BLACK);
        h--;
    }
    else if (((li==finli)&& (co==finco)))
    {   li=li+t;
        draw_circle_full(li,co,r);
        sup_d(li-t,co,t);
        draw_circle_full(li-t,co,r);
        set_drawing_color(color_BLACK);
        touche=dir();
        sleep(5);
        stop_graphics();
    }
 touche=dir();
   update_graphics();
}
get_key();
return 0;
}

