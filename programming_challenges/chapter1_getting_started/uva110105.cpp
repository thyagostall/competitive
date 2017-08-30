#include <cstdio>
#include <cstdlib>

void createNewImage(int, int);
void clearTable();
void colorPixel(int, int, char);
void drawVerticalLine(int, int, int, char);
void drawHorizontalLine(int, int, int, char);
void drawFilledRectangle(int, int, int, int, char);
void fillRegion(int, int, char);
void fillItem(char, char, int, int);
void fillItem_Stack(char, char, int, int);
void writeFile(char *);

void purgeLine();

typedef struct st_point point;

struct st_point {
    int x, y;
    point *next;
};

point *stack;

void createStack(point *);
void destroyStack();
void push(point *);
point *pop();
point *createPoint(int, int);

char image[300][300];
int img_m = 0, img_n = 0;

int main() {
    char command;
    int x1, y1, x2, y2;
    char c, name[50], trash[100];

    while (scanf("%c", &command) != EOF) {
        switch (command) {
            case 'I':
                scanf("%d %d", &x1, &y1);
                createNewImage(x1, y1);
                break;
            case 'C':
                clearTable();
                break;
            case 'L':
                scanf("%d %d %c", &x1, &y1, &c);
                colorPixel(x1, y1, c);
                break;
            case 'V':
                scanf("%d %d %d %c", &x1, &y1, &y2, &c);
                drawVerticalLine(x1, y1, y2, c);
                break;
            case 'H':
                scanf("%d %d %d %c", &x1, &x2, &y1, &c);
                drawHorizontalLine(x1, x2, y1, c);
                break;
            case 'K':
                scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
                drawFilledRectangle(x1, y1, x2, y2, c);
                break;
            case 'F':
                scanf("%d %d %c", &x1, &y1, &c);
                fillRegion(x1, y1, c);
                break;
            case 'S':
                scanf("%s", name);
                writeFile(name);
                break;
            case 'X':
                return 0;
            case '\n':
                break;
            default:
                purgeLine();               
                continue;
        }
    }
}

void createNewImage(int m, int n) {
    img_m = m;
    img_n = n;
    clearTable(); 
}

void clearTable() {
    int i, j;

    for (i = 0; i < img_m; i++) {
        for (j = 0; j < img_n; j++) {
            image[j][i] = 'O'; 
        }
    }
}

void colorPixel(int x, int y, char c) {
    image[y - 1][x - 1] = c;
}

void drawVerticalLine(int x, int y1, int y2, char c) {
    int j;

    if (y1 > y2) {
        j = y1;
        y1 = y2;
        y2 = j;
    }

    for (j = y1 - 1; j < y2; j++) {
        image[j][x - 1] = c;
    }
}

void drawHorizontalLine(int x1, int x2, int y, char c) {
    int i;

    if (x1 > x2) {
        i = x1;
        x1 = x2;
        x2 = i;
    }

    for (i = x1 - 1; i < x2; i++) {
        image[y - 1][i] = c;
    }
}

void drawFilledRectangle(int x1, int y1, int x2, int y2, char c) {
    int i, j;

    if (x1 > x2) {
        i = x1;
        x1 = x2;
        x2 = i;
    }
    
    if (y1 > y2) {
        i = y1;
        y1 = y2;
        y2 = i;
    }

    for (i = x1 - 1; i < x2; i++) {
        for (j = y1 - 1; j < y2; j++) {
            image[j][i] = c;
        }
    }
}

void fillRegion(int x, int y, char c) {
    fillItem(image[y - 1][x - 1], c, x - 1, y - 1); 
}

void fillItem(char old_pixel, char new_pixel, int x, int y) {    
    if (old_pixel == new_pixel) {
        return;
    }

    if (image[y][x] != old_pixel) {
        return;
    }

    image[y][x] = new_pixel;

    if (y != 0) {
        fillItem(old_pixel, new_pixel, x, y - 1);
    }

    if (y < img_n) {
        fillItem(old_pixel, new_pixel, x, y + 1);        
    }

    if (x != 0) {
        fillItem(old_pixel, new_pixel, x - 1, y);
    }

    if (x < img_m) {
        fillItem(old_pixel, new_pixel, x + 1, y);
    }
}

void fillItem_Stack(char old_pixel, char new_pixel, int x, int y) {
    if (old_pixel == new_pixel)
        return;

    int i;

    point *p, *s;
    
    p = createPoint(x, y);
    createStack(p);
    
    while (p = pop()) {
        if (image[p->y][p->x] != old_pixel) {
            free(p);
            continue;
        }

        image[p->y][p->x] = new_pixel;

        if (y != 0) {
            s = createPoint(p->x, p->y - 1);
            push(s);
        }

        if (y < img_m) {
            s = createPoint(p->x, p->y + 1);
            push(s);
        }

        if (x != 0) {
            s = createPoint(p->x - 1, p->y);
            push(s);
        }

        if (x < img_n) {
            s = createPoint(p->x + 1, p->y);
            push(s);
        }

        free(p);
    }

    destroyStack();
}

void createStack(point *p) {
    stack = p;
}

void destroyStack() {
    point *temp;

    while (stack) {
        temp = pop();
        free(temp);
    }
}

void push(point *p) {
    p->next = stack;
    stack = p;
}

point *pop() {
    point *result;

    result = stack;

    if (result)
        stack = result->next;

    return result;
}

point *createPoint(int x, int y) {
    point *result;

    result = (point *) malloc(sizeof(point));
    result->x = x;
    result->y = y;
    result->next = 0;

    return result;
}

void writeFile(char *name) {
    int i, j;

    printf("%s\n", name);

    for (i = 0; i < img_n; i++) {
        for (j = 0; j < img_m; j++) {
            printf("%c", image[i][j]);
        }

        printf("\n");
    }
}

void purgeLine() {
    char c;

    while (c != '\n' && c != EOF)
        scanf("%c", &c);
}
