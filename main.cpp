#include <iostream>
#include <iostream>
#include<fstream>
#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include<cmath>
using namespace std;
int score;
int chekpresent[1000]={0};
string to_string(long long int n){
    string ans="";
    while(n){
        ans+=n%10+'0';
        n/=10;
    }
    for(int i=0;i<ans.size();i++){
        swap(ans[i],ans[ans.size()-1-i]);
    }
    return ans;
}
TTF_Font* font;
SDL_Texture *texture, *text;
int img3_w, img3_h;
SDL_Rect img3_rect;
SDL_Window * m_window;
SDL_Renderer * m_renderer;
SDL_Texture* m_img2 = NULL;
SDL_Texture* m_enter1 = NULL;
int img2_w, img2_h;
SDL_Rect img2_rect;
SDL_Rect start_rect;
string TextBox(SDL_Renderer *Renderer, int x_position, int y_position, int R, int G, int B)
{
    bool caps_lock = false;
    int A=0.5;
    int W = 1280;
    int H = 800;
    bool quit = false ;
    char ch=0;
    SDL_Event *event = new SDL_Event();
    string name = "";
    char lastkey;
    name = name.substr(0, name.length()-1);
    while (!quit)
    {
        ch = 0;
        //SDL_RenderClear(Renderer);
        SDL_RenderPresent(Renderer);
        if(SDL_PollEvent(event))
        {
            if(event -> type == SDL_KEYUP)
            {
                switch(event->key.keysym.sym)
                {
                    case SDLK_SPACE:
                    //quit = true;
                    ch = ' ';
                    break;
                    case SDLK_RETURN:
                    quit = true;
                    break;
                    case SDLK_KP_ENTER:
                    quit = true;
                    break;
                    case SDLK_CAPSLOCK:
                    ch=0;
                    caps_lock = !caps_lock;
                    break;
                    case SDLK_BACKSPACE:
                    ch = 0;
                    if(name.length()!=0)
                    {
                    name.pop_back();


                   textRGBA(Renderer,x_position,y_position,name.c_str(),2,40,R,G,B,255);

                   SDL_RenderCopy(m_renderer, m_enter1, NULL, &img2_rect);
                    }
                    break;
                    default :
                    if(event->key.keysym.sym != SDLK_UP && event->key.keysym.sym != SDLK_DOWN && event->key.keysym.sym != SDLK_LEFT && event->key.keysym.sym != SDLK_RIGHT)
                    ch = event->key.keysym.sym;
                    break;
                }
                if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' ') || (ch >= '0' && ch <= '9') && name.length()<25 && !quit && ch != 0)
                {
                    if(caps_lock == 1 && ch != ' ' && (ch < '0' || ch > '9'))
                    name+=ch + 'A' - 'a';
                    else
                    name+=ch ;
                }
                if(name != "" && !quit)
                textRGBA(Renderer,x_position,y_position,name.c_str(),2,40,R,G,B,255);

            }
        }
        SDL_RenderPresent(Renderer);
        lastkey = event->key.keysym.sym;
    }
    string output;
    if (lastkey == name[name.length()-1])
        output = name.substr(0, name.length()-1);
    else
        output = name;
    return output;
}
int main( int argc, char * argv[] )
{

     if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load the audio file into memory
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    if (SDL_LoadWAV("aaa.wav", &wavSpec, &wavBuffer, &wavLength) == NULL)
    {
        printf("SDL_LoadWAV failed: %s\n", SDL_GetError());
        return 1;
    }

    // Open the audio device
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0)
    {
        printf("SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        return 1;
    }

    // Start playing the audio
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    if (success != 0)
    {
        printf("SDL_QueueAudio failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_PauseAudioDevice(deviceId, 0);
    srand(time(NULL));
    string input;
    bool startgame=false;
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN ;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;

    int img_w, img_h;
    SDL_Rect img_rect;
    int bf_w, bf_h;
    SDL_Rect bf_rect;
    int bbbf_w, bbbf_h;
    SDL_Rect bbbf_rect;
    int lb_w, lb_h;
    SDL_Rect lb_rect;

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1280, 800, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    SDL_RenderPresent( m_renderer );

      SDL_Texture* m_help= NULL;
    m_help =IMG_LoadTexture(m_renderer, "help.JPG");
    SDL_QueryTexture(m_help, NULL, NULL, &img_w, &img_h);
    start_rect.x = 0;
    start_rect.y = 0;
    start_rect.w = img_w * 1.08;
    start_rect.h = img_h * 1.2;
 // SDL_RenderCopy(m_renderer, m_help, NULL, &start_rect);

      SDL_Texture* m_help2= NULL;
    m_help2 =IMG_LoadTexture(m_renderer, "help2.PNG");
    SDL_QueryTexture(m_help2, NULL, NULL, &img_w, &img_h);
    start_rect.x = 0;
    start_rect.y = 0;
    start_rect.w = img_w * 1.08;
    start_rect.h = img_h * 1.2;

      SDL_Texture* m_start= NULL;
    m_start =IMG_LoadTexture(m_renderer, "start.JPG");
    SDL_QueryTexture(m_start, NULL, NULL, &img_w, &img_h);
    start_rect.x = 0;
    start_rect.y = 0;
    start_rect.w = img_w * 1.08;
    start_rect.h = img_h * 1.2;
//  SDL_RenderCopy(m_renderer, m_start, NULL, &start_rect);
    // Render a new color bar every 0.5 seconds
      SDL_Texture* m_menu = NULL;
    m_menu=IMG_LoadTexture(m_renderer, "menu.JPG");
    SDL_QueryTexture(m_menu, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 0.666;
    img_rect.h = img_h * 0.74;
 // SDL_RenderCopy(m_renderer, m_menu, NULL, &img_rect);
 //SDL_RenderPresent( m_renderer );
 //SDL_Delay(5000);
SDL_Texture* m_img3 = NULL;
    m_img3 = IMG_LoadTexture(m_renderer, "map.PNG");
    SDL_QueryTexture(m_img3, NULL, NULL, &img3_w, &img3_h);
    img3_rect.x = -150;
    img3_rect.y = 10;
    img3_rect.w = img3_w * 1.3;
    img3_rect.h = img3_h * 1.4;
    // copy the texture to the rendering context
   // SDL_RenderCopy(m_renderer, m_img3, NULL, &img3_rect);
    SDL_Texture* m_img4 = NULL;
    m_img4 = IMG_LoadTexture(m_renderer, "mapp.JPG");
    SDL_QueryTexture(m_img4, NULL, NULL, &img3_w, &img3_h);
    img3_rect.x = -150;
    img3_rect.y = 10;
    img3_rect.w = img3_w * 1.3;
    img3_rect.h = img3_h * 1.4;
    // copy the texture to the rendering context
    //SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);

    SDL_Texture* m_enter2 = NULL;
    m_enter2=IMG_LoadTexture(m_renderer, "enter2.JPG");
    SDL_QueryTexture(m_enter2, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 0.666;
    img_rect.h = img_h * 0.74;
 //  SDL_RenderCopy(m_renderer, m_enter2, NULL, &img_rect);

      //SDL_Texture* m_enter1 = NULL;
    m_enter1=IMG_LoadTexture(m_renderer, "enter1.JPG");
     SDL_QueryTexture(m_enter1, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 0.666;
    img_rect.h = img_h * 0.74;
 //  SDL_RenderCopy(m_renderer, m_enter1, NULL, &img_rect);


      SDL_Texture* m_register = NULL;
    m_register=IMG_LoadTexture(m_renderer, "register.PNG");
     SDL_QueryTexture(m_register, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 0.666;
    img_rect.h = img_h * 0.74;
 //   SDL_RenderCopy(m_renderer, m_register, NULL, &img_rect);

    SDL_Texture* m_login = NULL;
    m_login=IMG_LoadTexture(m_renderer, "login.PNG");
     SDL_QueryTexture(m_login, NULL, NULL, &img_w, &img_h);
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = img_w * 0.666;
    img_rect.h = img_h * 0.74;
 //   SDL_RenderCopy(m_renderer, m_login, NULL, &img_rect);

    //SDL_Texture* m_img2 = NULL;
    m_img2 = IMG_LoadTexture(m_renderer,"first.PNG");
    SDL_QueryTexture(m_img2, NULL, NULL, &img2_w, &img2_h);
    img2_rect.x = 0;
    img2_rect.y = 0;
    img2_rect.w = img2_w * 0.666;
    img2_rect.h = img2_h *0.74;
    // copy the texture to the rendering context
    //SDL_RenderCopy(m_renderer, m_img2, NULL, &img_rect);

    SDL_Texture* m_img = NULL;
    m_img = IMG_LoadTexture(m_renderer,"jun.JPG");
        SDL_QueryTexture(m_img, NULL, NULL, &img_w, &img_h);
        img_rect.x =500;
        img_rect.y = 300;
        img_rect.w = img_w *1;
        img_rect.h = img_h *1 ;


      SDL_Texture* m_lb1 = NULL;
    m_lb1 = IMG_LoadTexture(m_renderer, "lb1.JPG");
    SDL_QueryTexture(m_lb1, NULL, NULL, &lb_w, &lb_h);
    lb_rect.x = -170;
    lb_rect.y = 0;
    lb_rect.w = lb_w * 0.6;
    lb_rect.h = lb_h * 0.65;
    // copy the texture to the rendering context
   // SDL_RenderCopy(m_renderer, m_lb1, NULL, &lb_rect);

SDL_Texture* m_back = NULL;
    m_back = IMG_LoadTexture(m_renderer, "bf.JPG");
    SDL_QueryTexture(m_back, NULL, NULL, &bf_w, &bf_h);
    bf_rect.x = -170;
    bf_rect.y = 0;
    bf_rect.w = bf_w * 0.6;
    bf_rect.h = bf_h * 0.65;
    // copy the texture to the rendering context
  //  SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);

    SDL_Texture* m_back2 = NULL;
    m_back2 = IMG_LoadTexture(m_renderer, "bbbf.JPG");
    SDL_QueryTexture(m_back2, NULL, NULL, &bbbf_w, &bbbf_h);
    bbbf_rect.x = -170;
    bbbf_rect.y = 0;
    bbbf_rect.w = bbbf_w * 0.6;
    bbbf_rect.h = bbbf_h * 0.65;
    // copy the texture to the rendering context
    // SDL_RenderCopy(m_renderer, m_back, NULL, &bbbf_rect);

    SDL_RenderPresent( m_renderer );

int chekpresent_color[1000]={0};
int color_ball[2]={0};
//int color_plus=0;
int change_ball=1;
int color[1000];
    int flag=0;
    int flag3=0;
    SDL_Event *e = new SDL_Event();
while(!startgame){
        if(flag==0){
        e->type = 0;
        SDL_PollEvent(e);
        if(e->type==SDL_MOUSEMOTION){
            double x=e->motion.x;
            double y=e->motion.y;

        if(x>=495&&x<=785 && y>=340&&y<=460){
             SDL_RenderCopy(m_renderer, m_login, NULL, &img2_rect);
             SDL_RenderPresent( m_renderer );
        }else if(x>=415&&x<=865 && y<=620&&y>=490){
            SDL_RenderCopy(m_renderer, m_register, NULL, &img2_rect);
            SDL_RenderPresent( m_renderer );
       }else{
             SDL_RenderCopy(m_renderer, m_img2, NULL, &img2_rect);
            // rectangleRGBA(m_renderer,410,490,870,630,255,255,25,255);
             SDL_RenderPresent( m_renderer );
       }

       }

       // e->type = 0;
        SDL_PollEvent(e);

       if(e->type==SDL_MOUSEBUTTONDOWN){

            double x2=e->motion.x;
            double y2=e->motion.y;

            if(x2>=495&&x2<=785 && y2>=340&&y2<=460){
                flag=1;
            while(flag==1){
                SDL_RenderCopy(m_renderer, m_enter1, NULL, &img2_rect);
                SDL_RenderPresent( m_renderer );

                 e->type = 0;
                SDL_PollEvent(e);

                if(e->type==SDL_MOUSEBUTTONDOWN){
                        double x3=e->button.x;
                        double y3=e->button.y;
                        string pass,pass2;
                        string username,user2;
                        int userr=0;
                        int passs=0;
                        if(x3>=595&&x3<=1085 && y3>=340&&y3<=460){
                            bool user=true;
                            while(user){
                                ofstream userfile("username.text",ios::app);
                                username = TextBox(m_renderer, 635, 370, 200, 100, 255);
                                user2=username;
                                userfile<<username<<endl;
                                userfile.close();
                               //  textRGBA(m_renderer,635 ,370 ,username.c_str(),2,40,200,100,255,255);
                                while(flag3==0){
                                     e->type = 0;
                                    SDL_PollEvent(e);

                                    if(e->type==SDL_MOUSEBUTTONDOWN){
                                            double x3=e->button.x;
                                            double y3=e->button.y;
                                            if(x3>=595&&x3<=1085 && y3>=480&&y3<=580){

                                                    bool passc=true;

                                                    while(passc){
                                                        ofstream passfile("password.text",ios::app);
                                                        pass = TextBox(m_renderer, 660, 500, 100, 100, 255);
                                                        passfile<<pass<<endl;
                                                        passfile.close();

                                                        flag3=1;

                                                        passc=false;
                                                    }

                                            }

                                    }

                                }
                                user=false;
                            }

                         }
                         //  rectangleRGBA(m_renderer,400,600,885,710,255,255,25,255);

                        else if(x3>=400&&x3<=885 && y3>=600&&y3<=710){

                                 flag=false;
                                startgame=true;


                        }


                }

            }
// rectangleRGBA(m_renderer,410,490,870,630,255,255,25,255);
        }else if(x2>=410&&x2<=870 && y2>=490&&y2<=630){
            int flag2=1;
            flag=1;
            while(flag==1){
                SDL_RenderCopy(m_renderer, m_enter2, NULL, &img2_rect);
                SDL_RenderPresent( m_renderer );

                e->type = 0;
                SDL_PollEvent(e);

                if(e->type==SDL_MOUSEBUTTONDOWN){
                        double x3=e->button.x;
                        double y3=e->button.y;
                        string pass,pass2;
                        string username,user2;

                        if(x3>=595&&x3<=1085 && y3>=340&&y3<=460){
                            bool user=true;
                            while(user){

                                username = TextBox(m_renderer, 635, 370, 200, 100, 255);
                               //textRGBA(m_renderer,635 ,370 ,username.c_str(),2,40,200,100,255,255);
                               while(flag2==1){

                               e->type = 0;
                                SDL_PollEvent(e);

                                if(e->type==SDL_MOUSEBUTTONDOWN){
                                double x4=e->button.x;
                                double y4=e->button.y;

                                if(x4>=595&&x4<=1085 && y4>=480&&y4<=580){
                                      bool passc=true;

                                        while(passc){

                                            string mytext,mytext2;
                                            pass = TextBox(m_renderer, 660, 500, 100, 100, 255);
                                            ifstream read("username.text");
                                            ifstream read2("password.text");
                                            while(true){
                                                getline(read,mytext);
                                                 getline(read2,mytext2);
                                                if(mytext==username){

                                                    if(mytext2==pass){
                                                        flag=false;
                                                        flag2=false;
                                                        startgame=true;
                                                        break;

                                                    }
                                                }

                                            }


                                           ofstream userfile("username.text",ios::app);
                                           userfile<<username<<endl;
                                           userfile.close();
                                           ofstream passfile("password.text",ios::app);
                                           passfile<<pass<<endl;
                                           passfile.close();







                                            passc=false;
                                        }





                                }
                                }


                            }
                            user=false;
                            }

                         }




                        }

                    }

                }
            }
        }
    }
    int start_mode = 0;
    while(start_mode==0){
        SDL_RenderCopy(m_renderer, m_menu, NULL, &img2_rect);
            e->type = 0;
            SDL_PollEvent(e);
            if(e->type==SDL_MOUSEBUTTONDOWN){
                    double x=e->button.x;
                    double y=e->button.y;
                    if(x>500&&x<730&&y>330&&y<410){
                            while(start_mode==0){
                                SDL_RenderCopy(m_renderer, m_start, NULL, &start_rect);
                              //  rectangleRGBA(m_renderer,485,300,780,400,255,255,255,255);
                              //  rectangleRGBA(m_renderer,485,445,780,545,255,255,255,255);
                              //  rectangleRGBA(m_renderer,485,590,780,690,255,255,255,255);
                               e->type = 0;
                               SDL_PollEvent(e);
                                if(e->type==SDL_MOUSEBUTTONDOWN){
                                        double x=e->button.x;
                                        double y=e->button.y;
                                        if(x>485&&x<780&&y>300&&y<400){
                                            start_mode=1;
                                        }else if(x>485&&x<780&&y>445&&y<545){
                                            start_mode=2;
                                        }else if(x>485&&x<780&&y>590&&y<690){
                                            start_mode=3;
                                        }
                                }

                                SDL_RenderPresent(m_renderer);
                            }

                    }else if(x>500&&x<730&&y>450&&y<530){
                        bool bord=true;
                        SDL_RenderCopy(m_renderer, m_help2, NULL, &start_rect);
                                SDL_RenderPresent(m_renderer);
                                  ifstream read("score.text");
                                ifstream read2("username.text");
                                int a,b,c,i=0;
                                int a2,b2,c2;
                                string n1,n2,n3,n4;
                                int scoree[100];
                                int scorer[100];
                                while(bord){
                                    if(read.good()){
                                        read>>scoree[i];

                                        i++;
                                    }else{bord=false;}
                                }
                                for(int j=0;j<i;j++){
                                    scorer[j]=scoree[j];
                                }
                                sort(scorer,scorer+i);
                                a=scorer[i-1];
                                b=scorer[i-2];
                                c=scorer[i-3];

                                for(int j=0;j<i;j++){
                                    if(scoree[j]==a){
                                        a2=j;
                                    }else if(scoree[j]==b){
                                        b2=j;
                                    }else if(scoree[j]==c){
                                        c2=j;
                                    }
                                }
                                for(int j=0;j<i;j++){

                                    if(j==a2){
                                        read2>>n1;
                                    }else if(j==b2){
                                        read2>>n2;
                                    }else if(j==c2){
                                        read2>>n3;
                                    }else{read2>>n4;}

                                }

                                read.close();
                                read2.close();

                                textRGBA(m_renderer,480,350,n1.c_str(),2,50,0,0,0,255);
                                textRGBA(m_renderer,480,450,n2.c_str(),2,50,0,0,0,255);
                                textRGBA(m_renderer,480,530,n3.c_str(),2,50,0,0,0,255);
                                  textRGBA(m_renderer,880,350,to_string(a).c_str(),2,50,0,0,0,255);
                                textRGBA(m_renderer,880,450,to_string(b).c_str(),2,50,0,0,0,255);
                                textRGBA(m_renderer,880,530,to_string(c).c_str(),2,50,0,0,0,255);

                         int chek_help=0;

                        while(chek_help==0){

                                //SDL_RenderCopy(m_renderer, m_help2, NULL, &start_rect);
                               //SDL_RenderPresent(m_renderer);
                                e->type = 0;
                                SDL_PollEvent(e);
                                if(e->type==SDL_MOUSEBUTTONDOWN){
                                        double x=e->button.x;
                                        double y=e->button.y;
                                        if(x>530&&x<740&&y>590&&y<710){
                                            chek_help=1;
                                        }

                                }

                        }



                    }else if(x>500&&x<730&&y>570&&y<650){
                        int chek_help=0;
                        while(chek_help==0){
                                SDL_RenderCopy(m_renderer, m_help, NULL, &start_rect);
                             //   rectangleRGBA(m_renderer,530,590,740,710,255,255,255,255);
                                SDL_RenderPresent(m_renderer);
                                e->type = 0;
                                SDL_PollEvent(e);

                                if(e->type==SDL_MOUSEBUTTONDOWN){
                                        double x=e->button.x;
                                        double y=e->button.y;
                                        if(x>530&&x<740&&y>590&&y<710){
                                            chek_help=1;
                                        }

                                }

                        }
                    }
            }

        SDL_RenderPresent( m_renderer );
    }
int t=0;
bool finalball=true;
while(start_mode==1&&t<=4000 && finalball){
int arr[62]={1047,1023,989,939,884,826,765,702,641,580,519,458,396,339,283,238,205,211,261,319,362,413,469,530,589,653,714,772,828,867,888,892,868,824,769,708,649,585,521,464,407,360,319,258,212,213,241,285,341,400,461,523,584,642,705,768,828,887,941,986,1023,1049};
int ar[62]={297,237,187,144,116,100,91,86,86,85,90,95,112,133,167,210,266,331,363,346,296,258,233,214,203,202,208,230,264,312,371,440,502,544,571,588,594,594,588,574,552,512,461,451,493,560,617,660,686,703,711,719,721,721,719,709,697,678,653,605,552,491};



for(int i=0;i<80;i++){
    color[i]=rand()%4;
}

int start=0;
int chek_ch=0;
double teta=0;
double b=500 + img_w /2 , z=300+ img_h/2;
while(t<=4000 && finalball){
        e->type = 0;
          SDL_PollEvent(e);
            bool pause=true;
          if(e->type==SDL_KEYDOWN){
            switch(e->key.keysym.sym){
            case SDLK_SPACE:
                swap(color_ball[0],color_ball[1]);
                break;
            case SDLK_p:
                while(pause){
                        SDL_RenderCopy(m_renderer, m_help, NULL, &start_rect);
                        //   rectangleRGBA(m_renderer,530,590,740,710,255,255,255,255);
                        SDL_RenderPresent(m_renderer);
                        e->type = 0;
                        SDL_PollEvent(e);

                        if(e->type==SDL_MOUSEBUTTONDOWN){
                                double x=e->button.x;
                                double y=e->button.y;
                                if(x>530&&x<740&&y>590&&y<710){
                                        pause=false;
                                        t=8000;
                                        e->type = 0;
                                }else{pause=false;
                                      e->type = 0;
                                }

                        }
                }
                break;
            }
          }

        //  e->type = 0;
        if(e->type==SDL_MOUSEMOTION){

            double x=e->motion.x;
            double y=e->motion.y;
            double rot;
            if(x<=b && y<=z){
                 rot=(z-y)/(b-x);
                 teta=180*atan(rot)/3.1415;

            }
            else if(x>=b && y<=z){
                rot=(z-y)/(x-b);
                teta=180-(180*atan(rot)/3.1415);

            }
            else if(x>=b && y>=z){
                rot=(y-z)/(x-b);
                teta=180+(180*atan(rot)/3.1415);
            }
            else if(x<=b && y>=z){
                rot=(y-z)/(b-x);
                teta=360-(180*atan(rot)/3.1415);
            }


        }

            SDL_RenderPresent( m_renderer );
            SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
            SDL_RenderClear( m_renderer );
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);



            if(change_ball==1){
                    color_ball[0]=color_ball[1];
               for(int i=0;i<80;i++){

                if(chekpresent[i]==1){
                    color_ball[1]=color[i];
                    break;

                }
               }
               change_ball=0;
           }

            int r=img_w /2 -76;

            int r2=img_w /2 -130;
            double ball = 3.1415*teta /180;
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);





          if(color_ball[0]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
          }else if(color_ball[0]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[0]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );


          if(color_ball[1]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }




       double x2,y2,shib;
       double b2=500+img_w /2 - r*cos(ball), z2= 300+ img_h / 2 - r*sin(ball);
        //e->type = 0;
       SDL_PollEvent(e);

       if(e->type==SDL_MOUSEBUTTONDOWN){


            change_ball=1;


            double x_markaz;
            double y_markaz;
            double tt=5,mm=1;
            x2=e->button.x;
            y2=e->button.y;
            //int malom_i=chek_fasele(500 + img_w /2, 300+ img_h / 2 ,x2,y2,2,arr,ar,chekpresent);




    /////////////////////////////////////////11111111/////////////////////////////////////////



            if(x2<=b2 && y2<=z2){
                shib=(z2-y2)/(b2-x2);
                int chek_ellip=0;
                int i_newball;
                while(b2- mm*tt>0&& z2-mm*tt*shib>0 && chek_ellip ==0){
                         //////////////////////////


          if(color_ball[1]==0){

                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
          }

                    if(chek_ellip==0){

                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                        }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                        }
                        x_markaz=b2-mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm+=1;
                    }
               for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }

                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){

                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
                 textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
                //SDL_RenderClear( m_renderer );
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
          }

            }




            /////////////////////2222222222222222////////////////////////






            else if(x2>=b2 && y2<=z2){
                shib=(z2-y2)/(x2-b2);
                int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 - mm*tt*shib > 0 && chek_ellip ==0){

                        if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                    // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                    if(chek_ellip==0){
                            if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                            }
                      // filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm++;
                    }
                for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                        start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }
                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
               // SDL_RenderClear( m_renderer );
                textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }



            //////////////////3333333333333333333333333//////////////






            else if(x2>=b2 && y2>=z2){
                shib=(y2-z2)/(x2-b2);
              //  tt=tt/shib;
                //while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800){
               // filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
               // mm++;


                  int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800 && chek_ellip ==0){
                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                   // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
                    if(chek_ellip==0){
                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                      //  filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
               for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
              //  SDL_RenderClear( m_renderer );
               textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }

            //////////44444444444444444444444444///////////////////




            else if(x2<=b2 && y2>=z2){
                shib=(y2-z2)/(b2-x2);
                tt=tt/shib;
                //  while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800){
              //  filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);


                int chek_ellip=0;
                int i_newball;
                while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800&& chek_ellip==0){

                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }



                    if(chek_ellip==0){
                         if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                       // filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2-mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
              for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }

                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }

            SDL_RenderPresent( m_renderer );
         //   SDL_RenderClear( m_renderer );
             textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                SDL_Delay(15);
                }

            }

      }


