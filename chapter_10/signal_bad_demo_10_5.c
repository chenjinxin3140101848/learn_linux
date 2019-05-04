#include<apue.h>
#include<pwd.h>

void debug_password_info(struct passwd *pwd_ptr)
{
    if (NULL == pwd_ptr)
    {
        err_sys("param is NULL!");
    }
    printf("password Home directory = %s\n"
           "password real name = %s\n"
           "password name = %s\n"
           "password password = %s\n"
           "password shell = %s\n"
           "password uid  = %d\n"
           "password gid  = %d\n",
           pwd_ptr->pw_dir,
           pwd_ptr->pw_gecos, pwd_ptr->pw_name, pwd_ptr->pw_passwd, pwd_ptr->pw_shell, pwd_ptr->pw_uid, pwd_ptr->pw_gid);
}
void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("it's a sgnal handler and signo = %d",signo);

    if((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error!");
    else
    {
        debug_password_info(rootptr);
    }
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;
    signal(SIGALRM,my_alarm);
    alarm(1); //In 1 seconds, the process will get a SIGALRM
    for(;;)
    {
        
        if((ptr = getpwnam("king")) == NULL)
        {
            err_sys("getpwnam error!");
        }
        //debug_password_info(ptr);
        if (strcmp(ptr->pw_name, "king") != 0)
        {
            printf("return value corrupted!,pw_name = %s\n",ptr->pw_name);
        }
        
    }

}