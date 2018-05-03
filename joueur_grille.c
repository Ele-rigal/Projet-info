#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/* pour compiler ce fichier:  gcc –o cocotte cocotte.c libgraphique.c –lglut –lGLU –lGL –lm */
/* indispensable pour compiler un programme utilisant la bibliothèque graphique: */

#include "libgraphique.h"
#include "libgraphique_fonts.h"
#include "libgraphique.c"
#include <unistd.h>
#include <wchar.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif
#define COTE_MIN (WINDOW_WIDTH < WINDOW_HEIGHT ? WINDOW_WIDTH : WINDOW_HEIGHT)
void score(int i)
   {
    set_font(font_HELVETICA_18);
    set_drawing_color(color_BLACK);
    draw_printf(320,242,"GAGNE! Score: %d",i);
    if(i>=60){
        draw_printf(320,190,"Vous etes digne de Thesee!!!");
        draw_printf(320,150,"A bientot dans une prochaine quete!");
    }
    else if((i<60)&&(i>=20))
        draw_printf(320,190,"Mouais,vous pouvez faire mieux!");
    else
        draw_printf(320,190,"Très mauvais,un fil d'Arianne aurait pu vous aider");
    update_graphics();
    sleep(5);
    get_key();
    clear_screen();
}
void regles(int t,int x,int y)
{
      set_font(font_HELVETICA_18);
set_drawing_color(color_BLACK);
draw_printf(x,y,"Vous venez d'entrer dans un labyrinthe!!!");
draw_printf(x,y-t,"Si le chemin est bon,la cloison s'abbatra devant vous ,");
draw_printf(x,y-2*t,"sinon dommage,rebroussez chemin! ");
draw_printf(x,y-3*t,"Pour cela,utilisez les touches directionelles de votre clavier");
draw_printf(x,y-4*t,"Appuyez sur une touche pour commencer");
update_graphics();
get_key();
clear_screen();
}
void init(int tab[])
{   int i;
    for(i=0;i<1000;i++)
        tab[i]=0;
}
int existe(int tab[],int x1,int y1,int x2,int y2,int n )
{
    int i;
    for(i=0;i<n-3;i++)
    {
        if((tab[i]==x1)&&(tab[i+1]==y1)&&(tab[i+2]==x2)&&(tab[i+3]==y2))
            return 1;
    }
    return 0;
}
int main(void)
{int tab[1000];
srand(time(NULL)); //init la fonction rand()
int n,t,finli,finco,li,co,x1,y1,x2,y2,x;
int i,m,xn1,yn1,xn2,yn2,xm1,ym1,xm2,ym2;
char rep[100];
printf("entrez le nom du fichier a ouvrir:  ");
scanf("%s",rep);
FILE* fic=fopen(rep,"r");
start_graphics();
set_drawing_color(color_BLACK);
fscanf(fic,"%d %d %d %d %d %d",&n,&t,&co,&li,&finli,&finco);
m=n;
init(tab);
i=0;
do {
    x=fscanf(fic,"%d",&tab[i]);
    i++;
}while(x==1);
int taille=i;
//calcul pour centrer la grille
int marge_c=(WINDOW_WIDTH-(t*n))/2;
int marge_h=(WINDOW_HEIGHT-(t*m))/2;
xn1=marge_c;
yn1=marge_h;
xm1=marge_c;
ym1=marge_h;
regles(t,xm1-2*t,ym1+n*t);
/*//dessin ligne du bas
xn2=xn1+(m)*t;
yn2=yn1;
draw_line(xn1, yn1, xn2, yn2);
//dessin côté Gauche
ym2=ym1+(n)*t;
xm2=xm1;
draw_line(xm1, ym1, xm2, ym2);
//dessin ligne du haut
xn2=xn1+(m)*t;
yn2=yn1+(m)*t;
draw_line(xm2, ym2, xn2, yn2);
//dessin côté droit
ym2=ym1+(n)*t;
xn2=xn1+(m)*t;
draw_line(xn2, yn1, xn2, ym2);*/
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
update_graphics();
int r=t/6;
draw_circle_full(li,co,r); //création du curseur
set_font(font_HELVETICA_12);
draw_string(xn1-2*t,yn2-(t/2),"entree --->");
draw_string(xm2,ym1+(t/2),"<--- sortie");
set_drawing_color(color_WHITE);
draw_line(li-(t/2),co-(t/2),li-(t/2),co+(t/2)); //entrée
draw_line(xn2,yn1,xn2,yn1+t); //sortie
update_graphics();
printf("co=%d li=%d finco=%d finli=%d",co,li,finco,finli);
int touche;
i=100;
set_drawing_color(color_BLACK);
x1=li+(t/2);
y1=co-(t/2);
x2=li+(t/2);
y2=co+(t/2);
while((x2!=tab[taille-1])&&(y2!=tab[taille]))
{
touche=get_key();
//printf("%d",touche); mouchar pour vérifier que le rand marchait bien
     if ((co==finli)&& (li==finco))
    {   x2=x2/1000;
        y2=y2*1000;
        draw_circle_full(li,co,r);
        set_drawing_color(color_BLACK);
    }
   else if(touche==key_LEFT&&(li-(t/2)>xn1))
    {
        x1=li-(t/2);
        y1=co-(t/2);
        x2=li-(t/2);
        y2=co+(t/2);
        if(existe(tab,x1,y1,x2,y2,taille)==1)
        {   li=li-t;
            draw_circle_full(li,co,r);
            set_drawing_color(color_WHITE);
            draw_circle_full(li+t,co,r);
            draw_line(x1,y1,x2,y2);
             set_drawing_color(color_BLACK);
        }
        else{
            draw_circle_full(li,co,r);
        }
    }
    else if(touche==key_RIGHT&&(x2!=xn2))
    {
        x1=li+(t/2);
        y1=co-(t/2);
        x2=li+(t/2);
        y2=co+(t/2);
        if(existe(tab,x1,y1,x2,y2,taille)==1)
        {   li=li+t;
            draw_circle_full(li,co,r);
            set_drawing_color(color_WHITE);
            draw_circle_full(li-t,co,r);
            draw_line(x1,y1,x2,y2);
             set_drawing_color(color_BLACK);
        }
        else{
           draw_circle_full(li,co,r);
        }
    }
    else if(touche==key_DOWN&&(y2!=ym1))
     {
        x1=li-(t/2);
        y1=co-(t/2);
        x2=li+(t/2);
        y2= co-(t/2);
        if(existe(tab,x1,y1,x2,y2,taille)==1)
            {co=co-t;
            draw_circle_full(li,co,r);
            set_drawing_color(color_WHITE);
            draw_circle_full(li,co+t,r);
            draw_line(x1,y1,x2,y2);
            set_drawing_color(color_BLACK);
        }
        else{
           draw_circle_full(li,co,r);
        }
    }
    else if(touche==key_UP&&(y2!=ym2))
      {
        x1=li-(t/2);
        y1=co+(t/2);
        x2=li+(t/2);
        y2=co+(t/2);
        if(existe(tab,x1,y1,x2,y2,taille)==1)
        {   co=co+t;
            draw_circle_full(li,co,r);
            set_drawing_color(color_WHITE);
            draw_circle_full(li,co-t,r);
            draw_line(x1,y1,x2,y2);
            set_drawing_color(color_BLACK);
        }
        else{
            draw_circle_full(li,co,r);
        }
    }
    update_graphics();
    i--;
}
 clear_screen();
score(i);
stop_graphics();
fclose(fic);
get_key();
while(getchar() != '\n');getchar();
   return 0;
}


