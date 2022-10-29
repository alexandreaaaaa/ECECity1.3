#include <allegro.h>
#include <png.h>
#include <time.h>
#include <stdbool.h>
#define TAILLEX 45
#define TAILLEY 45
#define NBBTN 3



BITMAP* recup_sprites( BITMAP*scr,int w,int h,int startx,int starty,int col,int element)
{
    BITMAP *bmp;
    int x,y;
    bmp=create_bitmap(w,h);
    if (bmp!=NULL)
    {
        x = startx + (element%col)*w;
        y = starty + (element/col)*h;
        blit( scr, bmp, x, y, 0, 0, w, h);
    }
    return bmp;
}
void carre(BITMAP*bmp, int x, int y, int color)
{
    int points[8]={x+3, y+3, 23+x, 14+y, x+3, y+25, x-17, 14+y};
    polygon(bmp, 4, points, color);
}
void moveCamera(int*x, int*y)
{
    if (key[KEY_RIGHT]) {
        *x -= 2;
    } else if (key[KEY_LEFT]) {
        *x += 2;
    }
    if (key[KEY_UP]) {
        *y += 2;
    } else if (key[KEY_DOWN]) {
        *y -= 2;
    }
}
void targetBitmap(BITMAP*bmp, int x, int y)
{
    int i, j;
    rectfill(bmp, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
    for (i = 0; i < TAILLEX; i++) {
        for (j = 0; j < TAILLEY; j++) {
            carre(bmp, (SCREEN_W / 2) + 23*i - 23 * j + x+20, 125 + 13 * i + 13 * j + y-1, makecol(1, j, i));
        }
    }
    rectfill(bmp, 20, 20, 238, 500, makecol(0, 0, 0));
    rectfill(bmp, 30, 30, 94, 94, makecol(0, 0, 1));
    rectfill(bmp, 97, 30, 161, 94, makecol(0, 0, 2));
    rectfill(bmp, 164, 30, 228, 94, makecol(0, 0, 3));
}



void mouseOnCase(BITMAP*bmp, BITMAP*targetBitmap, int matriceMap[TAILLEX][TAILLEY], int x, int y, int*l, int*c)
{
    int i, j;
    for (i = 0; i < TAILLEX; i++) {
        for (j = 0; j < TAILLEY; j++) {
            if(getpixel(targetBitmap, mouse_x, mouse_y)==makecol(1, j, i)&&matriceMap[i][j]!=-1)
            {
                carre(bmp, (SCREEN_W / 2) + 23*i - 23 * j + x+20, 125 + 13 * i + 13 * j + y-1, makecol(191, 41, 41));
                *l=i;
                *c=j;
            }
        }
    }
}

void initialisationAllegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(NULL);
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void cutSprites(BITMAP*matriceSol[3][17], BITMAP*asset)
{
    //Sols et routes
    int i, j;
    matriceSol[0][0]= recup_sprites(asset, 47, 47, 161, 702, 17, 0);
    matriceSol[0][1]= recup_sprites(asset, 47, 47, 106, 702, 17, 0);
    matriceSol[0][2]= recup_sprites(asset, 47, 47, 53, 757, 17, 0);
    matriceSol[0][3]= recup_sprites(asset, 47, 47, 106, 757, 17, 0);
    matriceSol[0][4]= recup_sprites(asset, 47, 47, 161, 757, 17, 0);
    for(i=0; i<4; i++)
    {
        matriceSol[0][i+5]= recup_sprites(asset, 47, 47, i*53, 809, 17, 0);
    }
    for(i=0; i<3; i++)
    {
        matriceSol[0][i+9]= recup_sprites(asset, 47, 47, i*53, 859, 17, 0);
    }
    matriceSol[0][12]= recup_sprites(asset, 47, 47, 161, 859, 17, 0);
    for(i=0; i<2; i++)
    {
        matriceSol[0][i+13]= recup_sprites(asset, 47, 47, i*53, 910, 17, 0);
    }
    matriceSol[0][16]= recup_sprites(asset, 47, 47, 161, 910, 17, 0);

    //Eau
    matriceSol[1][0]= recup_sprites(asset, 47, 47, 265, 702, 17, 0);
    matriceSol[1][1]= recup_sprites(asset, 47, 47, 316, 702, 17, 0);
    matriceSol[1][2]= recup_sprites(asset, 47, 47, 367, 757, 17, 0);
    for(i=0; i<4; i++)
    {
        matriceSol[1][i+3]= recup_sprites(asset, 47, 47, 212+i*53, 757, 17, 0);
    }
    for(i=0; i<4; i++)
    {
        matriceSol[1][i+7]= recup_sprites(asset, 47, 47, 212+i*53, 809, 17, 0);
    }
    for(i=0; i<4; i++)
    {
        matriceSol[1][i+11]= recup_sprites(asset, 47, 47, 212+i*53, 859, 17, 0);
    }
}

void affichageMap(BITMAP*bmp, BITMAP*matriceSol[3][17], int matriceMap[TAILLEX][TAILLEY], int x, int y)
{
    int i, j;
    for (i = 0; i < TAILLEX; i++)
    {
        for(j=0; j<TAILLEY; j++)
        {
            draw_sprite(bmp, matriceSol[0][matriceMap[i][j]], (SCREEN_W / 2) + 23 * i - 23 * j + x,125 + 13 * i + 13 * j + y);
        }
    }
}

void trifill(BITMAP*bmp, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
    int points[6]={x1, y1, x2, y2, x3, y3};
    polygon(bmp,3, points,color);
}

void carreIcone(BITMAP*bmp, int x1, int y1, int x2, int y2, int c1, int c2, int c3)
{
    rectfill(bmp, x1, y1, x2, y2, c1);
    rectfill(bmp, x2-3, y1, x2, y2, c2);
    rectfill(bmp, x1, y2-3, x2, y2, c2);
    rectfill(bmp, x1, y1, x2, y1+3, c3);
    rectfill(bmp, x1, y1, x1+3, y2, c3);
    trifill(bmp, x1, y2, x1+3, y2-3, x1+3, y2, c2);
    trifill(bmp, x2-3, y1+3, x2, y1, x2, y1+3, c2);
}


//void btnTerrain(BITMAP*bmp, BITMAP*targetBmp, int**matriceMap, bool**btn, int x, int y, int l, int c)
void appuiSurBtn(BITMAP*bmp, BITMAP*targetBmp, bool*btn, int nbBtn, int xBtn, int yBtn)
{
    if (getpixel(targetBmp, mouse_x, mouse_y) == makecol(0, 0, nbBtn+1) && mouse_b == 1&&btn[nbBtn]==false) {
        btn[nbBtn] = true;
    }
    if (btn[nbBtn] == false) {
        carreIcone(bmp, xBtn, yBtn, xBtn+64, yBtn+64, makecol(150, 150, 150), makecol(65, 65, 65), makecol(225, 225, 225));
    }
    else {
        carreIcone(bmp, xBtn, yBtn, xBtn+64, yBtn+64, makecol(80, 80, 80), makecol(225, 225, 225), makecol(40, 40, 40));
    }
}
void barreOutils(BITMAP*bmp, BITMAP*targetBitmap, BITMAP*matriceSol[3][170], int *btn)
{
    carreIcone(bmp, 20, 20, 238, 500, makecol(150, 150, 150), makecol(65, 65, 65), makecol(225, 225, 225));
    appuiSurBtn(bmp, targetBitmap, btn,  0, 30, 30);
    draw_sprite(bmp, matriceSol[0][1], 39, 39);
    appuiSurBtn(bmp, targetBitmap, btn, 1, 97, 30);
    draw_sprite(bmp, matriceSol[0][3], 106, 39);

}

bool reseau(int matriceReseau[TAILLEX][TAILLEY], int a, int b, int c, int d, int e, int*lR, int*cR)
{
    int i, j;
    for(i=0; i<TAILLEX; i++)
    {
        for(j=0; j<TAILLEY; j++)
        {
            if(matriceReseau[i][j-1]==a && matriceReseau[i+1][j]==b && matriceReseau[i][j+1]==c && matriceReseau[i-1][j]==d && matriceReseau[i][j]==e)
            {
                *lR=i;
                *cR=j;
                return true;
            }
        }
    }
}

int main()
{
    // Lancer allegro et le mode graphique
    initialisationAllegro();
    srand((time(NULL)));
    int i, j, k, x=0, y=0, l, c, lReseau, cReseau;
    int matriceMap[5][TAILLEX][TAILLEY];
    int matriceReseau[TAILLEX][TAILLEY];
    BITMAP*matriceSol[3][17];
    BITMAP*matriceBatiment[5];
    BITMAP*asset;
    BITMAP*bmp = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP*targetBmp = create_bitmap(SCREEN_W, SCREEN_H);
    bool btn[5];
    int lastBtnOn=0,lastBtnOff=0;

    asset=load_bitmap("C:\\Users\\ASUS\\OneDrive\\Bureau\\untitled1\\Spritesheet.bmp",NULL);
    cutSprites(&matriceSol, asset);
    for(i=0; i<NBBTN; i++)
    {
        btn[i]=false;
    }
    for(j=0; j<TAILLEX; j++)
    {
        for(k=0; k<TAILLEY; k++)
        {
            matriceMap[0][j][k]=0;
            matriceReseau[j][k]=0;
        }
    }
    // Boucle interactive
    while (!key[KEY_ESC])
    {
        clear_bitmap(bmp);
        rectfill(bmp, 0, 0, SCREEN_W, SCREEN_H, makecol(189, 232, 242));
        moveCamera(&x, &y);
        targetBitmap(targetBmp, x, y);
        affichageMap(bmp, matriceSol, matriceMap, x, y);


        //Bouton placer terrain
        if(btn[0]==true)
        {
            for(i=0; i<NBBTN; i++) {
                if (btn[i] == true && i != 0) {
                    btn[i] = false;
                }
            }
            mouseOnCase(bmp, targetBmp, matriceMap, x, y, &l, &c);
            if(mouse_b==1&&getpixel(targetBmp, mouse_x, mouse_y)!=(makecol(0, 0, 0)&&makecol(0, 0, 1)&&makecol(0, 0, 2))) {
                for (i = -1; i < 2; i++) {
                    for (j = -1; j < 2; j++) {
                        matriceMap[0][l + i][c + j] = 1;
                    }
                }
            }
            if(mouse_b&2) {
                btn[0]=false;
            }
        }
        //Bouton placer route
        if(btn[1]==true)
        {
            for(i=0; i<NBBTN; i++)
            {
                if(btn[i]==true&&i!=1)
                {
                    btn[i]=false;
                }
            }
            mouseOnCase(bmp, targetBmp, matriceMap, x, y, &l, &c);
            if(mouse_b==1&&getpixel(targetBmp, mouse_x, mouse_y)!=(makecol(0, 0, 0)||makecol(0, 0, 1)||makecol(0, 0, 2))) {
                matriceMap[0][l][c] = 3;
                matriceReseau[l][c]=1;
            }
        }

        if(reseau(matriceReseau, 0, 0, 1, 1, 1, &lReseau, &cReseau)==true)
        {
            matriceMap[0][lReseau][cReseau]=9;
            matriceMap[0][lReseau][cReseau+1]=2;
        }
        if(reseau(matriceReseau, 1, 1, 1, 1, 1, &lReseau, &cReseau)==true)
        {
            matriceMap[0][lReseau][cReseau]=4;
            matriceMap[0][lReseau][cReseau-1]=2;
            matriceMap[0][lReseau][cReseau+1]=2;
        }
        if(reseau(matriceReseau, 1, 1, 0, 1, 1, &lReseau, &cReseau)==true)
        {
            matriceMap[0][lReseau][cReseau]=7;
            matriceMap[0][lReseau][cReseau-1]=2;
        }
        if(reseau(matriceReseau, 0, 1, 1, 1, 1, &lReseau, &cReseau)==true)
        {
            matriceMap[0][lReseau][cReseau]=5;
            matriceMap[0][lReseau][cReseau-1]=2;
        }





        //btnTerrain(bmp, targetBmp, matriceMap, btn, x, y, l, c);

        barreOutils(bmp, targetBmp, matriceSol, btn);
        draw_sprite(bmp, mouse_sprite, mouse_x, mouse_y);
        blit(bmp, targetBmp, 0, 0, 0, 0, bmp->w, bmp->h);
        blit(targetBmp, screen, 0, 0, 0, 0, bmp->w, bmp->h);
        lastBtnOn=mouse_b;
    }
    return 0;
}
END_OF_MAIN()
