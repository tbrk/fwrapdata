
#include <stdio.h>
#include <string.h>

#include <CoreFoundation/CoreFoundation.h>
#include "fwrapdata.h"

/*
    cc -c fwrapdata.c
    cc -o test fwrapdata.o test.c -framework CoreFoundation
*/

void show_data(CFMutableDataRef data)
{
    const UInt8 *contents = CFDataGetBytePtr(data);
    CFIndex len = CFDataGetLength(data);

    fputs("data=```", stdout);
    fwrite(contents, len, 1, stdout);
    fputs("```\n", stdout);
}

void encode_data(CFMutableDataRef data)
{
    const UInt8 *contents = CFDataGetBytePtr(data);
    CFIndex len = CFDataGetLength(data);

    fputs("data=```", stdout);
    for (int i = 0; i < len; ++i)
	fprintf(stdout, "(%02x)", contents[i]);
    fputs("```\n", stdout);
}

int
main (void)
{
    int ch;
    FILE *stream;
    char buffer[8192];
    CFMutableDataRef data = CFDataCreateMutable(NULL, 0);

    stream = fwrapdata(data);
    fprintf(stream, "Hello %s!\n", "world");
    fflush(stream);
    show_data(data);

    fseek(stream, 0, SEEK_SET);
    while ((ch = fgetc(stream)) != EOF)
	printf ("Got %c\n", ch);

    fseek(stream, 6, SEEK_SET);
    fgets(buffer, sizeof(buffer), stream);
    printf("Got \"%s\"\n", buffer);

    fseek(stream, 6, SEEK_SET);
    fputs("universe!\n", stream);
    fflush(stream);
    show_data(data);

    fseek(stream, 0, SEEK_SET);
    while ((ch = fgetc(stream)) != EOF)
	printf ("Got %c\n", ch);

    fseek(stream, 10, SEEK_END);
    encode_data(data);

    fclose (stream);
    CFRelease(data);

    return 0;
}

