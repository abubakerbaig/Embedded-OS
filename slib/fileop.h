#define X O_CREAT|O_WRONLY
#define Y O_CREAT|O_RDONLY

int opening(char *,int );
int reading(int );
int writing(int );