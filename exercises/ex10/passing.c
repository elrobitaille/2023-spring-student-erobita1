#include <stdio.h>

// TODO: declare the getDate function
int getDate(int *month, int *day, int *year);

int main() {

  int mon = 10;
  int day = 12;
  int yr = 2025;
  
  char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  int new_date = getDate(&mon, &day, &yr);

  printf("Month: %d, Day: %d, Year: %d\n", mon, day, yr);

  while (getDate(&mon, &day, &yr) == 3) { 
    printf("%s %d, %d\n", months[mon-1], day, yr);
  }
  
  return 0;
}

// TODO: define the getDate function to prompt for and read a date in the form
// MM/DD/YYYY, passing the inputs as integers back to main through the parameters
// and returning the number of values successfully read

int getDate(int *month, int *day, int *year) {
  int *values = ("%d/%d/%d", month, day, year);
  return *values;
}

