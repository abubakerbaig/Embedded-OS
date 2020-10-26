int reading(int fd)  {
    char rstr[64];
    read(fd,rstr,sizeof(rstr));
    printf("Content of the file: \n \t %s \n",rstr);
    
}