/*
    Author: Pedro (n@zgul) Figueiredo <pedro.figueiredo@gmail.com>
    Copyright (c) 2014 Pedro (n@zgul)Figueiredo
    This file is part of Zapata.

    Zapata is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zapata is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with Zapata.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>
#include <base/str_map.h>
#include <log/log.h>
#include <pthread.h>

using namespace std;
using namespace __gnu_cxx;

namespace zapata {

	/**
	 * Responsible for counting references to a given <b><i>smart_ptr</i></b>.
	 * Invoking <b><i>add</i></b> increases the counter. Invoking <b><i>release</i></b> decreases the counter.
	 * @see smart_ptr
	 */
	class smart_counter {
		private:

		public:
			/**
			 * The actual counter variable.
			 */
			size_t __pointed;
			smart_counter();
			~smart_counter();

			/**
			 * Increases the value hold by <b><i>__pointed</i></b>
			 */
			void add();
			/**
			 * Decreases the value hold by <b><i>__pointed</i></b>
			 */
			size_t release();

			inline friend ostream& operator<<(ostream& os, smart_counter& f) {
				os << "smart_counter<" << f.__pointed << ">";
				return os;
			}
	};


	/**
	 * Table that holds the list of <b><i>smart_counter</i></b>s for allocated <b><i>smart_ptr</i></b>s
	 * @see smart_counter
	 * @see smart_ptr
	 */
	class smart_ref_table : public str_map<smart_counter*> {
		public:
			smart_ref_table();
			~smart_ref_table();

			smart_counter* add(void* ptr);
			size_t release(void* ptr);
			void remove(void* ptr);
	};

	extern pthread_key_t __memory_key;

	template<typename T>
	class smart_ptr {
		private:
			T* __target;

		public:
			typedef T element_type;

			explicit smart_ptr(T* ptr = NULL) throw () {
				this->__target = NULL;
				this->set(ptr);
			}

			explicit smart_ptr(T& ptr) throw () {
				this->__target = NULL;
				this->set(&ptr);
			}

			smart_ptr(smart_ptr& rhs) throw () {
				this->__target = NULL;
				this->set(rhs.__target);
			}

			template<typename Y>
			smart_ptr(smart_ptr<Y>& rhs) throw () {
				this->__target = NULL;
				this->set(rhs.__target);
			}

			smart_ptr& operator=(smart_ptr& rhs) throw () {
				this->set(rhs.__target);
				return *this;
			}

			template<typename Y>
			smart_ptr& operator=(smart_ptr<Y>& rhs) throw () {
				this->set(rhs.__target);
				return *this;
			}

			smart_ptr& operator=(T* rhs) throw () {
				this->set(rhs);
				return *this;
			}

			smart_ptr& operator=(T& rhs) throw () {
				this->set(&rhs);
				return *this;
			}

			~smart_ptr() throw () {
				smart_ref_table* _memory = NULL;
				if ((_memory = static_cast<smart_ref_table*>(pthread_getspecific(zapata::__memory_key))) == NULL) {
					_memory = new smart_ref_table();
					pthread_setspecific(zapata::__memory_key, _memory);
				}
				if (this->__target != NULL && _memory->release(this->__target) == 0) {
					_memory->remove(this->__target);
					delete this->__target;
				}
			}

			T* get() const throw () {
				return this->__target;
			}
			T& operator*() const throw () {
				return *this->__target;
			}
			T* operator->() const throw () {
				return this->__target;
			}

			T* release() throw () {
				smart_ref_table* _memory = NULL;
				if ((_memory = static_cast<smart_ref_table*>(pthread_getspecific(zapata::__memory_key))) == NULL) {
					_memory = new smart_ref_table();
					pthread_setspecific(zapata::__memory_key, _memory);
				}
				_memory->release(this->__target);

				T* tmp = this->__target;
				this->__target = NULL;
				return tmp;
			}

			void destroy() throw () {
				delete this->__target;
				this->__target = NULL;
			}

			void set(T* ptr = NULL) throw () {
				if (ptr == NULL) {
					ptr = new T();
				}
				if (this->__target != ptr) {
					smart_ref_table* _memory = NULL;
					if ((_memory = static_cast<smart_ref_table*>(pthread_getspecific(zapata::__memory_key))) == NULL) {
						_memory = new smart_ref_table();
						pthread_setspecific(zapata::__memory_key, _memory);
					}
					if (this->__target != NULL && _memory->release(this->__target) == 0) {
						_memory->remove(this->__target);
						delete this->__target;
					}
					this->__target = ptr;
					_memory->add(ptr);
				}
			}

			friend ostream& operator<<(ostream& _out, smart_ptr<T>& _in) {
				_out << (string) *(_in.__target);
				return _out;
			}
			smart_ptr<T>& operator<<(const char* _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(string _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(bool _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(int _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(long _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(long long _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(double _in) {
				(*this->__target) << _in;
				return *this;
			}
#ifdef __LP64__
			smart_ptr<T>& operator<<(unsigned int _in) {
				(*this->__target) << _in;
				return *this;
			}
#endif
			smart_ptr<T>& operator<<(size_t _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(ObjectOp _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(T& _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator<<(smart_ptr<T>& _in) {
				(*this->__target) << _in;
				return *this;
			}
			template<typename Y>
			smart_ptr<T>& operator<<(smart_ptr<Y>& _in) {
				(*this->__target) << _in;
				return *this;
			}
			template<typename Y>
			smart_ptr<T>& operator<<(Y& _in) {
				(*this->__target) << _in;
				return *this;
			}
			smart_ptr<T>& operator>>(string _in) {
				(*this->__target) >> _in;
				return *this;
			}
			smart_ptr<T>& operator>>(const char* _in) {
				(*this->__target) >> _in;
				return *this;
			}
			smart_ptr<T>& operator>>(long long _in) {
				(*this->__target) >> _in;
				return *this;
			}
			smart_ptr<T>& operator>>(ObjectOp _in) {
				(*this->__target) >> _in;
				return *this;
			}
			T& operator[](size_t _idx) {
				return (T&) this->__target->get(_idx);
			}
			T& operator[](const char* _idx){
				return (T&) this->__target->get(_idx);
			}
			T& operator[](string& _idx){
				return (T&) this->__target->get(_idx.data());
			}

	};

}

