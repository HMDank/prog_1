#include "base.h"

String s_sub(String s, int i, int j) {
  require_not_null(s);
  int n = strlen(s);
  if (i < 0)
    i = 0;
  if (j > n)
    j = n;
  if (i >= j || i >= n || j <= 0) {
    char *a = xmalloc(1 * sizeof(char));
    a[0] = '\0';
    return a;
  }
  // assert i < j && i < n && j > 0
  n = j - i;
  char *a = xmalloc((n + 1) * sizeof(char));
  memcpy(a, s + i, n * sizeof(char));
  a[n] = '\0';
  return a;
}

typedef struct statstics_s {
  // todo
  double avg_age;
  double std_age;
  double avg_mouse_time;
  double avg_touchscreen_time;
  double avg_keyboard_time;
} statstics;

statstics make_statstics() {
  // todo
  statstics stats = {0, 0.0, 0.0, 0.0, 0.0};
  return stats;
}

void print_statstics(statstics s) {
  // todo
  printf("Average Age: %f\n", s.avg_age);
  printf("Age Standard Deviation: %f\n", s.std_age);
  printf("Average Mouse Time: %f\n", s.avg_mouse_time);
  printf("Average Touchscreen Time: %f\n", s.avg_touchscreen_time);
  printf("Average Keyboard Time: %f\n", s.avg_keyboard_time);
}

statstics compute_statstics(String table) {
  statstics stats = make_statstics();
  int total_length = s_length(table);
  int current_char = 0;
  int row_amount = -1;
  int start;
  char type;
  int type_amount[3] = {0, 0, 0};
  double sum_of_total_time_per_type[3] = {0.0, 0.0, 0.0};
  double current_time;
  double std = 0.0;

  char ch;

  // move pointer to start of first line
  while (s_get(table, current_char) != '\n')
    current_char++;
  current_char++;

  // count number of data rows
  for (int row = 0; row < total_length; row++)
    if (s_get(table, row) == '\n')
      row_amount++;

  /* first pass: sum ages and times per type */
  for (int row = 1; row <= row_amount; row++) {
    start = current_char;
    while ((ch = s_get(table, current_char)) != '\t' && ch != '\0')
      current_char++;
    stats.avg_age += i_of_s(s_sub(table, start, current_char));
    if (ch == '\t')
      current_char++;

    type = s_get(table, current_char);
    current_char++;
    // skip tab after type
    current_char++;

    start = current_char;
    while ((ch = s_get(table, current_char)) != '\n' && ch != '\0')
      current_char++;
    current_time = d_of_s(s_sub(table, start, current_char));

    if (type == 'm') {
      type_amount[0]++;
      sum_of_total_time_per_type[0] += current_time;
    } else if (type == 't') {
      type_amount[1]++;
      sum_of_total_time_per_type[1] += current_time;
    } else if (type == 'k') {
      type_amount[2]++;
      sum_of_total_time_per_type[2] += current_time;
    }

    if (ch == '\n')
      current_char++;
  }

  stats.avg_age /= row_amount;
  stats.avg_mouse_time = sum_of_total_time_per_type[0] / type_amount[0];
  stats.avg_touchscreen_time = sum_of_total_time_per_type[1] / type_amount[1];
  stats.avg_keyboard_time = sum_of_total_time_per_type[2] / type_amount[2];

  current_char = 0;
  while (s_get(table, current_char) != '\n')
    current_char++;
  current_char++;

  for (int row = 1; row <= row_amount; row++) {
    start = current_char;
    while ((ch = s_get(table, current_char)) != '\t' && ch != '\0')
      current_char++;
    std += pow(d_of_s(s_sub(table, start, current_char)) - stats.avg_age, 2);

    while ((ch = s_get(table, current_char)) != '\n' && ch != '\0')
      current_char++;
    if (ch == '\n')
      current_char++;
  }

  stats.std_age = sqrt(std / (row_amount - 1));
  return stats;
}

int main(void) {
  String table = s_read_file("measurements.txt");
  statstics statstics = compute_statstics(table);
  print_statstics(statstics);
  return 0;
}
