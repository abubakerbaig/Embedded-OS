int writing(int fd)  {
    
    char wstr[64];

    printf("Enter String to write in a file:\n");
    scanf(" %[^\n]s",wstr);

    return write(fd,wstr,strlen(wstr));
    
}