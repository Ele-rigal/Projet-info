#include <stdlib.h>

#include <stdio.h>

#include <time.h>

/* pour compiler ce fichier:  gcc –o cocotte cocotte.c libgraphique.c –lglut –lGLU –lGL –lm */
/* indispensable pour compiler un programme utilisant la bibliothèque graphique: */
#include "libgraphique.h"
//#include "libgraphique_fonts.h"
//#include "libgraphique.c"
#include <unistd.h>
//#include <stdio.h>
/*#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif*/
#define COTE_MIN (WINDOW_WIDTH < WINDOW_HEIGHT ? WINDOW_WIDTH : WINDOW_HEIGHT)

typedef int ENTIER;
ENTIER x;
void ecrit_init(FILE* fic,int n,int t,int co,int li,int finco,int finli)
{
	fprintf(fic,"%d \n",n);
	fprintf(fic,"%d \n",t);
	fprintf(fic,"%d \n",co);
	fprintf(fic,"%d \n",li);
	fprintf(fic,"%d \n",finco);
	fprintf(fic,"%d \n",finli);
}
void ecrit(FILE* fic,int x1,int y1,int x2,int y2)
{
	fprintf(fic,"%d \n",x1);
	fprintf(fic,"%d\n",y1);
	fprintf(fic,"%d\n",x2);
	fprintf(fic,"%d\n",y2);
}
int dir(){
    int dire[4]={key_LEFT,key_RIGHT,key_DOWN,key_UP};
    int i=rand()%4;
    x=dire[i];
    return x;
}
void sup_g(FILE* fichier,int li,int co,int t)
{//supprime cloison quand on tourne a gauche
    int x1=li-(t/2);
    int y1=co-(t/2);
    int x2=li-(t/2);
    int y2=co+(t/2);
    ecrit(fichier,x1,y1,x2,y2);
    set_drawing_color(color_WHITE);
    draw_line(x1,y1,x2,y2);
    update_graphics();
}
void sup_d(FILE* fichier,int li,int co,int t)
{//supprime cloison quand on tourne a droite
    int x1=li+(t/2);
    int y1=co-(t/2);
    int x2=li+(t/2);
    int y2=co+(t/2);
     ecrit(fichier,x1,y1,x2,y2);
    set_drawing_color(color_WHITE);
    draw_line(x1,y1,x2,y2);
 update_graphics();
}
void sup_haut(FILE* fichier,int li,int co,int t)
{   int x1=li-(t/2);
    int y1=co+(t/2);
    int x2=li+(t/2);
    int y2=co+(t/2);
     ecrit(fichier,x1,y1,x2,y2);
    set_drawing_color(color_WHITE);
    draw_line(x1,y1,x2,y2);
    update_graphics();
}

void sup_bas(FILE* fichier,int li,int co,int t)
{	int x1=li-(t/2);
	int y1=co-(t/2);
	int x2=li+(t/2);
	int y2= co-(t/2);
	 ecrit(fichier,x1,y1,x2,y2);
    set_drawing_color(color_WHITE);
    draw_line(x1, y1, x2, y2);
    update_graphics();
}

long factorielle(int n)
{
   if(n == 0)
      return 1;
   else
      return n*factorielle(n-1);
}

int main(void){
	char rep[100];
    srand(time(NULL)); //init la fonction rand()
    int i,n,m,t,xn1,yn1,xn2,yn2,xm1,ym1,xm2,ym2;
	printf("entrez le nom du fic à creer(format .txt):   ");
	scanf("%s",rep);

//crea fichier
	FILE* fichier;
	fichier=fopen(rep,"w");
    printf("entrez la taille du cote du carre:");
    scanf("%d",&n);
    m=n;
    printf("entrez la taille des cases:");
    scanf("%d",&t);

//calcul pour centrer la grille
int marge_c=(WINDOW_WIDTH-(t*n))/2;
int marge_h=(WINDOW_HEIGHT-(t*m))/2;
//début de l'interface graphique
start_graphics();
set_drawing_color(color_BLACK);
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

set_drawing_color(color_BLACK);
ecrit_init(fichier,n,t,co,li,finco,finli);
sup_g(fichier,li,co,t);
while((li<=finli)&&(co>=finco))
{
//int touche=get_key();
//printf("%d",touche); mouchar pour vérifier que le rand marchait bien
    if(((touche==key_LEFT)&&(li>(xn1+(t/2))))&&(g>0))
    {   li=li-t;
        draw_circle_full(li,co,r);
        sup_g(fichier,li+t,co,t);
        draw_circle_full(li+t,co,r);
        set_drawing_color(color_BLACK);
        g--;

    }
    else if(((touche==key_RIGHT)&&(li<xn2-(t/2)))&&(d>1))
    {   li=li+t;
        draw_circle_full(li,co,r);
        sup_d(fichier,li-t,co,t);
        draw_circle_full(li-t,co,r);
        set_drawing_color(color_BLACK);
        touche=dir();
        d--;
    }
    else if(((touche==key_DOWN)&&(co>finco))&&(b>1))
    {   co=co-t;
        draw_circle_full(li,co,r);
        sup_bas(fichier,li,co+t,t);
        draw_circle_full(li,co+t,r);
        set_drawing_color(color_BLACK);
        b--;
    }
    else if(((touche==key_UP)&&(co<yn1-(1.5*t)))&&(h>0))
    {   co=co+t;
        draw_circle_full(li,co,r);
        sup_haut(fichier,li,co-t,t);
        draw_circle_full(li,co-t,r);
        set_drawing_color(color_BLACK);
        h--;
    }
    else if (((li==finli)&& (co==finco)))
    {   li=li+t;
        draw_circle_full(li,co,r);
        sup_d(fichier,li-t,co,t);
        draw_circle_full(li-t,co,r);
        set_drawing_color(color_BLACK);
        touche=dir();
	fclose(fichier);
        sleep(5);
        stop_graphics();
    }
 touche=dir();
   update_graphics();
}
get_key();
return 0;
}

