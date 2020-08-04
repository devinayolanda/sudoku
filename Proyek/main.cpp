#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "backtracking.h"
using namespace std;

sf::RenderWindow window(sf::VideoMode(700, 700), "Sudoku");

//Texture
sf::Texture text_background;
sf::Texture text_btnPlay;
sf::Texture text_btnRandom;
sf::Texture text_btnSpecial;
sf::Texture text_btnExit;
sf::Texture text_btnMenu;
sf::Texture text_square[9][9];
sf::Texture text_temp;
sf::Texture text_red;
sf::Texture text_angka[10];
sf::Texture text_pause;
sf::Texture text_btnResume;
sf::Texture text_btnReset;
sf::Texture text_btnBack;
sf::Texture text_title;
sf::Texture text_done;
sf::Texture text_finish;
sf::Texture text_btnfinish;

//Sprite
sf::Sprite spr_background;
sf::Sprite spr_btnPlay;
sf::Sprite spr_btnRandom;
sf::Sprite spr_btnSpecial;
sf::Sprite spr_btnExit;
sf::Sprite spr_btnMenu;
sf::Sprite spr_square[9][9];
sf::Sprite spr_temp;
sf::Sprite spr_red;
sf::Sprite spr_pause;
sf::Sprite spr_btnResume;
sf::Sprite spr_btnReset;
sf::Sprite spr_btnBack;
sf::Sprite spr_title;
sf::Sprite spr_done;
sf::Sprite spr_finish;
sf::Sprite spr_btnfinish;

//backtrack
backtrack h;

//file
fstream file;

void main(){
	goto home;

done:
	text_background.loadFromFile("Asset/game.png");
	spr_background.setTexture(text_background);

	text_finish.loadFromFile("Asset/finish.png");
	spr_finish.setTexture(text_finish);
	text_btnfinish.loadFromFile("Asset/btnfinish.png");
	spr_btnfinish.setTexture(text_btnfinish);
	spr_btnfinish.setPosition(270, 350);

	text_temp.loadFromFile("Asset/papan.png");
	spr_temp.setTexture(text_temp);
	spr_temp.setPosition(78,111);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if(spr_btnfinish.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					goto home;
				}
			}
		}
		window.clear();
		window.draw(spr_background);
		window.draw(spr_temp);
		window.draw(spr_finish);
		window.draw(spr_btnfinish);
		window.display();
	}

play:
	bool cekpause=false, cekklik=false, done=false, cekdone=false;
	int tempi, tempj, isi[9][9];

	text_background.loadFromFile("Asset/game.png");
	spr_background.setTexture(text_background);

	spr_title.setTexture(text_title);
	spr_title.setPosition(150, 25);

	spr_done.setTexture(text_done);
	spr_done.setPosition(78,58);

	//set square
	h.setmap();
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			isi[i][j] = h.getval(i,j);
			spr_square[i][j].setTexture(text_angka[isi[i][j]]);
			spr_square[i][j].setPosition((78+(61*j)),(111+(61*i)));
		}
	}

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				//ngecek yang lagi di klik
				for(int i=0; i<9; i++){
					for(int j=0; j<9; j++){
						if(spr_square[i][j].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !cekpause && isi && !cekdone){
							cekklik=true;
							spr_red.setTexture(text_red);
							spr_red.setPosition((spr_square[i][j].getPosition().x+0.3), (spr_square[i][j].getPosition().y+0.5));
							int a = h.getregion(i,j);
							int b = h.getval(i,j);
							h.safe(i, j, b, a);
							tempi=i; tempj=j;
						}
					}
				}

				//kalo mencet tombol menu
				if(spr_btnMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					cekpause=true;
					spr_pause.setTexture(text_pause);
					spr_btnResume.setTexture(text_btnResume);
					spr_btnResume.setPosition(220, 282);
					spr_btnReset.setTexture(text_btnReset);
					spr_btnReset.setPosition(320, 282);
					spr_btnBack.setTexture(text_btnBack);
					spr_btnBack.setPosition(420, 282);
				}

				if(spr_btnResume.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && cekpause){
					//resume
					cekpause=false;
				} else if (spr_btnReset.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && cekpause){
					//reset
					goto play;
				} else if (spr_btnBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && cekpause){
					//home
					goto home;
				}

				if(cekdone && !cekpause){
					cekdone=false;
				}

				//cek selesai
				if(spr_done.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !cekpause){
					if(h.cekplay()){
						done=true;
						cekdone=false;
						text_finish.loadFromFile("Asset/finish.png");
						spr_finish.setTexture(text_finish);
						text_btnfinish.loadFromFile("Asset/btnfinish.png");
						spr_btnfinish.setTexture(text_btnfinish);
						spr_btnfinish.setPosition(270, 350);
					} else {
						done=false;
						cekdone=true;
						text_finish.loadFromFile("Asset/wrong.png");
						spr_finish.setTexture(text_finish);
					}
				}

				if(done){
					if(spr_btnfinish.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !cekpause){
						goto home;
					}
				}
			}

			//ngecek inputan keyboard
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[1]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,1);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[2]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,2);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[3]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,3);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[4]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,4);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[5]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,5);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[6]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,6);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[7]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,7);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[8]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,8);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[9]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,9);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && !cekpause){
				spr_square[tempi][tempj].setTexture(text_angka[0]);
				spr_square[tempi][tempj].setPosition(spr_square[tempi][tempj].getPosition().x, spr_square[tempi][tempj].getPosition().y);
				h.in(tempi,tempj,0);
			}
		}

		window.clear();
		window.draw(spr_background);
		if(!cekpause){
			window.draw(spr_done);
		}
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				window.draw(spr_square[i][j]);
			}
		}
		if(!cekpause && cekklik){
			window.draw(spr_red);
		}
		window.draw(spr_temp);
		window.draw(spr_btnMenu);
		if(cekpause){
			window.draw(spr_pause);
			window.draw(spr_btnResume);
			window.draw(spr_btnReset);
			window.draw(spr_btnBack);
		}
		if(cekdone){
			window.draw(spr_finish);
		}
		if(done){
			window.draw(spr_finish);
			window.draw(spr_btnfinish);
		}
		window.draw(spr_title);
		window.display();
	}

