#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/stat.h>


 //判断是否是目录
int is_dir(char *dir)
{
        struct stat info;
        stat(dir,&info);
        if(S_ISDIR(info.st_mode))
        {
                return 1;
        }
        return 0;
}


void dirWalk(char *dir)
{
	if(0==is_dir(dir))
	{
		return;
	}
	char path[1024];
	struct dirent *dp;
        DIR *dfd;
	if((dfd=opendir(dir)) == NULL)
	{
		perror("dir cannot open");
		exit(-1);
	}
	//开始打印
	while((dp=readdir(dfd)) != NULL){
		//printf("%s\n",dp->d_name);
		//检测是否是目录
		if((strcmp(dp->d_name,".")==0) || (strcmp(dp->d_name,"..")==0))
		{
			continue;
		}
//		char path[100];
//		strcpy(path,dir);
//		strcat(path,dp->d_name);
//		printf("%s/n",path);
		sprintf(path, "%s/%s", dir, dp->d_name);
//		printf("%s\n",path);
		if(is_dir(path)==0)
		{
		//	printf("--");
			printf("├──%s\n",dp->d_name);
		}else{
			//dirWalk(path);
			printf("  %s\n",dp->d_name);
			sprintf(path, "%s/%s", dir, dp->d_name);
			dirWalk(path);
		}
	}
}

//判断是否是目录
/*
bool is_dir(char *dir)
{
	struct stat info;
	stat(dir,&info);
	if(S_ISDIR(info,st_mode))
	{
		return true;
	}
	return false;
}
*/
int main()
{
	dirWalk("/data/c");
	return 0;
}
