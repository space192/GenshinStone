#include "prototypes.h"
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 600
#define login "login_screen.png"
#define compte "se_creer_un_compte.png"
#define main_m "main_menu.png"
#define d "the_gate.png"

void receptionT(int *port, sf::TcpSocket *socket, std::vector<int> *deck);
bool checkOnline(sf::Packet *paquet, sf::TcpSocket *socket, int LOGIN, std::string nomJoueur);

int main(int argc, char **argv)
{

    srand((unsigned int)time(0));

    //case start
    std::stringstream test;
    test<<"What is your name";
    std::stringstream test2;
    test2<<"What is your password";

    //case create
    std::stringstream createName;
    std::stringstream createPassword;
    std::stringstream createDate;
    std::stringstream dd,mm,aaaa;

    createName<<"What is your name";
    createPassword<<"What is your password";
    dd<<"dd";
    mm<<"mm";
    aaaa<<"aaaa";


    //Menu du jeu
    std::stringstream startGame;
    startGame<<"Start a game";
    std::stringstream deckOption;
    deckOption<<"Deck option";
    std::stringstream friends;
    friends<<"Amies";
    std::stringstream quitterJeu;
    quitterJeu<<"Quitter";

    //Menu ami
    std::stringstream textbox;
    textbox<<"Search for a friend";
    std::string searchfriend;
    std::stringstream friendRequest;
    friendRequest<<"Friend request Yes No";
    bool select = false;

    //deck
    std::stringstream deck1;
    std::stringstream deck2;
    std::stringstream deck3;
    std::stringstream deck4;
    deck1<<"DECK 1 ";
    deck2<<"DECK 2 ";
    deck3<<"DECK 3 ";
    deck4<<"DECK 4 ";
    std::string Empty = "* VIDE *";

    //mettre ici le code pour chequer si les decks sont vide ou non
    deck1<<Empty;
    deck2<<Empty;
    deck3<<Empty;
    deck4<<Empty;

    //Deck
    bool open = false, reset = true;
    SDL_Texture *img = NULL;
    SDL_Surface *black = IMG_Load("deck.png");
    SDL_Surface *black1 = IMG_Load("deck.png");
    SDL_Surface *black2 = IMG_Load("deck2.png");
    SDL_Surface *black3 = IMG_Load("deck3.png");
    SDL_Surface *black4 = IMG_Load("deck4.png");
    SDL_Surface *q = IMG_Load("the_gate.png");
    int w,h;
    SDL_Window *deckWindow = NULL;
    SDL_Surface *deckWindowSurface = NULL;
    std::vector<Cartes*> toutesCartes;
    std::vector<int> deckJoueur;
    std::vector<int> selected;

    std::vector<int> CARTERECUSERVEUR;


    //putting all the cards need to put this as a function later;
    std::vector<SDL_Surface*> imageCache;
    initDeckCartes(imageCache);


    //Amis
    //On a 5 amis max vraiment pas envie de re ecrire tout mon code visuel
    std::stringstream user1, user2, user3, user4, user5, userS;
    SDL_Rect rUser1, rUser2, rUser3, rUser4, rUser5, rUserS;
    SDL_Texture *tUser1, *tUser2, *tUser3, *tUser4, *tUser5, *tUserS;

    //Mettre ici la partie ou on recupere les noms des gens ou les laisser vide si on a pas d'amis
    //aussi mettre si ils sont online ou pas
    int nbAmis;
    std::string tempAmis;
    user1 << " ";
    user2 << " ";
    user3 << " ";
    user4 << " ";
    user5 << " ";
    userS.str(" ");
    int tempO;
    //online = true;
    SDL_Color online = {0,255,0,0}, offline = {255,0,0,0};
    //SDL_Color onlineC;
    //Ici pour verifier si les amis sont co ou pas
    /*
    if(online)
    {
        onlineC = {0,255,0,0};
    }
    else
    {
        onlineC = {255,0,0,0}

    }
    */




    for(int i = 0; i < 18; i++)
    {
        lierCarteEtId(i,toutesCartes);
        selected.push_back(false);
    }
    int cardnmb = 0, cardpage = 1, carteSelec = -1;
    std::vector<std::vector<int> > alldecks;
    actualiserCarteDeck(toutesCartes);
    for(int i = 0; i<4; i++)
    {
        alldecks.push_back(deckJoueur);
    }








    SDL_Event event;
    SDL_Rect rect1, rect2, rect3, rect4, rect5, position;

    SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2, *texture3, *texture4, *texture5, *textureA;
    SDL_Window *window;
    char *font_path;
    int quit;

    if (argc == 1)
    {
        font_path = "ARLRDBD.ttf";
    }
    else if (argc == 2)
    {
        font_path = argv[1];
    }

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_StartTextInput();
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("fournierfamily.ovh", 53000);
    if(status != sf::Socket::Done)
    {
        std::cout << "erreur lors de la connexion" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (font == NULL)
    {
        exit(EXIT_FAILURE);
    }


    sf::Packet paquet;
    int reception;
    int jour,mois,annee, LOGIN = 0, action;
    int port = -1;
    int inQUEUE;
    int deck0S = 0,deck1S = 0,deck2S= 0,deck3S=0;
    sf::Thread thread(std::bind(&receptionT, &port, &socket, &CARTERECUSERVEUR));
    SDL_Surface *windowSurface = NULL;
    windowSurface = SDL_GetWindowSurface( window );
    int resultat;
    std::string name;
    std::string mdp;
    std::string temp;
    std::string cname;
    std::string cmdp;
    std::string cdate;
    int state = 0;
    quit = 0;
    int page = 2;
    bool load = true;
    while (!quit)
    {
        if(port != -1)
        {
            jeu(port, name, CARTERECUSERVEUR);
            thread.terminate();
            port = -1;
            inQUEUE = 0;
            CARTERECUSERVEUR.clear();
            page = 4;
            load = true;
        }
        while (SDL_PollEvent(&event) == 1)
        {

            switch(page)
            {
            case 1:
                if(load)
                {
                SDL_BlitSurface(q, NULL, windowSurface, NULL);
                SDL_UpdateWindowSurface(window);
                load = false;
                }

                break;

            case 2:

                if(load)
                {
                img = IMG_LoadTexture(renderer,login);
                SDL_QueryTexture(img, NULL,NULL,&w,&h);
                SDL_Rect im; im.x = 0; im.y = 0; im.h = h; im.w = w;
                get_text_and_rect(renderer, 400, 260, (char*)test.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, 365, (char*)test2.str().c_str(), font, &texture2, &rect2);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, img, NULL, &im);
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);

                SDL_RenderPresent(renderer);
                load = false;
                }
                break;
            case 3:
                if(load)
                {
                img = IMG_LoadTexture(renderer,compte);
                SDL_QueryTexture(img, NULL,NULL,&w,&h);
                SDL_Rect im; im.x = 0; im.y = 0; im.h = h; im.w = w;
                get_text_and_rect(renderer, 400, 245, (char*)createName.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, 315, (char*)createPassword.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 415, 400, (char*)dd.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 530, 400, (char*)mm.str().c_str(), font, &texture4, &rect4);
                get_text_and_rect(renderer, 640, 400, (char*)aaaa.str().c_str(), font, &texture5, &rect5);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, img, NULL, &im);
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer, texture4, NULL, &rect4);
                SDL_RenderCopy(renderer, texture5, NULL, &rect5);

                SDL_RenderPresent(renderer);
                load = false;
                }
                break;
            case 4:
                if(load)
                {
                img = IMG_LoadTexture(renderer,main_m);
                SDL_QueryTexture(img, NULL,NULL,&w,&h);
                SDL_Rect im; im.x = 0; im.y = 0; im.h = h; im.w = w;
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, img, NULL, &im);

                SDL_RenderPresent(renderer);
                load = false;
                }
                break;
            case 5:
                if(load)
                {
                get_text_and_rect(renderer, 200, 400, (char*)startGame.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 200, rect1.y + rect1.h, (char*)deckOption.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 200, rect2.y + rect2.h, (char*)quitterJeu.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 400, 200, (char*)friends.str().c_str(), font, &texture4, &rect4);
                get_text_and_rect(renderer, 600, 200, (char*)textbox.str().c_str(), font, &texture5, &rect5);

                //Je sais que c'est pas opti mais je decouvre le SDL
                if(checkOnline(&paquet,&socket, LOGIN, user1.str()) == true)
                {
                    get_text_and_rect(renderer, 600, 300, (char*)user1.str().c_str(), font, &tUser1, &rUser1, online);
                }
                else
                {
                    get_text_and_rect(renderer, 600, 300, (char*)user1.str().c_str(), font, &tUser1, &rUser1, offline);
                }
                if(checkOnline(&paquet,&socket, LOGIN, user2.str()) == true)
                {
                    get_text_and_rect(renderer, 600, 325, (char*)user2.str().c_str(), font, &tUser2, &rUser2, online);
                }
                else
                {
                    get_text_and_rect(renderer, 600, 325, (char*)user2.str().c_str(), font, &tUser2, &rUser2, offline);
                }
                if(checkOnline(&paquet,&socket, LOGIN, user3.str()) == true)
                {
                    get_text_and_rect(renderer, 600, 350, (char*)user3.str().c_str(), font, &tUser3, &rUser3, online);
                }
                else
                {
                    get_text_and_rect(renderer, 600, 350, (char*)user3.str().c_str(), font, &tUser3, &rUser3, offline);
                }
                if(checkOnline(&paquet,&socket, LOGIN, user4.str()) == true)
                {
                    get_text_and_rect(renderer, 600, 375, (char*)user4.str().c_str(), font, &tUser4, &rUser4, online);
                }
                else
                {
                    get_text_and_rect(renderer, 600, 375, (char*)user4.str().c_str(), font, &tUser4, &rUser4, offline);
                }
                if(checkOnline(&paquet,&socket, LOGIN, user5.str()) == true)
                {
                    get_text_and_rect(renderer, 600, 400, (char*)user5.str().c_str(), font, &tUser5, &rUser5, online);
                }
                else
                {
                    get_text_and_rect(renderer, 600, 400, (char*)user5.str().c_str(), font, &tUser5, &rUser5, offline);
                }

                get_text_and_rect(renderer, 600, 225, (char*)userS.str().c_str(), font, &tUserS, &rUserS);




                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);
                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer,texture4, NULL, &rect4);
                SDL_RenderCopy(renderer,texture5, NULL, &rect5);

                SDL_RenderCopy(renderer,tUser1, NULL, &rUser1);
                SDL_RenderCopy(renderer,tUser2, NULL, &rUser2);
                SDL_RenderCopy(renderer,tUser3, NULL, &rUser3);
                SDL_RenderCopy(renderer,tUser4, NULL, &rUser4);
                SDL_RenderCopy(renderer,tUser5, NULL, &rUser5);
                SDL_RenderCopy(renderer,tUserS, NULL, &rUserS);

                SDL_RenderPresent(renderer);
                load = false;
                }
                break;
            case 6:
                if(load)
                {

                if(reset)
                {

                    if(alldecks[3].size() != 0 || deck3S == 1)
                    {
                        deck4.str(" ");
                        deck4<<"Deck 4";
                    }
                    if(alldecks[2].size() != 0|| deck2S == 1)
                    {
                        deck3.str(" ");
                        deck3<<"Deck 3";
                    }
                    if(alldecks[1].size()!=0|| deck1S == 1)
                    {
                        deck2.str(" ");
                        deck2<<"Deck 2";
                    }
                    if(alldecks[0].size()!=0|| deck0S == 1)
                    {
                        deck1.str(" ");
                        deck1<<"Deck 1";
                    }
                    reset = false;

                }

                img = IMG_LoadTexture(renderer,d);
                SDL_QueryTexture(img, NULL,NULL,&w,&h);
                SDL_Rect im; im.x = 0; im.y = 0; im.h = h; im.w = w;
                get_text_and_rect(renderer, 400, 300, (char*)deck1.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, rect1.y + rect1.h, (char*)deck2.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 400, rect2.y + rect2.h, (char*)deck3.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 400, rect3.y + rect3.h, (char*)deck4.str().c_str(), font, &texture4, &rect4);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                 SDL_RenderCopy(renderer, img, NULL, &im);
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer,texture4, NULL, &rect4);

                SDL_RenderPresent(renderer);
                load = false;
                }
                break;
            case 7:
                if(!open)
                {
                    deckWindow = SDL_CreateWindow("Deck",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_SHOWN);
                    deckWindowSurface = SDL_GetWindowSurface( deckWindow );
                    SDL_BlitSurface(black, NULL, deckWindowSurface, NULL);
                    SDL_UpdateWindowSurface(deckWindow);
                    open = true;

                }
                else
                {
                    //pwindowSurface = SDL_GetWindowSurface( pWindow );
                    SDL_BlitSurface(black, NULL, deckWindowSurface, NULL);
                    actualiserImageDeck(toutesCartes,imageCache,deckWindowSurface,selected);
                    SDL_UpdateWindowSurface(deckWindow);
                }
                if(cardnmb==25 )
                {
                    std::cout<<"test";
                    open = false;
                    page = 4;
                    SDL_DestroyWindow(deckWindow);
                    alldecks[cardpage-1]=deckJoueur;
                    paquet.clear();
                    paquet << 2 << LOGIN;
                    socket.send(paquet);
                    paquet.clear();
                    paquet << 1;
                    socket.send(paquet);
                    paquet.clear();
                    paquet << cardpage-1;
                    socket.send(paquet);
                    paquet.clear();
                    paquet << alldecks[cardpage-1].size();
                    for(int i = 0 ; i < alldecks[cardpage-1].size();i++)
                    {
                        paquet << alldecks[cardpage-1][i];
                    }
                    socket.send(paquet);
                    paquet.clear();
                    deckJoueur.erase(deckJoueur.begin(),deckJoueur.end());
                    for(int i = 0; i<25; i++)
                    {
                        selected[i] = 0;
                    }
                    cardnmb = 0;
                    black = black1;
                    cardpage = 1;
                    reset = true;
                    break;
                }

                break;
            }



            switch(page)
            {
            //page q
            case 1:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        load = true;
                        page = 4;
                        break;
                    }
                    break;
                }
                break;
            //page start commencer jeu
            case 2:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_BACKSPACE:
                        load = true;
                        if(state == 0)
                        {
                            test.str(" ");
                        }
                        else
                        {
                            test2.str(" ");
                        }
                        break;
                    case SDLK_TAB:
                        if(state == 0)
                        {
                            state++;
                        }
                        else
                        {
                            state--;
                        }
                        break;
                    case SDLK_RETURN:
                        name = test.str();
                        mdp = test2.str();
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << name << mdp;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> reception;
                        paquet.clear();
                        if(reception == 1)
                        {
                            page = 4;
                            LOGIN = 1;
                            load = true;
                        }
                        break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    load= true;
                    if(state == 0)
                    {
                        test<<event.text.text;
                    }
                    else
                    {
                        test2<<event.text.text;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:

                    std::cout<<event.button.x<<" "<<event.button.y<<std::endl;

                    if(event.button.x >359 && event.button.x <735 && event.button.y >245 && event.button.y <298)
                    {
                        state = 0;
                    }

                    else if(event.button.x >359 && event.button.x <735 && event.button.y >349 && event.button.y <399)
                    {
                        state = 1;
                    }
                    else if(event.button.x >370 && event.button.x <503 && event.button.y >434 && event.button.y <457)
                    {
                        name = test.str();
                        mdp = test2.str();
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << name << mdp;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> reception;
                        paquet.clear();
                        if(reception == 1)
                        {
                            page = 4;
                            LOGIN = 1;
                            load = true;
                        }
                    }
                    else if(event.button.x >588 && event.button.x <728 && event.button.y >434 && event.button.y <457)
                    {
                        page = 3;
                        load = true;
                    }
                    break;

                }
                break;
            //case cree compte
            case 3:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_BACKSPACE:
                        load = true;
                        if(state == 0)
                        {
                            createName.str(" ");
                        }
                        else if(state == 1)
                        {
                            createPassword.str(" ");
                        }
                        else if(state == 2)
                        {
                            dd.str(" ");
                        }
                        else if(state ==3)
                        {
                            mm.str(" ");
                        }
                        else
                        {
                            aaaa.str(" ");
                        }

                        break;
                    case SDLK_TAB:
                        if(state <5)
                        {
                            state++;
                        }
                        else
                        {
                            state = 0;
                        }
                        break;
                    case SDLK_RETURN:
                        createName<<dd.str()<<mm.str()<<aaaa.str();
                        cname = createName.str();
                        cmdp = createPassword.str();
                        cdate = createDate.str();
                        paquet.clear();
                        action = 2;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << cname << cmdp << jour << mois << annee;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> reception;
                        paquet.clear();
                        if(reception == 6)
                        {
                            page = 2;
                            LOGIN = 0;
                            load = true;
                        }
                        break;

                    }
                    break;
                case SDL_TEXTINPUT:
                    load= true;
                    if(state == 0)
                    {
                        createName<<event.text.text;
                    }
                    else if(state == 1)
                    {
                        createPassword<<event.text.text;
                    }
                    else if (state == 2)
                    {
                        dd<<event.text.text;
                    }
                    else if(state == 3)
                    {
                        mm<<event.text.text;
                    }
                    else
                    {
                        aaaa<< event.text.text;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    std::cout<<event.button.x<<" "<<event.button.y<<std::endl;

                    if(event.button.x >357 && event.button.x <736 && event.button.y >236 && event.button.y <283)
                    {
                        state = 0;
                    }
                    else if(event.button.x >357 && event.button.x <736 && event.button.y >310 && event.button.y <360)
                    {
                        state = 1;
                    }

                    else if(event.button.x >405 && event.button.x <473 && event.button.y >389 && event.button.y <440)
                    {
                        state = 2;
                    }
                    else if(event.button.x >516 && event.button.x <583 && event.button.y >389 && event.button.y <440)
                    {
                        state = 3;
                    }
                    else if(event.button.x >628 && event.button.x <730 && event.button.y >389 && event.button.y <440)
                    {
                        state = 4;
                    }
                    else if(event.button.x >480 && event.button.x <620 && event.button.y >479 && event.button.y <502)
                    {
                        cname = createName.str();
                        cmdp = createPassword.str();
                        cdate = createDate.str();
                        paquet.clear();
                        action = 2;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << cname << cmdp << jour << mois << annee;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> reception;
                        paquet.clear();
                        if(reception == 6)
                        {
                            page = 2;
                            LOGIN = 0;
                            load = true;
                        }
                    }
                    break;
                }
                break;

            case 4:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        if(inQUEUE == 1)
                        {
                            thread.terminate();
                            paquet.clear();
                            action = 4;
                            paquet << action << LOGIN;
                            socket.send(paquet);
                            paquet.clear();
                            inQUEUE = 0;
                            SDL_Delay(100);
                        }
                        else
                        {
                            quit = 1;
                        }
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    //juste pour voir ou est quoi
                    //std::cout<<event.button.x<<" "<<event.button.y<<std::endl;

                    if(event.button.x >469 && event.button.x <624 && event.button.y >177 && event.button.y <191)
                    {
                        //ici mettre le debut du jeu avec serv
                        /*
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 4;
                        */
                        paquet.clear();
                        paquet << 2 << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 2;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> deck0S >> deck1S >> deck2S >> deck3S;
                        paquet.clear();
                        page = 6;
                        load = true;
                    }
                    else if(event.button.x >448 && event.button.x <647 && event.button.y >220 && event.button.y <240)
                    {
                        //aller au deck
                        std::cout<<"Deck";
                        page = 7;
                        load = true;
                    }
                    else if(event.button.x >471 && event.button.x <620 && event.button.y >309 && event.button.y <328)
                    {
                        //quitter jeu rien a changer
                        std::cout<<"quitter";
                        quit = 1;
                    }
                    if(event.button.x >448 && event.button.x <638 && event.button.y >265 && event.button.y <286)
                    {

                        std::cout<<"amies";
                        page = 5;
                        load = true;
                        paquet.clear();
                        paquet << 3 << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 1;
                        socket.send(paquet);
                        paquet.clear();
                        socket.receive(paquet);
                        paquet >> nbAmis;
                        for(int i = 0 ; i < nbAmis;i++)
                        {
                            paquet.clear();
                            socket.receive(paquet);
                            paquet >> tempAmis;
                            switch(i)
                            {
                            case 0:
                                {
                                    user1.str(tempAmis);
                                    break;
                                }
                            case 1:
                                {
                                    user2.str(tempAmis);
                                    break;
                                }
                            case 2:
                                {
                                    user3.str(tempAmis);
                                    break;
                                }
                            case 3:
                                {
                                    user4.str(tempAmis);
                                    break;
                                }
                            case 4:
                                {
                                    user5.str(tempAmis);
                                    break;
                                }
                            }
                        }
                        break;

                    }
                    break;

                }
                break;
            case 5:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_BACKSPACE:
                        load = true;
                        if(select == true)
                        {
                            textbox.str(" ");
                        }
                        break;
                    case SDLK_RETURN:
                        if(select == true)
                        {
                            searchfriend = textbox.str();
                            paquet.clear();
                            paquet << 3 << LOGIN;
                            socket.send(paquet);
                            paquet.clear();
                            paquet << 2;
                            socket.send(paquet);
                            paquet.clear();
                            paquet << searchfriend;
                            socket.send(paquet);
                            paquet.clear();
                            socket.receive(paquet);
                            paquet >> resultat;
                            if (resultat == 1)
                            {
                                userS<<"Friend request sent to ";
                                userS<<searchfriend;
                            }
                            else
                            {
                                userS << "Joueur non trouvé";
                            }
                            load = true;
                        }
                        break;
                    }
                    break;
                    case SDL_TEXTINPUT:
                    {
                        load = true;
                        if(select == true)
                        {
                            textbox << event.text.text;
                        }
                        break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    //std::cout<<event.button.x<<" "<<event.button.y<<std::endl;
                    if(event.button.x >600 && event.button.x <816 && event.button.y >200 && event.button.y <224 && select == false)
                    {
                        //ici mettre le debut du jeu avec serv
                        std::cout<<"Start";
                        select = true;
                    }
                    else if(event.button.x <500)
                    {
                        page = 4;
                        load = true;
                    }
                    break;
                }
                break;
            case 6:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        page = 4;
                        load = true;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x >400 && event.button.x <590 && event.button.y >300 && event.button.y <324 && deck0S == 1)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 0;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 1;
                        load = true;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >330 && event.button.y <354 || deck1S == 1)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 1;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 1;
                        load = true;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >362 && event.button.y <378 && deck2S == 1)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 2;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 1;
                        load = true;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >389 && event.button.y <407 && deck3S == 1)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        paquet << 3;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 1;
                        load = true;
                    }
                    break;
                }
                break;
            case 7:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        open = false;
                        page = 4;
                        SDL_DestroyWindow(deckWindow);
                        reset = true;
                        black = black1;
                        cardpage = 1;
                        load = true;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    carteSelec = selectionCarte(toutesCartes, event.button.x, event.button.y);
                    std::cout<<event.button.x<<" "<<event.button.y<<std::endl;
                    if(event.button.x >1098 && event.button.x <1198 && event.button.y >1026 && event.button.y <1049 && cardpage<4)
                    {

                        cardpage++;
                        std::cout<<cardpage<<std::endl;
                        switch(cardpage)
                        {
                        case 2:
                            black = black2;
                            break;
                        case 3:
                            black = black3;
                            break;
                        case 4:
                            black = black4;
                            break;
                        }
                        for(int i = 0; i<20; i++)
                        {
                            selected[i] = 0;
                        }
                        cardnmb = 0;
                    }
                    else if(event.button.x >831 && event.button.x <931 && event.button.y >1020 && event.button.y <1053 && cardpage>1)
                    {
                        cardpage--;
                        switch(cardpage)
                        {
                        case 2:
                            black = black2;
                            break;
                        case 3:
                            black = black3;
                            break;
                        case 1:
                            black = black1;
                            break;
                        }
                        for(int i = 0; i<20; i++)
                        {
                            selected[i] = 0;
                        }
                        cardnmb = 0;
                    }
                    if(carteSelec != -1 )
                    {
                        if(selected[carteSelec] <3)
                        {
                            deckJoueur.push_back(toutesCartes[carteSelec]->getImage());
                            selected[carteSelec]++;
                            position = toutesCartes[carteSelec]->getPosition();
                            std::cout<<"Cartes " << carteSelec <<" was added "<<std::endl;
                            cardnmb++;
                        }
                        else
                        {
                            cardnmb--;
                            cardnmb--;
                            deckJoueur.erase(deckJoueur.begin()+cardnmb);
                            selected[carteSelec] = 0;


                            std::cout<<"Cartes " <<carteSelec << " was deleted "<<toutesCartes[carteSelec]->getImage()<<std::endl;
                        }
                    }

                    break;
                }
                break;

            }


        }

    }
    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    /*
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);

    SDL_DestroyTexture(tUser1);
    SDL_DestroyTexture(tUser2);
    SDL_DestroyTexture(tUser3);
    SDL_DestroyTexture(tUser4);
    SDL_DestroyTexture(tUser5);
    SDL_DestroyTexture(tUserS);
    SDL_DestroyTexture(textureA);
    */

    SDL_DestroyRenderer(renderer);

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    system("pause");
    return EXIT_SUCCESS;
}




void receptionT(int *port, sf::TcpSocket *socket, std::vector<int> *deck)
{
    sf::Packet paquet;
    int taille, temp;
    socket->receive(paquet);
    paquet >> *port;
    paquet >> taille;
    for(int i = 0 ; i < taille ; i++)
    {
        paquet >> temp;
        deck->push_back(temp);
    }

    std::cout << deck->size();
}




bool checkOnline(sf::Packet *paquet, sf::TcpSocket *socket, int LOGIN, std::string nomJoueur)
{
    int tempO;
    if(nomJoueur != " ")
    {
        paquet->clear();
        *paquet << 3 << LOGIN;
        socket->send(*paquet);
        paquet->clear();
        *paquet << 7;
        socket->send(*paquet);
        paquet->clear();
        *paquet << nomJoueur;
        socket->send(*paquet);
        paquet->clear();
        socket->receive(*paquet);
        *paquet >> tempO;
        if(tempO == 1)
        {
            return true;
        }
        else if (tempO == 0)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
