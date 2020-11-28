#include "prototypes.h"
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 900

void receptionT(int *port, sf::TcpSocket *socket);

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
    createName<<"What is your name";
    createPassword<<"What is your password";
    createDate<<"What is your birthday (ddmmyyyy)";


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
    SDL_Surface *black = IMG_Load("fond.jpg");
    SDL_Surface *black1 = IMG_Load("fond.jpg");
    SDL_Surface *black2 = IMG_Load("fond2.jpg");
    SDL_Surface *black3 = IMG_Load("fond3.jpg");
    SDL_Surface *black4 = IMG_Load("fond4.jpg");
    SDL_Window *deckWindow = NULL;
    SDL_Surface *deckWindowSurface = NULL;
    std::vector<Cartes*> toutesCartes;
    std::vector<int> deckJoueur;
    std::vector<int> selected;


    //putting all the cards need to put this as a function later;
    std::vector<SDL_Surface*> imageCache;
    initDeckCartes(imageCache);


    for(int i = 0; i < 18; i++)
    {
        lierCarteEtId(i,0,toutesCartes);
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
    SDL_Texture *texture1, *texture2, *texture3, *texture4, *texture5;
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
    sf::Thread thread(std::bind(&receptionT, &port, &socket));
    SDL_Surface *windowSurface = NULL;
    windowSurface = SDL_GetWindowSurface( window );
    SDL_Surface *fond = IMG_Load("open.png");

    std::string name;
    std::string mdp;
    std::string temp;
    std::string cname;
    std::string cmdp;
    std::string cdate;
    int state = 0;
    quit = 0;
    int page = 1;
    while (!quit)
    {
        if(port != -1)
        {
            std::cout << "COUCOU" << std::endl;
            jeu(port, name);
            thread.terminate();
            port = -1;
            inQUEUE = 0;
        }
        while (SDL_PollEvent(&event) == 1)
        {

            switch(page)
            {
            case 1:
                SDL_BlitSurface(fond, NULL, windowSurface, NULL);
                SDL_UpdateWindowSurface(window);
                break;

            case 2:


                get_text_and_rect(renderer, 400, 400, (char*)test.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 380, rect1.y + rect1.h, (char*)test2.str().c_str(), font, &texture2, &rect2);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);

                SDL_RenderPresent(renderer);
                break;
            case 3:
                get_text_and_rect(renderer, 400, 400, (char*)createName.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, rect1.y + rect1.h, (char*)createPassword.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 400, rect2.y + rect2.h, (char*)createDate.str().c_str(), font, &texture3, &rect3);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);

                SDL_RenderPresent(renderer);
                break;
            case 4:
                get_text_and_rect(renderer, 400, 400, (char*)startGame.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, rect1.y + rect1.h, (char*)deckOption.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 400, rect2.y + rect2.h, (char*)quitterJeu.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 600, 200, (char*)friends.str().c_str(), font, &texture4, &rect4);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer,texture4, NULL, &rect4);

                SDL_RenderPresent(renderer);
                break;
            case 5:
                get_text_and_rect(renderer, 200, 400, (char*)startGame.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 200, rect1.y + rect1.h, (char*)deckOption.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 200, rect2.y + rect2.h, (char*)quitterJeu.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 400, 200, (char*)friends.str().c_str(), font, &texture4, &rect4);
                get_text_and_rect(renderer, 600, 200, (char*)textbox.str().c_str(), font, &texture5, &rect5);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer,texture4, NULL, &rect4);
                SDL_RenderCopy(renderer,texture5, NULL, &rect5);

                SDL_RenderPresent(renderer);
                break;
            case 6:

                if(reset)
                {

                    if(alldecks[3].size() != 0)
                    {
                        deck4.str(" ");
                        deck4<<"Deck 4";
                    }
                    if(alldecks[2].size() != 0)
                    {
                        deck3.str(" ");
                        deck3<<"Deck 3";
                    }
                    if(alldecks[1].size()!=0)
                    {
                        deck2.str(" ");
                        deck2<<"Deck 2";
                    }
                    if(alldecks[0].size()!=0)
                    {
                        deck1.str(" ");
                        deck1<<"Deck 1";
                    }
                    reset = false;

                }


                get_text_and_rect(renderer, 400, 400, (char*)deck1.str().c_str(), font, &texture1, &rect1);
                get_text_and_rect(renderer, 400, rect1.y + rect1.h, (char*)deck2.str().c_str(), font, &texture2, &rect2);
                get_text_and_rect(renderer, 400, rect2.y + rect2.h, (char*)deck3.str().c_str(), font, &texture3, &rect3);
                get_text_and_rect(renderer, 400, rect3.y + rect3.h, (char*)deck4.str().c_str(), font, &texture4, &rect4);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderClear(renderer);

                /* Use TTF textures. */
                SDL_RenderCopy(renderer, texture1, NULL, &rect1);
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
                SDL_RenderCopy(renderer, texture3, NULL, &rect3);
                SDL_RenderCopy(renderer,texture4, NULL, &rect4);

                SDL_RenderPresent(renderer);
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
                    deckJoueur.erase(deckJoueur.begin(),deckJoueur.end());
                    for(int i = 0; i<20; i++)
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
            //page boutton
            case 1:
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x >100 && event.button.x <515 && event.button.y >390 && event.button.y <500)
                    {
                        page++;
                    }
                    else if(event.button.x >622 && event.button.x <1030 && event.button.y >400 && event.button.y <500)
                    {
                        page = 3;
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
                        }
                        break;
                    }
                    break;
                case SDL_TEXTINPUT:
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
                    //std::cout<<event.button.x<<" "<<event.button.y<<std::endl;
                    if(event.button.x >400 && event.button.x <614 && event.button.y >400 && event.button.y <424)
                    {
                        state = 0;
                    }

                    else if(event.button.x >377 && event.button.x <641 && event.button.y >432 && event.button.y <456)
                    {
                        state = 1;
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
                        if(state == 0)
                        {
                            createName.str(" ");
                        }
                        else if(state == 1)
                        {
                            createPassword.str(" ");
                        }
                        else
                        {
                            createDate.str(" ");
                        }

                        break;
                    case SDLK_TAB:
                        if(state <2)
                        {
                            state++;
                        }
                        else
                        {
                            state = 0;
                        }
                        break;
                    case SDLK_RETURN:
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
                            page = 1;
                            LOGIN = 0;
                        }
                        break;

                    }
                    break;
                case SDL_TEXTINPUT:
                    if(state == 0)
                    {
                        createName<<event.text.text;
                    }
                    else if(state == 1)
                    {
                        createPassword<<event.text.text;
                    }
                    else
                    {
                        createDate<<event.text.text;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // std::cout<<event.button.x<<" "<<event.button.y<<std::endl;
                    if(event.button.x >400 && event.button.x <611 && event.button.y >400 && event.button.y <424)
                    {
                        state = 0;
                    }
                    else if(event.button.x >400 && event.button.x <664 && event.button.y >434 && event.button.y <458)
                    {
                        state = 1;
                    }
                    else if(event.button.x >400 && event.button.x <800 && event.button.y >462 && event.button.y <486)
                    {
                        state = 2;
                    }
                    break;
                }

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
                    if(event.button.x >400 && event.button.x <548 && event.button.y >400 && event.button.y <424)
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
                        page = 6;
                    }
                    else if(event.button.x >400 && event.button.x <539 && event.button.y >432 && event.button.y <456)
                    {
                        //aller au deck
                        std::cout<<"Deck";
                        page = 7;
                    }
                    else if(event.button.x >400 && event.button.x <488 && event.button.y >461 && event.button.y <485)
                    {
                        //quitter jeu rien a changer
                        std::cout<<"quitter";
                        quit = 1;
                    }
                    else if(event.button.x >600 && event.button.x <670 && event.button.y >205 && event.button.y <229)
                    {
                        std::cout<<"amies";
                        page = 5;
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
                        if(select == true)
                        {
                            textbox.str(" ");
                        }
                        break;
                    case SDLK_RETURN:
                        if(select == true)
                        {
                            //system de recherche d'amies
                            searchfriend = textbox.str();
                            std::cout<<searchfriend<<std::endl;
                        }
                        break;

                    default:
                        int a = event.key.keysym.sym;
                        char w = static_cast<char>(a);
                        if(select == true)
                        {
                            textbox<<w;
                        }
                        break;
                    }
                    break;
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
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x >400 && event.button.x <590 && event.button.y >400 && event.button.y <424 && alldecks[0].size()!=0)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 4;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >430 && event.button.y <454 && alldecks[1].size()!=0)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 4;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >462 && event.button.y <478 && alldecks[2].size()!=0)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 4;
                    }
                    else if(event.button.x >400 && event.button.x <590 && event.button.y >489 && event.button.y <507 && alldecks[3].size()!=0)
                    {
                        /*alldecks[0] dois etre envoyer au serv*/
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        inQUEUE = 1;
                        page = 4;
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
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    carteSelec = selectionCarte(toutesCartes, event.button.x, event.button.y);
                    if(event.button.x >833 && event.button.x <842 && event.button.y >980 && event.button.y <1004)
                    {
                        cardpage = 1;
                        black = black1;
                        for(int i = 0; i<20; i++)
                        {
                            selected[i] = 0;
                        }
                        cardnmb = 0;
                    }
                    else if(event.button.x >877 && event.button.x <888 && event.button.y >980 && event.button.y <1004)
                    {
                        cardpage = 2;
                        black = black2;
                        for(int i = 0; i<20; i++)
                        {
                            selected[i] = 0;
                        }
                        cardnmb = 0;
                    }
                    else if(event.button.x >921 && event.button.x <931 && event.button.y >980 && event.button.y <1004)
                    {
                        cardpage = 3;
                        black = black3;
                        for(int i = 0; i<20; i++)
                        {
                            selected[i] = 0;
                        }
                        cardnmb = 0;
                    }
                    else if(event.button.x >963 && event.button.x <975 && event.button.y >980 && event.button.y <1004)
                    {
                        cardpage = 4;
                        black = black4;
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
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}




void receptionT(int *port, sf::TcpSocket *socket)
{
    sf::Packet paquet;
    socket->receive(paquet);
    paquet >> *port;
    std::cout << *port << std::endl;
}
