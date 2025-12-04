/*
Compile: make people
Run: ./people
make people && ./people
*/

#include "base.h"

// Represents statistics of a people table.
struct Statistics {
	int mean_year;
	int number_males;
	int number_females;
	int number_diverse;
	double mean_height_males; // in m
	double mean_height_females; // in m
	double mean_height_diverse; // in m
	double mean_length_of_names;
};

typedef struct Statistics Statistics;


//Returns substring of s from character i to character j
String s_sub(String s, int i, int j) {
    require_not_null(s);
    int n = strlen(s);
    if (i < 0) i = 0;
    if (j > n) j = n;
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


Statistics make_statistics(void) {
	Statistics ps = { 0, 0, 0, 0, 0.0, 0.0, 0.0 };
	return ps;
}

void print_statistics(Statistics s) {
	printf("mean year: %d\n", s.mean_year);
	printf("number males: %d\n", s.number_males);
	printf("number females: %d\n", s.number_females);
	printf("number diverse: %d\n", s.number_diverse);
	printf("mean height males: %.2f\n", s.mean_height_males);
	printf("mean height females: %.2f\n", s.mean_height_females);
	printf("mean height diverse: %.2f\n", s.mean_height_diverse);
	printf("mean length of names: %3.2f characters\n", s.mean_length_of_names);

}

Statistics compute_statistics(String table) {
	Statistics ps = make_statistics();
	int n = s_length(table);
	int i = 0; //aktuelle Position im String
	
	while (s_get(table, i) != '\n') i++; // skip first row
	if (i < n && s_get(table, i) == '\n') i++;

	int count = 0;
	int sum_years = 0;
	int males = 0, females = 0, diverse = 0;
	double sum_height_m = 0.0, sum_height_f = 0.0, sum_height_d = 0.0;
	double sum_name_lengths = 0.0;

	while (i < n) {

		int j = i;
		while (j < n && s_get(table, j) != '\n') j++;
		
		if (j == i) {
			if (j < n && s_get(table, j) == '\n') j++;
			i = j;
			continue;
		}
		int p = i;
		int tab1 = -1, tab2 = -1, tab3 = -1;
		int k = i;
		while (k < j) {
			char c = s_get(table, k);
			if (c == '\t') {
				if (tab1 == -1) tab1 = k;
				else if (tab2 == -1) tab2 = k;
				else if (tab3 == -1) tab3 = k;
			}
			k++;
		}
		if (tab1 == -1) { i = j + 1; continue; }
		if (tab2 == -1) tab2 = tab1 + 1;
		if (tab3 == -1) tab3 = tab2 + 1;

		String year_s = s_sub(table, p, tab1);
		int year = i_of_s(year_s);
		free(year_s);

		String gender_s = s_sub(table, tab1 + 1, tab2);
		char gender = (s_length(gender_s) > 0) ? s_get(gender_s, 0) : '?';
		free(gender_s);

		String height_s = s_sub(table, tab2 + 1, tab3);
		double height = d_of_s(height_s);
		free(height_s);

		String name_s = s_sub(table, tab3 + 1, j);

		int namelen = s_length(name_s);
		if (namelen > 0 && s_get(name_s, namelen - 1) == '\r') {
			String tmp = s_sub(name_s, 0, namelen - 1);
			free(name_s);
			name_s = tmp;
			namelen = s_length(name_s);
		}
		sum_years += year;
		count++;
		sum_name_lengths += (double) namelen;
		if (gender == 'm') { males++; sum_height_m += height; }
		else if (gender == 'f') { females++; sum_height_f += height; }
		else { diverse++; sum_height_d += height; }

		free(name_s);

		if (j < n && s_get(table, j) == '\n') j++;
		i = j;
	}

	ps.number_males = males;
	ps.number_females = females;
	ps.number_diverse = diverse;
	if (count > 0) {
		double mean_year = (double) sum_years / (double) count;
		ps.mean_year = (int) (mean_year + 0.5);
		ps.mean_height_males = (males > 0) ? (sum_height_m / (double) males) : 0.0;
		ps.mean_height_females = (females > 0) ? (sum_height_f / (double) females) : 0.0;
		ps.mean_height_diverse = (diverse > 0) ? (sum_height_d / (double) diverse) : 0.0;
		ps.mean_length_of_names = sum_name_lengths / (double) count;
	} else {
		ps.mean_year = 0;
		ps.mean_height_males = ps.mean_height_females = ps.mean_height_diverse = 0.0;
		ps.mean_length_of_names = 0.0;
	}
	
	return ps;
}


int main(void) {
	String table = s_read_file("people.txt");
	Statistics s = compute_statistics(table);
	print_statistics(s);
	
	/*
	Erwartete Ausgabe:
	
	mean year: 1974
	number males: 445
	number females: 455
	number diverse: 100
	mean height males: 1.79
	mean height females: 1.64
	mean height diverse: 1.61
	mean length of names: 13.20
	*/
	
	return 0;
}
