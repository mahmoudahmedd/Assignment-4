#include <iostream>
#include "bst_fci.h"
#include "string_line.h"

using namespace std;

int main()
{
    int line = 0;
    BSTFCI <stringLine> t;

    cout << "Enter text(enter DONE! on a separate line to exit): " << endl;

    /*
    I am for truth,
    no matter who tells it.
    I am for justice,
    no matter who it is for or against.
    Malcom X
    DONE!
    */

    while(true)
    {
        string str;
        getline(cin, str);

        str.erase(remove(str.begin(), str.end(), '.'), str.end());
        str.erase(remove(str.begin(), str.end(), ','), str.end());

        if (str == "DONE!")
            break;

        ++line;
        string word = "";

        for (unsigned int i = 0; i < str.size(); ++i)
        {
            if(str[i] != ' ')
            {
                word.push_back(str[i]);
            }
            else
            {
                t.insertStringLine(word, line);
                word = "";
            }
        }

        if (!word.empty())  /// handling last word in a line.
        {
            t.insertStringLine(word, line);
        }
    }

    t.linearPrint();

    return 0;
}
