#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <chipmunk.h>
#include "physics.h"
#include "init.h"
#include "collision.h"
#include <stdlib.h>

//definice-------------------------- 
typedef struct {
    int h;
    int w;
    int x;
    int y;
    float alpha;
    bool selected;
} Body;

int main()
{
    bool Key_Play = 0;
    bool Key_Menu = 1;
    bool Key_Levels = 0;
    bool Win = 0;
    int bird_qantity = 3;
    int body_qantity = 8;
    Body* body = malloc(body_qantity * sizeof(Body));
    Rigid_body* rigid_body = malloc(body_qantity * sizeof(Rigid_body));
    if (!init())
    {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    if (!loadMedia())
    {
        printf("Failed to initialize  media fails!\n");
        closeGame();
        return -1;
    }
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    SDL_GetWindowSize(gWindow, &WINDOW_WIDTH, &WINDOW_HEIGHT);

    SDL_Rect bird1Rect;
    SDL_Rect bird2Rect;
    SDL_Rect bird3Rect;
    SDL_Rect slingRect;
    SDL_Rect sling2Rect;
    SDL_Rect pigRect;
    SDL_Rect boardRect1;
    SDL_Rect boardRect2;
    SDL_Rect boardRect3;

    SDL_Rect TextButton1Rect;
    SDL_Rect TextButton2Rect;
    SDL_Rect TextButton3Rect;
    SDL_Rect TextButtonExitToMenuRect;
    SDL_Rect TextYouWinRect;

    SDL_Rect button;
    SDL_Rect ButtonLevelsOpenRect;
    SDL_Rect ButtonLevelsCloseRect;
    SDL_Rect Button_NextRect;
    SDL_Rect Button_LevelsRect;
    SDL_Rect Button_RetryRect;

    SDL_Rect rect;
   //-------------------------------
    //tlačitka-----------------------
    int button_qantity = 8;
    int buttonMenu_qantity = 3;
    int button_width = 250;
    int button_height = 50;
    int ButtonSpase = 50;
    int* button_x = (int*) malloc(button_qantity * sizeof(int));
    int* button_y = (int*) malloc(button_qantity * sizeof(int));
    bool* Key_change = (bool*) malloc(button_qantity * sizeof(bool));
    
    for (int i = 0; i < buttonMenu_qantity; i++)
    {
        button_x[i] = WINDOW_WIDTH / 2 - (button_width/2);
        button_y[i] = WINDOW_HEIGHT / 2 - (((buttonMenu_qantity - 1) * (button_height + ButtonSpase)) / 2) - (button_height/2) + i *(button_height + 50);
    }

    button_x[3] = WINDOW_WIDTH / 2 - (button_width/2);
    button_y[3] = WINDOW_HEIGHT - button_height - 20;
    //tlačítka pro výběr úrovně
    int buttonLevels_qantity = 8;
    int button_level_width = 104;
    int button_level_height = 104;
    int button_level_x;
    int button_level_y;
    int button_level_is_open;
    button_level_is_open = 1;
    
    //umístění tlačítka úrovně
            button_level_x = button_level_width + 10;
            button_level_y = (WINDOW_HEIGHT / 4) - (button_level_height / 2);

            button_level_x = button_level_width + 10;
            button_level_y = (WINDOW_HEIGHT / 4) - (button_level_height / 2);
    //----------------------------    
    //textures from bodies    
    SDL_Event e;
    bool quit = false;
    SDL_Renderer *renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_Texture *bird1_txtr = SDL_CreateTextureFromSurface(renderer, gBird1);
    SDL_Texture *bird2_txtr = SDL_CreateTextureFromSurface(renderer, gBird2);
    SDL_Texture *bird3_txtr = SDL_CreateTextureFromSurface(renderer, gBird3);

    SDL_Texture *sling1_txtr = SDL_CreateTextureFromSurface(renderer, gSling);
    SDL_Texture *sling2_txtr = SDL_CreateTextureFromSurface(renderer, gSling2);

    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(renderer, gBackground);
    SDL_Texture *background_texture1 = SDL_CreateTextureFromSurface(renderer, gBackground1);

    SDL_Texture* pig_txtr=SDL_CreateTextureFromSurface(renderer, gpig);

    SDL_Texture* board1_txtr = SDL_CreateTextureFromSurface(renderer, gboard2); // wooden panel1
    SDL_Texture* board2_txtr = SDL_CreateTextureFromSurface(renderer, gboard1); // wooden panel2
    SDL_Texture* board3_txtr = SDL_CreateTextureFromSurface(renderer, gboard2); // wooden panel1

    SDL_Texture* ButtonLevelsOpen_txtr=SDL_CreateTextureFromSurface(renderer, gButtonLevelsOpen);
    SDL_Texture* ButtonLevelsClose_txtr=SDL_CreateTextureFromSurface(renderer, gButtonLevelsClose);

    SDL_Texture* Button_Next_txtr=SDL_CreateTextureFromSurface(renderer, gButton_Next);
    SDL_Texture* Button_Levels_txtr=SDL_CreateTextureFromSurface(renderer, gButton_Levels);
    SDL_Texture* Button_Retry_txtr=SDL_CreateTextureFromSurface(renderer, gButton_Retry);

    //textures from text
    
    TTF_Font * font1 = TTF_OpenFont("font.ttf", 24);
    SDL_Color text_color = {255, 255, 255};
    SDL_Surface* text_surface1 = TTF_RenderText_Solid(font1, "PLAY", text_color);
    SDL_Texture* text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1);

    SDL_Surface* text_surface2 = TTF_RenderText_Solid(font1, "LEVELS", text_color);
    SDL_Texture* text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);

    SDL_Surface* text_surface3 = TTF_RenderText_Solid(font1, "EXIT", text_color);
    SDL_Texture* text_texture3 = SDL_CreateTextureFromSurface(renderer, text_surface3);

    SDL_Surface* text_surface4 = TTF_RenderText_Solid(font1, "MENU", text_color);
    SDL_Texture* text_texture4 = SDL_CreateTextureFromSurface(renderer, text_surface4);

    SDL_Surface* text_surface5 = TTF_RenderText_Solid(font1, "YOU WIN!", text_color);
    SDL_Texture* text_texture5 = SDL_CreateTextureFromSurface(renderer, text_surface5);
  
    //Settings=====================================================
    body[0].x = 10; //Počáteční poloha ptáka № 1 podle X
    body[0].y = WINDOW_HEIGHT - 76 - 150;//Počáteční poloha ptáka № 1 podle Y
    body[0].selected = false;//uchopení ptáka №1 pomocí kurzoru
    body[0].h = 60;
    body[0].w = 60;

    body[1].x = 71; //Počáteční poloha ptáka № 2 podle X
    body[1].y = WINDOW_HEIGHT - 76 - 150;//Počáteční poloha ptáka № 2 podle Y
    body[1].selected = false;//uchopení ptáka №2 pomocí kurzoru
    body[1].h = 60;
    body[1].w = 60;

    body[2].x = 131; //Počáteční poloha ptáka № 3 podle X
    body[2].y = WINDOW_HEIGHT - 76 - 150;//Počáteční poloha ptáka №3 podle Y
    body[2].selected = false;//uchopení ptáka №3 pomocí kurzoru
    body[2].h = 60;
    body[2].w = 60;
    
    body[3].x = WINDOW_WIDTH - 200; //Počáteční poloha prasete podle X
    body[3].y = WINDOW_HEIGHT - 450;//Počáteční poloha prasete podle Y
    body[3].selected = false;
    body[3].h = 60;
    body[3].w = 110;

    // board 1
    body[4].x = WINDOW_WIDTH - 110; // board Х0
    body[4].y = WINDOW_HEIGHT - 250;// board Y0 
    body[4].selected = false;
    body[4].h = 86;
    body[4].w = 24;
    body[4].alpha = 0;

    // board 2
    body[5].x = WINDOW_WIDTH - 290; // board Х0
    body[5].y = WINDOW_HEIGHT - 350;// board Y0 
    body[5].selected = false;
    body[5].h = 23;
    body[5].w = 207;
    body[5].alpha = 0;

    // board 3
    body[6].x = WINDOW_WIDTH - 290; // board Х0
    body[6].y = WINDOW_HEIGHT - 250;// board Y0 
    body[6].selected = false;
    body[6].h = 86;
    body[6].w = 24;
    body[6].alpha = 0;

    int* k = (int*) malloc(body_qantity * sizeof(int));//počítadlo fyziky (nedotýkat se)
    int* k1 = (int*) malloc(body_qantity * sizeof(int));//počítadlo fyziky (nedotýkat se)
    int* k2 = (int*) malloc(body_qantity * sizeof(int));//počítadlo fyziky (nedotýkat se)
    for (int i=0; i < body_qantity;i++) k[i]=0;
    for (int i=0; i < body_qantity;i++) k1[i]=0;
    for (int i=0; i < body_qantity;i++) k2[i]=0;

    int sling_thickness = 12;//tloušťka gumičky na praku
    int slingX1 = 338;//poloha peraku č. 1 podle X, změňte to
    int slingY1 = WINDOW_HEIGHT - 180 - sling_thickness / 2;//poloha praku č. 1 podle Y, změňte to
    int slingX2 = slingX1 - 43;//oloha praku č. 2 podle X
    int slingY2 = WINDOW_HEIGHT - 185 - sling_thickness / 2;//poloha praku č. 2 podle Y, změňte to

    float* StartEventTimeFall = (float*) malloc(body_qantity * sizeof(float));//okamžik začatků pádu
    float* EventTimeFall = (float*) malloc(body_qantity * sizeof(float));//Doba pokračování pádu
    float* StartEventTimeMove = (float*) malloc(body_qantity * sizeof(float));//okamžik začátku pohybu (vlevo, vpravo)
    float* EventTimeMove = (float*) malloc(body_qantity * sizeof(float));//okamžik pokračování  pohybu (vlevo, vpravo)
    for (int i=0; i < body_qantity;i++) StartEventTimeFall[i]=0;
    for (int i=0; i < body_qantity;i++) EventTimeFall[i]=0;
    for (int i=0; i < body_qantity;i++) StartEventTimeMove[i]=0;
    for (int i=0; i < body_qantity;i++)  EventTimeMove[i]=0;

    float* pointX = (float*) malloc(body_qantity * sizeof(float));
    float* pointY = (float*) malloc(body_qantity * sizeof(float));
  
    float G = 15;//gravitační zrychlení

    float* Vx = (float*) malloc(body_qantity * sizeof(float));//start speed X
    float* Vy = (float*) malloc(body_qantity * sizeof(float));//start speed y
    for (int i=0; i < body_qantity;i++) Vx[i]=0;
    for (int i=0; i < body_qantity;i++) Vy[i]=0;

    int* X0 = (int*) malloc(body_qantity * sizeof(int));//X souřadnice na začátku pohybu
    int* Y0 = (int*) malloc(body_qantity * sizeof(int));//y souřadnice na začátku pohybu
    for (int i=0; i < body_qantity;i++) X0[i]=0;
    for (int i=0; i < body_qantity;i++) Y0[i]=0;