random:
	h.setStatus();
	int ceksoal[9][9];
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			ceksoal[i][j]=0;
		}
	}
	h.setmap();
	if(!h.solve(window, 2, ceksoal)){
		goto home;
	} else {
		goto done;
	}

solve:
	h.setStatus();
	file.open("file.txt", ios::in);
	int a[9][9], ceksoal1[9][9];
	if(file.is_open()){
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				file >> a[i][j];
				if(a[i][j]!=0){
					ceksoal1[i][j]=1;
				} else {
					ceksoal1[i][j]=0;
				}
			}
		}
	}
	file.close();
	h.setmap(a);
	if(h.solve(window, 3, ceksoal1)==false){
		goto home;
	} else {
		goto done;
	}

home:
	text_background.loadFromFile("Asset/home.png");
	spr_background.setTexture(text_background);

	text_btnPlay.loadFromFile("Asset/btnplay.png");
	spr_btnPlay.setTexture(text_btnPlay);
	spr_btnPlay.setPosition(250,350);

	text_btnRandom.loadFromFile("Asset/btnrandom.png");
	spr_btnRandom.setTexture(text_btnRandom);
	spr_btnRandom.setPosition(250,420);

	text_btnSpecial.loadFromFile("Asset/btnspecial.png");
	spr_btnSpecial.setTexture(text_btnSpecial);
	spr_btnSpecial.setPosition(250,490);

	text_btnExit.loadFromFile("Asset/btnexit.png");
	spr_btnExit.setTexture(text_btnExit);
	spr_btnExit.setPosition(250,560);

	text_temp.loadFromFile("Asset/garis.png");
	spr_temp.setTexture(text_temp);
	spr_temp.setPosition(77, 114);

	text_btnMenu.loadFromFile("Asset/menu.png");
	spr_btnMenu.setTexture(text_btnMenu);
	spr_btnMenu.setPosition(600, 20);

	text_red.loadFromFile("Asset/red.png");

	text_done.loadFromFile("Asset/done.png");

	//angka
	text_angka[0].loadFromFile("Asset/0.png");
	text_angka[1].loadFromFile("Asset/1.png");
	text_angka[2].loadFromFile("Asset/2.png");
	text_angka[3].loadFromFile("Asset/3.png");
	text_angka[4].loadFromFile("Asset/4.png");
	text_angka[5].loadFromFile("Asset/5.png");
	text_angka[6].loadFromFile("Asset/6.png");
	text_angka[7].loadFromFile("Asset/7.png");
	text_angka[8].loadFromFile("Asset/8.png");
	text_angka[9].loadFromFile("Asset/9.png");

	//pause
	text_pause.loadFromFile("Asset/pause.png");
	text_btnResume.loadFromFile("Asset/resume.png");
	text_btnReset.loadFromFile("Asset/reset.png");
	text_btnBack.loadFromFile("Asset/back.png");

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				//ngecek pilihan game
				if(spr_btnPlay.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					text_title.loadFromFile("Asset/titleplay.png");
					goto play;
				} else if (spr_btnRandom.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					h.setMouse(event.mouseButton.x, event.mouseButton.y);
					goto random;
				} else if (spr_btnSpecial.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					goto solve;
				} else if (spr_btnExit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
					window.close();
				}
			}
		}
		window.clear();
		window.draw(spr_background);
		window.draw(spr_btnPlay);
		window.draw(spr_btnRandom);
		window.draw(spr_btnSpecial);
		window.draw(spr_btnExit);
		window.display();
	}
}