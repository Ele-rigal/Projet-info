
void draw_grid(lines,columns,size)
	{


	}	

int move_left(int *x,int *lines)
	{
		if (x ==0)
		return -1;
		else 
			*x= *x-1 


	}
int move_right(int *x,int *lines)
	{

	if (*x==(*lines)-2)
	return -1;
	else 
		*x=*x+1;
	}
	
int move_up(int *y,int *columns)
	{
	if (*y ==0)
	return -1;
	else 
		*y=*y+1;

	}
int move_down(int *y,int *columns)
	{
	if (*y==(*columns)-2)
	return -1;
	else 
	*y=*y-1;
	} 
void update_graphics()
	{
	clear_screen();
       /*



	*/
	upddate_graphics();

	}
 int jeu()
	{
	int compteur =0;
	GRID *g;
	POS *p;
	END *e;
	draw_grid();
	int a;
	do
	{
	if (getkey()==key_LEFT)
	a = move_left((*p).x,*lines);
	else if (getkey()==key_RIGHT)
	a= move_right((*p).x,*lines);
	else if (getkey()==key_UP)
	a= move_up((*p).y,*columns);
	else if (getkey()==key_DOWN)
	a=move_down((*p).y,*columns);
	}while(a ==-1)
	
	compteur ++;
	//update_graphics();
	



	}while(*p != *e);





	}
	



















