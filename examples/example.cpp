/*  $Id: example.cpp,v 1.6 2015/01/21 03:00:42 sarrazip Exp $
    C++ BoolStuff example program.

    Written by Pierre Sarrazin <http://sarrazip.com/>
    This file is in the public domain.
*/

#include <boolstuff/BoolExprParser.h>
#include <assert.h>
#include <stdlib.h>

using namespace std;
using namespace boolstuff;


static
ostream &
operator << (ostream &out, const set<string> &s)
{
    for (set<string>::const_iterator it = s.begin(); it != s.end(); it++)
        out << *it << " ";
    return out;
}


int main()
{
    BoolExprParser parser;
    string line;

    while (getline(cin, line))
    {
        try
        {
            BoolExpr<string> *expr = parser.parse(line);
            
            assert(expr != NULL);  // any error must have thrown an exception

            cout << "Original expression     : " << flush;
            expr->print(cout);
            cout << "\n";

            BoolExpr<string> *dnf = BoolExpr<string>::getDisjunctiveNormalForm(expr);

            // NOTE: 'expr' is now unusable. 
            // The original tree has been transformed by the preceding call. 
            //
            expr = NULL;

            cout << "Disjunctive normal form : ";
            if (dnf != NULL)
                cout << dnf;
            else
                cout << "FALSE";

            cout << "\n";

            if (dnf != NULL)
            {
                typedef vector<const BoolExpr<string> *> V;
                typedef V::const_iterator IT;

                V termRoots;
                dnf->getDNFTermRoots(inserter(termRoots, termRoots.end()));
                for (IT it = termRoots.begin(); it != termRoots.end(); it++)
                {
                    const BoolExpr<string> *term = *it;
                    set<string> positives, negatives;
                    term->getTreeVariables(positives, negatives);

                    cout << "Term       : " << term << "\n";
                    cout << "  Positives: " << positives << "\n";
                    cout << "  Negatives: " << negatives << "\n";
                }
            }

            cout << endl;
            delete dnf;

            // Note that we do not destroy 'expr', because it was implicitly
            // destroyed by the call to boolstuff_get_disjunctive_normal_form().
        }
        catch (BoolExprParser::Error &err)
        {
            cout << "Error #" << err.code << " at character #" << err.index << endl;
        }
    }

    return EXIT_SUCCESS;
}
