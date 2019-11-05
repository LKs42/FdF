#include "fdf.h"

void liner(int *img, t_point *a, t_point *b)
{
	int tab[10];

	tab[0] = a->x;
	tab[1] = b->x;
	tab[2] = a->y;
	tab[3] = b->y;
	tab[4] = abs(tab[1]-tab[0]);
	tab[5] = tab[0]<tab[1] ? 1 : -1;
	tab[6] = abs(tab[3]-tab[2]);
	tab[7] = tab[2]<tab[3] ? 1 : -1;
	tab[8] = (tab[4]>tab[6] ? tab[4] : -tab[6])/2;
	while(!(tab[0]==tab[1] && tab[2]==tab[3]))
	{
		fill_pixel(img, tab[0], tab[2], a->color);
		tab[9] = tab[8];
		if (tab[9] > -tab[4])
		{
			tab[8] -= tab[6];
			tab[0] += tab[5];
		}
		if (tab[9] < tab[6])
		{
			tab[8] += tab[4];
			tab[2] += tab[7];
		}
	}
}