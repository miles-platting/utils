/////////////////////////////////////////////////////////////////////////////
// Name:        utils.cpp
// Author:      David Beech
/////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/stat.h> 	// stat
#include <errno.h>    	// errno, ENOENT, EEXIST
#include <unistd.h>		// F_OK

#include <memory>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>
#include <strstream>
#include <exception>
#include <memory>
#include <ctime>

#include <cctype>
#include <algorithm>
#include <streambuf>

#include "utils.h"
using namespace oz_utils;

/*
	0.4.0 	Remove file_utils namespace and encapsulate
			methods in oz_utils
*/
const string UTILSVERSION = "0.4.0-dev";

/*
timestamp_t get_timestamp ()
{
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

off_t fsize(string filename) {
    struct stat st;

    if (stat(filename.c_str(), &st) == 0)
        return st.st_size;
    fprintf(stderr, "Cannot determine size of %s: %s\n",
        filename.c_str(), strerror(errno));

    return -1;
}

char *read_file(string filename, string msg, long* i_ok)
{   if (access( filename.c_str(), F_OK) != -1 )
    {   FILE *f         = fopen(filename.c_str(), "rt");
        long length     = fsize(filename.c_str());
        char *buffer    = (char *) malloc(length + 1);
        buffer[length]  = '\0';
        fread(buffer, 1, length, f);
        fclose(f);
        *i_ok = length;
        return buffer;
    }
    msg = "NON_EXISTENT_FILE";
    return NULL;
}

void sql_stmt(sqlite3* db, string& stmt, string& s_error) {
  char *errmsg;
  int   ret;

  ret = sqlite3_exec(db, stmt.c_str(), 0, 0, &errmsg);

  if (ret != SQLITE_OK) {
    s_error = fmt::format("Error {0} in {1}", errmsg, stmt);
  }
}
*/

/*
using field_names = vector<string>;         //table field names
using record_data = vector<string>;         //field data of a record
using record_set  = vector<record_data>;    //a set of records

struct result_set {
  field_names sv_field_names;
  record_set vrs_set;
};

result_set rs;

int build_table_callback
  ( void *p_data,
    int num_fields,
    char **p_fields,
    char **p_col_names
  ) {

  int i_first_row = 0;
  int i;
  int *p_rn = (int*)p_data;

  if (i_first_row) {
    i_first_row = 0;
    for (i = 0; i < num_fields; i++) {
      rs.sv_field_names.push_back(string(p_col_names[i]));
    }
  }

  (*p_rn)++;

  record_data rd;
  for (i = 0; i < num_fields; i++) {
    rd.push_back(string(p_fields[i]));
  }
  rs.vrs_set.push_back(rd);
 
  return 0;
}
*/
/*
int select_stmt_build(sqlite3* db, const string& stmt, string& s_error) {
  char *errmsg;
  int   ret;
  int   nrecs = 0;

  ret = sqlite3_exec(db, stmt.c_str(), build_table_callback, &nrecs, &errmsg);
  if (ret != SQLITE_OK) {
    s_error = fmt::format("Error {0} in {1}", string(errmsg), stmt);
    return 0;
  }
  return nrecs;
}
*/

typedef std::chrono::system_clock Clock;


//These should adaptable/modifiable for locale 
const string oz_utils::s_months[]     
	= 	{	"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug",
           	"Sep","Oct","Nov","Dec"
        };
const string oz_utils::s_months_full[]
	= 	{ 	"January","February","March","April","May","June",
           	"July","August","September","October",
			"November","December"
		};
