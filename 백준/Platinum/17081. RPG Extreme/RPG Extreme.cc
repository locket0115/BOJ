#include <bits/stdc++.h>
using namespace std;

enum dir { L, R, U, D };
const int DIR[][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };	//y, x

enum effects {
	// 장신구 효과 flag
	HR = 0x0001,
	RE = 0x0002,
	CO = 0x0004,
	EX = 0x0008,
	DX = 0x0010,
	HU = 0x0020,
	CU = 0x0040
};
enum cell_type {
	EMPTY		= 0x0001,
	WALL		= 0x0002,
	MONSTER		= 0x0004,
	TRAP		= 0x0008,
	ITEM		= 0x0010
};


enum item_type { WEAPON, ARMOR, ACCESSORY };
struct item {
	int pos_y, pos_x;
	item_type type;
	int val;	// 무기: 공격력, 방어구: 방어력, 장신구: 효과
};


struct character {
	int start_y, start_x;
	int pos_y, pos_x;

	int lvl;		// 레벨
	int exp_cur;	// 현재 경험치
	int hp_cur;		// 현재체력
	int hp_max;		// 최대체력
	int atk;		// 공격력 (순수)
	int def;		// 방어력 (순수)
	int weapon;		// 무기 공격력
	int armor;		// 갑옷 방어력

	int accessory_flag;				// 장신구 (4개까지 가능. 중복은 X) -> flag
	int accessory_used_flag;		// 장신구 사용했으면 flag에 체크

	character() {}
	character(int _y, int _x) : start_y(_y), start_x(_x),
		pos_y(_y), pos_x(_x), exp_cur(0), lvl(1),
		hp_cur(20), hp_max(20), atk(2), def(2),
		weapon(0), armor(0), accessory_flag(0), accessory_used_flag(0) {}

	
	int get_def() { return def + armor; }
	int get_atk() {
		int base = atk + weapon;
		
		// 첫번째 공격 뻥튀기 -> CO, DX
		if ((accessory_flag & CO) && !(accessory_used_flag & CO)) {
			if (accessory_flag & DX)
				base *= 3;
			else
				base *= 2;

			accessory_used_flag |= CO;
		}

		return base;
	}

	// 전투 승리할 때마다 호출해야 함 (중요)
	void rest() {
		// HR 효과 적용
		if (accessory_flag & HR)
			hp_cur = min(hp_max, hp_cur + 3);
		 
		// CO, HU 복구
		accessory_used_flag &= ~CO;
		accessory_used_flag &= ~HU;
	}

	// exp만큼의 경험치를 획득
	// --
	// 레벨업하면 true
	bool obtain_exp(const int& exp) {
		// EX 효과
		if (accessory_flag & EX)
			exp_cur += floor(exp * 1.2);
		else
			exp_cur += exp;

		// 레벨업 처리
		if (exp_cur >= 5*lvl) {
			++lvl;
			exp_cur = 0;	// 남은 경험치는 버렷

			// 스텟 업 & 회복
			hp_max += 5;
			hp_cur = hp_max;
			atk += 2;
			def += 2;

			return true;
		}

		return false;
	}

	// 아이템(무기, 방어구, 장신구)을 획득
	void obtain_item(const item& it) {
		if (it.type == WEAPON) {
			weapon = it.val;
		}
		else if (it.type == ARMOR) {
			armor = it.val;
		}
		else {
			// 4개 이상 꼈거나 동일한거 낀 경우 X
			if (bitset<7>(accessory_flag).count() < 4 && !(accessory_flag & it.val)) {
				accessory_flag |= it.val;
			}
		}
	}

	// 전투에서 damage만큼의 데미지를 입음 (보스한테 온 데미지면 from_boss=true)
	// --
	// 죽으면 true
	bool attacked(const int& damage, bool from_boss) {
		// HU 효과
		if (from_boss && (accessory_flag & HU) && !(accessory_used_flag & HU)) {
			hp_cur = hp_max;
			accessory_used_flag |= HU;

			return false;
		}
		else {
			hp_cur -= max(1, damage-get_def());

			return hp_cur <= 0;
		}
	}

