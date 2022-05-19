#include <ncurses.h>
#include <stdio.h>
#include <fcntl.h> 
#include <errno.h> 


#define DELAY 7000
#define MAX_SPEED 2000
#define MAX_INPUT 100;



void print_speed(double speed);
void print_input(double input);


FILE *f;


int main()
{	
	int fd = open("/dev/ttyAMA0", O_WRONLY);
	if (fd < 0){
		perror("Can't open /dev/ttyAMA0");
		return -1;
	}
	
	dup2(fd, 1);
	
	double speed = 0.0f;
	double input = 0.1f;
	
	move(3, 10);	
	print_speed(0);
	move(7, 10);	
	print_input(0);
	
	initscr();
	noecho();
	curs_set(FALSE);
	
	while (1) {
		f = fopen("/tmp/comm.bin", "r");
		
		fread(&speed, sizeof(double), 1, f);
		fread(&input, sizeof(double), 1, f);
		fclose(f);
		
		move(3, 10);	
		print_speed(speed);
		move(7, 10);	
		print_input(input);
		
		usleep(DELAY);
		
		clear();
		refresh();
		
	}
	
	endwin();
	return 0;
}

void print_speed(double speed) {
	int i = 0;
	start_color();
	
	printw("Current speed of the motor:");
	move (4, 10);
	printw("##################################################");
	move (6, 10);
	printw("##################################################");
	
	move (4, 9);
	addch('#');
	move (5, 9);
	addch('#');
	move (6, 9);
	addch('#');
	
	move (4, 60);
	addch('#');
	move (5, 60);
	addch('#');
	move (6, 60);
	addch('#');
	

	

	
	move(5, 10);
	
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	
	for (i = 0; i < speed; i += 40) {
		if (i > 1000 && i < 1700)
			attron(COLOR_PAIR(1));
		else if (i > 1700)
			attron(COLOR_PAIR(2)); 
	
	
		addch('@');
		refresh();
		
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
	}
	refresh();

}

void print_input(double input) {
	int i = 0;
	start_color();
	
	printw("Current input of the motor:");
	move (8, 10);
	printw("##################################################");
	move (10, 10);
	printw("##################################################");
	
	move (8, 9);
	addch('#');
	move (9, 9);
	addch('#');
	move (10, 9);
	addch('#');
	
	move (8, 60);
	addch('#');
	move (9, 60);
	addch('#');
	move (10, 60);
	addch('#');
	

	

	
	move(9, 10);
	
	
	for (i = 0; i < input; i += 2) {
	
		addch('@');
		refresh();
		
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
	}
	refresh();

}
