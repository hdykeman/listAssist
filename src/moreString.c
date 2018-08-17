#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* int_to_str(int num, int n)
{
	char *s;
	int i;
	s = (char*) malloc(sizeof(char *) * n + 1);
	s[n] = '\0';
	for (i = n-1; i >= 0; --i) {
		s[i] = (char) ((num % 10) + 48);
		num /= 10;
	}
	return s;
}

void printnchar(char c, int n)
{
	for (; n > 0; --n)
		printf("%c", c);
}

char* get_day_string(int daynum)
{
	switch (daynum) {
		case 0: return "Sunday"; break;
		case 1: return "Monday"; break;
		case 2: return "Tuesday"; break;
		case 3: return "Wednesday"; break;
		case 4: return "Thursday"; break;
		case 5: return "Friday"; break;
		case 6: return "Saturday"; break;
	}
}

char* get_month(int month_num)
{
	switch (month_num) {
		case 0: return "January"; break;
		case 1: return "February"; break;
		case 2: return "March"; break;
		case 3: return "April"; break;
		case 4: return "May"; break;
		case 5: return "June"; break;
		case 6: return "July"; break;
		case 7: return "August"; break;
		case 8: return "September"; break;
		case 9: return "October"; break;
		case 10: return "November"; break;
		case 11: return "December"; break;
	} 
}

char* get_date_string(int* daynum)
{
	char *date_string, *month;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	date_string = (char*) calloc(40, sizeof(char *));
	*daynum = tm.tm_wday;
	strcat(date_string, get_day_string(tm.tm_wday));
	strcat(date_string, " ");
	strcat(date_string, int_to_str(tm.tm_mday, 2));
	strcat(date_string, " ");
	strcat(date_string, get_month(tm.tm_mon));
	return date_string;
}


