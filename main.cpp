#include "prototypes.h"
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 900

void receptionT(int *port, sf::TcpSocket *socket);

int main(int argc, char **argv)
{

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


    SDL_Event event;
    SDL_Rect rect1, rect2, rect3, rect4;
    SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2, *texture3, *texture4;
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
    sf::Thread thread(std::bind(&receptionT, &port, &socket));
    SDL_Surface *windowSurface = NULL;
    windowSurface = SDL_GetWindowSurface( window );
    SDL_Surface *fond = IMG_Load("open.png");

    std::string name;
    std::string mdp;

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
            jeu(port);
            port = -1;
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
            }



            switch(page)
            {
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
                    default:
                        int a = event.key.keysym.sym;
                        char w = static_cast<char>(a);
                        if(state == 0)
                        {
                            test<<w;
                        }
                        else
                        {
                            test2<<w;
                        }
                        break;
                    }
                    break;



                }
                break;
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
                    default:
                        //le c devant c'est au cas ou tu veux 2 types de variable dependant de
                        //si ils essaient de se co ou si il essaient de cree un compte genre si
                        //name = vide donc cree compte parce cname entier

                        int a = event.key.keysym.sym;
                        char w = static_cast<char>(a);
                        if(state == 0)
                        {
                            createName<<w;
                        }
                        else if(state == 1)
                        {
                            createPassword<<w;
                        }
                        else
                        {
                            createDate<<w;
                        }
                        break;
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
                        quit = 1;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    //juste pour voir ou est quoi
                    //std::cout<<event.button.x<<" "<<event.button.y<<std::endl;
                    if(event.button.x >400 && event.button.x <548 && event.button.y >400 && event.button.y <424)
                    {
                        //ici mettre le debut du jeu avec serv
                        std::cout<<"Start";
                        paquet.clear();
                        action = 1;
                        paquet << action << LOGIN;
                        socket.send(paquet);
                        paquet.clear();
                        thread.launch();
                        page = 4;
                    }
                    else if(event.button.x >400 && event.button.x <539 && event.button.y >432 && event.button.y <456)
                    {
                        //aller au deck
                        std::cout<<"Deck";
                        quit = 1;
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
                        quit =1;
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
