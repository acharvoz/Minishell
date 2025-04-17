/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:05:46 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/17 14:44:58 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
liste des tests et resultats :
- test'$HOME'test -> test$HOMEtest
- '$HOME' -> $HOME
- "$HOME" -> /home/acharvoz
- '"$HOME"' -> "$HOME"
- "'$HOME'" -> '/home/acharvoz'
- e'c'"h"o -> fait echo donc ligne vide
- test'$HOME'test -> test$HOMEtest
- test"$HOME"test -> test/home/acharvoztest
- $USER$caca'$USER' -> acharvoz$USER
- asdasd "$HOME" -> asdasd /home/acharvoz

- unclosed quotes
- espaces debut et fin // espaces avant apres quotes
// espaces avant et apres pipes // pipes dans quotes // pipes hors quotes

- echo "12\"" -> demander comment ca doit se comporter
bugs :
<< $USER -> ne pas expand; faisable en fonction
*/