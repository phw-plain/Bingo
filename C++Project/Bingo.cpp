#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

#define INWON 1 // 인원 수(일인용)

bool b;

class Bingo {
private:
	int bingos[12] = { 0 };
	int bord[5][5] = { 0 };
public:
	string name;
	int bingo;
	Bingo(string name) {
		bingo = 0;
		this->name = name;
		char ox = '0';
		cout << "▷ 유저 " << name << " 생성 되었습니다." << endl;
		while (true) {
			if (ox != 'O' && ox != 'o' && ox != 'X' && ox != 'x') {
				cout << "▷ 보드 자동 생성 하시겠습니까? (o,x)" << endl;
				cout << "▶ ";
				cin >> ox;
				break;
			} else {
				cout << "▷입력 오류" << endl;
				system("pause");
				system("cls");
			}
		}
		cout << endl << "▷ 보드 생성을 시작합니다." << endl;
		if (ox == 'O' || ox == 'o') {
			rand_bord();
			Sleep(1000);
			cout << endl << "	로 ";
			Sleep(1000);
			cout << " 딩 ";
			Sleep(1000);
			cout << " 중 ";
			for (int i = 0; i < 3; i++) {
				Sleep(1000);
				cout << " · ";
			}
			Sleep(1000);
			cout << endl << endl;
			system("pause");
		}
		else if (ox == 'X' || ox == 'x') create_bord();
		system("cls");
		print();
		cout << endl << "▷ 보드 생성을 마칩니다." << endl << endl;
		system("pause");
		system("cls");
	}
	Bingo() {
		bingo = 0;
		name = "Ai";
		rand_bord();
	}
	void rand_bord() {
		srand((unsigned)time(NULL));
		int ran = rand() % 99 + 1;;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while(!sameCheck(ran)) // true를 반환할때 까지 반복
					ran = rand() % 99 + 1;
				bord[i][j] = ran;

			}
		}
	}
	void create_bord() {
		int i = 0, j = 0, num = 0;
		while (i!=5) {
			system("cls");
			print();
			cout << "▷ 빈칸에 들어갈 숫자를 입력해 주세요. (1~99)" << endl;
			cout << "▶ ";
			cin >> num;
			if (num <= 99 && num >= 1) {
				if (sameCheck(num)) {
					bord[i][j] = num;
					if (j == 4) {
						i++; j = 0;
					}
					else j++;
				} else {
					cout << "▷ 입력 실패 (중복되지 않는 수를 입력해 주세요.)" << endl;
					system("pause");
				}
			} else {
				cout << "▷ 입력 실패 (0부터 99 사이의 수를 입력해 주세요.)" << endl;
				system("pause");
			}
		}
	}
	bool check(int num) { 
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bord[i][j] == num) {
					bord[i][j] = 0;
					return true;
				}
			}
		}
		return false;
	}

	bool sameCheck(int num) { // 중복된 수가 없으면 true 반환
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bord[i][j] == num) {
					return false;
				}
			}
		}
		return true;
	}

	void print() {
		printf("  ________________________________________________\n");
		printf("|\t\t\t\t\t\t   |\n");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if(bord[i][j] < 10) printf("|     %d   ", bord[i][j]);
				else printf("|    %d   ", bord[i][j]);
			}
			printf(" |\n");
			if(i<4)printf("|  ㅡㅡㅡ |  ㅡㅡㅡ |  ㅡㅡㅡ |  ㅡㅡㅡ |  ㅡㅡㅡ  |\n");
		}
		printf("| ________________________________________________ |\n");
	}
	
	void ifbingo() {
		for (int i = 0; i < 5; i++) {
			if (bord[i][0] == 0 && bord[i][1] == 0 && bord[i][2] == 0 && bord[i][3] == 0 && bord[i][4] == 0) bingos[i] = 1;
		}
		for (int i = 0; i < 5; i++) {
			if (bord[0][i] == 0 && bord[1][i] == 0 && bord[2][i] == 0 && bord[3][i] == 0 && bord[4][i] == 0) bingos[i+5] = 1;
		}
		if (bord[0][0] == 0 && bord[1][1] == 0 && bord[2][2] == 0 && bord[3][3] == 0 && bord[4][4] == 0) bingos[10] = 1;
		if (bord[0][4] == 0 && bord[1][3] == 0 && bord[2][2] == 0 && bord[3][1] == 0 && bord[4][0] == 0) bingos[11] = 1;
	}

	void sumbingos(){
		bingo = 0;
		for (int i = 0; i < 12; i++) {
			bingo += bingos[i];
		}
	}

	static void print_game(Bingo Gamer, Bingo Ai);
}; 

static int level;
void play(Bingo Gamer, Bingo Ai);
bool play_check(Bingo Gamer, Bingo Ai);

