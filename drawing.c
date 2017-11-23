#include <sdl.h>
#include <stdio.h>
#include <math.h>

//trying wolf 3d again:

//initialize the renderer:
SDL_Renderer	*init(char *title)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow(title, 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, 1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	return (ren);
}

int		abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	swap(int *n1, int *n2)
{
	int temp;

	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}


//draw function:
void	draw_line(SDL_Renderer *ren, int x1, int y1, int x2, int y2)
{
	double	slope;
	double	offset;
	int		iterate;
	int		*a;
	int		*b;

	slope = 0;
	offset = 0;
	if (abs(x1 - x2) >= abs(y1 - y2))
	{
		a = &x1;
		b = &y1;
	}
	else
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
		a = &y1;
		b = &x1;
	}
		iterate = -1 + (2 * (x1 < x2));
		slope = ((double)abs(y1 - y2) / (double)abs(x1 - x2)) * (-1 + (2 * (y1 < y2)));
		while (x1 != x2)
		{
			if (offset >= 0.49999 || offset <= -0.5)
			{
				offset -= -1 + (2 * (y1 < y2));
				y1 += -1 + (2 * (y1 < y2));
			}
			SDL_RenderDrawPoint(ren, *a, *b);
			x1 += iterate;
			offset += slope;
		}
}

//gameworld:
#define mapWidth 24
#define mapHeight 24

//Map dimensions:
int     Width = mapWidth;
int     Height = mapHeight;


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//main program flow:
int     main()
{
    //in player struct:
    //position of the player:
    double posX = 2, posY = 2;
    //direction of player:
    double dirX = -1, dirY = 0;
    //camera plane of the player:
    double planeX = 0, planeY = 0.66;
    //Movement for player in map:
    int    MoveX = 0;
    int    MoveY = 0;

    //in fps struct:
    //current frame:
    double aTime = 0;
    //previous frame:
    double oldTime = 0;

    //create screen now:
    SDL_Renderer *ren = init("wolf3D");
    SDL_Event  event;
    //SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    
    int     w = 640;
    int     h = 480;

    //game loop:
    while (1)
    {
        int x = 0;
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        //Ray casting algorithm:
        //for (x = 0; x <= w - 1; x++)
        while (x < w)
        {
            //caculate ray position and direction:
            double      cameraX = 2 * x / (double)w - 1; // x-coordinate in cam space
            double      rayPosX = posX;
            double      rayPosY = posY;
            double      rayDirX = dirX + planeX * cameraX;
            double      rayDirY = dirY + planeY * cameraX;

            //DDA:
            //current position in map:
            int     mapX = (int)rayPosX;
            int     mapY = (int)rayPosY;

            //length of ray from current position to next x or y-side:
            double  sideDistX;
            double  sideDistY;

            //length of ray from one x or y-side to next x or y-side:
            double  deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
            double  deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
            double  perpWallDist;

            //what dir to step in x or y-dir (either +1 or -1)
            int     stepX;
            int     stepY;

            int     hit = 0; //was there a wall hit?
            int     side;

            //calculate step and initial sideDist:
            if (0 > rayDirX)
            {
                stepX = -1;
                sideDistX = (rayPosX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
            }
            if (0 > rayDirY)
            {
                stepY = -1;
                sideDistY = (rayPosY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
            }

            //Perfoming DDA:
            while (0 == hit)
            {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }

            //calculate distance projected on camera direction:
            if (0 == side)
                perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

            //calculate height of line to draw on screen:
            int     lineHeight = (int)(h / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe:
            int     drawStart = -lineHeight / 2 + h / 2;
            if (drawStart <  0)
                drawStart = 0;
            int     drawEnd = lineHeight / 2 + h / 2;
            if (drawEnd >= h)
                drawEnd = h - 1;

            int     i = 0;
            if (i < drawStart + 1)
            {
                SDL_SetRenderDrawColor(ren, 10, 130, 235, 255);
                draw_line(ren, x, i, x, drawStart);
                i++;
            }
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            //Reference: https://github.com/Siyanda-Mzam/TheWolf/blob/master/src/draw.c
            if (0 == side)
            {
                if (0 > stepX)
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
            }
            else
            {
                if (0 > stepY)
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                else
                    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
            }
                draw_line(ren, x, drawStart + 2, x, drawEnd);
            i = drawEnd + 2;
            if (i >= drawEnd && i < h)
            {
                SDL_SetRenderDrawColor(ren, 210, 180, 140, 255);
                draw_line(ren, x, i, x, h);
                i++;
            }
            x++;
        }

        //timing for input and FPS counter:
        oldTime = aTime;
        aTime = SDL_GetTicks();
        double  frameTime = (aTime - oldTime) / 1000.0;
        //printf("%f\n",1.0 / frameTime);
        SDL_RenderPresent(ren);
       

        //speed modifiers:
        double  moveSpeed = frameTime * 30.0; //the constant value is in squares/second
        double  rotSpeed = frameTime * 6.0; //constant value is in radians/second
        
            while (SDL_PollEvent(&event))
            {
                MoveX = posX + dirX * moveSpeed;
                MoveY = posY + dirY * moveSpeed;
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        if (worldMap[(int)MoveX][(int)(posY)] == 0)
                            posX += dirX * moveSpeed;
                        if (worldMap[(int)(posX)][(int)MoveY] == 0)
                            posY += dirY * moveSpeed;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        if (worldMap[(int)MoveX][(int)(posY)] == 0)
                            posX -= dirX * moveSpeed;
                        if (worldMap[(int)(posX)][(int)MoveY] == 0)
                            posY -= dirY * moveSpeed;
                    }
                    printf("X Position: %f\n", posX);
                    printf("Y Position: %f\n", posY);
                    printf("\n");
                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        double  oldDirX = dirX;
                        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    }
                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        double  oldDirX = dirX;
                        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                        double oldPlaneX = planeX;
                        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        exit(-1);
                    }
                }
            }
    }
    return (0);
}