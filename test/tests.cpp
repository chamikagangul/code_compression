// C++ program for the above approach
#include <bits/stdc++.h>
using namespace std;

// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<string, int> &M)
{

    // Print the multimap
    for (auto &it : M)
    {
        cout << it.second << ' '
             << it.first << endl;
    }

    // Declare a multimap
    multimap<string, int> MM;

    // Insert every (key-value) pairs from
    // map M to multimap MM as (value-key)
    // pairs
    for (auto &it : M)
    {
        MM.insert({it.first, it.second});
    }
}

// Driver Code
int main()
{

    // Declare Map
    multimap<int, string> M;

    // Given Map
    M = {{-1, "aa2"},
         {-5, "aa1"},
         {-3, "aa1"},
         {-9, "aa1"},
         {-1, "aa1"},
         {-1, "aa4"},
         {-1, "aa3"},
         {-1, "aa6"}};

    for (auto &it : M)
    {
        cout << it.second << ' '
             << it.first << endl;
    }

    return 0;
}