//-----------------------------------------------------
    bool collision_y[8];
    while (!quit)
    {
    //místa pro herní prvky: těla, tlačítka, pozadí
    bird1Rect.x = body[0].x;
    bird1Rect.y = body[0].y;
    bird1Rect.w = body[0].w;
    bird1Rect.h = body[0].h;

    bird2Rect.x = body[1].x;
    bird2Rect.y = body[1].y;
    bird2Rect.w = body[1].w;
    bird2Rect.h = body[1].h;

    bird3Rect.x = body[2].x;
    bird3Rect.y = body[2].y;
    bird3Rect.w = body[2].w;
    bird3Rect.h = body[2].h;

    slingRect.x = slingX1 - 28;
    slingRect.y = slingY1 - 24;
    slingRect.w = 40;
    slingRect.h = 201;

    sling2Rect.x = slingRect.x - 30;
    sling2Rect.y = slingRect.y - 10;
    sling2Rect.w = 45;
    sling2Rect.h = 125;

    pigRect.x = body[3].x;
    pigRect.y = body[3].y;
    pigRect.w = body[3].w;
    pigRect.h = body[3].h;

    boardRect1.x = body[4].x;
    boardRect1.y = body[4].y;
    boardRect1.w = body[4].w;
    boardRect1.h = body[4].h;

    boardRect2.x = body[5].x;
    boardRect2.y = body[5].y;
    boardRect2.w = body[5].w;
    boardRect2.h = body[5].h;

    boardRect3.x = body[6].x;
    boardRect3.y = body[6].y;
    boardRect3.w = body[6].w;
    boardRect3.h = body[6].h;

    TextButton1Rect.w = 75; //Width button №1
    TextButton1Rect.h = 40; //Hight button №1
    TextButton1Rect.x = button_x[0] + (button_width / 2) - (TextButton1Rect.w / 2);
    TextButton1Rect.y = button_y[0] + (button_height / 2) - (TextButton1Rect.h / 2);

    TextButton2Rect.w = 75; //Width button №2
    TextButton2Rect.h = 40; //Hight button №2
    TextButton2Rect.x = button_x[1] + (button_width / 2) - (TextButton2Rect.w / 2);
    TextButton2Rect.y = button_y[1] + (button_height / 2) - (TextButton2Rect.h / 2);

    TextButton3Rect.w = 75; //Width button №3
    TextButton3Rect.h = 40; //Hight button №3
    TextButton3Rect.x = button_x[2] + (button_width / 2) - (TextButton3Rect.w / 2);
    TextButton3Rect.y = button_y[2] + (button_height / 2) - (TextButton3Rect.h / 2);

    TextButtonExitToMenuRect.w = 75; //Width button №3
    TextButtonExitToMenuRect.h = 40; //Hight button №3
    TextButtonExitToMenuRect.x = button_x[3] + (button_width / 2) - (TextButtonExitToMenuRect.w / 2);
    TextButtonExitToMenuRect.y = button_y[3] + (button_height / 2) - (TextButtonExitToMenuRect.h / 2);

    TextYouWinRect.w = 300;
    TextYouWinRect.h = 75;
    TextYouWinRect.x = (WINDOW_WIDTH / 2) - (TextYouWinRect.w / 2);
    TextYouWinRect.y = 200;

    ButtonLevelsOpenRect.x = button_level_x;
    ButtonLevelsOpenRect.y = button_level_y; 
    ButtonLevelsOpenRect.h = button_level_height;
    ButtonLevelsOpenRect.w = button_level_width;

    ButtonLevelsCloseRect.x = button_level_x;
    ButtonLevelsCloseRect.y = button_level_y; 
    ButtonLevelsCloseRect.h = button_level_height + 7;
    ButtonLevelsCloseRect.w = button_level_width;

    Button_LevelsRect.x = WINDOW_WIDTH / 2 - 170;
    Button_LevelsRect.y = WINDOW_HEIGHT / 2 + 100;
    Button_LevelsRect.h = 116;
    Button_LevelsRect.w = 116;

    Button_RetryRect.x = WINDOW_WIDTH / 2 - 58;
    Button_RetryRect.y = WINDOW_HEIGHT / 2 + 100;
    Button_RetryRect.h = 116;
    Button_RetryRect.w = 116;

    Button_NextRect.x = WINDOW_WIDTH / 2 + 55;
    Button_NextRect.y = WINDOW_HEIGHT / 2 + 100;
    Button_NextRect.h = 116;
    Button_NextRect.w = 116;


    //rigid bodys for collision
   //Ground
   rigid_body[body_qantity - 1].x = 0;
   rigid_body[body_qantity - 1].y = WINDOW_HEIGHT - 76 + 60;
   rigid_body[body_qantity - 1].round = 0;
   rigid_body[body_qantity - 1].h = 10;
   rigid_body[body_qantity - 1].w = WINDOW_WIDTH;
   //--------
   rigid_body[0].x = body[0].x;
   rigid_body[0].y = body[0].y;
   rigid_body[0].round = 0;
   rigid_body[0].r = 30;
   rigid_body[0].h = 60;
   rigid_body[0].w = 60;
   rigid_body[0].m = 50;

   rigid_body[1].x = body[1].x;
   rigid_body[1].y = body[1].y;
   rigid_body[1].round = 0;
   rigid_body[1].h = 60;
   rigid_body[1].w = 60;

   rigid_body[2].x = body[2].x;
   rigid_body[2].y = body[2].y;
   rigid_body[2].round = 0;
   rigid_body[2].h = 60;
   rigid_body[2].w = 60;

   rigid_body[3].x = body[3].x+ 30;//pig
   rigid_body[3].y = body[3].y + 10;
   rigid_body[3].round = 1;
   rigid_body[3].r = 25;
   rigid_body[3].h = 60;
   rigid_body[3].w = 60;
   rigid_body[3].m = 50;

   rigid_body[4].x = body[4].x;// board 1
   rigid_body[4].y = body[4].y;
   rigid_body[4].round = 0;
   rigid_body[4].r = 30;
   rigid_body[4].h = body[4].h;
   rigid_body[4].w = body[4].w;
   rigid_body[4].m = 50;
   rigid_body[4].alpha = body[4].alpha;

   rigid_body[5].x = body[5].x;//board 2
   rigid_body[5].y = body[5].y;
   rigid_body[5].round = 0;
   rigid_body[5].r = 30;
   rigid_body[5].h = body[5].h;
   rigid_body[5].w = body[5].w;
   rigid_body[5].m = 50;
   rigid_body[5].alpha = body[5].alpha;

   rigid_body[6].x = body[6].x ;//board 3
   rigid_body[6].y = body[6].y;
   rigid_body[6].round = 0;
   rigid_body[6].r = 30;
   rigid_body[6].h = body[6].h;
   rigid_body[6].w = body[6].w;
   rigid_body[6].m = 50;
   rigid_body[6].alpha = body[6].alpha;


    


    Uint32 CurrentFrameTime = SDL_GetTicks64();//time

 

    SDL_PollEvent(&e);

     
        //opustit hru
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                Key_Play = 0;
                Key_Levels = 0;
                Key_Menu = 1;
            }
        }
    //Button menu
    int mouseX;
    int mouseY;
    if (e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
        //tlačítka menu a návrat
        for (int i = 0; i < buttonMenu_qantity + 1; i++)
        {
            if ((mouseX > button_x[i])&&(mouseX < button_x[i] + button_width)&&(mouseY > button_y[i])&&(mouseY < button_y[i] + button_height))
                {
                    Key_change[i] = 1;
                }
                else Key_change[i] = 0;
    
        
        }
        //tlačítka pro výběr úrovně
        if ((mouseX > button_level_x)&&(mouseX < button_level_x + button_level_width)&&(mouseY > button_level_y)&&(mouseY < button_level_y + button_level_height))
        {
            Key_change[4] = 1;
            if (button_level_y >= ((WINDOW_HEIGHT / 4) - (button_level_height / 2)))
            {
                button_level_y = button_level_y - 10;
            }
            
            
        }else 
        {
            if (button_level_y <= ((WINDOW_HEIGHT / 4) - (button_level_height / 2)))
            {
                button_level_y = button_level_y + 10;
            }
            Key_change[4] = 0;
        }
        //tlacitka po vítězství
        if ((mouseX > Button_LevelsRect.x)&&(mouseX < Button_LevelsRect.x + Button_LevelsRect.w)&&(mouseY > Button_LevelsRect.y)&&(mouseY < Button_LevelsRect.y + Button_LevelsRect.h))
        {
            Key_change[5] = 1;
        }
        else Key_change[5] = 0;

        if ((mouseX > Button_RetryRect.x)&&(mouseX < Button_RetryRect.x + Button_RetryRect.w)&&(mouseY > Button_RetryRect.y)&&(mouseY < Button_RetryRect.y + Button_RetryRect.h))
        {
            Key_change[6] = 1;
        }
        else Key_change[6] = 0;
        


            if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    //menu buttons
                    if ((Key_change[0] == 1)&&(Key_Menu == 1)&&(Key_Play == 0)&&(Key_Levels == 0))
                    {
                        Key_Play = 1;
                        Key_Menu = 0;
                        Win = 0;
                    }
                    if ((Key_change[1] == 1)&&(Key_Menu == 1)&&(Key_Play == 0)&&(Key_Levels == 0))
                    {
                        Key_Levels = 1;
                        Key_Menu = 0;
                        Win = 0;
                    }
                    if ((Key_change[2] == 1)&&(Key_Menu == 1)&&(Key_Play == 0)&&(Key_Levels == 0))
                    {
                        quit = true;
                    }
                    //button return to menu
                    if ((Key_change[3] == 1)&&(Key_Menu == 0)&&(Key_Play == 0)&&(Key_Levels == 1))
                    {
                        Key_Levels = 0;
                        Key_Menu = 1;
                        Win = 0;
                    }
                    //levels sellect
                    if(Key_change[4] == 1)
                    {
                        Key_Play = 1;
                        Key_Levels = 0;
                        Key_Menu = 0;
                        Win = 0;
                    }
                    //win
                    //levels
                    if((Key_change[5] == 1)&&(Win == 1))
                    {
                        Win = 0;
                        Key_Menu = 0;
                        Key_Play = 0;
                        Key_Levels = 1;
                        
                    }
                    //retry
                    if((Key_change[6] == 1)&&(Win == 1))
                    {
                        Win = 0;  
                        Key_Menu = 0;
                        Key_Levels = 0;
                        Key_Play = 1;
                    }
                    if ((Key_change[5] == 1)||(Key_change[6] == 1)||(Key_change[4] == 1))
                    {
                        body[0].x = 10; //Výchozí poloha ptáka №1 podle Х
                        body[0].y = WINDOW_HEIGHT - 76 - 150;//Výchozí poloha ptáka №1 podle Y

                        body[1].x = 71; //Výchozí poloha ptáka №2 podle Х
                        body[1].y = WINDOW_HEIGHT - 76 - 150;//Výchozí poloha ptáka №2 podle Y

                        body[2].x = 131; //Výchozí poloha ptáka №3 podle Х
                        body[2].y = WINDOW_HEIGHT - 76 - 150;//Výchozí poloha ptáka №3 podle Y
                        
                        body[3].x = WINDOW_WIDTH - 200; //Výchozí pozice prasete podle Х
                        body[3].y = WINDOW_HEIGHT - 450;//Výchozí pozice prasete podle Y

                        // board 1
                        body[4].x = WINDOW_WIDTH - 110; // board Х0
                        body[4].y = WINDOW_HEIGHT - 250;// board Y0 

                        // board 2
                        body[5].x = WINDOW_WIDTH - 290; // board Х0
                        body[5].y = WINDOW_HEIGHT - 350;// board Y0 

                        // board 3
                        body[6].x = WINDOW_WIDTH - 290; // board Х0
                        body[6].y = WINDOW_HEIGHT - 250;// board Y0 
                        for (int i = 0; i < body_qantity - 1; i++)
                        {
                            k[i] = 0;
                            k1[i] = 0;
                            k2[i] = 0;
                            Vx[i] = 0;
                            Vy[i] = 0;
                        }
                    }
                    
                }


       if (Key_Play == 1)
       {
            //sledování myši chytání ptáků a tažení
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                for (int i = 0; i < bird_qantity; i++){ 
                    if ((mouseX > body[i].x)&&(mouseX < (body[i].x + body[i].w))&&(mouseY > body[i].y)&&(mouseY < (body[i].y + body[i].h))&&(mouseX < ((WINDOW_WIDTH / 2) - 200)))
                    {
                        body[i].selected = 1;
                    }
                }
            
            }else if (e.type == SDL_MOUSEBUTTONUP)
            {
                for (int i = 0; i < bird_qantity;i++) body[i].selected = false;
            }
            if (e.type == SDL_MOUSEMOTION)
            {
                for (int i = 0; i < bird_qantity;i++)
                {
                    if (body[i].selected)
                    {
                        body[i].x = e.motion.x - 50;
                        body[i].y = e.motion.y - 30;
                    }
                }
            }
        
            // Physics====================================
            for (int i = 0; i < body_qantity-1;i++)
            {
                // start speeed po vytazeni praku (начальная корость при натяжении рогатки)
                if( i < bird_qantity)
                {
                    Vx[i] = start_speed_X (body[i].x, body[i].y, body[i].h, body[i].w, slingRect.x, slingRect.y, body[i].selected, Vx[i]);
                    Vy[i] = start_speed_Y (body[i].x, body[i].y, body[i].h, body[i].w, slingRect.x, slingRect.y, body[i].selected, Vy[i]);
                }
                // move in Х
                
                k1[i]++;
                if (k1[i] == 1)
                {
                    X0[i] = body[i].x;
                    StartEventTimeMove[i] = CurrentFrameTime;
                }
                EventTimeMove[i] = (CurrentFrameTime - StartEventTimeMove[i]) / 100;
                body[i].x = X0[i] + Vx[i] * EventTimeMove[i] * 5;
                
                if(body[i].selected == true)
                {
                    StartEventTimeMove[i] = 0;
                    EventTimeMove[i] = 0;
                    k1[i] = 0;
                }

                if ((body[i].selected == false)&&((body[i].x >= WINDOW_WIDTH - body[i].w-10) || (body[i].x <= 0)))
                {
                    Vx[i] = 0;
                    X0[i] = body[i].x;
                    StartEventTimeMove[i] = CurrentFrameTime;
                }
                // friction (treni)
                if ((body[i].selected == false) && (collision(rigid_body[body_qantity - 1],rigid_body[i])))
                {
                    X0[i] = body[i].x;
                    StartEventTimeMove[i] = CurrentFrameTime;
                    if (Vx[i] > 0.01)
                    {
                        Vx[i] = Vx[i] - 0.01;
                        X0[i] = body[i].x;
                        StartEventTimeMove[i] = CurrentFrameTime;
                    }
                    else Vx[i] = 0;
                }

                collision_y[i] = false;
                // check all boidies for collision
                for (int j = 0; j < body_qantity-1;j++)
                {
                    if ((j != i)&&(body[i].selected == false)&&(body[j].selected == false))
                    {
                        // x collision
                        if ((collision(rigid_body[i], rigid_body[j]) == 1) 
                            &&(((rigid_body[i].x > rigid_body[j].x) && (Vx[i] < 0.0) && (Vx[j] > Vx[i]))
                                || ((rigid_body[i].x < rigid_body[j].x) && (Vx[i] > 0.0) && (Vx[j] < Vx[i]))
                                ))
                        {
                            Vx[i] = -(Vx[i] + Vx[j]) / 2;
                            Vx[j] = -Vx[i];
                            
                            X0[j] = body[j].x;
                            StartEventTimeMove[j] = CurrentFrameTime;
                            X0[i] = body[i].x;
                            StartEventTimeMove[i] = CurrentFrameTime;

                        }
                        else 
                        // y collision
                        if ((collision(rigid_body[i], rigid_body[j]) == 1)
                            &&(rigid_body[i].y+G * EventTimeFall[i] * EventTimeFall[i] * 0.5
                                // check if on the next time step the body will be lower than the one below
                                > rigid_body[j].y- rigid_body[i].h/2- rigid_body[j].h/2)&&
                            // check if the body i above body j
                            (rigid_body[i].y < rigid_body[j].y))
                        {
                            Vy[i] = 0.0;
                            Y0[i] = body[i].y;
                            StartEventTimeFall[i] = CurrentFrameTime;
                            collision_y[i] = true;

                        }
                        
                    }
                }
                //victory condition
                for (int k = 0; k < bird_qantity; k++)
                {
                    if (collision(rigid_body[k], rigid_body[3]) == 1)
                    {
                        Key_Play = 0;
                        Key_Menu = 0;
                        Win = 1;
                    }
                }

            
                // move in Y
                if ((body[i].selected == false) && (collision(rigid_body[body_qantity - 1],rigid_body[i]) == 0)&&(collision_y[i] ==false))
                {
                    k[i]++;
                    if (k[i] == 1)
                    {
                        Y0[i] = body[i].y;
                        StartEventTimeFall[i] = CurrentFrameTime;
                    }
                    EventTimeFall[i] = (CurrentFrameTime - StartEventTimeFall[i])/100;
                    body[i].y = Y0[i] + Vy[i] * EventTimeFall[i] + G * EventTimeFall[i] * EventTimeFall[i] * 0.5;
                }
                if(body[i].selected == true)
                {
                    StartEventTimeFall[i] = 0;
                    EventTimeFall[i] = 0;
                    k[i] = 0;
                }
                if ((body[i].selected == false)&&((collision(rigid_body[body_qantity - 1],rigid_body[i]) == 1) || (body[i].x >= WINDOW_WIDTH - body[i].w-10) || (body[i].x <= 0)))
                {
                    StartEventTimeFall[i] = 0;
                    EventTimeFall[i] = 0;
                    k[i] = 0;
                    Vy[i] = 0;

                } 
            
            }
        } 

        //==============================================
        //render all
        SDL_RenderClear(renderer);
        //draw menu buttons 
        if ((Key_Play == 0)&&(Key_Levels == 0)&&(Key_Menu == 1)&&(Win == 0))
        {
            SDL_RenderCopy(renderer, background_texture1, NULL, NULL); // draw background
            for (int i = 0; i < buttonMenu_qantity; i++)
            {
                if (Key_change[i] == 1)
                {
                    SDL_SetRenderDrawColor(renderer,  255, 223, 0, 255);
                    button.y = button_y[i];
                    button.x = button_x[i]; 
                    button.h = button_height;
                    button.w = button_width;
                    
                    SDL_RenderFillRect(renderer, &button);
                }
                else SDL_SetRenderDrawColor(renderer,  255, 255, 255, 255);
            }
            
            SDL_RenderCopy(renderer, text_texture1,  NULL, &TextButton1Rect);

            SDL_RenderCopy(renderer, text_texture2,  NULL, &TextButton2Rect);

            SDL_RenderCopy(renderer, text_texture3,  NULL, &TextButton3Rect);

            
        }

        //draw swith level buttons
        if ((Key_Play == 0)&&(Key_Levels == 1))
        {
            SDL_RenderCopy(renderer, background_texture1, NULL, NULL); // draw background
            if (Key_change[3] == 1)
            {
                SDL_SetRenderDrawColor(renderer,  255, 223, 0, 255);
                button.y = button_y[3];
                button.x = button_x[3]; 
                button.h = button_height;
                button.w = button_width;
                
                SDL_RenderFillRect(renderer, &button);
            }
            SDL_RenderCopy(renderer, text_texture4,  NULL, &TextButtonExitToMenuRect);


            for (int i = 0; i < buttonLevels_qantity; i++)
            {
                    ButtonLevelsOpenRect.x = button_level_x;
                    ButtonLevelsOpenRect.y = button_level_y; 
                    ButtonLevelsOpenRect.h = button_level_height;
                    ButtonLevelsOpenRect.w = button_level_width;

                    ButtonLevelsCloseRect.x = button_level_x;
                    ButtonLevelsCloseRect.y = button_level_y; 
                    ButtonLevelsCloseRect.h = button_level_height + 7;
                    ButtonLevelsCloseRect.w = button_level_width;

                    SDL_RenderCopy(renderer, ButtonLevelsOpen_txtr,  NULL, &ButtonLevelsOpenRect);
            }
        }
        //draw win menu
        if ((Win == 1)&&(Key_Play == 0))
        { 
            SDL_RenderCopy(renderer, background_texture1, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,  0, 0, 0, 0);
                        rect.h = WINDOW_HEIGHT;
                        rect.w = 400;
                        rect.x = (WINDOW_WIDTH / 2) - (rect.w / 2);
                        rect.y = 0;
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderCopy(renderer, text_texture5, NULL, &TextYouWinRect);
            SDL_RenderCopy(renderer, Button_Next_txtr,  NULL, &Button_NextRect);
            SDL_RenderCopy(renderer, Button_Levels_txtr,  NULL, &Button_LevelsRect);
            SDL_RenderCopy(renderer, Button_Retry_txtr,  NULL, &Button_RetryRect);
        }
        
        
        
