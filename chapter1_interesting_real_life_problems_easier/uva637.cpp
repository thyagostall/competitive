#include <cstdio>
#include <cmath>

#define MAX_SHEET 101

#define BLANK -100

int print_page(int page[4], int page_number)
{
    if (page[0] != BLANK || page[1] != BLANK) {
        printf("Sheet %d, front: ", page_number);
        if (page[0] == BLANK) {
            printf("Blank, ");
        } else {
            printf("%d, ", page[0]);
        }
        
        if (page[1] == BLANK) {
            printf("Blank\n");
        } else {
            printf("%d\n", page[1]);
        }
    }
   
    if (page[2] != BLANK || page[3] != BLANK) {
        printf("Sheet %d, back : ", page_number);
        if (page[2] == BLANK) {
            printf("Blank, ");
        } else {
            printf("%d, ", page[2]);
        }
        
        if (page[3] == BLANK) {
            printf("Blank\n");
        } else {
            printf("%d\n", page[3]);
        }
    }
}

int main()
{
    int n, i, j, sheet_qty, page;
    int sheets[MAX_SHEET][4];
    while (scanf("%d", &n) != EOF && n > 0) {
        sheet_qty = ceil(n / 4.);
        for (i = 0; i < sheet_qty; i++) {
            sheets[i][0] = BLANK;
            sheets[i][1] = BLANK;
            sheets[i][2] = BLANK;
            sheets[i][3] = BLANK;
        }
       
        page = 1;
        for (i = 0; i < sheet_qty; i++) {
            j = 2;
            while (j-- && page <= n) {
                if (page % 2) {
                    sheets[i][1] = page;
                } else {
                    sheets[i][2] = page;
                }
                page++;
            }
        }
        for (i = sheet_qty - 1; i >= 0; i--) {
            j = 2;
            while (j-- && page <= n) {
                if (page % 2) {
                    sheets[i][3] = page;
                } else {
                    sheets[i][0] = page;
                }
                page++;
            }
        }

        printf("Printing order for %d pages:\n", n);
        for (i = 0; i < sheet_qty; i++) {
            print_page(sheets[i], i + 1);
        }
    }
}
