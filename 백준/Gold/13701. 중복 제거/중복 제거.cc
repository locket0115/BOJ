#include <string>
#include <iostream>
#include <bitset>

using namespace std;

bitset <(1 << 25)> bits;

int main() {
	int input;

	while (scanf("%d", &input) != EOF) {
		if (bits[input] == 0) {
			bits[input] = 1;
			printf("%d ", input);
		}
	}
	return 0;
}