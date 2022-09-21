#include "/public/read.h"
#include "/public/colors.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

int main() {
	cout << RED << "Hello World!\n" << "I am Reset.\n" << GREEN << "Welcome to the Farm!\n";
	cout << BOLDBLACK << "This is boldblack!\n";
	cout << BOLDGREEN << "This is boldgreen!\n";
	cout << RESET;
	set_cursor_mode(false);
	for (int i = 0; i < 255; i++) {
		clearscreen();
		setcolor(i,0,0);
		movecursor(i % 10,i % 30);
		cout << "Welcome to the Spooky Door" << endl;
		usleep(10'000); //Pauses the program for 100'000 usec
	}
	cout << RESET;
	resetcolor();
	//Ocean Blue: 35, 125, 150

	//Move a monster on the screen
	const auto [ROWS,COLS] = get_terminal_size(); //How big the screen
	cout << ROWS << " " << COLS << endl;
	int x = COLS / 2;
	int y = ROWS / 2;
	setcolor(53,97,43);
	set_raw_mode(true); //Nonblocking I/O
	while (true) {
		int ch = quick_read(); //Read from the keyboard
		if (ch == ERR) {
			//cout << "User didn't type anything!\n";
			usleep(100'000);
		}
		if (ch == 'Q' or ch == 'q') break;
		if (ch == UP_ARROW) y--;
		if (ch == DOWN_ARROW) y++;
		if (ch == LEFT_ARROW) x--;
		if (ch == RIGHT_ARROW) x++;
		y = clamp(y,0,ROWS-2);
		x = clamp(x,0,COLS-2);
		clearscreen();
		movecursor(y,x);
		cout << "🐰" << endl;
	}
	//Clean up after yourself
	set_raw_mode(false);
	resetcolor();
	set_cursor_mode(true);
	clearscreen();
}