const string oz_utils::s_days[]
	= 	{ 	"Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
const string oz_utils::s_days_full[]   
	= 	{ 	"Sunday","Monday","Tueday","Wednesday","Thursday",
           	"Friday","Saturday"
       	};


int oz_utils::day_of_week(int y, int m, int d)	/* 0 = Sunday */
{	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

// trim from end of string (right)

string& oz_utils::rtrim(std::string& s, const char* t)
{    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
string& oz_utils::ltrim(std::string& s, const char* t)
{    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (left & right)
string& oz_utils::trim(std::string& s, const char* t)
{    return ltrim(rtrim(s, t), t);
}

/*!	Find tag "key" and return its value

*/

string oz_utils::http_get_field
	(const string key, const string s_data, const char* t)
{	string::size_type start, end;
	string strStart, strEnd, result;

	strStart = "<" + key + ">";
	strEnd = "</" + key + ">";
	result.clear();

	start = s_data.find(strStart);
	if (start != string::npos)
	{	end = s_data.find(strEnd);
		if (end != string::npos)
		{	start += strStart.length();
			result = s_data.substr(start, end - start);
			trim(result,t);
		}
	}
	return result;
}

string oz_utils::get_utils_version(void)
{	return UTILSVERSION;
}

double oz_utils::utan(double degrees)
{	return tan(degrees/LU_RAD);
}

double oz_utils::ucos(double degrees)
{	return cos(degrees/LU_RAD);
}

double oz_utils::usin(double degrees)
{	return sin(degrees/LU_RAD);
}

string oz_utils::localtime_now()
{	string s;
	time_t rawtime;
  	struct tm * timeinfo;
  	time (&rawtime);
	timeinfo = localtime (&rawtime);
	s = asctime(timeinfo);
  	return s;
}


/*
This is probably not available on Windows.
*/
bool oz_utils::is_dir_exist(const std::string& path)
{   
	struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {	return false;
    }
    return (info.st_mode & S_IFDIR) != 0;

}

bool oz_utils::make_path(const std::string& path)
{
    mode_t mode = 0755;
    int ret = mkdir(path.c_str(), mode);
    if (ret == 0)
        return true;

    switch (errno)
    {	case ENOENT:
        {	int pos = path.find_last_of('/');
            if (pos == std::string::npos)
                return false;
            if (!make_path( path.substr(0, pos) ))
                return false;
        }
        // now, try to create again
        return 0 == mkdir(path.c_str(), mode);
    	case EEXIST:
        	return is_dir_exist(path);
    	default:
        	return false;
    }
}


int oz_utils::qsort_dbl(const void *a, const void *b)
{	const double *da = (const double *) a;
	const double *db = (const double *) b;
	return (*da > *db) - (*da < *db);
}

void oz_utils::replace_all(	string& str, const string& s_from, 
							const string& s_to) 
{
    if (s_from.empty())
        return;
    string wsRet;
    wsRet.reserve(str.length());
    size_t start_pos = 0, pos;
    while ((pos = str.find(s_from, start_pos)) != string::npos) {
        wsRet += str.substr(start_pos, pos - start_pos);
        wsRet += s_to;
        pos += s_from.length();
        start_pos = pos;
    }
    wsRet += str.substr(start_pos);
    str.swap(wsRet);
}

//xml_read.cpp was here

bool oz_utils::is_empty_field(string& data)
{	return data == "''";
}

string oz_utils::str_clean(string& s_src)
{	string t;
	t = s_src;
	if (!is_empty_field(s_src))
		replace_all(t,"'","''");
	replace_all(t,"%","%%");
	replace_all(t,"^","");
	replace_all(t,"|","");
	return t;
}

void oz_utils::check_str_db(string& data)
{	if (!is_empty_field(data))
		replace_all(data,"'","''");
	replace_all(data,"%","%%");
}

void oz_utils::check_str_db(vector_str& data)
{	vector_str::iterator it;
	for (it = data.begin(); it != data.end(); it++)
	{	check_str_db(*it);
	}
}

void oz_utils::check_pc(vector_str& data)
{	unsigned int k;
	for (k = 0; k < data.size(); k++)
	{	replace_all(data[k],"%","%%");
	}
}


/*! Some characters ' ^ and | need to be filtered from text which is 
	written to the databases.

	- ' replace with ''
	- ^ replace with space
	- | replace with space

	^ and | are used by current database code. Will not be required in 
	future version.

*/

void oz_utils::check_valid(string& data, const char* ws)
{	if (!is_empty_field(data))
	{	replace_all(data,"'","''");
	}
	replace_all(data,"^","");
	replace_all(data,"|","");
	trim(data,ws);
}

void oz_utils::check_valid(vector_str& data, const char* ws)
{	unsigned int k;
	for (k = 0; k < data.size(); k++)
	{	check_valid(data[k], ws);
	}
}

void oz_utils::check_valid(str_str_map& data, const char* ws)
{	str_str_map::iterator it;
	for (it = data.begin(); it != data.end(); ++it)
	{	check_valid((*it).second, ws);
	}
}

void oz_utils::prepare_string(const string& tmp, string& tgt)
{	tgt = tmp;
	if (!is_empty_field(tgt))
		replace_all(tgt,"'","''");
}

void oz_utils::cvt_str_dbl(string& src, double& tgt)
{	replace_all(src,",","");
	tgt = strtod(src.c_str(),NULL);
}


/*	split

	Split a string (s) at each s_key occurence and
	return a string vector containing the resultant
	strings

*/
int oz_utils::split(vector_str &v, string s, string s_key)
{
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(s_key)) != std::string::npos) {
    	token = s.substr(0, pos);
    	v.push_back(token);
    	s.erase(0, pos + s_key.length());
	}
	v.push_back(s);
	return v.size();
}

vector_str oz_utils::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector_str tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

bool oz_utils::get_file_contents(string fname, string& s_data, string& s_msg)
{	std::ifstream in(fname, std::ios::in | std::ios::binary);
  	if (in)
  	{	s_data = std::string((std::istreambuf_iterator<char>(in)), 
  				std::istreambuf_iterator<char>());
  		return true;
  	}
  	s_msg = string(__FUNCTION__) + string (" cannot open ") + fname;
  	return false;
}

bool oz_utils::read_file(string fname, string& data, string& s_msg)
{	ifstream file;
	string t;
	ostringstream ost;
	file.open(fname.c_str(), ios::in);
	if (file.is_open())
	{	ost << file.rdbuf();
		data = ost.str();
		file.close();
		return true;
	}
	else
	{	s_msg = string(__FUNCTION__) + string (" cannot open ") 
					+ fname; 
		return false;
	}
}

bool oz_utils::read_file_binary(string& fname, string& data, string& s_msg)
{	ifstream file;
	ostringstream ost;

	file.open(fname.c_str(), ios::in | ios::binary);
	if (file.is_open())
	{	ost << file.rdbuf();
		data = ost.str();
		file.close();
		return true;
	}
	else
	{	s_msg = string(__FUNCTION__) + string (" cannot open ") 
					+ fname;
 		return false;
	}
}

bool oz_utils::save_file_binary(string& fname, string& data, string& s_msg)
{	ofstream file;
	string t;

	file.open(fname.c_str(), ios::out  | ios::binary);
	if (file.is_open())
	{	file << data;
		file.close();
		return true;
	}
	else
	{	s_msg = string(__FUNCTION__) + string (" cannot open ") + fname;
 		return false;
	}
}

bool oz_utils::save_file(string fname, string& data, string& s_msg)
{	ofstream file;
	string t;
	bool status = false;
	
	status = !fname.empty();
	if (status)
	{	try
		{	file.open(fname.c_str(), ios::out);
			if (file.is_open())
			{	file << data;
				file.close();
			}
			else
			{	s_msg = string(__FUNCTION__) + string (" cannot save ") 
							+ fname;
 				status = false;
			}
		}
		catch (std::exception& e)
		{	s_msg = string(__FUNCTION__) + string (" cannot open ") 
						+ fname + " " + e.what();
 			status = false;
		}
	}
	else
	{	s_msg = string(__FUNCTION__) + string (" empty file name ") + fname;
		status = false;
	}
	return status;
}

/*
	Test: attempt to open non-existent file
*/
bool oz_utils::append_file(string& fname, string& data, string& s_msg)
{	ofstream file;
	string t;
	bool b_status{false};

	b_status = !fname.empty();
	if (b_status) {
		try {
			file.open(fname.c_str(), std::ios::out|std::ios::app);
			if (file.is_open())
			{	file << data;
				file.close();
				b_status = true;
			}
			else
			{	s_msg = string(__FUNCTION__) + string (" cannot open ") 
							+ fname;
 
			}
		} 
		catch (std::exception& e) {
			s_msg = string(__FUNCTION__) + string (" cannot open ") + 
						fname + " " + e.what();
			b_status = false;
		}
	}
	return b_status;
}

bool oz_utils::copy_file(string& srcfname, string& destfname, string& s_msg)
{	ofstream srcfile;
	ofstream destfile;
	bool status = false;

	srcfile.open(srcfname.c_str(), ios::in | ios::binary);
	status = srcfile.is_open();
	if (status)
	{	destfile.open(destfname.c_str(), ios::out | ios::binary);
		status = destfile.is_open();
		if (status)
		{	destfile << srcfile.rdbuf();
			destfile.close();
		}
		else
		{	srcfile.close();
			s_msg = string(__FUNCTION__) + string (" cannot create ") 
						+ destfname;
		}
		srcfile.close();
	}
	else
	{	s_msg = string(__FUNCTION__) + string (" cannot open ") 
					+ srcfname;
	}
	return status;
}

void oz_utils::validate_file_name(string& fn)
{	replace_all(fn," ","_");
	replace_all(fn,"?","_");
	replace_all(fn,"[","_");
	replace_all(fn,"]","_");
	replace_all(fn,"/","_");
	replace_all(fn,"\\","_");
	replace_all(fn,"=","_");
	replace_all(fn,"+","_");
	replace_all(fn,"<","_");
	replace_all(fn,">","_");
	replace_all(fn,":","_");
	replace_all(fn,";","_");
	replace_all(fn,"\"","_");
	replace_all(fn,",","_");
}

int oz_utils::compare_double(double a, double b)
{	int v = 0;
	if (a < b) v = -1;
	if (a == b) v = 0;
	if (a > b) v = 1;
	return v;
}

string oz_utils::row(string data)
{	string t;
	t = "<tr>" + data + "</tr>\n";
	return t;
}

string oz_utils::cell(string data)
{	string t;
	t = "<td>" + data + "</td>";
	return t;
}

string oz_utils::cell(char* data)
{	string t;
	t = "<td>" + string(data) + "</td>";
	return t;
}

string oz_utils::cellright(string data)
{	string t;
	t = "<td align = \"right\">" + data + "</td>";
	return t;
}

string oz_utils::cellright(char* data)
{	string t;
	t = "<td align = \"right\">" + string(data) + "</td>";
	return t;
}

oz_utils::logger::logger(char const *s_path)
	: log_stream( new std::ofstream(s_path))
{	s_file_name = s_path;	
};

void oz_utils::logger::log_msg(char* caller, string m_msg, bool b_nl)
{	if (b_nl)
	{	*log_stream << caller << endl << m_msg << endl;
	}
	else
	{	*log_stream << caller << " " << m_msg << endl;
	}
}

void oz_utils::logger::log_msg(string caller, string m_msg, bool b_nl)
{	if (b_nl)
	{	*log_stream << caller << endl << m_msg << endl;
	}
	else
	{	*log_stream << caller << " " << m_msg << endl;
	}
}

