
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

int main()
{
    while (1) {
        // print shell line
        printDir();
        // take input

    }
    return 0;
}
