/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iterator>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include <random>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
int main() 
{
    mt19937 mt; 
    uniform_int_distribution <int> int_dist(0, 1000);
    vector <int> vec(10); 
    
    generate(begin(vec), end(vec), [&](){return int_dist(mt);});
    

    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
   
    cout << endl;
    auto max_ele = max_element(cbegin(vec), cend(vec));
    int max = *max_ele;
    cout << "max value is: " << *max_ele << endl;
    cout << "index is: " << distance(cbegin(vec) ,max_ele) << endl;
    cout << "sum of vec is: " << accumulate(cbegin(vec), cend(vec), 0) << endl;
    
    auto parti = partition(begin(vec), end(vec), [](int n){return (n%2 == 0);});

    cout << "no of odd ele is :" << (cend(vec) - parti) << endl;
    
    vector <double> dub_vec(10); 
    cout << "new vec:" << endl; 
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    transform(begin(vec), end(vec),begin(dub_vec) ,[max](double n){return (n / max);});
    cout << endl;
    copy(dub_vec.begin(), dub_vec.end(), ostream_iterator<double>(cout, " "));
    cout << endl;

    vector <int> vec_cpy{vec}; 
    sort(begin(vec_cpy),end(vec_cpy));

    auto lower = lower_bound(begin(vec_cpy),end(vec_cpy), 455);
    copy(vec_cpy.begin(), vec_cpy.end(), ostream_iterator<int>(cout, " "));
    cout << endl << "lower bound is : " << *lower << endl;
    cout << "no of ele lower then 455 : " << distance(begin(vec_cpy), lower) << endl;
    vector <double> vec_dub;
    auto odd_iter = copy_if(vec_cpy.begin(), vec_cpy.end(), back_inserter(vec_dub), [](int v) {return (v % 2 == 1);});
    
    copy(vec_dub.begin(), vec_dub.end(), ostream_iterator<double>(cout, " "));
    cout << endl << "no of odd nums : " << vec_dub.size() << endl;
    sort(vec_dub.begin(), vec_dub.end() , greater<double>());
    copy(vec_dub.begin(), vec_dub.end(), ostream_iterator<double>(cout, " "));
    shuffle(next(begin(vec_dub)), prev(end(vec_dub)), mt);
    cout << endl << "after shuffle : " << endl; 
    copy(vec_dub.begin(), vec_dub.end(), ostream_iterator<double>(cout, " "));
    
    cout <<  endl  <<"this vec is : " << endl ;
    shuffle(begin(vec), end(vec), mt);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    
    auto last_ele = remove_if(vec.begin(), vec.end(), [](int v){return ((v % 2) == 1 );});
    ofstream file{"open.txt"};
    if(file.is_open() == false)
    {
        cout << "couln't open file";
    }

    copy(begin(vec), last_ele, ostream_iterator<int>(file, " "));

    ifstream word_file{"words.txt"};
    if(word_file.is_open() == false)
    {
        cout << "couln't open file";
    }
    
    vector <string> str_vec;

    istream_iterator <string> buf_iter_str(word_file) ,eof_iter;

    copy(buf_iter_str, eof_iter, back_inserter(str_vec));

    auto word_num = str_vec.size();


    transform(begin(str_vec), end(str_vec), begin(str_vec),
    [](string s) 
    {
        transform(begin(s), end(s), begin(s), [](char c){return toupper(c);});    
        s.erase(remove_if(begin(s), end(s),
                             [](char c) { return (!isalpha(c)); }), end(s));
        return s;
    });
    
    sort(begin(str_vec), end(str_vec));
    auto last = unique(begin(str_vec), end(str_vec));

    str_vec.erase(last, end(str_vec));
    
    cout << endl;
    copy(begin(str_vec), end(str_vec), ostream_iterator<string>(cout, " "));
    cout << endl;
    cout << endl; 

    word_file.clear();
    word_file.seekg(0 , ios::beg);
    istreambuf_iterator <char> buf_iter_char(word_file) ,eof_char_iter;
    
    auto char_num = count_if(buf_iter_char, eof_char_iter, [](char c){return true;});
    
    word_file.clear();
    word_file.seekg(0 , ios::beg);    
 
    istreambuf_iterator <char> buf_iter_char2(word_file);
    auto endl_num = count_if(buf_iter_char2, eof_char_iter, [](char c){return (c == '\n');});
    
    cout << endl << "NO. of chars: " << char_num << " No. of endl: " << endl_num << " No. of words: " << word_num << endl;
    
    ifstream word_file2{"words2.txt"};
    if(word_file.is_open() == false)
    {
        cout << "couln't open file";
    }
    word_file.clear();
    word_file.seekg(0 , ios::beg);   

    vector <string> vec_word;
    vector <string> vec_word2;
    vector <string> vec_common;
    istream_iterator <string> stream_word(word_file) ,eof_iter3;
    istream_iterator <string> stream_word2(word_file2) ,eof_iter2;
    copy(stream_word, eof_iter3, back_inserter(vec_word));
    copy(stream_word2, eof_iter2, back_inserter(vec_word2));

    transform(begin(vec_word), end(vec_word), begin(vec_word),
    [](string s) 
    {
        transform(begin(s), end(s), begin(s), [](char c){return toupper(c);});    
        s.erase(remove_if(begin(s), end(s),
                             [](char c) { return (!isalpha(c)); }), end(s));
        return s;
    });

    transform(begin(vec_word2), end(vec_word2), begin(vec_word2),
    [](string s) 
    {
        transform(begin(s), end(s), begin(s), [](char c){return toupper(c);});    
        s.erase(remove_if(begin(s), end(s),
                             [](char c) { return (!isalpha(c)); }), end(s));
        return s;
    });
 
    cout << endl;
    cout << endl;
    copy(begin(vec_word),end(vec_word), ostream_iterator <string> (cout, " "));

    cout << endl;
    copy(begin(vec_word2),end(vec_word2), ostream_iterator <string> (cout, " "));
    cout << endl;

    sort(begin(vec_word),end(vec_word));
    sort(begin(vec_word2),end(vec_word2));
    cout << endl << "intersect:  " << endl;
    set_intersection(begin(vec_word),end(vec_word),begin(vec_word2),end(vec_word2),back_inserter(vec_common));
    sort(begin(vec_common),end(vec_common));
    unique(begin(vec_common),end(vec_common));
    
    cout << endl;
    copy(begin(vec_common),end(vec_common), ostream_iterator <string> (cout, " "));
    cout << endl;

    vector <int> vec_ints(6);

    iota(begin(vec_ints), end(vec_ints),1);
    auto sum = partial_sum(begin(vec_ints), end(vec_ints),begin(vec_ints), multiplies<int>());
    
    //copy(begin(vec_ints),end(vec_ints), ostream_iterator <int> (cout, " "));
    cout << endl << "factorial sum : " << *prev(sum) << endl;
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
