#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void childFunction(char *input)
{
    printf("I am a child working for my parent\n");

    char op;
    // extracts the operation from the input string and assign to op
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            op = input[i];
            break;
        }
    }

    double operands[2];
    char *remains;
    // extracting operands and converting them into double
    char *token = strtok(input, &op);
    for (int i = 0; token != NULL; i++)
    {
        operands[i] = strtod(token, &remains); //converts token to double
        token = strtok(NULL, &op);
    }

    double result;
    // calculator
    switch (op)
    {
    case '+':
        result = operands[0] + operands[1];
        break;
    case '-':
        result = operands[0] - operands[1];
        break;
    case '*':
        result = operands[0] * operands[1];
        break;
    case '/':
        result = operands[0] / operands[1];
        break;
    default:
        exit(55);
    }

    // writing the result in result.txt
    int fd = open("result.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    char tmp[15];
    sprintf(tmp, "%lf", result);
    write(fd, tmp, strlen(tmp));
    close(fd);
    exit(0);
}

int main()
{
    pid_t pid;
    int fd;
    int status;
    char c;
    char input[50];

    printf("This program is simple calculator\n");

    while (1)
    {
        printf("Enter an expression, e.g., 134.5 + 456>\n");
        read(STDIN_FILENO, input, sizeof(input));

        if ((pid = fork()) > 0) // parent
        {
            printf("Created a child to perform task, waiting...\n");
            wait(&status);

            if (WEXITSTATUS(status) == 55)
                printf("Wrong expression\n");
            else
            {
                fd = open("result.txt", O_RDONLY);
                while (read(fd, &c, 1) > 0)
                    write(STDOUT_FILENO, &c, 1);
                printf("\n");
                close(fd);
            }
        }
        else if (pid == 0) //child
        {
            childFunction(input);
        }
    }
    exit(0);
}