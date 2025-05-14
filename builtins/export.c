/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teandria <teandria@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:33:51 by teandria          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:12 by teandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ft_putchar_fd(char c, int fd) {
    write(fd, &c, 1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		n;
	int		len;

	len = (ft_strlen(s1)) + (ft_strlen(s2)) + 1;
	result = malloc(len * sizeof(const char));
	i = 0;
	n = 0;
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		result[i] = s2[n];
		i++;
		n++;
	}
	result[i] = '\0';
	return (result);
}

char *ft_strdup(const char *s1) {
    char *copy = malloc(strlen(s1) + 1);
    if (copy)
        strcpy(copy, s1);
    return copy;
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
    return strncmp(s1, s2, n);
}

int ft_isalnum(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}

int ft_isdigit(int c) {
    return c >= '0' && c <= '9';
}

int len_envp_key(char *str) {
    int i = 0;
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    return i;
}

int len_envp(char **envp_cpy)
{
    int i;

    i = 0;
    while (envp_cpy[i] != NULL)
        i++;
    return (i);
}

int print_var_export(char **envp_cpy, int len_envp)
{
    int i;
    int l;

	i = 0;
    while (i < len_envp)
    {
		l = 0;
		write(1, "declare -x ", 11);
        while (envp_cpy[i][l])
        {
            ft_putchar_fd(envp_cpy[i][l], 1);
            l++;
        }
		write(1, "\n", 1);
        i++;
    }
	return (0);
}

int export_var_exist(char *str, char **envp_cpy)
{
	int	i;

	i = len_envp_key(str);
	while (*envp_cpy)
	{
		if (ft_strncmp(str, *envp_cpy, i) == 0 && len_envp_key(*envp_cpy) == i)
			return (1);
		envp_cpy++;
	}
	return (0);
}

void	update_export_var(char *str, char **envp_cpy)
{
	int	i;
	int	l;

	i = len_envp_key(str);
	l = 0;
	while (envp_cpy[l])
	{
		if (ft_strncmp(str, envp_cpy[l], i) == 0 && len_envp_key(envp_cpy[l]) == i)
		{
			free(envp_cpy[l]);
			envp_cpy[l] = ft_strdup(str);
			return ;
		}
		l++;
	}
	envp_cpy[l] = ft_strdup(str);
	envp_cpy[l + 1] = NULL;
}

int export_add_value(char *str, char **envp_cpy, int i)
{
    char    *tmp;
    char    *n_val;
    int     n = 0;
    int     l = 0;

    i += 2;
    tmp = malloc(sizeof(char) * (ft_strlen(str + i) + 1));
    if (!tmp)
        return (0);
    while (str[i])
    {
        tmp[n++] = str[i++];
    }
    tmp[n] = '\0';

    while (envp_cpy[l])
    {
        if (ft_strncmp(str, envp_cpy[l], len_envp_key(str)) == 0
            && len_envp_key(envp_cpy[l]) == len_envp_key(str))
        {
            n_val = ft_strjoin(envp_cpy[l], tmp);
            free(envp_cpy[l]);
            envp_cpy[l] = n_val;
            free(tmp);
            return (1);
        }
        l++;
    }
    free(tmp);
    return (0);
}

int validate_export_arg(char *str, char **envp_cpy)
{
    int i = 0;

    if (!str || ft_isdigit(str[0]) || str[0] == '=')
        return (0);
    while (str[i] && str[i] != '=' && str[i] != '+')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    if (str[i] == '+' && str[i + 1] == '=')
        return (export_add_value(str, envp_cpy, i));
    if (str[i] == '=' || str[i] == '\0')
        return (1);
    return (0);
}


int ft_export(char **args, char **envp_cpy)
{
	int	rst = 0;

	if (!args || args[0] == NULL)
		return (print_var_export(envp_cpy, len_envp(envp_cpy)));

	while (*args)
	{
		if (validate_export_arg(*args, envp_cpy) && !export_var_exist(*args, envp_cpy))
			update_export_var(*args, envp_cpy);
		args++;
	}
	return (rst);
}

char **copy_env(char **envp)
{
    int len = len_envp(envp);
    char **copy = malloc(sizeof(char *) * (len + 50)); // marge de croissance
    int i = 0;
    while (envp[i])
    {
        copy[i] = strdup(envp[i]);
        i++;
    }
    copy[i] = NULL;
    return copy;
}

// Fonction utilitaire pour imprimer l’environnement
void print_env(char **envp)
{
    printf("---- Environnement ----\n");
    for (int i = 0; envp[i]; i++)
        printf("[%d] %s\n", i, envp[i]);
    printf("-----------------------\n");
}

// Tests en série
void test_case(char *description, char **args, char **envp)
{
    printf("\n===== %s =====\n", description);
    ft_export(args, envp);
    print_env(envp);
}

int main(void)
{
    char *initial_env[] = {
        strdup("PATH=/usr/bin"),
        strdup("HOME=/home/student"),
        NULL
    };

    char **envp_cpy = copy_env(initial_env);

    // 1. export sans argument
    test_case("1. Export sans argument", NULL, envp_cpy);

    // 2. export VAR=value
    char *test2[] = { "USER=student42", "SHELL=/bin/bash", NULL };
    test_case("2. Export de nouvelles variables", test2, envp_cpy);

    // 3. export d'une variable existante (écrasement)
    char *test3[] = { "USER=root", NULL };
    test_case("3. Redéfinir une variable existante", test3, envp_cpy);

    // 4. export avec +=
    char *test4[] = { "USER+=_dev", NULL };
    test_case("4. Ajout avec += (concat)", test4, envp_cpy);

    // 5. export d'une variable sans valeur (clé seule)
    char *test5[] = { "DEBUG", NULL };
    test_case("5. Clé seule sans valeur", test5, envp_cpy);

    // 6. concaténation après export d'une clé seule
    char *test6[] = { "DEBUG+=_mode", NULL };
    test_case("6. += après export d'une clé seule", test6, envp_cpy);

    // 7. export invalide : commence par chiffre, ou juste '='
    char *test7[] = { "1INVALID=bad", "=oops", NULL };
    test_case("7. Mauvais identifiants (invalides)", test7, envp_cpy);

    // 8. export VAR+= (sans contenu à ajouter)
    char *test8[] = { "DEBUG+=", NULL };
    test_case("8. += sans valeur à ajouter", test8, envp_cpy);

    // 9. export d’un nom avec symbole non autorisé
    char *test9[] = { "NA-ME=value", "VAR$=bad", NULL };
    test_case("9. Nom de variable invalide (caractères interdits)", test9, envp_cpy);

    // Libération
    for (int i = 0; envp_cpy[i]; i++)
        free(envp_cpy[i]);
    free(envp_cpy);

    return 0;
}
