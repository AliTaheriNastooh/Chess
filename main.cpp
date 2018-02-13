#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include<cstdlib>
#include <windows.h>
#include<ctime>
using namespace std;



void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}


void print(int i , int j , char c,int color){
gotoxy(j,i);
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, color);
cout<<c;
}


void print(int i , int j , string& c,int color){
gotoxy(j,i);
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, color);
cout<<c;
}



class board;
class piece;
enum colorPieces{black,white};
class king;
class bishop;
class knight;
class pawn;
class rook;
class queen;
class chesspieces;
class board;

class ui{
public:
	board* board1;
	ui();
	string temp2;
	string temp;
	pair<pair<char,int>,pair<char,int>> tmp;
	 pair<pair<char,int>,pair<char,int>> get_choice(string s)
	{
		temp="                                                                 ";
		print(18,0,temp,15);
		print(19,0,temp,15);
		temp=s;
		temp+=":please enter your choice start movement piece of board: ";
		print(18,0,temp,15);
		cin>>tmp.first.first;
		cin>>tmp.first.second;
	    temp2=s;
		temp2+=":please enter your choice that distation piece of board: ";
		print(19,0,temp2,15);
		cin>>tmp.second.first;
		cin>>tmp.second.second;


		return tmp;
	}
	void print_string(string s){
	print(19,0,s,5);

	}
	void error(string s){
	print(20,0,s,4);
	Sleep(1000);
	s="                                             ";
	print(20,0,s,4);
	}
	void printBoard();

};


class piece{
public:
	chesspieces* mem;
	colorPieces color;
	pair<char ,int >coordinate;

};
class board{
public:
	static board* instance;
	//enum colorPiece1{black , white}color1;
	piece memboard[8][8];
	king* kb;
	rook* rb1;
	rook* rb2;
	queen* qb;
	pawn* pb1;
	pawn* pb2;
	pawn* pb3;
	pawn* pb4;
	pawn* pb5;
	pawn* pb6;
	pawn* pb7;
	pawn* pb8;
	knight* kb1;
	knight* kb2;
	bishop* bb1;
	bishop* bb2;
	king* kw;
	rook* rw1;
	rook* rw2;
	queen* qw;
	pawn* pw1;
	pawn* pw2;
	pawn* pw3;
	pawn* pw4;
	pawn* pw5;
	pawn* pw6;
	pawn* pw7;
	pawn* pw8;
	knight* kw1;
	knight* kw2;
	bishop* bw1;
	bishop* bw2;
	chesspieces* piecesBlack[16];
	chesspieces* piecesWhite[16];
	int nBlack;
	int nWhite;

private:
	board();

public:

	static board* getInstance(){
	if(instance==nullptr)
		instance=new board();
	return instance;
	}

	void initial_assign();
};
board* board::instance=nullptr;








class chesspieces{
public:
	board* board1;
	string name;
    colorPieces color;
	piece* position;
	virtual bool move(pair<char,int>dest)=0;
	void set_board(){
		board1=board::getInstance();
	}

};
class king:public chesspieces{
public:
	king(string s){
		name=s;
	}
	bool move(pair<char,int > dest){
		set_board();
		colorPieces colorme;
		if(dest.first>'h' || dest.first<'a')
			return false;
		if(dest.second>8 || dest.second<1)
			return false;
		if(abs(this->position->coordinate.first-dest.first)>=2 || abs(this->position->coordinate.second-dest.second)>=2 )
			return false;
		if(this->color==white)
		{
			if(abs(board1->piecesBlack[0]->position->coordinate.first-dest.first)<2 && abs(board1->piecesBlack[0]->position->coordinate.second-dest.second)<2 )
			{
				return false;
			}
		}
		else
		{
			if(abs(board1->piecesWhite[0]->position->coordinate.first-dest.first)<2 && abs(board1->piecesWhite[0]->position->coordinate.second-dest.second)<2 )
			{
				return false;
			}
		}
		return true;
	}