int main() {
	int num = 0;
	while (num != 3) {
		cout << "<<<  메뉴  >>>" << endl;
		cout << "1. 게임 시작" << endl;
		cout << "2. 게임 설명" << endl;
		cout << "3. 게임 종료" << endl;
		cout << "▶ ";
		cin >> num;


		if (num == 1) {
			system("cls");
			string name;
			cout << "이름 설정" << endl;
			cout << "▶ ";
			cin >> name;
			while (true) {
				system("cls");
				cout << "난이도 설정" << endl;
				cout << "1. ★☆☆☆☆ 쉬움" << endl;
				cout << "2. ★★☆☆☆ 보통" << endl;
				cout << "3. ★★★☆☆ 어려움" << endl;
				cout << "▶ ";
				cin >> level;
				if (level != 1 && level != 2 && level != 3) {
					cout << endl << "▷ 입력 실패. 난이도를 입력해 주세요." << endl << endl;
					system("pause");
					system("cls");
				}
				else break;
			}
			system("cls");

			Bingo Gamer(name);
			Bingo Ai;

			play(Gamer, Ai);
		} else if (num == 2) {
			system("cls");
			cout << "			<<< 1인용 빙고 게임 >>>" << endl;
			cout << endl << "▷ 1인용 빙고 게임은 Ai가 상대로 플레이를 진행합니다." << endl;
			cout << endl << "▷ 1~99까지의 중복되지 않는 숫자로 빙고판을 수동 or 자동으로 채웁니다." << endl;
			cout << endl << "▷ 난이도에 따라 빙고 갯수를 결정할 수 있습니다." << endl;
			cout << endl << "▷ 빙고판의 체크는 0으로 표시됩니다." << endl;
			cout << endl << "▷ 선 플레이어는 유저이며 가장 먼저 빙고를 완성한 사람이 승리하게 됩니다." << endl;
			cout << endl << "※ 숫자 이외의 문자를 입력하지 마세요." << endl << endl;
		} else if (num == 3) {
			system("cls");
			cout << "▷ 게임을 종료합니다." << endl << endl;
			system("pause");
			break;
		} else {
			cout << endl << "입력 오류" << endl << endl;
		}

		system("pause");
		system("cls");
	}
	return 0;
}

static void print_game(Bingo Gamer, Bingo Ai) {
	cout << "\t\t   < " << Gamer.name << "의 빙고 >" << endl;
	Gamer.print();
	cout << "\n\n\t\t   < " << Ai.name << "의 빙고 >" << endl;
	Ai.print();
}

void play(Bingo Gamer, Bingo Ai) {
	bool TF = true;
	int num;
	int sequence[25] = {};
	while (TF) { // 난이도에 따른 빙고 갯수를 만족하면 반복문을 종료
		print_game(Gamer, Ai);
		cout << endl <<  "▷ "<< Gamer.name << "의 차례 입니다. 빙고판에서 요소를 선택해주세요." << endl;
		cout << "▶ ";
		cin >> num;
		
		if (Gamer.check(num)) {
			Ai.check(num);
			system("cls");
			print_game(Gamer, Ai);
			cout << endl <<  "▷ " << Gamer.name << "의 차례 입니다. 빙고판에서 요소를 선택해주세요." << endl;
			cout << "▶ " << num << endl << endl;
			system("pause");
			system("cls");

			TF = play_check(Gamer, Ai);
			if (!TF) break;
			
			print_game(Gamer, Ai);
			cout << endl << "▷ " << Ai.name << "의 차례입니다. " << endl;
			cout << "▶ ";
			Sleep(3500);

			int ran;
			while (true) { 
				ran = rand() % 99 + 1;
				if (Ai.check(ran)) {
					Gamer.check(ran);
					system("cls");
					print_game(Gamer, Ai);
					cout << endl << "▷ " << Ai.name << "의 차례입니다. " << endl;
					cout << "▶ ";
					cout << ran << endl << endl;
					system("pause");
					TF = play_check(Gamer, Ai);
					if (!TF) break;
					break;
				}
			}
		} else {
			cout << "▷ 입력 오류 입니다." << endl;
			system("pause");
		}
		system("cls");
	}
}

bool play_check(Bingo Gamer, Bingo Ai) {
	// 빙고가 있는지 12가지 체크
	Gamer.ifbingo(); 
	Ai.ifbingo();
	// 조건을 만족하는 빙고의 갯수
	Gamer.sumbingos();
	Ai.sumbingos();

	if (Gamer.bingo == level || Ai.bingo == level) {
		system("cls");
		cout << "<<<  게임 결과  >>>" << endl;
		cout << "Gamer : " << Gamer.bingo << endl;
		cout << "Ai : " << Ai.bingo << endl;
		if (Gamer.bingo == level) {
			cout << endl << "▷ " << Gamer.name << "의 승리입니다!!" << endl << endl;
		} else {
			cout << endl << "▷ " << Ai.name << "의 승리입니다!!" << endl << endl;
		}
		return false;
	} else {
		return true;
	}
}