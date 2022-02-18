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
	int *str;
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

int	*ft_arrdup(const int *a, int len)
{
	int *a_dup;

	a_dup = (int *)malloc(sizeof(int) * len);
	if (!a_dup)
		return (0);
	ft_memcpy(a_dup, a, len);
	return (a_dup);
}

int main(void)
{
	int *str;
	int len;
	int  test = 0;	
	char *test_str;
	t_list *lst;

	lst = NULL;
	str = ft_pass_to_string(lst);
	len = ft_lstsize(lst);

	/*touch >*/
	test_str = ft_arrdup("touch >");
	printf ("--------------TEST%i--------------", test);
}