	~king(){
		if(position!=nullptr)
			delete position;
	}
};
class rook:public chesspieces{
public:
	rook(string s){
		name=s;
	}
	bool move(pair<char,int > dest)
	{
		set_board();
		if(board1->memboard[dest.second-1][dest.first-'a'].mem!= nullptr){
		if(this->color==board1->memboard[dest.second-1][dest.first-'a'].mem->color)
		{
			return false;
		}
		if(dest.first==this->position->coordinate.first  &&  dest.second==this->position->coordinate.second)
		{
			return false;
		}
		}
		if(dest.first==this->position->coordinate.first  || dest.second==this->position->coordinate.second )
		{
			if(dest.first==this->position->coordinate.first){
				for(int i=min(this->position->coordinate.second,dest.second)+1; i<max(this->position->coordinate.second,dest.second); i++){
					if(board1->memboard[i-1][dest.first-'a'].mem!=nullptr)
					{
						return false;
					}
				}
				return true;
			}
			else{
				for(int i=min(this->position->coordinate.first,dest.first)-'a'+1; i<max(this->position->coordinate.first,dest.first)-'a'; i++){
					if(board1->memboard[dest.second-1][i].mem!=nullptr)
					{
						return false;
					}
				}
				return true;

			}
		}
		return false;
	}
	~rook(){
		if(position!=nullptr)
			delete position;
	}
};
class queen:public chesspieces{
public:
	queen(string s){
		name=s;
	}

	bool move(pair<char,int > dest){
		set_board();
		if(board1->memboard[dest.second-1][dest.first-'a'].mem != nullptr){
		if(this->color==board1->memboard[dest.second-1][dest.first-'a'].mem->color)
		{
			return false;
		}
		if(dest.first==this->position->coordinate.first  &&  dest.second==this->position->coordinate.second)
		{
			return false;
		}
		}

		if(dest.first==this->position->coordinate.first  || dest.second==this->position->coordinate.second )
		{
			if(dest.first==this->position->coordinate.first){
				for(int i=min(this->position->coordinate.second,dest.second)+1; i<max(this->position->coordinate.second,dest.second); i++){
					if(board1->memboard[i-1][dest.first-'a'].mem!=nullptr)
					{
						return false;
					}
				}
				return true;
			}
			else{
				for(int i=min(this->position->coordinate.first,dest.first)-'a'+1; i<max(this->position->coordinate.first,dest.first)-'a'; i++){
					if(board1->memboard[dest.second-1][i].mem!=nullptr)
					{
						return false;
					}
				}
				return true;

			}
		}
		if(abs(dest.first-this->position->coordinate.first)==abs(dest.second-this->position->coordinate.second))
		{
			if((dest.first > this->position->coordinate.first && dest.second < this->position->coordinate.second) || (dest.first<this->position->coordinate.first && dest.second > this->position->coordinate.second))
			{
				int i,j;
				for( i=max(dest.first,this->position->coordinate.first)-'a'-1, j=min(dest.second,this->position->coordinate.second)+1;i>min(dest.first,this->position->coordinate.first)-'a';i--,j++)
				{
				if(board1->memboard[j-1][i].mem!=nullptr){
					return false;
				}

				}
			return true;
			}
			else
			{
				int i,j;
			for( i=min(dest.first,this->position->coordinate.first)-'a'+1, j=min(dest.second,this->position->coordinate.second)+1;j<max(dest.second,this->position->coordinate.second);i++,j++)
			{
				if(board1->memboard[j-1][i].mem!=nullptr){
					return false;
				}

			}
			return true;
			}
		}
		return false;

	}
	~queen(){
		if(position!=nullptr)
			delete position;
	}
};




