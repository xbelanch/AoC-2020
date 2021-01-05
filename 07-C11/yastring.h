// grabbed from: https://stackoverflow.com/questions/47116974/remove-a-substring-from-a-string-in-c
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

// grabbed from: https://stackoverflow.com/questions/8512958/is-there-a-windows-variant-of-strsep-function
char* strsplit(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
        {
            *stringp = NULL;
        }
    else
        {
            *p = '\0';
            *stringp = p + 1;
        }

    return start;
}