	// spike를 밟음
	// --
	// 죽으면 true
	bool attacked_by_spike() {
		if (accessory_flag & DX)
			hp_cur -= 1;
		else
			hp_cur -= 5;

		return hp_cur <= 0;

		/*if (hp_cur <= 0)
			return (false == reincarnate());
		else
			return false;*/
	}

	// RE 장신구 사용
	// --
	// 사용했으면 true 반환
	// 사용할 환경이 아니거나 없으면 false 반환
	bool reincarnate() {
		// RE 효과 발동
		if (hp_cur <= 0 && accessory_flag & RE) {
			pos_y = start_y;
			pos_x = start_x;
			hp_cur = hp_max;
			accessory_flag &= ~RE;	// 제거
			return true;
		}
		else
			return false;
	}

	void print() {
		cout << "LV : " << lvl << '\n'
			<< "HP : " << max(hp_cur, 0) << '/' << hp_max << '\n'
			<< "ATT : " << atk << '+' << weapon << '\n'
			<< "DEF : " << def << '+' << armor << '\n'
			<< "EXP : " << exp_cur << '/' << lvl * 5 << '\n';
	}
};

struct monster {
	int pos_y, pos_x;

	int hp_max;
	int hp_cur;
	int atk;
	int def;
	int exp;

	bool is_boss;
	string name;


	monster() {}
	monster(int r, int c, string s, int w, int a, int h, int e, bool boss)
	: pos_y(r), pos_x(c), name(s), atk(w), def(a), hp_cur(h), hp_max(h),
	exp(e), is_boss(boss) {}
	

	// damage 만큼의 데미지를 입음
	// 죽으면 true
	bool attacked(const int& damage) {
		hp_cur -= max(1, damage - def);
		return hp_cur <= 0;
	}
};

struct game {
	character hero;
	vector<monster> monsters;
	vector<item> items;
	vector<vector<cell_type>> cells;

	int passed_turns;
	string directions;

	game(): passed_turns(0) {}