class pawn:public chesspieces{
public:
	pawn(string s){
		name=s;
	}
	bool move(pair<char,int > dest){
		set_board();
		if(this->color==white){
		if(dest.second-2==this->position->coordinate.second  &&   dest.first==this->position->coordinate.first &&this->position->coordinate.second==2 &&board1->memboard[dest.second-1][dest.first-'a'].mem ==nullptr )
			return true;
		if(dest.second-1==this->position->coordinate.second  &&  dest.first+1==this->position->coordinate.first && board1->memboard[dest.second-1][dest.first-'a'].mem !=nullptr && board1->memboard[dest.second-1][dest.first-'a'].mem->color != this->color  )
			return true;
		if(dest.second-1==this->position->coordinate.second  &&   dest.first==this->position->coordinate.first && board1->memboard[dest.second-1][dest.first-'a'].mem ==nullptr )
			return true;
		if(dest.second-1==this->position->coordinate.second  &&  dest.first-1==this->position->coordinate.first && board1->memboard[dest.second-1][dest.first-'a'].mem->color != this->color && board1->memboard[dest.second-1][dest.first-'a'].mem !=nullptr)
			return true;
		}
		else{
		if(dest.second+2==this->position->coordinate.second  &&   dest.first==this->position->coordinate.first && this->position->coordinate.second==7 &&board1->memboard[dest.second-1][dest.first-'a'].mem ==nullptr )
			return true;
		if(dest.second+1==this->position->coordinate.second  &&  dest.first-1==this->position->coordinate.first && board1->memboard[dest.second-1][dest.first-'a'].mem !=nullptr&& board1->memboard[dest.second-1][dest.first-'a'].mem->color != this->color  )
			return true;
		if(dest.second+1==this->position->coordinate.second  &&   dest.first==this->position->coordinate.first && board1->memboard[dest.second-1][dest.first-'a'].mem ==nullptr )
			return true;
		if(dest.second+1==this->position->coordinate.second  &&  dest.first+1==this->position->coordinate.first&& board1->memboard[dest.second-1][dest.first-'a'].mem !=nullptr && board1->memboard[dest.second-1][dest.first-'a'].mem->color != this->color )
			return true;

		}
		return false;
	}
	~pawn(){
		if(position!=nullptr)
			delete position;
	}
};
class knight:public chesspieces{
public:
	knight(string s){
		name=s;
	}
	bool move(pair<char,int > dest)
	{
		set_board();

		if(board1->memboard[dest.second-1][dest.first-'a'].mem != nullptr){
		if(this->color==board1->memboard[dest.second-1][dest.first-'a'].mem->color)
		{
			return false;
		}
		if(dest.first==this->position->coordinate.first  &&  dest.second==this->position->coordinate.second)
		{
			return false;
		}
		}


		if(abs(dest.first-this->position->coordinate.first)==2 && abs(dest.second-this->position->coordinate.second)==1 && (board1->memboard[dest.second-1][dest.first-'a'].mem==nullptr || (board1->memboard[dest.second-1][dest.first-'a'].mem!=nullptr &&board1->memboard[dest.first][dest.second].mem->color!=this->color )))
		{
			return true;
		}
		if(abs(dest.second-this->position->coordinate.second)==2 && abs(dest.first-this->position->coordinate.first)==1 && (board1->memboard[dest.second-1][dest.first-'a'].mem==nullptr || (board1->memboard[dest.second-1][dest.first-'a'].mem->color!=this->color && board1->memboard[dest.second-1][dest.first-'a'].mem!=nullptr)))
		{
			return true;
		}
		return false;

	}
	~knight(){
		if(position!=nullptr)
			delete position;
	}
};
class bishop:public chesspieces{
public:
	bishop(string s){
		name=s;
	}
	bool move(pair<char,int > dest)
	{
		set_board();
		if(board1->memboard[dest.second-1][dest.first-'a'].mem!= nullptr){
		if(this->color==board1->memboard[dest.second-1][dest.first-'a'].mem->color)
		{
			return false;
		}
		if(dest.first==this->position->coordinate.first  &&  dest.second==this->position->coordinate.second)
		{
			return false;
		}
	}
		if(abs(dest.first-this->position->coordinate.first)==abs(dest.second-this->position->coordinate.second))
		{
			if((dest.first > this->position->coordinate.first && dest.second < this->position->coordinate.second) || (dest.first<this->position->coordinate.first && dest.second > this->position->coordinate.second))
			{
				int i,j;
				for( i=max(dest.first,this->position->coordinate.first)-'a'-1, j=min(dest.second,this->position->coordinate.second)+1;i>min(dest.first,this->position->coordinate.first)-'a';i--,j++)
				{
				if(board1->memboard[j-1][i].mem!=nullptr){
					return false;
				}

				}
			return true;
			}
			else
			{
				int i,j;
			for( i=min(dest.first,this->position->coordinate.first)-'a'+1, j=min(dest.second,this->position->coordinate.second)+1;j<max(dest.second,this->position->coordinate.second);i++,j++)
			{
				if(board1->memboard[j-1][i].mem!=nullptr){
					return false;
				}

			}
			return true;
			}
		}
		return false;
	}
	~bishop(){
		if(position!=nullptr)
			delete position;
	}
};

