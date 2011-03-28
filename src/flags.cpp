/*
   Copyright 2011 Carl Anderson

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <ctype.h>   /* for isgraph */
#include <getopt.h>  /* for getopt_long */
#include <libgen.h>  /* for basename */
#include <stdlib.h>  /* for atoi */
#include <string.h>  /* for strdup */

#include <iomanip>
#include <iostream>

#include "flags.hpp"

using namespace std;


// Static members.
string Flag::codes;
string Flag::program_name;
list<struct option> Flag::options;
list<Flag *> Flag::instances;
map<const char, Flag *> Flag::short_names;
map<const string, Flag *> Flag::long_names;

static unsigned int longest_long_name = 0;
static string prog_name;


// Special Flags.
DEFINE_flag(help, 0, "Display flags for this command.");


/**
 * 
 */
void Flag::show_help() {
  char * program_name = strdup(prog_name.c_str());
  cout << "\nUsage: " << basename(program_name);

  list<Flag *> & flags = Flag::instances;
  if (flags.empty()) return;

  cout << " [options]";
  for (list<Flag *>::iterator i = flags.begin(); i != flags.end(); ++i) {
    cout << "\n" << **i;
  }
  cout << endl;
}


/**
 * 
 */
int Flag::parse(int * p_argc, char *** p_argv, const bool remove_flags) {
  int argc = *p_argc;
  char ** argv = *p_argv;

  // Grab the program name from argv[0] for --help output later.
  prog_name = argv[0];

  // Put the options into an array, as getopt expects them.
  struct option * options = new struct option[Flag::options.size()];
  int x = 0;
  typedef list<struct option>::iterator iter;
  for (iter i = Flag::options.begin(), e = Flag::options.end(); i != e; ++i) {
    options[x++] = *i;
  }

  // Parse the arguments.
  for (int c = 0, index = 0; c != -1; index = 0) {
    c = getopt_long(argc, argv, Flag::codes.c_str(), options, &index);
    switch (c) {
      case -1: break;

      case 0: {  // longopt with no short name.
        const string long_name = options[index].name;
        Flag * flag = Flag::long_names[long_name];
        if (flag) flag -> set(optarg);
        if (flag == &FLAGS_OPT_help) {
          Flag::show_help();
        }
        break;
      }

      case '?': {  // unknown option.
        // TODO(cpa): do something sensible here...
        cout << "QUESTION MARK" << endl; break;
      }

      default: {  // short option
        if (Flag::short_names.find(c) == Flag::short_names.end()) {
          cout << "ERROR: failed to find a flag matching '" << c << "'" << endl;
        } else {
          Flag * flag = Flag::short_names[c];
          if (flag) flag -> set(optarg);
        }
        break;
      }
    }
  }

  // TODO(cpa): check optind < argc - see manpage...
  cout << "optind = " << optind << ", argc = " << argc << endl;

  delete [] options;
  return 0;
}


/**
 * 
 */
template <typename T>
void safe_add(map<const T, Flag *> & known, const T key, Flag * value) {
  if (known.find(key) != known.end()) {
    cout << "ERROR: ambiguous flags defined: duplicate key: "
         << "'" << key << "'\n" << *known[key] << "\n" << *value << endl;
  }
  known[key] = value;
}


/**
 * Returns true if all characters in the input string are isgraph.
 */
bool all_isgraph(const char * input) {
  for (int i = 0; input && input[i] != '\0'; ++i) {
    if (!isgraph(input[i]))
      return false;
  }
  return true;
}


/**
 * 
 */
Flag::Flag(const char * ln, const char sn, const char * ds, const bool has_arg)
  : long_name(ln), short_name(sn), description(ds)
{
  Flag::instances.push_back(this);

  // Map the names to this Flag object (if names are valid).
  if (short_name && isgraph(short_name))
    safe_add(Flag::short_names, short_name, this);
  if (all_isgraph(long_name)) {
    safe_add(Flag::long_names, string(long_name), this);
  } else {
    cout << "WARNING: Flag long name '" << long_name
         << "' is not legal and will be ignored." << endl;
  }

  // Keep track of the longest name for later help output formatting.
  string temp(long_name);
  if (temp.length() > longest_long_name) {
    longest_long_name = temp.length();
  }

  // Create an option struct and add it to the list.
  Flag::options.push_back((struct option) {ln, has_arg ? 1 : 0, 0, sn});

  // Add the short_name to a flag_code string.
  if (short_name) {
     if (isgraph(short_name)) {
      Flag::codes.push_back(short_name);
      if (has_arg) {
        Flag::codes.push_back(':');
      }
    } else {
      cout << "WARNING: Flag short name character '" << short_name
           << "' is not legal and will be ignored." << endl;
    }
  }
}


Flag::~Flag() {
  // TODO(cpa): delete the option structs, if this is the --help option ???
}


/**
 * 
 */
ostream & Flag::insert(ostream & out) const {
  if (short_name)
    out << "  -" << short_name;
  else
    out << "    ";

  if (long_name) {
    out << "  --" << long_name;
    out << string(2 + longest_long_name - string(long_name).length(), ' ');
  }

  if (description) out << description;
  return out;
}


/**
 * 
 */
ostream & operator << (ostream & out, const Flag & flag) {
  return flag.insert(out);
}


/**
 * 
 */
IntFlag::IntFlag(const char * ln, const char sn, int * val, const int dv, const char * ds)
  : Flag(ln, sn, ds, true), value(val)
{
  *value = dv;
}


/**
 * 
 */
void IntFlag::set(const char * optarg) {
  *value = atoi(optarg);
}


/**
 * 
 */
ostream & IntFlag::insert(ostream & out) const {
  Flag::insert(out);
  if (value && *value) {
    out << "  Default: " << *value;
  }
  return out;
}


/**
 * 
 */
StringFlag::StringFlag(const char * ln, const char sn, string * val, const char * dv, const char * ds)
  : Flag(ln, sn, ds, true), value(val)
{
  set(dv);
}


/**
 * 
 */
void StringFlag::set(const char * optarg) {
  if (optarg) {
    *value = string(optarg);
  } else {
    value -> clear();
  }
}


/**
 * 
 */
ostream & StringFlag::insert(ostream & out) const {
  Flag::insert(out);
  if (!value -> empty()) {
    out << "  Default: '" << *value << "'";
  }
  return out;
}


/**
 * 
 */
BoolFlag::BoolFlag(const char * ln, const char sn, bool * val, const bool dv, const char * ds, const bool has_arg)
  : Flag(ln, sn, ds, has_arg), value(val)
{
  *val = dv;
}


/**
 * 
 */
void BoolFlag::set(const char * optarg) {
  if (optarg) {
    string opt(optarg);
    if (opt == "true") {
      *value = true;
    } else if (opt == "false") {
      *value = false;
    } else {
      cout << "ERROR: boolean flags must be either true or false.  Got '"
           << optarg << "'" << endl;
    }
  } else {
    *value = true;
  }
}


/**
 * 
 */
ostream & BoolFlag::insert(ostream & out) const {
  return Flag::insert(out);
}