	void read(int n, int m) {
		//read map
		cells.resize(n);
		for (auto& v : cells)
			v.resize(m);

		int monster_cnt = 0;
		int item_cnt = 0;

		char ch;
		pair<int, int> boss_pos;	// y, x
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> ch;

				switch (ch) {
				case '@':
					hero = character(i, j);
					cells[i][j] = EMPTY;
					break;

				case '.':
					cells[i][j] = EMPTY;
					break;

				case '#':
					cells[i][j] = WALL;
					break;

				case 'M':
					boss_pos = { i, j };
				case '&':
					++monster_cnt;
					cells[i][j] = MONSTER;
					break;

				case '^':
					cells[i][j] = TRAP;
					break;

				case 'B':
					++item_cnt;
					cells[i][j] = ITEM;
					break;
				}
			}
		}

		// read dirs
		cin >> directions;

		// monsters
		int r, c, w, a, h, e;
		string s;
		monsters.resize(monster_cnt);
		for (auto& mm: monsters) {
			cin >> r >> c >> s >> w >> a >> h >> e;
			--r; --c;

			mm = monster(r, c, s, w, a, h, e, (make_pair(r,c) == boss_pos));
		}

		// items
		string t;
		items.resize(item_cnt);
		for (auto& ii : items) {
			cin >> r >> c >> t >> s;
			--r; --c;

			ii.pos_y = r;
			ii.pos_x = c;

			if (t == "W") {
				ii.type = WEAPON;
				ii.val = atoi(s.c_str());
			}
			else if (t == "A") {
				ii.type = ARMOR;
				ii.val = atoi(s.c_str());
			}
			else {
				ii.type = ACCESSORY;
				if (s == "HR") ii.val = HR;
				else if (s == "RE") ii.val = RE;
				else if (s == "CO") ii.val = CO;
				else if (s == "EX") ii.val = EX;
				else if (s == "DX") ii.val = DX;
				else if (s == "HU") ii.val = HU;
				else ii.val = CU;
			}
		}
	}

	void print_map() {
		// 보스랑 캐릭터 좌표 빼놔야함
		int r = cells.size();
		int c = cells[0].size();

		int hero_y=-1, hero_x=-1;
		int boss_y=-1, boss_x=-1;

		if (hero.hp_cur > 0) {
			hero_y = hero.pos_y;
			hero_x = hero.pos_x;
		}

		for (auto& m : monsters) {
			if (m.is_boss) {
				boss_y = m.pos_y;
                boss_x = m.pos_x;
            }
        }

		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (i == hero_y && j == hero_x)
					cout << '@';
				else if (i == boss_y && j == boss_x)
					cout << 'M';
				else {
					switch (cells[i][j]) {
					case EMPTY:
						cout << '.';
						break;

					case WALL:
						cout << '#';
						break;

					case MONSTER:
						cout << '&';
						break;

					case TRAP:
						cout << '^';
						break;

					case ITEM:
						cout << 'B';
						break;
					}
				}
			}
			cout << '\n';
		}
	}

	void start() {
		bool win = false;
		bool lose = false;
		string by_whom = "";

		for (auto& c: directions) {
            // 디버그용 코드
			// cout << "-----" << passed_turns << "-----\n";
			// print_map();
			// hero.print();
			// cout << "-----------\n";

			if (win || lose) break;


			// 일단 이동
			int dir_idx;
			if (c == 'L') dir_idx = L;
			else if (c == 'R') dir_idx = R;
			else if (c == 'U') dir_idx = U;
			else dir_idx = D;

			int next_y = hero.pos_y + DIR[dir_idx][0];
			int next_x = hero.pos_x + DIR[dir_idx][1];

			// 맵 바깥인 경우 or 그 방향에 벽이 있는 경우
			if ((next_y < 0 || next_y >= cells.size() || next_x < 0 || next_x >= cells[0].size()) ||
				(cells[next_y][next_x] == WALL)) {
				next_y = hero.pos_y;
				next_x = hero.pos_x;
			}

			hero.pos_y = next_y;
			hero.pos_x = next_x;

			// 이동 후 액션
			switch (cells[next_y][next_x]) {
			case MONSTER:
				for (auto it = monsters.begin(); it != monsters.end(); ++it) {
					auto& m = *it;
					if (m.pos_y == next_y && m.pos_x == next_x) {
						while (true) {
							if (m.attacked(hero.get_atk())) {
								// 몹 죽음
								if (m.is_boss) {
									win = true;
								}
								hero.obtain_exp(m.exp);
								cells[next_y][next_x] = EMPTY;
								monsters.erase(it);
								hero.rest();	// 전투휴무

								break;
							}

							if (hero.attacked(m.atk, m.is_boss)) {
								if (hero.reincarnate()) break;

								// 주인공 죽음
								lose = true;
								by_whom = m.name;

								break;
							}
						}

						break;
					}
				}
				break;

			case TRAP:
				if (hero.attacked_by_spike()) {
					if (hero.reincarnate()) break;

					// 가시에 죽음
					lose = true;
					by_whom = "SPIKE TRAP";
				}
				break;

			case ITEM:
				// 아이템 착용
				for (auto it = items.begin(); it != items.end(); ++it) {
					if (it->pos_y == next_y && it->pos_x == next_x) {
						hero.obtain_item(*it);
						items.erase(it);
						break;
					}
				}
				cells[next_y][next_x] = EMPTY;
				break;
			}

			++passed_turns;
		}

		
		// end check
		print_map();
		cout << "Passed Turns : " << passed_turns << '\n';
		hero.print();

		if (win) {
			cout << "YOU WIN!\n";
		}
		else if (lose) {
			cout << "YOU HAVE BEEN KILLED BY " << by_whom << "..\n";
		}
		else {
			cout << "Press any key to continue.\n";
		}
	}
};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	game g;
	g.read(n, m);
	g.start();

	return 0;
}