board::board(){
		 kb=new king("king black");
		 rb1=new rook("rook black1");
		 rb2=new rook("rook black2");
		 qb=new queen("queen black");
		 pb1=new pawn("pawn black1");
		 pb2=new pawn("pawn black2");
		 pb3=new pawn("pawn black3");
		 pb4=new pawn("pawn black4");
		 pb5=new pawn("pawn black5");
		 pb6=new pawn("pawn black6");
		 pb7=new pawn("pawn black7");
		 pb8=new pawn("pawn black8");
		 kb1=new knight("night black1");
		 kb2=new knight("night black1");
		 bb1=new bishop("bishop black1");
		 bb2=new bishop("bishop black2");
		 kw=new king("king white");
		 rw1=new rook("rook white1");;
		 rw2=new rook("rook white2");;
		 qw=new queen("queen white");
		 pw1=new pawn("pawn white1");;
		 pw2=new pawn("pawn white2");;
		 pw3=new pawn("pawn white3");;
		 pw4=new pawn("pawn white4");;
		 pw5=new pawn("pawn white5");;
		 pw6=new pawn("pawn white6");;
		 pw7=new pawn("pawn white7");
		 pw8=new pawn("pawn white8");;
		 kw1=new knight("night white1");
		 kw2=new knight("night white2");
		 bw1=new bishop("bishop white1");
		 bw2=new bishop("bishop white2");





		nBlack=16;
		nWhite=16;
		initial_assign();
		for(int i=0;i<8 ; i++){
			for(int j=0; j< 8 ;j++) {
				memboard[i][j].color= j%2? black : white;
				memboard[i][j].coordinate.second=i+1;
				memboard[i][j].coordinate.first=char('a'+j);
				switch(i){
				case 7:
					memboard[i][j].mem=piecesBlack[(j+4)%8];
					piecesBlack[(j+4)%8]->position=&memboard[i][j];
					piecesBlack[(j+4)%8]->color=black;

					break;
				case 6:
					memboard[i][j].mem=piecesBlack[j+8];
					piecesBlack[j+8]->position=&memboard[i][j];
					piecesBlack[j+8]->color=black;

					break;
				case 0:
					memboard[i][j].mem=piecesWhite[(j+4)%8];
					piecesWhite[(j+4)%8]->position=&memboard[i][j];
					piecesWhite[(j+4)%8]->color=white;
					//memboard[i][j].mem->color=white;
					break;
				case 1:
					memboard[i][j].mem=piecesWhite[j+8];
					piecesWhite[j+8]->position=&memboard[i][j];
					piecesWhite[j+8]->color=white;


					break;
				default:
					memboard[i][j].mem=nullptr;
					break;
				}


			}

		}



}


void board::initial_assign()
{
		piecesBlack[0]=kb;
		piecesBlack[1]=bb2;
		piecesBlack[2]=kb2;
		piecesBlack[3]=rb2;
		piecesBlack[4]=rb1;
		piecesBlack[5]=kb1;
		piecesBlack[6]=bb1;
		piecesBlack[7]=qb;
		piecesBlack[8]=pb1;
		piecesBlack[9]=pb2;
		piecesBlack[10]=pb3;
		piecesBlack[11]=pb4;
		piecesBlack[12]=pb5;
		piecesBlack[13]=pb6;
		piecesBlack[14]=pb7;
		piecesBlack[15]=pb8;

		piecesWhite[0]=kw;
		piecesWhite[1]=bw2;
		piecesWhite[2]=kw2;
		piecesWhite[3]=rw2;
		piecesWhite[4]=rw1;
		piecesWhite[5]=kw1;
		piecesWhite[6]=bw1;
		piecesWhite[7]=qw;
		piecesWhite[8]=pw1;
		piecesWhite[9]=pw2;
		piecesWhite[10]=pw3;
		piecesWhite[11]=pw4;
		piecesWhite[12]=pw5;
		piecesWhite[13]=pw6;
		piecesWhite[14]=pw7;
		piecesWhite[15]=pw8;



	}


