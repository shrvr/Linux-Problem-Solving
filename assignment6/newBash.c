#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

char **lineSeprator(char line[], char sep[])
{
    char **result;
    result = malloc(strlen(line) * sizeof(char *));
    char *token = strtok(line, sep);

    for (int j = 0; token != NULL; j++)
    {
        result[j] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(result[j], token);
        token = strtok(NULL, sep);
    }
    return result;
}

void cmdExecWithPipe(char line[], int pipe_count) // to execute piped command lines
{
    pid_t pid;
    int status;
    int NumberOfChilds = pipe_count + 1;
    int fp[NumberOfChilds][2];

    for (int i = 0; i < NumberOfChilds; i++) // Creates pipe between childs
    {
        if (pipe(fp[i]) == -1)
            exit(1);
    }

    char **pipedCmdLines;
    pipedCmdLines = lineSeprator(line, "|"); // seperates the piped command lines by pipe "|"

    for (int i = 0; i < NumberOfChilds; i++)
    {
        char **arguCmd = lineSeprator(pipedCmdLines[i], " ");
        if ((pid = fork()) == 0)
        {
            for (int j = 0; j < NumberOfChilds; j++)
            {
                if (j == i)
                    close(fp[j][1]);
                else if (j == (i + 1))
                    close(fp[j][0]);
                else
                {
                    close(fp[j][0]);
                    close(fp[j][1]);
                }
            }
            dup2(fp[i][0], 0);
            if (i != (NumberOfChilds - 1))
                dup2(fp[i + 1][1], 1);
            if (execvp(arguCmd[0], arguCmd) == -1)
            {
                exit(55);
            }

            close(fp[i][0]);
            close(fp[i + 1][1]);
            exit(0);
        }
    }
    for (int j = 0; j < NumberOfChilds; j++)
    {
        close(fp[j][0]);
        close(fp[j][1]);
    }

    while (NumberOfChilds > 0)
    {
        pid = wait(&status);
        if (WEXITSTATUS(status) == 55)
            printf("Command not found\n");
        NumberOfChilds--;
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int fd;
    int status;
    char line[100];
    int i = 0;
    int pipe_count = 0;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
    }
    else
        exit(-1);

    while (read(fd, &line[i], 1) == 1)
    {
        if (line[i] == '|')
        {
            pipe_count++; // counts pipe in command line
        }
        if (line[i] == '\n' || line[i] == '\0' || line[i] == ';')
        {
            line[i] = '\0';

            if (pipe_count > 0) // true if line contains pipe '|'
            {
                cmdExecWithPipe(line, pipe_count); // executes the line containing piped commands
            }
            else // executes the non piped command in line
            {
                char **argu = lineSeprator(line, " ");
                if ((pid = fork()) == 0) // childs
                {
                    if (execvp(argu[0], argu) == -1)
                    {
                        exit(55);
                    }
                    else
                        exit(0);
                }
                else
                {
                    wait(&status);
                    if (WEXITSTATUS(status) == 55)
                        printf("Command not found\n");
                }
            }
            i = 0;
            pipe_count = 0;
            continue;
        }
        i++;
    }
    close(fd);
}