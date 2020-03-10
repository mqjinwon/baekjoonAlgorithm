//baekjoon algorithm 13460
/**
//map sign
. : blank
# : barrier
0 : exit
R : red ball
B : blue ball
**/


#include <iostream>
#include <queue>
#include <utility>

using namespace std;

//input map size(N : COL, M : ROW)
static int N, M;
static pair<int, int> r_init_pos, b_init_pos;

char** makeMap() {

	//input map size(N : COL, M : ROW)
	cin >> N;
	cin >> M;

	//allocate map size
	char** map = new char* [M];

	for (int i = 0; i < M; ++i)
		map[i] = new char[M];

	char tmp;

	//make map
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> tmp;
			map[n][m] = tmp;
			if (tmp == 'R') {
				r_init_pos = make_pair(m, n);
			}
			if (tmp == 'B') {
				b_init_pos = make_pair(m, n);
			}
		}
	}

	return map;
}

void printMap(char** _map) {
	cout << "==============================================" << endl;

	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cout << _map[n][m] << "\t";
		}
		cout << endl;
	}

	cout << "==============================================" << endl;
}

enum Direction {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

enum Condition {
	NOTHING,
	REDGOAL,
	BLUEGOAL
};

/**
//map sign
. : blank
# : barrier
0 : exit
R : red ball
B : blue ball
**/
//position result after ball move
vector< pair<int, int> > moveBalls(char** _map, pair<int, int> _rPos,
	pair<int, int> _bPos, int _dir) {

	vector< pair<int, int> > result;
	pair<int, int> red_pos = make_pair(0, 0);
	pair<int, int> blue_pos = make_pair(0, 0);
	int con_flag = 0;
	char bChar, rChar;
	int rPosX = _rPos.first;
	int rPosY = _rPos.second;
	int bPosX = _bPos.first;
	int bPosY = _bPos.second;

	cout << "rPosX : " << rPosX << ", rPosY : " << rPosY <<
		", bPosx : " << bPosX << ", bPosY : " << bPosY << endl;

	bool end_flag = false;

	while (1) {

		end_flag = false;

		switch (_dir) {
		case UP:
			bChar = _map[bPosY - 1][bPosX];
			rChar = _map[rPosY - 1][rPosX];
			if (bChar == 'O') {
				end_flag = true;
				con_flag = BLUEGOAL;
				break;
			}
			else if (bChar == 'R') {
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				//if redball move -> blueball move
				else if (rChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;

				}
				else if (rChar == '.') {
					rPosY--;
					bPosY--;
					_map[rPosY][rPosX] = 'R';
					_map[bPosY][bPosX] = 'B';
					_map[bPosY + 1][bPosX] = '.';
				}
			}
			else {
				if (bChar == '#') {
					if (rChar == 'B') {
						end_flag = true;
						con_flag = NOTHING;
						break;
					}
				}
				else if (bChar == '.') {
					_map[bPosY][bPosX] = '.';
					bPosY--;
					_map[bPosY][bPosX] = 'B';
				}
				//redball move
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				else if (rChar == '#' && bChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;
				}
				else if (rChar == '.') {
					_map[rPosY][rPosX] = '.';
					rPosY--;
					_map[rPosY][rPosX] = 'R';
				}
			}
			break;
		case DOWN:
			bChar = _map[bPosY + 1][bPosX];
			rChar = _map[rPosY + 1][rPosX];
			if (bChar == 'O') {
				end_flag = true;
				con_flag = BLUEGOAL;
				break;
			}
			else if (bChar == 'R') {
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				//if redball move -> blueball move
				else if (rChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;

				}
				else if (rChar == '.') {
					rPosY++;
					bPosY++;
					_map[rPosY][rPosX] = 'R';
					_map[bPosY][bPosX] = 'B';
					_map[bPosY - 1][bPosX] = '.';
				}
			}
			else {
				if (bChar == '#') {
					if (rChar == 'B') {
						end_flag = true;
						con_flag = NOTHING;
						break;
					}
				}
				else if (bChar == '.') {
					_map[bPosY][bPosX] = '.';
					bPosY++;
					_map[bPosY][bPosX] = 'B';
				}
				//redball move
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				else if (rChar == '#' && bChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;
				}
				else if (rChar == '.') {
					_map[rPosY][rPosX] = '.';
					rPosY++;
					_map[rPosY][rPosX] = 'R';
				}
			}
			break;
		case LEFT:
			bChar = _map[bPosY][bPosX - 1];
			rChar = _map[rPosY][rPosX - 1];
			if (bChar == 'O') {
				end_flag = true;
				con_flag = BLUEGOAL;
				break;
			}
			else if (bChar == 'R') {
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				//if redball move -> blueball move
				else if (rChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;

				}
				else if (rChar == '.') {
					rPosX--;
					bPosX--;
					_map[rPosY][rPosX] = 'R';
					_map[bPosY][bPosX] = 'B';
					_map[bPosY][bPosX + 1] = '.';
				}
			}
			else {
				if (bChar == '#') {
					if (rChar == 'B') {
						end_flag = true;
						con_flag = NOTHING;
						break;
					}
				}
				else if (bChar == '.') {
					_map[bPosY][bPosX] = '.';
					bPosX--;
					_map[bPosY][bPosX] = 'B';
				}
				//redball move
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				else if (rChar == '#' && bChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;
				}
				else if (rChar == '.') {
					_map[rPosY][rPosX] = '.';
					rPosX--;
					_map[rPosY][rPosX] = 'R';
				}
			}
			break;
		case RIGHT:
			bChar = _map[bPosY][bPosX + 1];
			rChar = _map[rPosY][rPosX + 1];
			if (bChar == 'O') {
				end_flag = true;
				con_flag = BLUEGOAL;
				break;
			}
			else if (bChar == 'R') {
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				//if redball move -> blueball move
				else if (rChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;

				}
				else if (rChar == '.') {
					rPosX++;
					bPosX++;
					_map[rPosY][rPosX] = 'R';
					_map[bPosY][bPosX] = 'B';
					_map[bPosY][bPosX - 1] = '.';
				}
			}
			else {
				if (bChar == '#') {
					if (rChar == 'B') {
						end_flag = true;
						con_flag = NOTHING;
						break;
					}
				}
				else if (bChar == '.') {
					_map[bPosY][bPosX] = '.';
					bPosX++;
					_map[bPosY][bPosX] = 'B';
				}
				//redball move
				if (rChar == 'O') {
					end_flag = true;
					con_flag = REDGOAL;
					break;
				}
				else if (rChar == '#' && bChar == '#') {
					end_flag = true;
					con_flag = NOTHING;
					break;
				}
				else if (rChar == '.') {
					_map[rPosY][rPosX] = '.';
					rPosX++;
					_map[rPosY][rPosX] = 'R';
				}
			}
			break;
		default:;
		}

		if (end_flag == true) {
			break;
		}
	}

	red_pos = make_pair(rPosX, rPosY);
	blue_pos = make_pair(bPosX, bPosY);

	result.push_back(red_pos);
	result.push_back(blue_pos);
	result.push_back(make_pair(con_flag, 0));


	return result;
}

int main() {

	char** map = makeMap();

	printMap(map);

	// cout << "rPosX : " << r_init_pos.first << ", rPosY : " << r_init_pos.second <<
	// 				", bPosx : " << b_init_pos.first << ", bPosY : " << b_init_pos.second << endl;

	//push initial redball pos, blueball pos
	queue<pair<int, int> > r_pos;
	r_pos.push(r_init_pos);
	queue<pair<int, int> > b_pos;
	b_pos.push(b_init_pos);

	vector< pair<int, int> > tmp = moveBalls(map, r_pos.front(), b_pos.front(), RIGHT);


	cout << tmp[2].first << endl;

	printMap(map);
}