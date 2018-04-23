typedef int ENTIER;
ENTIER x;
int dir(){
    int dire[4]={key_LEFT,key_RIGHT,key_DOWN,key_UP};
    int i=rand()%4;
    x=dire[i];
    return x;
}
void sup_g(int li,int co,int t)
{//supprime cloison quand on tourne a gauche
    set_drawing_color(color_WHITE);
    draw_line(li-(t/2), co-(t/2), li-(t/2), co+(t/2));
    update_graphics();
}
void sup_d(int li,int co,int t)
{//supprime cloison quand on tourne a droite
    set_drawing_color(color_WHITE);
    draw_line(li+(t/2), co-(t/2), li+(t/2), co+(t/2)); update_graphics();
}
void sup_haut(int li,int co,int t)
{
    set_drawing_color(color_WHITE);
    draw_line(li-(t/2), co+(t/2), li+(t/2), co+(t/2));
    update_graphics();
}

void sup_bas(int li,int co,int t)
{
    set_drawing_color(color_WHITE);
    draw_line(li-(t/2), co-(t/2), li+(t/2), co-(t/2));
    update_graphics();
}

long factorielle(int n)
{
   if(n == 0)
      return 1;
   else
      return n*factorielle(n-1);
}

void ini_graph()
{
//début de l'interface graphique
start_graphics();
set_drawing_color(color_BLACK);
}
