#include <stdio.h>
#include <time.h>

const int NO_MONTHS = 12;
const int SECONDS_PER_DAY = 86400;
const int SECONDS_PER_HOUR = 3600;
const int MONTHLY_DAY_COUNT[NO_MONTHS] = {31, 28, 31, 30, 31, 30,
                                          31, 31, 30, 31, 30, 31};
char *MONTHS_AS_STR[NO_MONTHS] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
typedef struct date {
  int year;
  int month;
  int day;
  int hours;
  int minutes;
  int seconds;
  int day_of_week;
} date;

const date EPOCH_DATE = {.year = 1970, .month = 1, .day = 1, .day_of_week = 4};

int is_leap_year(int year) {
  if (year % 4 != 0)
    return 0;
  if (year % 100 != 0)
    return 1;
  return year % 400 == 0;
}

int days_in_month(int month, int year) {
  return month != 2 ? MONTHLY_DAY_COUNT[month] : is_leap_year(year) ? 29 : 28;
}

date epoch_to_date(long int epoch_seconds) {
  long int days_since_1970 = epoch_seconds / SECONDS_PER_DAY;
  int seconds = 0;
  int days_per_year = 365;
  date current_date = {.year = 0, .month = 1, .day = 1};

  // year calculation
  int years_since_epoch = 0;
  while (days_since_1970 >= days_per_year) {
    days_since_1970 -= days_per_year;
    years_since_epoch++;
    days_per_year = is_leap_year(1970 + years_since_epoch) ? 366 : 365;
  }
  current_date.year = 1970 + years_since_epoch;

  int current_month = 0;

  while (days_since_1970 >= days_in_month(current_month, current_date.year)) {
    days_since_1970 -= days_in_month(current_month, current_date.year);
    current_month++;
  }

  current_date.month = current_month + 1;
  current_date.day = days_since_1970;
  current_date.day_of_week = (EPOCH_DATE.day_of_week + days_since_1970) % 7 - 1;

  epoch_seconds %= SECONDS_PER_DAY;

  current_date.hours = (epoch_seconds / SECONDS_PER_HOUR) % 24 + 7;

  epoch_seconds %= 3600;

  current_date.minutes = epoch_seconds / 60;
  current_date.seconds = epoch_seconds % 60;

  return current_date;
}

char *get_day_of_week(int day) {
  char *days_of_week[7] = {"Sun", "Mon", "Tues", "Wed", "Thu", "Fri", "Sat"};
  return days_of_week[day];
}

const char *get_month_of_year(int month) {
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return months[month - 1];
}

//"Thu Feb 15 18:40:13 EST 2024"

void print_date(date d) {
  printf("%s %s %d %2d:%2d:%2d %s %d\n", get_day_of_week(d.day_of_week),
         get_month_of_year(d.month), d.day, d.hours, d.minutes, d.seconds,
         "EST", d.year);
}

/*
    testcases
    1708044862 :
*/

int main() {
  // print_date(EPOCH_DATE);

  time_t current_time;
  current_time = time(NULL);

  // date current_date = epoch_to_date(1708044862);
  // date current_date = epoch_to_date(1708056371);
  date current_date = epoch_to_date(current_time);

  // printf("%ld\n", current_time);
  print_date(current_date);
  return 0;
}
