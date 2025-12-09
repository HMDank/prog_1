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
  int table_len = s_length(table);
  int pos = 0, num_rows = -1, field_start;
  char input_type, c;
  int count[3] = {0, 0, 0}; // count per type: {mouse, touch, keyboard}
  double total_time[3] = {0.0, 0.0, 0.0}; // total time per type
  double time_val, variance_sum = 0.0;

  // skip header and count rows
  while (s_get(table, pos) != '\n')
    pos++;
  pos++;

  for (int i = 0; i < table_len; i++)
    if (s_get(table, i) == '\n')
      num_rows++;

  // sum ages and times per type
  for (int row = 1; row <= num_rows; row++) {
    field_start = pos;
    while ((c = s_get(table, pos)) != '\t' && c != '\0')
      pos++;
    stats.avg_age += d_of_s(s_sub(table, field_start, pos));
    if (c == '\t')
      pos++;

    input_type = s_get(table, pos++);
    pos++; // skip tab

    field_start = pos;
    while ((c = s_get(table, pos)) != '\n' && c != '\0')
      pos++;
    time_val = d_of_s(s_sub(table, field_start, pos));

    int type_idx = (input_type == 'm') ? 0 : (input_type == 't') ? 1 : 2;
    count[type_idx]++;
    total_time[type_idx] += time_val;

    if (c == '\n')
      pos++;
  }

  stats.avg_age /= num_rows;
  stats.avg_mouse_time = total_time[0] / count[0];
  stats.avg_touchscreen_time = total_time[1] / count[1];
  stats.avg_keyboard_time = total_time[2] / count[2];

  // compute std for age
  pos = 0;
  while (s_get(table, pos) != '\n')
    pos++;
  pos++;

  for (int row = 1; row <= num_rows; row++) {
    field_start = pos;
    while ((c = s_get(table, pos)) != '\t' && c != '\0')
      pos++;
    double age = d_of_s(s_sub(table, field_start, pos));
    variance_sum += pow((age - stats.avg_age), 2);

    while ((c = s_get(table, pos)) != '\n' && c != '\0')
      pos++;
    if (c == '\n')
      pos++;
  }

  stats.std_age = sqrt(variance_sum / (num_rows - 1));
  return stats;
}

int main(void) {
  String table = s_read_file("measurements.txt");
  statstics statstics = compute_statstics(table);
  print_statstics(statstics);
  return 0;
}
