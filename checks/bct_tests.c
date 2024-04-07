#include <assert.h>
#include <libc.h>
#include <stdbool.h>
#include "../include/minishell.h"

bool	strequal(char *str0, char *str1)
{
	int	rslt = strcmp(str0, str1);
	if (rslt)
		return (false);
	else
		return (true);
}

// "echo hi && ls -a -l && ls .gitignore | wc -l"

int	main(void)
{
	printf("\n#0 BINARY-COMMAND-TREE MANUAL POPULATION:\n");
	t_bct	*bct = malloc(sizeof(t_bct));
	t_bct	*left_child_node = malloc(sizeof(t_bct));
	t_bct	*right_child_node = malloc(sizeof(t_bct));
	bct->cmd = "&&";
	bct->left = left_child_node;
	bct->right = right_child_node;
	bct->left->cmd = "echo hi";
	bct->right->cmd = "ls";
	assert(strequal("&&", bct->cmd));
	printf("	bct->cmd: GOOD\n");
	assert(strequal("echo hi", bct->left->cmd));
	printf("	bct->left->cmd: GOOD\n");
	assert(strequal("ls", bct->right->cmd));
	printf("	bct->right->cmd: GOOD\n\n");



	printf("\n#1 PRIORITIZED TOKEN-LIST:\n");
	t_token	*token = malloc(sizeof(t_token));
	assert(strequal("|", token->word));
	assert(strequal("&&", token->next->word));
	assert(strequal("echo", token->next->next->word));
	assert(strequal("hi", token->next->next->next->word));
	assert(strequal("ls", token->next->next->next->next->word));
	assert(strequal("-a", token->next->next->next->next->next->word));
	assert(strequal("-l", token->next->next->next->next->next->next->word));
	assert(strequal("ls", token->next->next->next->next->next->next->next->word));
	assert(strequal(".gitignore", token->next->next->next->next->next->next->next->next->word));
	assert(strequal("wc", token->next->next->next->next->next->next->next->next->next->word));
	assert(strequal("-l", token->next->next->next->next->next->next->next->next->next->next->word));
}