void ui::printBoard(){
		for(int j=0 ; j<18 ; j+=2){
			for(int i=1 ; i<17 ; i+=1){
				print(i,j,179,2);
			}
		}

		for(int i=2 ; i<16 ; i+=2){
			for(int j=1 ; j<16 ; j+=2){

				print(i,j,196,2);
			}
			for(int j=2 ; j<16 ; j+=2){

				print(i,j,197,2);
			}
		}
		for(int j=0 ; j<17 ; j+=2){
				print(0,j,194,2);
			}
		for(int j=1 ; j<17 ; j+=2){
				print(0,j,196,2);
			}
		for(int j=0 ; j<17 ; j+=2){
				print(16,j,193,2);
			}
		for(int j=1 ; j<17 ; j+=2){
				print(16,j,196,2);
			}
		int c=1;
		for(int j=1 ; j<17 ; j+=2){
			print (17,j,96+c,2);
			c++;
		}
		 c=0;
		for(int i=15 ; i>0 ; i-=2){
			print (i,17,49+c,2);
			c++;
		}
		c=1;
		int c2=15;
		for(int i=0 ; i<8 ; i++)
		{
			c=1;
			for(int j=0 ; j<8 ; j++)
			{

				if(board1->memboard[i][j].mem!=nullptr)
				{
//					cout<<board1->memboard[i][j].mem->color;
					print(c2,c,board1->memboard[i][j].mem->name[0],(board1->memboard[i][j].mem->color)+14);
				}
				else{
					print(c2,c,' ',14);
				}
				c+=2;

			}
			c2-=2;
		}
	}

ui::ui(){
		board1=board::getInstance();

	}

void set_timerandom(){
time_t t;
time(&t);
srand(t);
}

int random(int start,int end){
	return(rand()%(end-start+1))+start;
}

class user{
public:
	string name;
	int id;
	virtual pair<pair<char,int>,pair<char,int>> get_choice()=0;
};

class person:public user{
	ui ui1;
	pair<pair<char,int>,pair<char,int>>tmp;
public:
	person(string s){
		name=s;
		//id=random(0,3000);
	}
	pair<pair<char,int>,pair<char,int>> get_choice(){

		while(1){
		 tmp=ui1.get_choice(name);
		 if(tmp.first.first>'h' || tmp.first.second>8 ||tmp.first.second<0 ||tmp.first.first<'a'){
			continue;
		 }
		 if(tmp.second.first>'h' || tmp.second.second>8 ||tmp.second.second<0 ||tmp.second.first<'a'){
			continue;
		 }
		 break;
		}
		return tmp;
	}
};


class brain:public user{};

