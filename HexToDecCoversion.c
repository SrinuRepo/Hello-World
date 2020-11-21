#include <stdio.h>

int main()
{
    printf("Hello World");
    
    char hex[] = "1a";
    
    int decimal = 0;
    int base = 1;
    
    int size = sizeof(hex);
    
    for(int i = size; i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base = base * 16;
        }
         
        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base = base * 16;
        }
        
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base = base * 16;
        }
    }

    printf("decimal value:%d\n", decimal);
    return 0;
}