//draw level
        if (Key_Play == 1)
        {
            SDL_RenderCopy(renderer, background_texture, NULL, NULL); // draw background
            SDL_RenderCopy(renderer, sling1_txtr, NULL, &slingRect); // draw sling 1

            //render gumicky 1
            for (int j = 0; j < bird_qantity;j++)
            {
                if ((sqrt(pow(body[j].x - slingX1 + 50, 2) + pow(body[j].y - slingRect.y, 2)) <= 150))
                {   
                    double l;
                    SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x30, 0xFF);

                    if(((slingX1 - body[j].x) > 0) && (body[j].selected == true)) l = 1;
                    else if (((slingX1 - body[j].x) < 0) && (body[j].selected == true)) l = 0;
                    
                    if ((l == 1) && (body[j].x < slingX1))
                    {
                        for (int b = 0; b < sling_thickness; b++) 
                        SDL_RenderDrawLine(renderer, body[j].x + 5, body[j].y + bird1Rect.h / 2 + b, slingX1, slingY1 + b);
                    }
                    else if ((l == 0) && (body[j].x > slingX1)) 
                        for (int b = 0; b < sling_thickness; b++) 
                        SDL_RenderDrawLine(renderer, body[j].x + bird1Rect.w + 5, body[j].y + bird1Rect.h / 2 + b, slingX1, slingY1 + b);
                    
                    
                    pointX[j] = body[j].x+30;
                    pointY[j] = body[j].y+30;
                    float i = 0;
                    while((i < 10) && (body[j].selected == 1))
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderFillRect(renderer, &rect);
                        rect.h = 10;
                        rect.w = 10;
                        rect.x = pointX[j]+Vx[j] * i*5;
                        rect.y = pointY[j]+Vy[j] * i + G * i * i * 0.5;
                        i = i + 0.5;
                    }
                }
            }
        
            // render birds
            SDL_RenderCopy(renderer, bird1_txtr, NULL, &bird1Rect); // draw bird 1
            SDL_RenderCopy(renderer, bird2_txtr, NULL, &bird2Rect); // draw bird 2
            SDL_RenderCopy(renderer, bird3_txtr, NULL, &bird3Rect); // draw bird 3
            SDL_RenderCopy(renderer, pig_txtr, NULL, &pigRect); // draw pig

            //render  2
            for (int j = 0; j < bird_qantity;j++)
            {
                if ((sqrt(pow(body[j].x - slingX1 + 50, 2) + pow(body[j].y - slingRect.y, 2)) <= 150))
                {
                    double l;
                    SDL_SetRenderDrawColor(renderer, 0x80, 0x40, 0x30, 0xFF);
                    if(((slingX2 - body[j].x) > 0) && (body[j].selected == true)) l = 1;
                    else if (((slingX2 - body[j].x) < 0) && (body[j].selected == true)) l = 0;
                    
                    if ((l == 1) && (body[j].x < slingX2))
                    {
                        for (int b = 0; b < sling_thickness; b++) SDL_RenderDrawLine(renderer, body[j].x + 5, body[j].y + bird1Rect.h / 2 + b, slingX2, slingY2 + b);
                    }
                    else if ((l == 0) && (body[j].x > slingX2)) for (int b = 0; b < sling_thickness; b++) SDL_RenderDrawLine(renderer, body[j].x + bird1Rect.w + 5, body[j].y + bird1Rect.h / 2 + b, slingX2, slingY2 + b);
                }

            }
            SDL_RenderCopyEx(renderer, board1_txtr, NULL, &boardRect1, body[4].alpha, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, board2_txtr, NULL, &boardRect2, body[5].alpha, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, board3_txtr, NULL, &boardRect3, body[6].alpha, NULL, SDL_FLIP_NONE);
            SDL_RenderCopy(renderer, sling2_txtr, NULL, &sling2Rect); // draw sling
        }

        // show renderer
        SDL_RenderPresent(renderer);
     
    }
    closeGame();

    free(body);
    free(rigid_body);
    free(k);
    free(k1);
    free(StartEventTimeFall);
    free(EventTimeFall);
    free(StartEventTimeMove);
    free(EventTimeMove);
    free(Vx);
    free(Vy);
    free(Y0);
    free(X0);
    free(pointX);
    free(pointY);
    free(button_x);
    free(button_y);
    free(Key_change);

    SDL_DestroyTexture(text_texture1);
    SDL_DestroyTexture(text_texture2);
    SDL_DestroyTexture(text_texture3);
    SDL_DestroyTexture(text_texture4);

    SDL_DestroyTexture(bird1_txtr);
    SDL_DestroyTexture(bird2_txtr);
    SDL_DestroyTexture(bird3_txtr);
    SDL_DestroyTexture(sling1_txtr);
    SDL_DestroyTexture(sling2_txtr);
    SDL_DestroyTexture(pig_txtr);
    SDL_DestroyTexture(board1_txtr);
    SDL_DestroyTexture(board2_txtr);

    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(background_texture1);

    SDL_DestroyTexture(ButtonLevelsOpen_txtr); 
    SDL_DestroyTexture(ButtonLevelsClose_txtr);
    SDL_DestroyTexture(Button_Next_txtr);
    SDL_DestroyTexture(Button_Levels_txtr);
    SDL_DestroyTexture(Button_Retry_txtr);

    return 0;

}