class manage{
public:
	ui ui1;
	user* user1;
	user* user2;
	board* board1;
	manage(user* us1,user* us2){
		user1=us1;
		user2=us2;
		board1=board::getInstance();
	}
	void start(){
		ui1.printBoard();
		int counter=1;
		int number_user;
		int flag=1;
		colorPieces color2;
		chesspieces* tmp2;
		pair<pair<char,int>,pair<char,int>> choice1;
		pair<pair<char,int>,pair<char,int>> choice2;
		while(counter){
			counter++;
			number_user=counter%2;
			while(flag){
				//cout in ui for user
				if(number_user)
					choice1=user2->get_choice();
				else
					choice1=user1->get_choice();
				if(!validation(choice1,number_user)){
					ui1.error("you choose invalid choice");
					continue;
				}
				tmp2=board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem;
				color2=board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem->color;
				board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem=nullptr;
				if(!check(color2))
				{
					/////
					board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem=tmp2;
					break;
				}
				else{
					ui1.error("you check and dont jump this chesspiece");
				}
			}

			if(board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem!= nullptr){

				if(board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem->color==black){
				for(int i=0 ; i <board1->nBlack ;i ++){
					if(board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem->position->coordinate==board1->piecesBlack[i]->position->coordinate)
					{
						swap(board1->piecesBlack[i],board1->piecesBlack[--board1->nBlack]);
					}
				}

				}
				else
				{
				for(int i=0 ; i <board1->nWhite ;i ++){
					if(board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem->position->coordinate==board1->piecesWhite[i]->position->coordinate)
					{
						swap(board1->piecesWhite[i],board1->piecesBlack[--board1->nWhite]);
					}
				}
				}



			}
			swapPieces(choice1);
			ui1.printBoard();
			if(board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem->color==black){
			color2=white;
			}
			else{
			color2=black;
			}
			if(	check(color2)){
				ui1.error("you are check");
				if(check_mate1(color2)){
					ui1.print_string("game end");
					return;
				}


			}
		}

	}
	bool check_mate1(colorPieces color1)
	{
		bool flag=true;
		pair<char,int> select;
		pair<pair<char,int>,pair<char,int>> choice1;
		chesspieces* tmp;
		chesspieces* pieces2[16];
		if(color1==black)
		{
			for(int i=0 ; i<board1->nBlack ; i++)
				pieces2[i]=board1->piecesBlack[i];
		}
		else{
			for(int i=0 ; i<board1->nWhite ; i++)
				pieces2[i]=board1->piecesWhite[i];
		}
			int i=board1->piecesBlack[0]->position->coordinate.first;
			int j=board1->piecesBlack[0]->position->coordinate.second;
				select.first=i+1;
				select.second=j;
				if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j-1][i-'a'+1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j-1][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j-1][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j-1][i-'a'+1].mem=tmp;
				if(flag==false)
					return flag;
				}


				select.first=i+1;
				select.second=j+1;
				if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j][i-'a'+1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j][i-'a'+1].mem=tmp;
				if(flag==false)
					return flag;
				}


				select.first=i+1;
				select.second=j-1;
				if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j-2][i-'a'+1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j-2][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j-2][i-'a'+1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j-2][i-'a'+1].mem=tmp;
				if(flag==false)
					return flag;
				}


				select.first=i-1;
				select.second=j;
			if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j-1][i-'a'-1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j-1][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j-1][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j-1][i-'a'-1].mem=tmp;
				if(flag==false)
					return flag;

			}

				select.first=i;
				select.second=j+1;
			if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j][i-'a'].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j][i-'a'].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j][i-'a'].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j][i-'a'].mem=tmp;
				if(flag==false)
					return flag;

			}

				select.first=i-1;
				select.second=j+1;
			if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j][i-'a'-1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j][i-'a'-1].mem=tmp;
				if(flag==false)
					return flag;

			}

				select.first=i;
				select.second=j-1;
			if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j-2][i-'a'].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j-2][i-'a'].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j-2][i-'a'].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j-2][i-'a'].mem=tmp;
				if(flag==false)
					return flag;

			}

				select.first=i-1;
				select.second=j-1;
			if(pieces2[0]->move(select)){
				flag=true;
				tmp=board1->memboard[j-2][i-'a'-1].mem;
				choice1.first=pieces2[0]->position->coordinate;
				choice1.second=board1->memboard[j-2][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				if(!check(black)){
					flag= false;
				}
				choice1.second=pieces2[0]->position->coordinate;
				choice1.first=board1->memboard[j-2][i-'a'-1].mem->position->coordinate;
				swapPieces(choice1);
				board1->memboard[j-2][i-'a'-1].mem=tmp;
				if(flag==false)
					return flag;

			}
			return true;

	}
	void swapPieces (pair<pair<char,int>,pair<char,int>> choice1){
				board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem->position->coordinate=choice1.second;
				board1->memboard[choice1.second.second-1][choice1.second.first-'a'].mem=board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem;
				board1->memboard[choice1.first.second-1][choice1.first.first-'a'].mem=nullptr;
	}
 	bool validation(pair<pair<char,int>,pair<char,int>> dest,int number_user)
	{
		if(board1->memboard[dest.first.second-1][dest.first.first-'a'].mem==nullptr)
		{
			return false;
		}
		if(number_user)
		{
			if(board1->memboard[dest.first.second-1][dest.first.first-'a'].mem->color!=black)
				return false;
		}
		else
		{
			if(board1->memboard[dest.first.second-1][dest.first.first-'a'].mem->color!=white)
				return false;
		}
		if(dest.first==dest.second){
			return false;
		}

		if(dest.second==board1->piecesBlack[0]->position->coordinate || dest.second==board1->piecesWhite[0]->position->coordinate){
			return false;
		}
		if(board1->memboard[dest.first.second-1][dest.first.first-'a'].mem->move(dest.second))
		{
			return true;
		}
		return false;
	}

	bool check(colorPieces color1)
	{
		if(color1==black){
			for(int i=0 ; i < board1->nWhite ; i++)
			{
			if(board1->piecesWhite[i]->move(board1->piecesBlack[0]->position->coordinate))
			{
				return true;
			}
		}
			return false;
		}
		else
		{
			for(int i=0 ; i < board1->nBlack ; i++)
			{
			if(board1->piecesBlack[i]->move(board1->piecesWhite[0]->position->coordinate))
			{
				return true;
			}
		}
			return false;
		}


	}
};


int main(){
	//ui::get_choice();
	//user* ali=new person("ali");
	person ali("ali");
	person reza("reza");
	manage s(&ali,&reza);
	ui w;
	w.printBoard();
	s.start();

	return 0;
}