#include <cstdio>

#define MEMORY_SIZE 1000
#define REGISTER_QTY 10

int memory[1050][5];
int registers[15];

int currPosition;
int operationQty;

void clear();

void setRegister(int, int);
void addToRegister(int, int);
void multiplyRegister(int, int);
void setRegisterFrom(int, int);
void addToRegisterFrom(int, int);
void multiplyRegisterFrom(int, int);
void setRegisterFromAddress(int, int);
void setMemoryFromAddress(int, int);
void gotoLocation(int, int);

int getMemValue(int);
void setMemValue(int, int);

void readCase();

int toInt(char);

void printRegisters() {
    int i;

    printf("|");

    for (i = 0; i < 10; i++) {
        printf(" %d |", registers[i]);
    }

    printf("\n\n");
}

void printMemory() {
    int i, j;

    printf("\n\n|");

    for (i = 0; i < 1000; i++) {
        printf(" %d%d%d |", memory[i][0], memory[i][1], memory[i][2]); 
        
        if (i % 15 == 0 && i != 0 || i == 14)
            printf("\n|");
    }

    printf("\n\n");
}

int main() {
    int i, caseQty;
    
    scanf("%d\n", &caseQty);

    for (i = 1; i <= caseQty; i++) {
        clear();
        readCase();

        if (i < caseQty)
            printf("\n");
    }

    return 0;
}

void readCase() {
    char operation = 0;
    char line[5];
    int param1, param2;

    currPosition = 0;
    operationQty = 0;

    while (true) {
        gets(line);

        if (feof(stdin) || line[0] == 0) {
            break;
        }

        memory[currPosition][0] = line[0] - 48;
        memory[currPosition][1] = line[1] - 48;
        memory[currPosition][2] = line[2] - 48;
        
        currPosition++;
    }

    currPosition = -1;

    while (currPosition < 999 && operation != '1') {
        currPosition++;
        operationQty++;

        operation = memory[currPosition][0] + 48;
        param1 = memory[currPosition][1];
        param2 = memory[currPosition][2];

        switch (operation) {
            case '2':
                setRegister(param1, param2);
                break;
            case '3':
                addToRegister(param1, param2);
                break;
            case '4':
                multiplyRegister(param1, param2);
                break;
            case '5':
                setRegisterFrom(param1, param2);
                break;                
            case '6':
                addToRegisterFrom(param1, param2);
                break;
            case '7':
                multiplyRegisterFrom(param1, param2);
                break;
            case '8':
                setRegisterFromAddress(param1, param2);
                break;
            case '9':
                setMemoryFromAddress(param1, param2);
                break;
            case '0':
                gotoLocation(param1, param2);
                break;
        }
    }

    printf("%d\n", operationQty);
}

void clear() {
    int i;

    for (i = 0; i < MEMORY_SIZE; i++) {
        memory[i][0] = 0;
        memory[i][1] = 0;
        memory[i][2] = 0;
        memory[i][3] = 0;
        memory[i][4] = 0;
    }

    for (i = 0; i < REGISTER_QTY; i++) {
        registers[i] = 0;
    }
}

void setRegister(int d, int n) {
    registers[d] = n % 1000;
}

void addToRegister(int d, int n) {
    registers[d] = (registers[d] + n) % 1000;
}

void multiplyRegister(int d, int n) {
    registers[d] = (registers[d] * n) % 1000;
}

void setRegisterFrom(int d, int s) {
    registers[d] = registers[s] % 1000;
}

void addToRegisterFrom(int d, int s) {
    registers[d] = (registers[d] + registers[s]) % 1000;
}

void multiplyRegisterFrom(int d, int s) {
    registers[d] = (registers[d] * registers[s]) % 1000;
}

void setRegisterFromAddress(int d, int a) {
    registers[d] = getMemValue(registers[a]);
}

void setMemoryFromAddress(int s, int a) {
    setMemValue(registers[a], registers[s] % 1000);
}

void gotoLocation(int d, int s) {
    if (registers[s]) {
        currPosition = registers[d] % 1000 - 1;
    }
}

int getMemValue(int d) {
    int result;

    result = memory[d][0] * 100;
    result += memory[d][1] * 10;
    result += memory[d][2];

    return result;
}

void setMemValue(int d, int value) {
    int temp = value;

    memory[d][0] = temp / 100;
    temp %= 100;

    memory[d][1] = temp / 10;
    temp %= 10;

    memory[d][2] = temp;
}
