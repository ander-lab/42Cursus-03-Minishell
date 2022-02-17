/* ************************************************************************** */
/*															  		          */
/*													   :::      :::::::: 	  */
/*	█╗      ███████╗██╗  ██╗███████╗██████╗           :+:      :+:    :+:	  */
/*	██║     ██╔════╝╚██╗██╔╝██╔════╝██╔══██╗        +:+ +:+         +:+  	  */
/*	██║     █████╗   ╚███╔╝ █████╗  ██████╔╝      +#+  +:+       +#+     	  */
/*	██║     ██╔══╝   ██╔██╗ ██╔══╝  ██╔══██╗    +#+#+#+#+#+   +#+        	  */
/*	███████╗███████╗██╔╝ ██╗███████╗██║  ██║         #+#    #+#          	  */
/*	╚══════╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝		###   ########.fr    	  */
/*															  		          */
/* ************************************************************************** */

#include "../includes/minishell.h"

int *ft_pass_to_string(t_list *lst)
{
	char	*str;
	int	i;

	i = 0;
	str = ft_calloc(ft_lstsize(lst), sizeof(int));
	while (lst)
	{
		str[i] = ((t_token_data *)lst->next->content)->token;
		lst = lst->next;
		i++;
	}
	return (str);
}

int main(void)
{
	int *str;
	int  test = 0;	
	char *test_str;
	t_list *lst;

	lst = NULL;
	str = ft_pass_to_string(lst);

	/*touch >*/
	test_str = ft_strdup("touch >");
	printf ("--------------TEST%i--------------", test);
	if (ft_str)
}
