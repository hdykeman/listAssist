# listAssist
Simple command-line based checklist tool written in C

Syntax: listAssist [files]

The listAssist tool reads one or more files containing comma-separated 
values and outputs a table of tasks ordered first by overall priority,
then by time required, and then by urgency. A number representing the
which days a task should be completed is used to filter out any tasks
that are not due on the day the program is executed.

If executed with no arguments, listAssist will default to the file
$HOME/daily_tasks.csv

Input files must be in the following format:

  task_name,u,t,d
  
Where u and t are integers between 1 and 4, where 1 indicates high priority.
u represents urgency and t = estimated time to complete. These numbers are
summed together by the program to give an overall priority for the task.

d is a number between 0 and 127 which represents which days the task should
be undertaken. The following numbers are added together to get the total figure:

  Sunday=1, Monday=2, Tuesday=4, Wednesday=8, Thursday=16, Friday=32, Saturday=64
  
For example, if a job J is to be completed every Monday and Friday, and has a 
high urgency and takes very little time, the following
line should be included:

  J,1,1,34
