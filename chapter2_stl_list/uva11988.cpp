#include <cstdio>
#include <list>

using namespace std;

void print_list(list<char> text)
{
    list<char>::iterator position;
    for (position = text.begin(); position != text.end(); position++) {
        printf("%c", *position);
    }
    printf("\n");
}

int main()
{
    char pressed;
    list<char> text;
    list<char>::iterator position;
    
    while (true) {
        text.clear();
        position = text.begin();

        while (scanf("%c", &pressed) && pressed != '\n') {
            if (pressed == '[') 
                position = text.begin();
            else if (pressed == ']') 
                position = text.end();
            else 
                text.insert(position, pressed);
        };
        
        if (text.begin() == text.end()) {
            break;
        }

        for (position = text.begin(); position != text.end(); position++) {
            printf("%c", *position);
        }
        printf("\n");
    }
}