if(t<=4000){
    if(t%100==0){
        int chek_per;
        for(int i=start+1;i>=0;i--){
            if(chekpresent_color[i]==0){
                chek_per=i;
            }
        }
        for(int i=chek_per-1;i>=0;i--){
            color[i+1]=color[i];
            chekpresent_color[i+1]=chekpresent_color[i];
        }
        color[0]=rand()%4;

        start++;
     //   for(int i=0;i<start;i++){
     //       cout<<chekpresent_color[i]<<" ";
      //  }
      //  cout<<endl;

    }


}

 for(int i=0;i<=start+1;i++){
         chekpresent[start]=1;
         chekpresent_color[0]=1;
        if(chekpresent_color[i]==1){
          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
        }
 }


t++;


    if(chekpresent_color[61]==1){
        finalball=false;
    }

    textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);



            SDL_RenderPresent( m_renderer );

           // SDL_Delay();

    }



}
while(start_mode==2){
int arr[62]={1047,1023,989,939,884,826,765,702,641,580,519,458,396,339,283,238,205,211,261,319,362,413,469,530,589,653,714,772,828,867,888,892,868,824,769,708,649,585,521,464,407,360,319,258,212,213,241,285,341,400,461,523,584,642,705,768,828,887,941,986,1023,1049};
int ar[62]={297,237,187,144,116,100,91,86,86,85,90,95,112,133,167,210,266,331,363,346,296,258,233,214,203,202,208,230,264,312,371,440,502,544,571,588,594,594,588,574,552,512,461,451,493,560,617,660,686,703,711,719,721,721,719,709,697,678,653,605,552,491};



for(int i=0;i<100;i++){
    color[i]=rand()%4;
}

int start=0;
int chek_ch=0;
double teta=0;
double b=500 + img_w /2 , z=300+ img_h/2;
while(finalball){

m_back = IMG_LoadTexture(m_renderer,"bf.JPG");
m_img = IMG_LoadTexture(m_renderer,"jun.JPG");
          e->type = 0;
          SDL_PollEvent(e);
          bool pause=true;
          if(e->type==SDL_KEYDOWN){
            switch(e->key.keysym.sym){
            case SDLK_SPACE:
                swap(color_ball[0],color_ball[1]);
                break;
            case SDLK_p:
                while(pause){
                        SDL_RenderCopy(m_renderer, m_help, NULL, &start_rect);
                        //   rectangleRGBA(m_renderer,530,590,740,710,255,255,255,255);
                        SDL_RenderPresent(m_renderer);
                        e->type = 0;
                        SDL_PollEvent(e);

                        if(e->type==SDL_MOUSEBUTTONDOWN){
                                double x=e->button.x;
                                double y=e->button.y;
                                if(x>530&&x<740&&y>590&&y<710){
                                        pause=false;
                                        finalball=false;
                                        start_mode=0;
                                        e->type = 0;
                                }else{pause=false;
                                      e->type = 0;
                                }

                        }
                }
                break;
            }
          }

        //  e->type = 0;
        if(e->type==SDL_MOUSEMOTION){

            double x=e->motion.x;
            double y=e->motion.y;
            double rot;
            if(x<=b && y<=z){
                 rot=(z-y)/(b-x);
                 teta=180*atan(rot)/3.1415;

            }
            else if(x>=b && y<=z){
                rot=(z-y)/(x-b);
                teta=180-(180*atan(rot)/3.1415);

            }
            else if(x>=b && y>=z){
                rot=(y-z)/(x-b);
                teta=180+(180*atan(rot)/3.1415);
            }
            else if(x<=b && y>=z){
                rot=(y-z)/(b-x);
                teta=360-(180*atan(rot)/3.1415);
            }


        }

            SDL_RenderPresent( m_renderer );
            SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
            SDL_RenderClear( m_renderer );
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);



            if(change_ball==1){
                    color_ball[0]=color_ball[1];
               for(int i=0;i<80;i++){

                if(chekpresent_color[i]==1){
                    color_ball[1]=color[i];
                    break;

                }
               }
               change_ball=0;
           }

            int r=img_w /2 -76;
            int r2=img_w /2 -130;
            double ball = 3.1415*teta /180;
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);





          if(color_ball[0]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
          }else if(color_ball[0]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[0]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );


          if(color_ball[1]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }




       double x2,y2,shib;
       double b2=500+img_w /2 - r*cos(ball), z2= 300+ img_h / 2 - r*sin(ball);
        //e->type = 0;
       SDL_PollEvent(e);

       if(e->type==SDL_MOUSEBUTTONDOWN){


            change_ball=1;


            double x_markaz;
            double y_markaz;
            double tt=5,mm=1;
            x2=e->button.x;
            y2=e->button.y;
            //int malom_i=chek_fasele(500 + img_w /2, 300+ img_h / 2 ,x2,y2,2,arr,ar,chekpresent);




    /////////////////////////////////////////11111111/////////////////////////////////////////



            if(x2<=b2 && y2<=z2){
                shib=(z2-y2)/(b2-x2);
                int chek_ellip=0;
                int i_newball;
                while(b2- mm*tt>0&& z2-mm*tt*shib>0 && chek_ellip ==0){
                         //////////////////////////


          if(color_ball[1]==0){

                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
          }

                    if(chek_ellip==0){

                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                        }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                        }
                        x_markaz=b2-mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm+=1;
                    }
               for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }

                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){

                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
                 textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
                //SDL_RenderClear( m_renderer );
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
          }

            }




            /////////////////////2222222222222222////////////////////////






            else if(x2>=b2 && y2<=z2){
                shib=(z2-y2)/(x2-b2);
                int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 - mm*tt*shib > 0 && chek_ellip ==0){

                        if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                    // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                    if(chek_ellip==0){
                            if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                            }
                      // filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm++;
                    }
                for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){

                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                       // cout<<"111";
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                        start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=1*(tedad_aghab);
                            }
                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
               // SDL_RenderClear( m_renderer );
                textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }



            //////////////////3333333333333333333333333//////////////






            else if(x2>=b2 && y2>=z2){
                shib=(y2-z2)/(x2-b2);
              //  tt=tt/shib;
                //while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800){
               // filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
               // mm++;


                  int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800 && chek_ellip ==0){
                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                   // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
                    if(chek_ellip==0){
                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                      //  filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
               for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
              //  SDL_RenderClear( m_renderer );
               textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }

            //////////44444444444444444444444444///////////////////




            else if(x2<=b2 && y2>=z2){
                shib=(y2-z2)/(b2-x2);
                tt=tt/shib;
                //  while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800){
              //  filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);


                int chek_ellip=0;
                int i_newball;
                while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800&& chek_ellip==0){

                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }



                    if(chek_ellip==0){
                         if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                       // filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2-mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
              for(int i=0;i<62;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }

                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){
                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }

            SDL_RenderPresent( m_renderer );
         //   SDL_RenderClear( m_renderer );
             textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_back, NULL, &bf_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                SDL_Delay(15);
                }

            }

      }


