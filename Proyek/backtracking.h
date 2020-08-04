#include <iostream>
#include<Windows.h>

using namespace std;

class backtrack{
private:
	int region[9][9], board[9][9];
	int posX, posY;
	bool status;
	sf::Event event;
	
	sf::Sprite spr_square[9][9];
	sf::Sprite spr_background;
	sf::Sprite spr_temp;
	sf::Sprite spr_title;
	sf::Sprite spr_btnBack;

	sf::Texture text_angka[9][9];
	sf::Texture text_background;
	sf::Texture text_temp;
	sf::Texture text_title;
	sf::Texture text_btnBack;
public:
	void setmap(){
		for(int i = 0; i<9; i++){
			for(int j=0; j<9; j++){
				board[i][j] = 0;
			}
		}
	}
	backtrack(){
		status=false;
		for(int i = 0; i<9; i++){
			for(int j=0; j<9; j++){
				board[i][j] = 0;
			}
		}
		//set region
		region[0][0] = 1;
		region[0][1] = 1;
		region[0][2] = 2;
		region[0][3] = 2;
		region[0][4] = 2;
		region[0][5] = 2;
		region[0][6] = 2;
		region[0][7] = 3;
		region[0][8] = 3;

		region[1][0] = 1;
		region[1][1] = 1;
		region[1][2] = 1;
		region[1][3] = 2;
		region[1][4] = 2;
		region[1][5] = 2;
		region[1][6] = 3;
		region[1][7] = 3;
		region[1][8] = 3;

		region[2][0] = 4;
		region[2][1] = 1;
		region[2][2] = 1;
		region[2][3] = 1;
		region[2][4] = 2;
		region[2][5] = 3;
		region[2][6] = 3;
		region[2][7] = 3;
		region[2][8] = 6;

		region[3][0] = 4;
		region[3][1] = 4;
		region[3][2] = 1;
		region[3][3] = 5;
		region[3][4] = 5;
		region[3][5] = 5;
		region[3][6] = 3;
		region[3][7] = 6;
		region[3][8] = 6;

		region[4][0] = 4;
		region[4][1] = 4;
		region[4][2] = 4;
		region[4][3] = 5;
		region[4][4] = 5;
		region[4][5] = 5;
		region[4][6] = 6;
		region[4][7] = 6;
		region[4][8] = 6;

		region[5][0] = 4;
		region[5][1] = 4;
		region[5][2] = 7;
		region[5][3] = 5;
		region[5][4] = 5;
		region[5][5] = 5;
		region[5][6] = 9;
		region[5][7] = 6;
		region[5][8] = 6;

		region[6][0] = 4;
		region[6][1] = 7;
		region[6][2] = 7;
		region[6][3] = 7;
		region[6][4] = 8;
		region[6][5] = 9;
		region[6][6] = 9;
		region[6][7] = 9;
		region[6][8] = 6;

		region[7][0] = 7;
		region[7][1] = 7;
		region[7][2] = 7;
		region[7][3] = 8;
		region[7][4] = 8;
		region[7][5] = 8;
		region[7][6] = 9;
		region[7][7] = 9;
		region[7][8] = 9;

		region[8][0] = 7;
		region[8][1] = 7;
		region[8][2] = 8;
		region[8][3] = 8;
		region[8][4] = 8;
		region[8][5] = 8;
		region[8][6] = 8;
		region[8][7] = 9;
		region[8][8] = 9;

		//background
		text_background.loadFromFile("Asset/game.png");
		spr_background.setTexture(text_background);

		//garis kuning
		text_temp.loadFromFile("Asset/garis.png");
		spr_temp.setTexture(text_temp);
		spr_temp.setPosition(77, 114);

		//pause
		text_btnBack.loadFromFile("Asset/back2.png");
		spr_btnBack.setTexture(text_btnBack);
		spr_btnBack.setPosition(600, 20);

		posX=0; posY=0;
	}
	~backtrack(){ }
	void setmap(int brd[9][9]){
		for(int i = 0; i<9; i++){
			for(int j=0; j<9; j++){
				board[i][j] = brd[i][j];
			}
		}
	}
	void in(int row, int col, int isi){
		board[row][col] = isi;
	}
	int getregion(int row, int col){
		int regnow = region[row][col];
		return regnow;
	}
	int getval(int row, int col){
		int val = board[row][col];
		return val;
	}
	bool safeplus(int row, int col, int isi){
		//cek row & col
		for (int i = 0; i < 9; i++){
			if (board[i][col] == isi){
				return false;
			}
		}
		for (int i = 0; i < 9; i++){
			if (board[row][i] == isi){
				return false;
			}
		}
		return true;
	}
	bool saferegion(int row, int col, int isi, int regnow){
		//cek sesuai region
		if (regnow == 1){
			if (board[0][0] == isi || board[0][1] == isi || board[1][0] == isi || board[1][1] == isi || board[1][2] == isi || board[2][1] == isi || board[2][2] == isi || board[2][3] == isi || board[3][2] == isi){
				return false;
			}
		}
		else if (regnow == 2){
			if (board[0][2] == isi || board[0][3] == isi || board[0][4] == isi || board[0][5] == isi || board[0][6] == isi || board[1][3] == isi || board[1][4] == isi || board[1][5] == isi || board[2][4] == isi){
				return false;
			}
		}
		else if (regnow == 3){
			if (board[0][7] == isi || board[0][8] == isi || board[1][6] == isi || board[1][7] == isi || board[1][8] == isi || board[2][5] == isi || board[2][6] == isi || board[2][7] == isi || board[3][6] == isi){
				return false;
			}
		}
		else if (regnow == 4){
			if (board[2][0] == isi || board[3][0] == isi || board[3][1] == isi || board[4][0] == isi || board[4][1] == isi || board[4][2] == isi || board[5][0] == isi || board[5][1] == isi || board[6][0] == isi){
				return false;
			}
		}
		else if (regnow == 5){
			if (board[3][3] == isi || board[3][4] == isi || board[3][5] == isi || board[4][3] == isi || board[4][4] == isi || board[4][5] == isi || board[5][3] == isi || board[5][4] == isi || board[5][5] == isi){
				return false;
			}
		}
		else if (regnow == 6){
			if (board[2][8] == isi || board[3][7] == isi || board[3][8] == isi || board[4][6] == isi || board[4][7] == isi || board[4][8] == isi || board[5][7] == isi || board[5][8] == isi || board[6][8] == isi){
				return false;
			}
		}
		else if (regnow == 7){
			if (board[5][2] == isi || board[6][1] == isi || board[6][2] == isi || board[6][3] == isi || board[7][0] == isi || board[7][1] == isi || board[7][2] == isi || board[8][0] == isi || board[8][1] == isi){
				return false;
			}
		}
		else if (regnow == 8){
			if (board[6][4] == isi || board[7][3] == isi || board[7][4] == isi || board[7][5] == isi || board[8][2] == isi || board[8][3] == isi || board[8][4] == isi || board[8][5] == isi || board[8][6] == isi){
				return false;
			}
		}
		else if (regnow == 9){
			if (board[5][6] == isi || board[6][5] == isi || board[6][6] == isi || board[6][7] == isi || board[7][6] == isi || board[7][7] == isi || board[7][8] == isi || board[8][7] == isi || board[8][8] == isi){
				return false;
			}
		}
		return true;
	}
	bool safe(int row, int col, int isi, int regnow){
		if (safeplus(row, col, isi) && saferegion(row, col, isi, regnow)){
			return true;
		}
		else {
			return false;
		}
	}
	void setGambar(int x, int row, int col, int cek){
		if(cek==0){
			if(x == 1){
				text_angka[row][col].loadFromFile("Asset/1.png");
			} else if(x == 2){
				text_angka[row][col].loadFromFile("Asset/2.png");
			} else if(x == 3){
				text_angka[row][col].loadFromFile("Asset/3.png");
			} else if(x == 4){
				text_angka[row][col].loadFromFile("Asset/4.png");
			} else if(x == 5){
				text_angka[row][col].loadFromFile("Asset/5.png");
			} else if(x == 6){
				text_angka[row][col].loadFromFile("Asset/6.png");
			} else if(x == 7){
				text_angka[row][col].loadFromFile("Asset/7.png");
			} else if(x == 8){
				text_angka[row][col].loadFromFile("Asset/8.png");
			} else if(x == 9){
				text_angka[row][col].loadFromFile("Asset/9.png");
			} else if(x == 0){
				text_angka[row][col].loadFromFile("Asset/0.png");
			}
		} else {
			if(x == 1){
				text_angka[row][col].loadFromFile("Asset/1s.png");
			} else if(x == 2){
				text_angka[row][col].loadFromFile("Asset/2s.png");
			} else if(x == 3){
				text_angka[row][col].loadFromFile("Asset/3s.png");
			} else if(x == 4){
				text_angka[row][col].loadFromFile("Asset/4s.png");
			} else if(x == 5){
				text_angka[row][col].loadFromFile("Asset/5s.png");
			} else if(x == 6){
				text_angka[row][col].loadFromFile("Asset/6s.png");
			} else if(x == 7){
				text_angka[row][col].loadFromFile("Asset/7s.png");
			} else if(x == 8){
				text_angka[row][col].loadFromFile("Asset/8s.png");
			} else if(x == 9){
				text_angka[row][col].loadFromFile("Asset/9s.png");
			}
		}
	}
	void print(int cek[9][9]){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				setGambar(board[i][j], i, j, cek[i][j]);
				spr_square[i][j].setTexture(text_angka[i][j]);
				spr_square[i][j].setPosition((78+(61*j)),(111+(61*i)));
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool available(int &row, int &col){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (board[i][j] == 0){
					row = i;
					col = j;
					return true;
				}
			}
		}
		return false;
	}
	void setStatus(){
		status=true;
	}
	bool solve(sf::RenderWindow& window, int game, int cek[9][9]){
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//tombol back
			if(event.type==sf::Event::MouseButtonReleased)
				if(event.mouseButton.button == sf::Mouse::Left){
					if(spr_btnBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
							status=false;
							return false;
					}
				}
		}

		if(!status)
				return false;

		int row, col;
		if(!available(row, col)){
			return false;
		}

		if(game==2){
			text_title.loadFromFile("Asset/titlerandom.png");
			spr_title.setTexture(text_title);
			spr_title.setPosition(150, 25);
		} else {
			text_title.loadFromFile("Asset/titlespecial.png");
			spr_title.setTexture(text_title);
			spr_title.setPosition(150, 25);
		}

		int regnow = region[row][col];
		for (int isi = 1; isi <= 9; isi++){
			if (safe(row, col, isi, regnow)){
				board[row][col] = isi;
				
				system("CLS");
				print(cek);

				window.clear();
				window.draw(spr_background);
				window.draw(spr_title);
				for(int i=0; i<9; i++){
					for(int j=0; j<9; j++){
						window.draw(spr_square[i][j]);
					}
				}
				window.draw(spr_temp);
				window.draw(spr_btnBack);
				window.display();

				if (solve(window, game, cek) && status){ //dicek kalo bisa
					return true;
				}

				if(!status)
					return false;

				bool full=true;
				for (int i = 0; i < 9; i++){
					for (int j = 0; j < 9; j++){
						if (board[i][j] == 0){
							full=false;
						}
					}
				}

				if(!full){
					board[row][col] = 0; //dikembalikan jadi 0 karena ndak bisa dilanjutkan & masih belum terisi semua
					setGambar(0, row, col, cek[row][col]);
					spr_square[row][col].setTexture(text_angka[row][col]);
					spr_square[row][col].setPosition((78+(61*col)),(111+(61*row)));
				} else {
					return true;
				}
			}
		}
		return false;
	}
	void setMouse(int x,int y){
		posX=x; posY=y;
	}
	int getX(){
		return posX;
	}
	int getY(){
		return posY;
	}
	bool safezero(int row, int col){
		if(board[row][col]==0){
			return false;
		}
		return true;
	}
	bool safehorizontal(int row, int col){
		for(int i=0; i<9; i++){
			if(i!=row){
				if(board[i][col]==board[row][col]){
					return false;
				}
			}
		}
		return true;
	}
	bool safevertical(int row, int col){
		for(int i=0; i<9; i++){
			if(i!=col){
				if(board[row][i]==board[row][col]){
					return false;
				}
			}
		}
		return true;
	}
	bool safereg(int row, int col){
		int cek=true;
		int reg = getregion(row, col);
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				if(i!=row && j!=col){
					if(region[i][j]==reg){
						if(board[i][j]==board[row][col]){
							cek=false;
							break;
						}
					}
				}
			}
			if(!cek)
				break;
		}
		if(cek){
			return true;
		} else {
			return false;
		}
	}
	bool cekplay(){
		bool cek=true;
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				if(safezero(i,j) && safevertical(i,j) && safehorizontal(i,j) && safereg(i,j)){
					cek=true;
				} else {
					cek=false;
					break;
				}
			}
			if(!cek)
				break;
		}
		if(cek){
			return true;
		} else {
			return false;
		}
	}
};