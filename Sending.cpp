#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include<iostream>

int SCRWIDTH=700,SCRHEIGHT=700;

class setpos
{
public:

  void dis(int i,std::string c,int R,int G,int B,int A)
    {

        font1.loadFromFile("Font/Best.ttf");

        temp[i].setString(c);
        temp[i].setFont(font1);
        temp[i].setCharacterSize(40);
        temp[i].setPosition(sf::Vector2f(SCRWIDTH/3.0f,(SCRHEIGHT/4.0f)+i*60));
        temp[i].setStyle(sf::Text::Italic);
        temp[i].setOutlineThickness(2);
        temp[i].setOutlineColor(sf::Color::Blue);
        temp[i].setColor(sf::Color(R,G,B,A));
    }

    private:
    sf::Font font1;

    public:
    sf::Text temp[10];
}pos,loading1;


int main(){
  sf::RenderWindow windownew(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "AI Chess");

    windownew.setFramerateLimit(30);

  sf::Event eventnew;

 sf::Texture l,t;
   l.loadFromFile("Images/loading1.png");
   t.loadFromFile("Images/9.jpg");

   sf::IntRect crop(0, 0, 700, 40);
  sf::Sprite sprite(l,crop),s(t);

  sf::Music music[7];
  music[0].openFromFile("Sounds/theme.ogg");
  music[1].openFromFile("Sounds/menu.wav");
  music[2].openFromFile("Sounds/click.wav");
  music[3].openFromFile("Sounds/invalid.wav");
  music[4].openFromFile("Sounds/eating.wav");
  music[5].openFromFile("Sounds/checkmate.wav");
  music[6].openFromFile("Sounds/exit.wav");

int loading=0;
bool multiplayer_mode;

pos.dis(0,"Play as White",0,255,0,255);
pos.dis(1,"Multi Player",0,255,0,255);
pos.dis(2,"Credit",0,255,0,255);
pos.dis(3,"Exit",0,255,0,255);


   while (windownew.isOpen())
    {
    sf::Vector2i MousePosition = sf::Mouse::getPosition(windownew);

        while (windownew.pollEvent(eventnew))
        {


            if( eventnew.type == sf::Event::Closed )
                windownew.close();
            if((eventnew.type==sf::Event::KeyPressed) and (eventnew.key.code== sf::Keyboard::Escape))
               windownew.close();
                windownew.draw(s);
                if(loading==0)
                {
                    music[0].play();
                    for(int k=0;k<15;k++)
                    {
                        sprite.setTextureRect(crop);
                        windownew.draw(sprite);

                        windownew.display();
                        sf::sleep(sf::seconds(0.25));
                    crop.height+=50;
                    }
                    loading=1;

                    windownew.draw(s);
                    SCRHEIGHT=2400; SCRWIDTH=400;
                    loading1.dis(0,"Wait             Loading.....",255,255,255,255);
                    windownew.draw(loading1.temp[0]);
                    windownew.display();

                    windownew.clear();

                    sf::sleep(sf::seconds(2));
                    for(int j=0;j<4;j++)
                    {windownew.draw(s);windownew.draw(pos.temp[j]);windownew.display();sf::sleep(sf::seconds(1));}


                }

                if(loading==1)
                {
                    for(int j=0;j<4;j++)
                    {windownew.draw(pos.temp[j]);}
                    windownew.display();
                    loading=2;
                }

                if(pos.temp[0].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR PLASY AS WHITE
                {
                    music[1].play();
                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos.temp[j].setString("");

                    pos.dis(0,"Play as White",255,255,255,255);
                    pos.dis(1,"Multi Player",0,255,0,255);
                    pos.dis(2,"Credit",0,255,0,255);
                    pos.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos.temp[j]);}

                    windownew.display();

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        windownew.clear(sf::Color::Black);

                        multiplayer_mode=false;


/*
                        sf::RenderWindow window(sf::VideoMode(700, 700), "Single Player");
                        window.clear();
                        sf::Event event;
                        while (window.isOpen())
                        {
                        sf::Vector2i pos = sf::Mouse::getPosition(window);

                            while (window.pollEvent(event))
                            {
                                if( event.type == sf::Event::Closed )
                                window.close();
                                ///SINGLE PLAYER GOES HERE
                                ///
                                ///
                                ///
                            }
                        }*/


                    }
                    break;

              }
              else if(pos.temp[1].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR Multi Player
              {
                  music[1].play();

                    SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos.temp[j].setString("");

                    pos.dis(0,"Play as White",0,255,0,255);
                    pos.dis(1,"Multi Player",255,255,255,255);
                    pos.dis(2,"Credit",0,255,0,255);
                    pos.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos.temp[j]);}

                    windownew.display();
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        multiplayer_mode=true;

                        sf::RenderWindow window(sf::VideoMode(700, 700), "Multi Player");
                        window.clear();
                        sf::Event event;
                        while (window.isOpen())
                        {
                        sf::Vector2i pos = sf::Mouse::getPosition(window);

                            while (window.pollEvent(event))
                            {
                                if( event.type == sf::Event::Closed )
                                window.close();
                                ///MULTI PLAYER CODE GOES HER
                                std::cout<<multiplayer_mode<<std::endl;
                                ///
                                ///
                                ///
                                ///
                            }

                        }
                    }
                    break;
              }


              else if(pos.temp[2].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR CREDIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos.temp[j].setString("");

                    pos.dis(0,"Play as White",0,255,0,255);
                    pos.dis(1,"Multi Player",0,255,0,255);
                    pos.dis(2,"Credit",255,255,255,255);
                    pos.dis(3,"Exit",0,255,0,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos.temp[j]);}

                    windownew.display();
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        SCRWIDTH=200;
                        windownew.clear();

                        for(int j=0;j<10;j++)
                        pos.temp[j].setString("");

                        pos.dis(0,"Created By: ",255,255,0,255);
                        pos.dis(1,"Nischal Maharjan (421)",0,255,0,255);
                        pos.dis(2,"Sangam Man Buddhacharya (438)",0,255,255,255);
                        pos.dis(3,"Shiva Bhandari (442)",200,200,255,255);
                        pos.dis(4,"Sunil Dhakal (447)",255,255,255,255);

                        for(int j=0;j<5;j++)
                        {windownew.draw(s);windownew.draw(pos.temp[j]);windownew.display();sf::sleep(sf::seconds(2));}
                         for(int j=0;j<5;j++)
                        {windownew.draw(pos.temp[j]);}
                            windownew.display();
                    }
                    break;
              }
              else if(pos.temp[3].getGlobalBounds().contains(MousePosition.x,MousePosition.y))//MOUSE FOR EXIT
              {
                  music[1].play();
                  SCRWIDTH=700;SCRHEIGHT=700;
                    for(int j=0;j<10;j++)
                    pos.temp[j].setString("");

                    pos.dis(0,"Play as White",0,255,0,255);
                    pos.dis(1,"Multi Player",0,255,0,255);
                    pos.dis(2,"Credit",0,255,0,255);
                    pos.dis(3,"Exit",255,255,255,255);

                    for(int j=0;j<4;j++)
                    {windownew.draw(pos.temp[j]);}

                    windownew.display();
                  if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        music[2].play();
                        music[6].play();
                        sf::sleep(sf::seconds(2));
                        windownew.close();
                    }
                    break;
              }
          }

    }
}
