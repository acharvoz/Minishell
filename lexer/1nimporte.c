/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1nimporte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharvoz <acharvoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:05:46 by acharvoz          #+#    #+#             */
/*   Updated: 2025/04/09 18:40:47 by acharvoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*il faut faire en sorte que je supprime toutes les quotes saufs celles qui sont deja dans des quotes 
liste des tests et resultats :
-test'$HOME'test -> test$HOMEtest
-'$HOME' -> $HOME
-"$HOME" -> /home/acharvoz
-'"$HOME"' -> "$HOME"
-"'$HOME'" -> '/home/acharvoz'					//s'expand pas ici soucis
-e'c'"h"o -> fait echo donc ligne vide
-test'$HOME'test -> test$HOMEtest
-test"$HOME"test -> test/home/acharvoztest

-unclosed quotes
-espaces debut et fin // espaces avant apres quotes // espaces avant et apres pipes // pipes dans quotes // pipes hors quotes
*/