#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[100];  // Buffer to hold the input string
    char *endptr;   // To store the address of the first invalid character after conversion
    double num;     // To store the converted number

    printf("Enter a floating-point number as a string: ");
    fgets(str, sizeof(str), stdin);  // Read a string from the user

    // Convert the string to a double
    num = strtod(str, &endptr);

    // Check if conversion was successful
    if (str == endptr) {
        printf("No conversion could be performed.\n");
    } else if (*endptr != '\0' && *endptr != '\n') {
        printf("Invalid character found: %s\n", endptr);
    } else {
        printf("Converted number: %f\n", num);
    }

    return 0;
}