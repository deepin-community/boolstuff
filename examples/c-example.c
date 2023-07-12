/*  $Id: c-example.c,v 1.1 2015/01/24 17:32:17 sarrazip Exp $
    C BoolStuff example program.

    Written by Pierre Sarrazin <http://sarrazip.com/>
    This file is in the public domain.
*/

#include <boolstuff/c-api.h>
#include <assert.h>
#include <stdlib.h>


static void print_variable_names(char *names[])
{
    size_t i;

    for (i = 0; names[i] != NULL; ++i)
        printf("%s ", names[i]);
}


int main()
{
    char line[512];

    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        boolexpr_t expr, dnf;
        size_t errorIndex;
        enum bool_error_t errorCode;

        expr = boolstuff_parse(line, &errorIndex, &errorCode);

        if (expr == NULL)
        {
            printf("Error #%d at character #%u\n\n", errorCode, (unsigned) errorIndex);
            continue;
        }

        printf("Original expression     : ");
        boolstuff_print_tree(stdout, expr);
        printf("\n");

        dnf = boolstuff_get_disjunctive_normal_form(expr);

        /*  NOTE: 'expr' is now unusable.
            The original tree has been transformed by the preceding call.
        */
        expr = NULL;

        printf("Disjunctive normal form : ");
        if (dnf != NULL)
            boolstuff_print_tree(stdout, dnf);
        else
            printf("FALSE");

        printf("\n");

        if (dnf != NULL)
        {
            size_t numRoots, i;
            boolexpr_t *treeRoots;  /* array */

            treeRoots = boolstuff_get_dnf_term_roots(dnf, &numRoots);

            for (i = 0; i < numRoots; ++i)
            {
                boolexpr_t term;
                char **positivesArray, **negativesArray;

                term = treeRoots[i];
                boolstuff_get_tree_variables(term, &positivesArray, &negativesArray);

                printf("Term       : ");
                boolstuff_print_tree(stdout, term);
                printf("\n");

                printf("Positives: ");
                print_variable_names(positivesArray);
                printf("\n");
                printf("Negatives: ");
                print_variable_names(negativesArray);
                printf("\n");

                boolstuff_free_variables_sets(positivesArray, negativesArray);
            }

            boolstuff_free_node_array(treeRoots);
        }

        printf("\n");
        boolstuff_destroy_tree(dnf);

        /*  Note that we do not destroy 'expr', because it was implicitly
            destroyed by the call to boolstuff_get_disjunctive_normal_form().
        */
    }

    return EXIT_SUCCESS;
}
