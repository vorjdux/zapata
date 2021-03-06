/*
The MIT License (MIT)

Copyright (c) 2017 n@zgul <n@zgul.me>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <zapata/log/log.h>
#include <zapata/text/manip.h>
#include <zapata/json.h>

using namespace std;
#if !defined __APPLE__
using namespace __gnu_cxx;
#endif

int main(int _argc, char* _argv[]) {
	zpt::json _options = zpt::conf::getopt(_argc, _argv);

	std::ifstream _ifs;
	_ifs.open(".zpt_rc");
	bool _initialized = _ifs.is_open();
	if (_initialized) {
		zpt::json _conf_options;
		_ifs >> _conf_options;
		if (_options["version"]->ok()) {
			_ifs.close();
			_conf_options << "version" << zpt::json{zpt::array,
								int(_options["version"][0]),
								int(_options["files"][0]),
								int(_options["files"][1])};
			std::ofstream _ofs;
			_ofs.open(".zpt_rc");
			_ofs << zpt::json::pretty(_conf_options) << flush;
			_ofs.close();
			return 0;
		}
		_options = _conf_options + _options;
	} else if (_options["version"]->ok()) {
		return 0;
	}

	std::string _input;

	std::string _project_name;
	if (_options["name"]->type() == zpt::JSString) {
		_project_name.assign(_options["name"]->str());
	} else {
		do {
			std::cout << "Project name: " << flush;
			std::getline(std::cin, _input);
			if (_input.find(" ") != std::string::npos) {
				std::cout << "   * Project name can't have spaces" << endl << flush;
			}
		} while (_input.length() == 0 || _input.find(" ") != std::string::npos);
		_project_name.assign(_input.data());
	}

	std::string _project_abbr;
	if (_options["abbr"]->type() == zpt::JSString) {
		_project_abbr.assign(_options["abbr"]->str());
	} else {
		do {
			std::cout << "Project abbreviation: " << flush;
			std::getline(std::cin, _input);
			if (_input.find(" ") != std::string::npos) {
				std::cout << "   * Project abbreviation can't have spaces" << endl << flush;
			}
		} while (_input.length() == 0 || _input.find(" ") != std::string::npos);
		_project_abbr.assign(_input.data());
	}

	std::string _path_prefix;
	if (_options["prefix"]->type() == zpt::JSString) {
		_path_prefix.assign(_options["prefix"]->str());
	} else {
		std::cout << "Path prefix: " << flush;
		std::getline(std::cin, _input, '\n');
		_path_prefix.assign(_input.data());
	}
	if (_path_prefix.back() == '/') {
		_path_prefix.erase(_path_prefix.length() - 1, 1);
	}

	std::string _dev_name;
	if (_options["developer"]["name"]->type() == zpt::JSString) {
		_dev_name.assign(_options["developer"]["name"]->str());
	} else {
		do {
			std::cout << "Developer name: " << flush;
			std::getline(std::cin, _input, '\n');
		} while (_input.length() == 0);
		_dev_name.assign(_input.data());
	}

	std::string _dev_email;
	if (_options["developer"]["email"]->type() == zpt::JSString) {
		_dev_email.assign(_options["developer"]["email"]->str());
	} else {
		do {
			std::cout << "Developer e-mail address: " << flush;
			std::getline(std::cin, _input);
			if (_input.find(" ") != std::string::npos) {
				std::cout << "   * E-mail can't have spaces" << endl << flush;
			}
		} while (_input.length() == 0 || _input.find(" ") != std::string::npos);
		_dev_email.assign(_input.data());
	}

	if (!_options["local"]->ok()) {
		std::string _yes = "yes";
		if (_initialized) {
			do {
				std::cout << "Project file found. Are you sure you want to override? [YES/no] "
					  << flush;
				std::getline(std::cin, _input);
			} while (_input.length() == 0);
			_yes.assign(_input.data());
		}
		if (_yes == "yes") {
			if (std::system("tar xvjf /usr/share/zapata/autoconf.template.tar.bz2"))
				;
			if (std::system((std::string("/usr/share/zapata/zinit_setup '") + _project_name +
					 std::string("' '") + _project_abbr + std::string("' '") + _dev_email +
					 std::string("' '") + _dev_name + std::string("' '") + _path_prefix +
					 std::string("'"))
					    .data()))
				;
		}
	}

	if (std::system((std::string("cp /usr/share/zapata/configure.ac .").data())))
		;
	if (std::system((std::string("cp /usr/share/zapata/changelog debian/").data())))
		;
	if (std::system((std::string("/usr/share/zapata/zinit_version '") + _project_name + std::string("' '") +
			 _project_abbr + std::string("' '") + _dev_email + std::string("' '") + _dev_name +
			 std::string("' '") + _path_prefix + std::string("'"))
			    .data()))
		;

	return 0;
}
