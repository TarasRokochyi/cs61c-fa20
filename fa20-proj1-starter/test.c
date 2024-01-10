#include <stdio.h>
#include <stdlib.h>

int main(void){

    char *filename = "test.txt";
    printf("before open\n");

    FILE *fp = fopen("test.txt", "r");

    printf("open file\n");

    char format[10], size[10];
    int cols, rows;
    fscanf(fp, "%s\n%d %d\n%s\n", format, &cols, &rows, size);

    printf("scanning\n");

    FILE *result = fopen("result.txt", "w");
    fprintf(result, "%s\n%d %d\n%s\n", format, cols, rows, size);

    char r[4], g[4], b[4];
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            fscanf(fp, "%3s %3s %3s", r, g, b);
            fprintf(result, "%3s %3s %3s   ", r, g, b);
        }
        fprintf(result, "\n");
    }


    fclose(fp);
    fclose(result);
}

