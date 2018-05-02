
#include <iostream>   // 
#include "utils.h"

using namespace std;
using namespace std::chrono;


int main(int argc, char** argv)
{
	oz_utils::logger log("thelog.txt");

	log.log_msg(__FUNCTION__,"starting",false);
	log.log_msg(__FUNCTION__,oz_utils::get_utils_version());

	string s_one("cppformat");
	string s_two("cppnoformat");

	if (oz_utils::is_dir_exist(s_one)) 
	{	cout << s_one << " Exists" << endl;
	}
	else
	{	cout << s_one << " Doesn't Exist" << endl;
	}
	if (oz_utils::is_dir_exist(s_two)) 
	{	cout << s_two << " Exists" << endl;
	}
	else
	{	cout << s_two << " Doesn't Exist" << endl;
	}

	string s_fname("save-test.txt");
	string s_data;
	string s_msg;
	bool b_test_ok;

	b_test_ok = oz_utils::read_file(s_fname, s_data, s_msg);
	cout << __LINE__ << " Check file read" << endl;
	if (b_test_ok) {
		cout << s_data << endl;
	}
	else {
		cout << s_msg << endl;
	}

	s_fname = "my-new-file.txt";
	b_test_ok = oz_utils::save_file(s_fname,s_data,s_msg);
	if (b_test_ok) {
		cout << "file saved\n";
	}
	else {
		cout << "file save failed: " << s_msg << "\n";
	}

	string s_new_name{"my-new-file-copy.txt"};
	b_test_ok = oz_utils::copy_file(s_fname,s_new_name,s_msg);
	if (b_test_ok) {
		cout << "file copy ok\n";
	}
	else {
		cout << "file copy failed: " << s_msg << "\n";
	}

	string s_added("\nadded\n");
	b_test_ok = oz_utils::append_file(s_fname,s_added,s_msg);
	if (b_test_ok) {
		cout << "file append ok\n";
	}
	else {
		cout << "file append failed: " << s_msg << "\n";
	}

	oz_utils::make_path("test-this/sub/sub");

	oz_utils::str_str_array s_array;
	string s_right = oz_utils::cellright(string("Hello"));
	cout << s_right << endl;

	string srfile("badfile.junk");
	cout << "Test missing binary file\n";
	b_test_ok = oz_utils::read_file_binary(srfile,s_data,s_msg);
	if (!b_test_ok) {
		cout << "Test missing binary file" << " passed\n";
	}


	string s_str("David Robert Beech");
	oz_utils::validate_file_name(s_str);
	cout << s_str << endl;
	cout << "Done\n";

	const char* ws = " \t\n\r\f\v.";


    string s1 ="David|Robert|Beech|Neill|Bostock|Hewitt|Proudlove|Sidebotham|Wulff";
    string s_delimiter = "|";
   	oz_utils::vector_str v;

    int result = oz_utils::split(v,s1,s_delimiter);
    cout << result << endl;
 
     for (auto n : v) {
        std::cout << "as is " << n << '\n';
    }

    //std::cout << "system_clock::now() " << system_clock::now() << '\n';
    std::cout << "localtime_now() " << oz_utils::localtime_now() << '\n';

    std::time_t t_result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&t_result))
              << result << " seconds since the Epoch\n";

    std::cout << "C++ version " << __cplusplus << "\n";

    //check_time();

    int dow = oz_utils::day_of_week(1948,4,25);
    std::cout << "David was born on " << oz_utils::s_days_full[dow] << std::endl;
    dow = oz_utils::day_of_week(1950,3,11);
 	std::cout << "Karen was born on " << oz_utils::s_days_full[dow] << std::endl;

	std::time_t t = std::time(nullptr);

  	cout << "SPLIT TEST 2 (with string delimiter) 999\n";
    s1 =	"David999Robert999Bostock999Hewitt999Proudlove999Sidebotham999"
    		"Dowler999"
    		"999"
    		"Karen999Maree999"
    		"999"
    s_delimiter = "999";
	oz_utils::vector_str v2;

    result = oz_utils::split(v2,s1,s_delimiter);

    cout << "vector size: " << result << endl;
    for (auto n : v2) {
    	cout << n << "\n";
    }

    cout << "Test all string handling for empty string\n\n";

	int i_len;
	bool bql = oz_utils::read_file("the_missing.file",s_data,s_msg);  
	cout << s_msg << "\n";       

	//trim testing
	string s_trim_test(" David Robert Beech ");
	cout 	<< s_trim_test << " left before " << s_trim_test.length() 
			<< " after " << oz_utils::ltrim(s_trim_test,ws) << s_trim_test.length()
			<< "\n";
	cout 	<< s_trim_test << " right before " << s_trim_test.length()  
			<< " after " << oz_utils::rtrim(s_trim_test,ws) << s_trim_test.length()
			<< "\n";

	s_trim_test = "...David   ";
	cout 	<< s_trim_test << " both before " << s_trim_test.length() << " "
			<< oz_utils::trim(s_trim_test,ws) << " " << s_trim_test.length()
			<< "\n";

	cout << "What about a string deflate ie remove all in char set x from a string\n"
		<< "But how would you do efficiently?\n\n";

	string s_test;
	oz_utils::rtrim(s_test,ws);
	oz_utils::ltrim(s_test,ws);
	oz_utils::trim(s_test,ws);

	cout << "version: " << oz_utils::get_utils_version() << "\n";
	log.log_msg("Finished","goodbye",false);
	cout << "Trust me, I'm a porgrammer\n";

	
}