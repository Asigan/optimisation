//
// Created by titou on 20/04/2022.
//

#ifndef OPTIMISATION_INTERFACE_H
#define OPTIMISATION_INTERFACE_H


#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;


class Interface{
public:
    Interface(vector<Client> clients) {
        setMinMaxs(clients);
        widthMap = ((double)(xMax - xMin))*(1+OFFSET*2);
        heightMap = ((double)(yMax - yMin))*(1+OFFSET*2);
        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            cout << "SDL could not initialize! SDL_Error" <<  SDL_GetError() << endl;
        } else {
            //Create window
            window = SDL_CreateWindow("Solution actuelle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                      SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            }
            else{

                window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                SDL_SetRenderDrawColor( window_renderer, 120, 100, 110, 255 );
                SDL_RenderClear( window_renderer );
                // Render the rect to the screen
                SDL_RenderPresent(window_renderer);
            }
        }
        if ( TTF_Init() < 0 ) {
            cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
        }

        font = TTF_OpenFont("../resources/bahnschrift.ttf", 15);
        if ( !font ) {
            cout << "Failed to load font: " << TTF_GetError() << endl;
        }
    }

    ~Interface(){
        TTF_CloseFont( font );
        TTF_Quit();
        //Destroy window
        SDL_DestroyWindow( window );

        //Quit SDL subsystems
        SDL_Quit();
    }
    void afficher(Solution s){
        tournees = s.getTournees();
        SDL_SetRenderDrawColor( window_renderer, 120, 100, 110, 255 );
        SDL_RenderClear( window_renderer );

        clients = tournees.begin()->getClients();
        int clientBefore;

        int couleur[] = {10, 10, 10};
        int couleur_a_modifier = 0;
        int interval_couleurs = (245.0*3.0)/tournees.size();
        SDL_Color color_link;
        for(auto tournee = tournees.begin(); tournee != tournees.end(); ++tournee){
            vector<int> clientsTournee = tournee->returnTournee();
            clientBefore = -1;

            color_link.r = couleur[0];
            color_link.g = couleur[1];
            color_link.b = couleur[2];
            for(auto client = clientsTournee.begin(); client != clientsTournee.end(); ++client){
                if(clientBefore != -1){
                    drawLink(clients[*client], clients[clientBefore], color_link);
                }
                clientBefore = *client;
            }
            drawLink(clients[clientBefore], clients[0], color_link);
            if(couleur[couleur_a_modifier] + interval_couleurs > 255){
                couleur[couleur_a_modifier] = 10;
                couleur_a_modifier++;
            }
            couleur[couleur_a_modifier] += interval_couleurs;
            for(auto client = clientsTournee.begin(); client != clientsTournee.end(); ++client) {
                drawClient(clients[*client]);
            }
        }
        writeText(("Nombre de camions : " + to_string(tournees.size())
        + " | Distance totale : " + to_string(s.getDistance())).c_str(), 0, 0);
        SDL_RenderPresent(window_renderer);
        SDL_Delay( 10000 );
    }



private:
    // Variables pour la gestion de fenêtre
    SDL_Window* window = NULL;
    SDL_Renderer *window_renderer;
    const int SCREEN_HEIGHT = 750;
    const int SCREEN_WIDTH = 750;

    // variables TTF font
    TTF_Font* font;

    // Variables de calcul de positions
    const double OFFSET = 0.2;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    double widthMap;
    double heightMap;
    vector<Client> clients;
    vector<Tournee> tournees;

    void setMinMaxs(vector<Client> clients){
        xMin = clients[0].getX();
        xMax = clients[0].getX();
        yMin = clients[0].getY();
        yMax = clients[0].getY();
        int tmp;
        for(auto c = clients.begin()+1; c != clients.end(); ++c){
            tmp = c->getX();
            if(tmp < xMin) {
                xMin = tmp;
            }
            else if(tmp > xMax){
                xMax = tmp;
            }

            tmp = c->getY();
            if(tmp < yMin){
                yMin = tmp;
            }
            else if(tmp > yMax){
                yMax = tmp;
            }
        }
    }

    void drawClient(Client c){
        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor( window_renderer, 100, 100, 255, 255 );


        SDL_Rect r;
        r.x = convertXClientToXWindow((double)c.getX());
        r.y = convertYClientToYWindow((double)c.getY());
        r.w = (SCREEN_WIDTH/widthMap)*(1.0-OFFSET);
        r.h = (SCREEN_HEIGHT/heightMap)*(1.0-OFFSET);
        if(c.getIndex() == 0){
            SDL_SetRenderDrawColor( window_renderer, 255, 50, 50, 255 );
            r.w *= 2;
            r.h *= 2;
        }
        // Render rect
        SDL_RenderFillRect( window_renderer, &r);

        writeText(to_string(c.getIndex()).c_str(), r.x, r.y);

    }
    double convertXClientToXWindow(double x){
        return (x/widthMap + OFFSET/2)*SCREEN_WIDTH;
    }
    double convertYClientToYWindow(double y){
        return (y/heightMap + OFFSET/2)*SCREEN_HEIGHT;
    }

    void writeText(const char* text, int posX, int posY){
        SDL_Color color = { 210, 200, 200 };

        SDL_Surface* text_surface = TTF_RenderText_Solid( font, text, color );
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(window_renderer, text_surface);
        SDL_Rect dest = { posX, posY, text_surface->w, text_surface->h };

        SDL_RenderCopy( window_renderer, text_texture, NULL, &dest );
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    void drawLink(Client c1, Client c2, SDL_Color color){
        SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, 125);
        SDL_RenderDrawLine(window_renderer, convertXClientToXWindow(c1.getX()), convertYClientToYWindow(c1.getY()),
                           convertXClientToXWindow(c2.getX()), convertYClientToYWindow(c2.getY()));
        SDL_RenderDrawLine(window_renderer, convertXClientToXWindow(c1.getX())+1, convertYClientToYWindow(c1.getY())+1,
                           convertXClientToXWindow(c2.getX())+1, convertYClientToYWindow(c2.getY()))+1;
    }
};

#endif //OPTIMISATION_INTERFACE_H
