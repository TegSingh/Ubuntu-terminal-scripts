#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CALLEN(x) (sizeof(x) / sizeof((x)[0]))

// Parameters to check date validity
int valid_month_31[7] = {1, 3, 5, 7, 8, 10, 12};
int valid_month_30[4] = {4, 6, 9, 11};

struct datetime
{
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    char timestring[50];
};

struct action_item
{
    char item[50];
    char type[50];
    char course_name[50];
    char due_at[50];
    char added_at[50];
};

// Sort the array of structures by due time
void sort_by_due_time()
{
    printf("Sort by due time called\n");
}

// Add item to the array of structures
void add_item(struct action_item *action_item)
{
    printf("Add deadline called\n");

    printf("Item: %s\n", action_item->item);
    printf("Type: %s\n", action_item->type);
    printf("Course Name: %s\n", action_item->course_name);
    printf("Course Name: %s\n", action_item->due_at);
    printf("Course Name: %s\n", action_item->added_at);

    // open the file to store the data
    FILE *fptr;
    fptr = fopen("Task-list.txt", "a");
    if (fptr == NULL)
    {
        printf("ERROR OPENING FILE\n");
        return -1;
    }
    fprintf(fptr, "Name: %s Type: %s Course Name: %s Deadline: %s Added: %s\n", action_item->item, action_item->type, action_item->course_name, action_item->due_at, action_item->added_at);
}

// Delete item from the array of structures
void delete_item()
{
    printf("Delete deadlines called\n");

    // open the file to write the data
    FILE *fptr;
    fptr = fopen("Task-list.txt", "r");
    if (fptr == NULL)
    {
        printf("ERROR OPENING FILE\n");
        return -1;
    }
    fclose(fptr);
}

void show_list()
{
    printf("Show Items called\n");
    FILE *fptr;
    fptr = fopen("Task-list.txt", "r");
    if (fptr == NULL)
    {
        printf("ERROR OPENING FILE\n");
        return -1;
    }
    fclose(fptr);
}

int find_value_in_array(int arr[], int value)
{
    int i = 0;
    while (arr[i] != NULL)
    {
        if (arr[i] == value)
            return value;
        else
            i++;
    }
    return -1;
}

int validate_day(int day, int month, int year)
{
    if (day < 1)
        return -1;
    if (find_value_in_array(valid_month_31, month) != -1)
        if (day > 31)
            return -1;
    if (find_value_in_array(valid_month_30, month) != -1)
        if (day > 30)
            return -1;
    if (month == 2)
        if ((day > 28 && year % 4 != 0) || (day > 29 && year % 4 == 0))
            return -1;
    return 1;
}

int main()
{

    struct action_item ai;
    int year, month, day, hours, minutes;
    int year_current, month_current, day_current, hours_current, minutes_current;

    // Get inputs
    printf("Enter Action Item name: ");
    gets(ai.item);

    printf("Enter Action Item type: ");
    gets(ai.type);

    printf("Enter Action Item Course Name: ");
    gets(ai.course_name);

    printf("Enter deadline information: \n");
    printf("Enter year: ");
    scanf("%d", &year);

    printf("Enter month: ");
    scanf("%d", &month);
    if (month < 1 || month > 12)
    {
        printf("Enter a valid month\n");
    }

    printf("Enter day: ");
    scanf("%d", &day);
    if (validate_day(day, month, year) == -1)
    {
        printf("Enter a valid date for the month:\n");
    }

    printf("Enter hours: ");
    scanf("%d", &hours);
    if (hours > 23 || hours < 0)
    {
        printf("Enter a valid value for hours:\n");
    }

    printf("Enter minutes: ");
    scanf("%d", &minutes);
    if (minutes > 59 || minutes < 0)
    {
        printf("Enter a valid value for minutes:\n");
    }

    // Store the deadline time in a string
    sprintf(ai.due_at, "%d-%d-%d %d:%d", year, month, day, hours, minutes);

    // Get current time and store in a datetime struct
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    year_current = local->tm_year + 1900;
    month_current = local->tm_mon + 1;
    day_current = local->tm_mday;
    hours_current = local->tm_hour;
    minutes_current = local->tm_min;

    // Store the current time in a string
    sprintf(ai.added_at, "%d-%d-%d %d:%d", year_current, month_current, day_current, hours_current, minutes_current);

    add_item(&ai);
    printf("List updated\n");

    return 0;
}