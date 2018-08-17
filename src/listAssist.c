#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "listAssist.h"
#include "moreString.h"		

int compare_priority(const void *p1, const void *p2)
{
	const char **a = *(const char***) p1;
	const char **b = *(const char***) p2;

	if (strcmp(a[3], b[3]))
		return strcmp(a[3], b[3]);
	else if (strcmp(a[2], b[2]))
		return strcmp(a[2], b[2]); 
	else if (strcmp(a[1], b[1]))
		return strcmp(a[1], b[1]);
	return strcmp(a[0], b[0]);
}

void print_table(char *date_string, char ***tasks, int daynum)
{
	int i, days;

	printf("\n%12s%28s\n", "Things to do", date_string);
	printnchar('=', 79); 
	printf("\n%-43s%-12s%-12s%-12s\n", "Task", "Urgency", "Time", "Priority");
	printnchar('=', 79);
	for (i = 0; tasks[i]; ++i) {
			days = (atoi(tasks[i][4]) >> daynum) & 0x01;
			if (days)
				printf("\n%-43s%-12s%-12s%-12s",
					tasks[i][0], tasks[i][1],
					tasks[i][2], tasks[i][3]);
	}
	printf("\n");
}

char ** get_task(char* raw_data, int* position)
{
	int i;
	char** task;
	char *days, *task_name, *urgency, *time, *priority;

	i = 0;
	task = (char**) malloc(sizeof(char**) * MAX_NAME_LENGTH + 5);
	task_name = (char*) malloc(sizeof(char*) * MAX_NAME_LENGTH);
	urgency = (char*) malloc(sizeof(char*) * 2);
	time = (char*) malloc(sizeof(char*) * 2);
	priority = (char*) malloc(sizeof(char*) * 2);
	days = (char*) malloc(sizeof(char*) * 4);
	while (*(raw_data + *position) != ',') {
		*(task_name + i) = *(raw_data + *position);
		++(*position);
		++i;
	}
	*(task_name + i) = '\0';
	++(*position);
	*urgency = *(raw_data + *position);
	*(urgency + 1) = '\0';
	++(*position); ++(*position);
	*time = *(raw_data + *position);
	*(time + 1) = '\0';
	++(*position); ++(*position);
	i = 0;
	while (*(raw_data + *position) >= '0' && *(raw_data + *position) <= '9') {
		*(days + i) = *(raw_data + *position);
		++i; ++(*position);
	}	
	*(days + i) = '\0';
	++(*position);
	*priority = (char) (*urgency + *time - 48);
	*(priority + 1) = '\0';
	*task = task_name;
	*(task + 1) = urgency;
	*(task + 2) = time;
	*(task + 3) = priority;
	*(task + 4) = days;
	return task;
}

int read_tasks(char* filename, char*** task_list)
{
	FILE* daily_tasks_file;
	char* raw_data;
	int task_no, position;

	task_no = position = 0;
	daily_tasks_file = fopen(filename, "r");
	raw_data = (char*) malloc(sizeof(char *) * MAX_TASKS * 100);
	*raw_data = fgetc(daily_tasks_file);
	while (*(raw_data + position) != EOF) {
		++position;
		*(raw_data + position) = fgetc(daily_tasks_file);
	}
	position = 0;
	while (*(raw_data + position) != EOF) {
		if (*(raw_data + position) == '#') {
			++position;
			while (*(raw_data + position) != '\n')
				++position;
			++position;
		}
		else {
			*(task_list + task_no) = get_task(raw_data, &position);
			++task_no;
		}
	}
}

int count_tasks(char*** tasks)
{
	int count;

	for (count = 0; tasks[count]; ++count);
	;
	return count;
}

int main(int argc, char** argv)
{
	char ***tasks, *date_string, *filename, ***tasks_offset;
	int task_count, daynum, position, i;

	tasks = (char***) calloc(MAX_TASKS, sizeof(char ***));
	if (argc == 1)
		read_tasks("daily_tasks.csv", tasks);
	else {
		position = 0;
		for (i = 1; i < argc; ++i) {
			read_tasks(argv[i], tasks + position);
			position += count_tasks(tasks);
		}
	}
	task_count = count_tasks(tasks);
	date_string = get_date_string(&daynum);
	qsort(tasks, task_count, sizeof(char **), compare_priority); 
	print_table(date_string, tasks, daynum);
}
