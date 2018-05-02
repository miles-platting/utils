/////////////////////////////////////////////////////////////////////////////
// Name:        libutils.h
// Author:      David Beech
/////////////////////////////////////////////////////////////////////////////

#ifndef __libutils_H__
#define __libutils_H__


#include <exception>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>

using namespace std;

namespace oz_utils
{
	typedef vector<string>				vector_str;
	typedef vector<vector_str>			vector_record;
	typedef map<string, string>			str_str_array;
	typedef map<int, string>			int_str_array;
	typedef map<int, string>			field_map;
	typedef map<string, string>			str_str_map;
	typedef multimap<string, string>	str_str_multimap;
	typedef vector<str_str_map>			record_vector;
	typedef pair<string, string>		str_str_pair;
	typedef vector<str_str_pair>		vector_str_pair;
	typedef vector<bool>				vector_bool;

	const double LU_PI = 3.141592654;
	const double LU_RAD = (360.0/(2 * LU_PI));

	double utan(double);
	double ucos(double);
	double usin(double);

	bool 	is_dir_exist(const std::string& path);
	bool 	make_path(const std::string& path);
	void	replace_all(string& str, const string& s_from, const string& s_to);
	string 	localtime_now();
	int 	day_of_week(int y, int m, int d);	/* 0 = Sunday */

/*!	if x2 is within d_limit of x1 make x2 = x1
*/
	template <typename D>
	void delta_swap(D x1, D& x2, D d_limit)
	{	D d_x = abs(x1 - x2);
		if (d_x <= d_limit)
		{	x2 = x1;
		}
	}

/*!	if x2 - x1 is less than <= d_limit and x2 > x1 return true
	ie determine if a point x1 is close to x2
*/
	template <typename D>
	bool delta_close(D x1, D x2, D d_limit)
	{	D d_x = x2 - x1;
		return d_x <= d_limit && d_x > 0;
	}

	int day_of_week(int y, int m, int d);	/* 0 = Sunday */
	extern const string s_months[];
	const extern string s_days[];
	const extern string s_months_full[];
	const extern string s_days_full[];

    bool save_file			(string fname, string& data, string& s_msg);
    bool append_file		(string& fname, string& data, string& s_msg);
    bool copy_file			(string& srcfname,string& destfname, string& t);
    bool read_file			(string fname, string& data, string& s_msg);
    bool read_file_binary	(string& fname, string& data, string& s_msg);
    bool save_file_binary	(string& fname, string& data, string& s_msg);
    void validate_file_name	(string& fname);
    string get_file_contents(const char *filename);
    bool get_file_contents	(string fname, string& s_data, string& s_msg);

	int			qsort_dbl           (const void *a, const void *b);
	int			compare_double		(double a, double b);

	bool		is_empty_field		(string& data);
	string		str_clean			(string& );
	void		check_str_db		(string& data);
	void		check_str_db		(vector_str& data);
	void		check_pc			(vector_str& data);


	void		cvt_str_dbl			(string& src, double& tgt);
	void		prepare_string		(const string& tmp, string& tgt);
	void		check_valid			(string& data, const char* ws);
	void		check_valid			(vector_str& data, const char* ws);
	void		check_valid			(str_str_map& data, const char* ws);
	bool		connected_state		(string&);
	bool		connected_state		(void);
	int 		split				(vector_str &v, string s, string s_key);
	vector_str  split				(const string &s, char delim);

	void		get_mac_address		(string&);

	/* 	Trim a string: ie remove any characters specified in char array t
		from string s
	*/
	string& rtrim(string& s, const char* t);
	string& ltrim(string& s, const char* t);
	string&  trim(string& s, const char* t);

	string row(string data);
	string cell(string data);
	string cell(char* data);
	string cellright(string data);
	string cellright(char* data);

	string get_utils_version(void);

	string http_get_field(const string key, const string s_data, const char* t);
	
	/* A very simple logger */
	class logger
	{	public:
			shared_ptr<std::ofstream> log_stream;
			/*
			The explicit specifier specifies that a constructor or conversion 
			function (since C++11) doesn't allow implicit conversions or 
			copy-initialization. It may only appear within the decl-specifier-seq 
			of the declaration of such a function within its class definition.
			*/
			explicit logger(char const *s_path);
			void log_msg(char* caller, string m_msg, bool b_nl = true);
			void log_msg(string caller, string m_msg, bool b_nl = true);
			string s_file_name;
	};

} //end namespace oz_utils

#endif
