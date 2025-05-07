int builtin_repeat(shell_data_t *shell_data, char **args)
{
    int count = 0;
    int pid = 0;
    int i = 0;

    if (!args[1] || !args[2]) {
        fprintf(stderr, "repeat: usage: repeat <n> <command>\n");
        return 1;
    }
    count = atoi(args[1]);
    if (count <= 0) {
        fprintf(stderr, "repeat: invalid repeat count: %s\n", args[1]);
        return 1;
    }
    while (i < count) {
        pid = fork();
        if (pid == 0) {
            execvp(args[2], &args[2]);
            perror("execvp");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            return 1;
        } else {
            int status = 0;
            waitpid(pid, &status, 0);
        }
        i++;
    }
    return 0;
}

int builtin_where(shell_data_t *shell_data, char **args)
{
    char **paths = NULL;
    char *path = NULL;
    int found = 0;
    int i = 0;
    char *full;
    size_t len;

    if (!args[1]) {
        fprintf(stderr, "where: missing argument\n");
        return 1;
    }
    if (sh_builtin_get(args[1]) != NULL) {
        printf("%s is a shell built-in\n", args[1]);
        found = 1;
    }
    path = sh_env_get(shell_data->env, "PATH");
    if (!path)
        return 1;
    paths = my_sepstr(path, ":");
    if (!paths)
        return 1;
    while (paths[i]) {
        len = strlen(paths[i]) + strlen(args[1]) + 2;
        full = malloc(len);
        if (!full) {
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return 1;
        }
        strcpy(full, paths[i]);
        strcat(full, "/");
        strcat(full, args[1]);
        if (access(full, X_OK) == 0) {
            printf("%s\n", full);
            found = 1;
        }
        free(full);
        i++;
    }
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);
    return found ? 0 : 1;
}

int builtin_which(shell_data_t *shell_data, char **args)
{
    char **paths = NULL;
    char *path = NULL;
    int i = 0;
    size_t len;
    char *full;

    if (!args[1]) {
        fprintf(stderr, "which: missing argument\n");
        return 1;
    }
    if (sh_builtin_get(args[1]) != NULL) {
        printf("%s: shell built-in command.\n", args[1]);
        return 0;
    }
    path = sh_env_get(shell_data->env, "PATH");
    if (!path)
        return 1;
    paths = my_sepstr(path, ":");
    if (!paths)
        return 1;
    while (paths[i]) {
        len = strlen(paths[i]) + strlen(args[1]) + 2;
        full = malloc(len);
        if (!full) {
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return 1;
        }
        strcpy(full, paths[i]);
        strcat(full, "/");
        strcat(full, args[1]);
        if (access(full, X_OK) == 0) {
            printf("%s\n", full);
            free(full);
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return 0;
        }
        free(full);
        i++;
    }
    for (int j = 0; paths[j]; j++)
        free(paths[j]);
    free(paths);
    printf("%s: Command not found.\n", args[1]);
    return 1;
}