if(t<=800){
    if(t%20==0){
        int chek_per;
        for(int i=start+1;i>=0;i--){
            if(chekpresent_color[i]==0){
                chek_per=i;
            }
        }
        for(int i=chek_per-1;i>=0;i--){
            color[i+1]=color[i];
            chekpresent_color[i+1]=chekpresent_color[i];
        }
        chekpresent_color[0]=1;
        color[0]=rand()%4;

        start++;

    }


}

 for(int i=0;i<=start+1;i++){
         //chekpresent[start]=1;
       //  if(t<=4000){
        // chekpresent_color[0]=1;
        // }
        if(chekpresent_color[i]==1){
          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
        }
}


t++;
int ccc=0;
    for(int i=0;i<62;i++){
        if(chekpresent_color[i]==1){
            ccc++;
        }
    }
    if(ccc==0){
        finalball=false;
        start_mode=0;
    }

    if(chekpresent_color[61]==1){
        finalball=false;
        start_mode=0;
    }

    textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);



            SDL_RenderPresent( m_renderer );

           // SDL_Delay();
            SDL_DestroyTexture(m_back);
            SDL_DestroyTexture(m_img);


    }



}
while(start_mode==3){
int arr[72]={220 ,221 ,218 ,220 ,220 ,222 ,224 ,229 ,260 ,315 ,379 ,441 ,504 ,565 ,628 ,687 ,749 ,814 ,871 ,932 ,991 ,1049 ,1101 ,1139 ,1165 ,1177 ,1172 ,1143 ,1103 ,1053 ,1000 ,940 ,879 ,817 ,752 ,693 ,631 ,570 ,507 ,443 ,385 ,338 ,334 ,337 ,331 ,332 ,336 ,345 ,388 ,449 ,513 ,572 ,633 ,698 ,758 ,821 ,879 ,938 ,992, 1030 ,1048 ,1041 ,1003 ,953 ,897 ,833 ,774 ,711 ,650 ,590 ,525};
int ar[72]={652 ,588 ,522 ,452 ,386 ,316 ,254 ,185 ,126 ,108 ,101 ,102 ,103 ,104 ,105 ,113 ,114 ,123 ,129 ,148 ,171 ,199 ,238 ,291 ,349, 415, 483, 544, 597, 637, 665, 684, 695, 704, 707, 709, 711, 709, 709, 707, 704, 660, 596, 530, 464, 392, 326, 261, 213, 205, 203, 203, 204, 209, 215, 227, 242 ,266 ,302 ,352 ,415 ,482 ,540, 575, 598, 606, 609, 609, 606, 604, 601};



for(int i=0;i<80;i++){
    color[i]=rand()%4;
}

int start=0;
int chek_ch=0;
double teta=0;
double b=500 + img_w /2 , z=300+ img_h/2;
while(finalball){
m_img4 = IMG_LoadTexture(m_renderer,"mapp.JPG");
m_back = IMG_LoadTexture(m_renderer,"bf.JPG");
m_img = IMG_LoadTexture(m_renderer,"jun.JPG");
        e->type = 0;
          SDL_PollEvent(e);
          bool pause=true;
          if(e->type==SDL_KEYDOWN){
            switch(e->key.keysym.sym){
            case SDLK_SPACE:
                swap(color_ball[0],color_ball[1]);
                break;
            case SDLK_p:
                while(pause){
                        SDL_RenderCopy(m_renderer, m_help, NULL, &start_rect);
                        //   rectangleRGBA(m_renderer,530,590,740,710,255,255,255,255);
                        SDL_RenderPresent(m_renderer);
                        e->type = 0;
                        SDL_PollEvent(e);

                        if(e->type==SDL_MOUSEBUTTONDOWN){
                                double x=e->button.x;
                                double y=e->button.y;
                                if(x>530&&x<740&&y>590&&y<710){
                                        pause=false;
                                        finalball=false;
                                        start_mode=0;
                                        e->type = 0;
                                }else{pause=false;
                                      e->type = 0;
                                }

                        }
                }
                break;
            }
          }

        //  e->type = 0;
        if(e->type==SDL_MOUSEMOTION){

            double x=e->motion.x;
            double y=e->motion.y;
            double rot;
            if(x<=b && y<=z){
                 rot=(z-y)/(b-x);
                 teta=180*atan(rot)/3.1415;

            }
            else if(x>=b && y<=z){
                rot=(z-y)/(x-b);
                teta=180-(180*atan(rot)/3.1415);

            }
            else if(x>=b && y>=z){
                rot=(y-z)/(x-b);
                teta=180+(180*atan(rot)/3.1415);
            }
            else if(x<=b && y>=z){
                rot=(y-z)/(b-x);
                teta=360-(180*atan(rot)/3.1415);
            }


        }

            SDL_RenderPresent( m_renderer );
            SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
            SDL_RenderClear( m_renderer );
           SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);



            if(change_ball==1){
                    color_ball[0]=color_ball[1];
               for(int i=0;i<80;i++){

                if(chekpresent_color[i]==1){
                    color_ball[1]=color[i];
                    break;

                }
               }
               change_ball=0;
           }

            int r=img_w /2 -76;

            int r2=img_w /2 -130;
            double ball = 3.1415*teta /180;
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
            filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);





          if(color_ball[0]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,255,0,0,255);
          }else if(color_ball[0]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[0]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r*cos(ball),300+ img_h / 2 - r*sin(ball),25,25,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );


          if(color_ball[1]==0){
           // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,255,0,0,255);
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,0,255);
          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,0,255,255);
          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
            // filledEllipseRGBA(m_renderer,arr[i%62],ar[i%62],29,29,0,255,255,255);
          }




       double x2,y2,shib;
       double b2=500+img_w /2 - r*cos(ball), z2= 300+ img_h / 2 - r*sin(ball);
        //e->type = 0;
       SDL_PollEvent(e);

       if(e->type==SDL_MOUSEBUTTONDOWN){


            change_ball=1;


            double x_markaz;
            double y_markaz;
            double tt=5,mm=1;
            x2=e->button.x;
            y2=e->button.y;
            //int malom_i=chek_fasele(500 + img_w /2, 300+ img_h / 2 ,x2,y2,2,arr,ar,chekpresent);




    /////////////////////////////////////////11111111/////////////////////////////////////////



            if(x2<=b2 && y2<=z2){
                shib=(z2-y2)/(b2-x2);
                int chek_ellip=0;
                int i_newball;
                while(b2- mm*tt>0&& z2-mm*tt*shib>0 && chek_ellip ==0){
                         //////////////////////////


          if(color_ball[1]==0){

                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
          }else if(color_ball[1]==1){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

          }else if(color_ball[1]==2){
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

          }else{
                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
          }

                    if(chek_ellip==0){

                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                        }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                        }
                        x_markaz=b2-mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm+=1;
                    }
               for(int i=0;i<72;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }

                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }



    for(int i=0;i<=start+1;i++){

                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
                 textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
                //SDL_RenderClear( m_renderer );
SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
          }

            }




            /////////////////////2222222222222222////////////////////////






            else if(x2>=b2 && y2<=z2){
                shib=(z2-y2)/(x2-b2);
                int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 - mm*tt*shib > 0 && chek_ellip ==0){

                        if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                    // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                    if(chek_ellip==0){
                            if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,0,255,255,255);

                            }
                      // filledEllipseRGBA(m_renderer,b2+ mm*tt,z2-mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2-mm*tt*shib;
                        mm++;
                    }
                for(int i=0;i<72;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){

                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                       // cout<<"111";
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                        start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=1*(tedad_aghab);
                            }
                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){

                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                              if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }




    for(int i=0;i<=start+1;i++){

                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
               // SDL_RenderClear( m_renderer );
                textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
          SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }



            //////////////////3333333333333333333333333//////////////






            else if(x2>=b2 && y2>=z2){
                shib=(y2-z2)/(x2-b2);
              //  tt=tt/shib;
                //while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800){
               // filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
               // mm++;


                  int chek_ellip=0;
                int i_newball;
                while(b2 + mm*tt < 1280 && z2 + mm*tt*shib < 800 && chek_ellip ==0){
                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }

                   // filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);
                    if(chek_ellip==0){
                        if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2+ mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                      //  filledEllipseRGBA(m_renderer , b2 + mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2+mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
               for(int i=0;i<72;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                            if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }




    for(int i=0;i<=start+1;i++){

                        if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }


                SDL_RenderPresent( m_renderer );
              //  SDL_RenderClear( m_renderer );
               textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
            SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                 SDL_Delay(15);
                }

            }

            //////////44444444444444444444444444///////////////////




            else if(x2<=b2 && y2>=z2){
                shib=(y2-z2)/(b2-x2);
                tt=tt/shib;
                //  while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800){
              //  filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);


                int chek_ellip=0;
                int i_newball;
                while(b2 - mm*tt > 0 && z2 + mm*tt*shib < 800&& chek_ellip==0){

                   if(color_ball[1]==0){

                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,255,0,0,255);
                        }else if(color_ball[1]==1){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,0,255);

                        }else if(color_ball[1]==2){
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,0,255,255);

                        }else{
                                filledEllipseRGBA(m_renderer,500 + img_w /2 - r2*cos(ball),300+ img_h / 2 - r2*sin(ball),15,15,0,255,255,255);
                        }



                    if(chek_ellip==0){
                         if(color_ball[0]==0){

                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,255,0,0,255);
                            }else if(color_ball[0]==1){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,0,255);

                            }else if(color_ball[0]==2){
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,0,255,255);

                            }else{
                                filledEllipseRGBA(m_renderer,b2- mm*tt,z2+mm*tt*shib,25,25,0,255,255,255);

                            }

                       // filledEllipseRGBA(m_renderer , b2 - mm*tt , z2 + mm*tt*shib,25,25,255,0,0,255);
                        x_markaz=b2-mm*tt;
                        y_markaz=z2+mm*tt*shib;
                        mm++;
                    }
              for(int i=0;i<72;i++){
                    if(arr[i]<x_markaz+30 && arr[i]>x_markaz-30 && ar[i]>y_markaz-30 && ar[i]<y_markaz+30){
                        if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==0){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;

                       // start++;

                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];


                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab>=3){
                               if(color_ball[0]==0){
                                score+=4*(tedad_aghab);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab);
                            }

                            if(tedad_aghab>6){
                                score*=2;
                            }

                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }




                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==0 &&chekpresent_color[i]==0 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                        chekpresent_color[i_newball]=1;
                       // color_plus++;
                       // start++;
                       /* for(int j=start;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }*/
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                             if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }
                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }

                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }else if(chekpresent_color[i-1]==1 &&chekpresent_color[i]==1 &&chekpresent_color[i+1]==1){
                        i_newball=i;
                        chek_ellip=1;
                       // chekpresent_color[i_newball]=1;
                       // color_plus++;
                       start++;
                       int chek_per;
                       for(int i=i_newball;i<=start+1;i++){
                        if(chekpresent_color[i]==0){
                            chek_per=i;
                            break;
                        }
                       }
                        for(int j=chek_per;j>i_newball;j--){
                            color[j]=color[j-1];
                            chekpresent_color[j]=chekpresent_color[j-1];
                        }
                        color[i_newball]=color_ball[0];
                        int tedad_jolo=1;
                        while(color[i_newball] == color[i_newball+tedad_jolo] && chekpresent_color[i_newball+tedad_jolo]==1){
                           // chekpresent_color[i_newball]=0;
                           // chekpresent_color[i_newball+tedad_jolo]=0;
                            tedad_jolo++;
                            //cout<<"gggg";

                        }

                        int tedad_aghab=1;
                        while(color[i_newball] == color[i_newball-tedad_aghab] && chekpresent_color[i_newball-tedad_aghab]==1){

                            tedad_aghab++;

                        }

                        if(tedad_aghab+tedad_jolo>=4){
                                if(color_ball[0]==0){
                                score+=4*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==1){
                                score+=3*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==2){
                                score+=2*(tedad_aghab+tedad_jolo);
                            }else if(color_ball[0]==3){
                                score+=1*(tedad_aghab+tedad_jolo);
                            }

                            if(tedad_aghab+tedad_jolo>6){
                                score*=2;
                            }
                            if(tedad_aghab>1){
                            for(int i=0;i<tedad_aghab;i++){

                                chekpresent_color[i_newball-i]=0;
                            }
                            }
                            if (tedad_jolo>1){
                            for(int i=0;i<tedad_jolo;i++){
                                chekpresent_color[i_newball+i]=0;
                            }
                            }


                        }
                        break;

                        }

                    }
                }




    for(int i=0;i<=start+1;i++){

          if(chekpresent_color[i]==1){

          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
          }
    }

            SDL_RenderPresent( m_renderer );
         //   SDL_RenderClear( m_renderer );
             textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);
           SDL_RenderCopy(m_renderer, m_img4, NULL, &img3_rect);
            SDL_RenderCopyEx(m_renderer,m_img,NULL,&img_rect,teta,NULL,SDL_FLIP_NONE);
                SDL_Delay(15);
                }

            }

      }


