#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

#define INWON 1 // �ο� ��(���ο�)

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
		cout << "�� ���� " << name << " ���� �Ǿ����ϴ�." << endl;
		while (true) {
			if (ox != 'O' && ox != 'o' && ox != 'X' && ox != 'x') {
				cout << "�� ���� �ڵ� ���� �Ͻðڽ��ϱ�? (o,x)" << endl;
				cout << "�� ";
				cin >> ox;
				break;
			} else {
				cout << "���Է� ����" << endl;
				system("pause");
				system("cls");
			}
		}
		cout << endl << "�� ���� ������ �����մϴ�." << endl;
		if (ox == 'O' || ox == 'o') {
			rand_bord();
			Sleep(1000);
			cout << endl << "	�� ";
			Sleep(1000);
			cout << " �� ";
			Sleep(1000);
			cout << " �� ";
			for (int i = 0; i < 3; i++) {
				Sleep(1000);
				cout << " �� ";
			}
			Sleep(1000);
			cout << endl << endl;
			system("pause");
		}
		else if (ox == 'X' || ox == 'x') create_bord();
		system("cls");
		print();
		cout << endl << "�� ���� ������ ��Ĩ�ϴ�." << endl << endl;
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
				while(!sameCheck(ran)) // true�� ��ȯ�Ҷ� ���� �ݺ�
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
			cout << "�� ��ĭ�� �� ���ڸ� �Է��� �ּ���. (1~99)" << endl;
			cout << "�� ";
			cin >> num;
			if (num <= 99 && num >= 1) {
				if (sameCheck(num)) {
					bord[i][j] = num;
					if (j == 4) {
						i++; j = 0;
					}
					else j++;
				} else {
					cout << "�� �Է� ���� (�ߺ����� �ʴ� ���� �Է��� �ּ���.)" << endl;
					system("pause");
				}
			} else {
				cout << "�� �Է� ���� (0���� 99 ������ ���� �Է��� �ּ���.)" << endl;
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

	bool sameCheck(int num) { // �ߺ��� ���� ������ true ��ȯ
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
			if(i<4)printf("|  �ѤѤ� |  �ѤѤ� |  �ѤѤ� |  �ѤѤ� |  �ѤѤ�  |\n");
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
		cout << "<<<  �޴�  >>>" << endl;
		cout << "1. ���� ����" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� ����" << endl;
		cout << "�� ";
		cin >> num;


		if (num == 1) {
			system("cls");
			string name;
			cout << "�̸� ����" << endl;
			cout << "�� ";
			cin >> name;
			while (true) {
				system("cls");
				cout << "���̵� ����" << endl;
				cout << "1. �ڡ١١١� ����" << endl;
				cout << "2. �ڡڡ١١� ����" << endl;
				cout << "3. �ڡڡڡ١� �����" << endl;
				cout << "�� ";
				cin >> level;
				if (level != 1 && level != 2 && level != 3) {
					cout << endl << "�� �Է� ����. ���̵��� �Է��� �ּ���." << endl << endl;
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
			cout << "			<<< 1�ο� ���� ���� >>>" << endl;
			cout << endl << "�� 1�ο� ���� ������ Ai�� ���� �÷��̸� �����մϴ�." << endl;
			cout << endl << "�� 1~99������ �ߺ����� �ʴ� ���ڷ� �������� ���� or �ڵ����� ä��ϴ�." << endl;
			cout << endl << "�� ���̵��� ���� ���� ������ ������ �� �ֽ��ϴ�." << endl;
			cout << endl << "�� �������� üũ�� 0���� ǥ�õ˴ϴ�." << endl;
			cout << endl << "�� �� �÷��̾�� �����̸� ���� ���� ���� �ϼ��� ����� �¸��ϰ� �˴ϴ�." << endl;
			cout << endl << "�� ���� �̿��� ���ڸ� �Է����� ������." << endl << endl;
		} else if (num == 3) {
			system("cls");
			cout << "�� ������ �����մϴ�." << endl << endl;
			system("pause");
			break;
		} else {
			cout << endl << "�Է� ����" << endl << endl;
		}

		system("pause");
		system("cls");
	}
	return 0;
}

static void print_game(Bingo Gamer, Bingo Ai) {
	cout << "\t\t   < " << Gamer.name << "�� ���� >" << endl;
	Gamer.print();
	cout << "\n\n\t\t   < " << Ai.name << "�� ���� >" << endl;
	Ai.print();
}

void play(Bingo Gamer, Bingo Ai) {
	bool TF = true;
	int num;
	int sequence[25] = {};
	while (TF) { // ���̵��� ���� ���� ������ �����ϸ� �ݺ����� ����
		print_game(Gamer, Ai);
		cout << endl <<  "�� "<< Gamer.name << "�� ���� �Դϴ�. �����ǿ��� ��Ҹ� �������ּ���." << endl;
		cout << "�� ";
		cin >> num;
		
		if (Gamer.check(num)) {
			Ai.check(num);
			system("cls");
			print_game(Gamer, Ai);
			cout << endl <<  "�� " << Gamer.name << "�� ���� �Դϴ�. �����ǿ��� ��Ҹ� �������ּ���." << endl;
			cout << "�� " << num << endl << endl;
			system("pause");
			system("cls");

			TF = play_check(Gamer, Ai);
			if (!TF) break;
			
			print_game(Gamer, Ai);
			cout << endl << "�� " << Ai.name << "�� �����Դϴ�. " << endl;
			cout << "�� ";
			Sleep(3500);

			int ran;
			while (true) { 
				ran = rand() % 99 + 1;
				if (Ai.check(ran)) {
					Gamer.check(ran);
					system("cls");
					print_game(Gamer, Ai);
					cout << endl << "�� " << Ai.name << "�� �����Դϴ�. " << endl;
					cout << "�� ";
					cout << ran << endl << endl;
					system("pause");
					TF = play_check(Gamer, Ai);
					if (!TF) break;
					break;
				}
			}
		} else {
			cout << "�� �Է� ���� �Դϴ�." << endl;
			system("pause");
		}
		system("cls");
	}
}

bool play_check(Bingo Gamer, Bingo Ai) {
	// ���� �ִ��� 12���� üũ
	Gamer.ifbingo(); 
	Ai.ifbingo();
	// ������ �����ϴ� ������ ����
	Gamer.sumbingos();
	Ai.sumbingos();

	if (Gamer.bingo == level || Ai.bingo == level) {
		system("cls");
		cout << endl << "<<<  ���� ���  >>>" << endl;
		cout << "Gamer : " << Gamer.bingo << endl;
		cout << "Ai : " << Ai.bingo << endl;
		if (Gamer.bingo == level) {
			cout << "�� " << endl << Gamer.name << "�� �¸��Դϴ�!!" << endl << endl;
		} else {
			cout << "�� " << endl << Ai.name << "�� �¸��Դϴ�!!" << endl << endl;
		}
		return false;
	} else {
		return true;
	}
}