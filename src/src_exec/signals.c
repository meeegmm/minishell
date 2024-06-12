#include "../../inc/minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
    // Перемещаем курсор на новую строку и выводим новое приглашение
    write(STDOUT_FILENO, "\n>$ ", 4);
}

void sigquit_handler(int sig)
{
    (void)sig;
    // Игнорируем сигнал
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    // Обработчик для SIGINT (Ctrl-C)
    sa.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}