if(t<=1200){
    if(t%20==0){
        int chek_per;
        for(int i=start+1;i>=0;i--){
            if(chekpresent_color[i]==0){
                chek_per=i;
            }
        }
        for(int i=chek_per-1;i>=0;i--){
            color[i+1]=color[i];
            chekpresent_color[i+1]=chekpresent_color[i];
        }
        color[0]=rand()%4;

        start++;
     //   for(int i=0;i<start;i++){
     //       cout<<chekpresent_color[i]<<" ";
      //  }
      //  cout<<endl;

    }


}

 for(int i=0;i<=start+1;i++){
         chekpresent[start]=1;
         if(t<=4000){
         chekpresent_color[0]=1;
         }else{chekpresent_color[0]=0;}
        if(chekpresent_color[i]==1){
          if(color[(i)]==0){
            filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,255,0,0,255);

          }else if(color[(i)]==1){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,0,255);
          }else if(color[(i)]==2){
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,0,255,255);
          }else{
             filledEllipseRGBA(m_renderer,arr[i%72],ar[i%72],29,29,0,255,255,255);
          }
           // SDL_RenderPresent( m_renderer );
        }
 }


t++;
int ccc=0;
    for(int i=0;i<72;i++){
        if(chekpresent_color[i]==1){
            ccc++;
        }
    }
    if(ccc==0){
        finalball=false;
        start_mode=0;
    }

    if(chekpresent_color[71]==1){
        finalball=false;
        start_mode=0;
    }

    textRGBA(m_renderer,10,10,to_string(score).c_str(),2,40,255,0,0,255);



            SDL_RenderPresent( m_renderer );

           // SDL_Delay();
    SDL_DestroyTexture(m_back);
    SDL_DestroyTexture(m_img4);
    SDL_DestroyTexture(m_img);

    }



}
fstream read("score.text",ios::app);
read<<score<<endl;
read.close();

        if(score<15){
            SDL_RenderCopy(m_renderer, m_lb1, NULL, &lb_rect);
            textRGBA(m_renderer,500,375,"your score is",2,50,0,0,0,255);
            textRGBA(m_renderer,610,455,to_string(score).c_str(),2,50,0,0,0,255);
            textRGBA(m_renderer,520,535,"try harder...",2,50,0,0,0,255);
        }else if(score<300){
            SDL_RenderCopy(m_renderer, m_lb1, NULL, &lb_rect);
            textRGBA(m_renderer,500,375,"your score is",2,50,0,0,0,255);
            textRGBA(m_renderer,610,455,to_string(score).c_str(),2,50,0,0,0,255);
            textRGBA(m_renderer,520,535,"well done!",2,50,0,0,0,255);

        }else if(score>=300){
            SDL_RenderCopy(m_renderer, m_lb1, NULL, &lb_rect);
            textRGBA(m_renderer,500,375,"your score is",2,50,0,0,0,255);
            textRGBA(m_renderer,610,455,to_string(score).c_str(),2,50,0,0,0,255);
            textRGBA(m_renderer,520,535,"you are a champ",2,50,255,0,0,255);
        }

while(true){
    SDL_RenderPresent(m_renderer);}
    SDL_DestroyTexture(m_back);
    SDL_DestroyTexture(m_img);
    SDL_DestroyTexture(m_img4);

    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;

}




