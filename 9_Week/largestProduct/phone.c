/* Read a name and number per line.  Note the limits on lengths.
There are two potential problems:
The name mustn't have any spaces in.
If the number starts with 0, it won't be preserved. */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    const int max = 100;
    char line[max], name[50];
    int n;
    FILE *in = fopen("in.txt", "r");
    fgets(line, max, in);
    while (! feof(in)) {
        sscanf(line, "%s %d", name, &n);
        printf("Name %s number %d\n", name, n);
        fgets(line, max, in);
    }
    fclose(in);
}
