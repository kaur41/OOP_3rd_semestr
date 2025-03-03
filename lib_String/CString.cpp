// Copyright 2024 Kirill Remizov

#include <iostream>
#include "../lib_Algorithms/algoritms.h"
#include "../lib_String/CString.h"

CString::CString() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new char[_capacity];
    _data[0] = '\0';
}

CString::CString(const CString& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = str._data[i];
    }
    _data[_size] = '\0';
}

CString::CString(const char* c_str) {
    _size = 0;
    while (c_str[_size] != '\0') {
        _size++;
    }
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c_str[i];
    }
    _data[_size] = '\0';
}

CString::CString(const char* c_str, size_t n) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c_str[i];
    }
    _data[_size] = '\0';
}

CString::CString(size_t n, char c) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c;
    }
    _data[_size] = '\0';
}

CString::CString(const CString& str, size_t pos, size_t len) {
    _size = len;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < len; i++) {
        _data[i] = str._data[i + pos];
    }
    _data[len] = '\0';
}

CString::~CString() {
    delete[] _data;
    _data = nullptr;
}

bool CString::empty() const noexcept {
    return _size == 0;
}

bool CString::full() const noexcept {
    return _size == -1;
}

void CString::print() const noexcept {
    size_t i = 0;
    while (_data[i] != '\0') {
        std::cout << _data[i];
        i++;
    }
    std::cout << "\n";
}

Status CString::check_overfull() const noexcept {
    Status stat = EMPTY;
    if (_size > 0) {
        stat = NOT_FULL;
        if (_capacity + STEP_CAPACITY == _max_capacity) {
            stat = CAPACITY_FULL_IN_ONE_STEP;
        }
        if (_capacity == _max_capacity) {
            stat = CAPACITY_FULL;
        }
        if (_size == _max_capacity) {
            stat = SIZE_FULL;
        }
        return stat;
    }
    return stat;
}

size_t CString::size() const noexcept {
    return _size;
}
size_t CString::capacity() const noexcept {
    return _capacity;
}
const char* CString::data() const {
    return _data;
}
void CString::swap(CString& str) {
    for (int i = 0; i < _size; i ++) {
        algorithms::swap(_data[i], str._data[i]);
    }
    _data[_size] = '\0';
    str._data[_size] = '\0';
}

CString CString::substr(size_t pos, size_t len) const {
    if (pos > _size || len > _size - pos) {
        throw std::out_of_range("Invalid substring parameters");
    }

    size_t new_size = len + 1;
    char* new_data = new char[new_size];
    for (size_t i = 0; i < len; i++) {
        new_data[i] = _data[i + pos];
    }
    new_data[len] = '\0';
    CString REP(new_data, new_size);
    delete[] new_data;
    return REP;
}

CString& CString::assign(const CString& str) {
    _size = 0;
    delete _data;
    while (str._data[_size] != '\0') {
        _size++;
    }
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = str._data[i];
    }
    _data[_size] = '\0';
    return *this;
}

CString& CString::assign(const CString& str, size_t pos, size_t len) {
    _size = len;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    delete _data;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = str._data[i+pos];
    }
    _data[_size] = '\0';
    return *this;
}
CString& CString::assign(const char* s) {
    _size = 0;
    delete _data;
    while (s[_size] != '\0') {
        _size++;
    }
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = s[i];
    }
    _data[_size] = '\0';
    return *this;
}

CString& CString::assign(const char* s, size_t n) {
    _size = 0;
    delete _data;
    while (s[_size] != '\0') {
        _size++;
    }
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = s[i+n];
    }
    _data[_size] = '\0';
    return *this;
}
CString& CString::assign(size_t n, char c) {
    _size = n;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    delete _data;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c;
    }
    _data[_size] = '\0';
    return *this;
}

int CString::compare(const CString& str) const noexcept {
    if (this->_size > str._size) {
        return 1;
    } else if (this->_size < str._size) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(_size, str._size); i++) {
            if (this->_data[i] < str._data[i]) {
                return -1;
            }
            if (this->_data[i] > str._data[i]) {
                return 11;
            }
        }
        return 0;
    }
}

int CString::compare(size_t pos, size_t len, const CString& str) const {
    if (len > str._size) {
        return 1;
    } else if (len < str._size) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(len, str._size); i++) {
            if (this->_data[i + pos] < str._data[i]) return -1;
            else if (this->_data[i + pos] > str._data[i]) return 1;
        }
        return 0;
    }
}
int CString::compare
(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen)
const {
    if (len > sublen) {
        return 1;
    } else if (len < sublen) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(len, sublen); i++) {
            if (this->_data[i + pos] < str._data[i + subpos]) {
                return -1;
            } else if (this->_data[i + pos] > str._data[i + subpos]) {
                return 1;
            }
        }
        return 0;
    }
}

int CString::compare(const char* s) const {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    if (_size > len) {
        return 1;
    } else if (_size < len) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(_size, len); i++) {
            if (this->_data[i] < s[i]) return -1;
            else if (this->_data[i] > s[i]) return 1;
        }
        return 0;
    }
}

int CString::compare(size_t pos, size_t len, const char* s) const {
    size_t _len = 0;
    while (s[_len] != '\0') {
        _len++;
    }
    if (len > _len) {
        return 1;
    } else if (len < _len) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(len, _len); i++) {
            if (this->_data[i + pos] < s[i]) return -1;
            else if (this->_data[i + pos] > s[i]) return 1;
        }
        return 0;
    }
}

int CString::compare(size_t pos, size_t len, const char* s, size_t n) const {
    size_t _len = 0;
    while (s[_len] != '\0') {
        _len++;
    }
    if (len > _len) {
        return 1;
    } else if (len < _len) {
        return -1;
    } else {
        for (size_t i = 0; i < algorithms::min(len, _len); i++) {
            if (this->_data[i + pos] < s[i + n]) return -1;
            else if (this->_data[i + pos] > s[i + n]) return 1;
        }
        return 0;
    }
}

void CString::clear() noexcept {
    delete _data;
    _size = 0;
    _capacity = 0 + STEP_CAPACITY;
    _data = new char[_capacity];
    _data[0] = '\0';
}

void CString::reserve(size_t n) {
    _capacity = ((_size + n) / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    char* new_data;
    new_data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _data[_size] = '\0';
}

void CString::resize(size_t n) {
    this->reserve(n);
    for (int i = 0; i < n; i++) {
        _data[i + _size] = '\0';
    }
    _data[n + _size] = '\0';
}

void CString::push_back(char c) {
    this->resize(1);
    _data[_size] = c;
    _size += 1;
}

void CString::update(const size_t __size) {
    _capacity = (__size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    char* new_data;
    new_data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _size = __size;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = new_data[i];
    }
    _data[_size] = '\0';
}

void CString::pop_back() {
    if (this->empty()) {
        throw std::logic_error
        ("Error in function pop_back(): source CString is empty");
    }
    _data[--_size] = '\0';
}

CString& CString::erase(size_t pos, size_t len) {
    char* new_data;
    new_data = new char[_capacity];
    int i = 0;
    int i1 = 0;
    while (i1 <= _size) {
        if (i1 < pos) {
            new_data[i] = _data[i];
            i++;
        } else if (i1 > pos + len) {
            new_data[i] = _data[i + len];
            i++;
        }
        i1++;
    }
    _size = i;
    new_data[_size] = '\0';
    delete _data;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = new_data[i];
    }
    _data[_size] = '\0';
    delete new_data;
    this->update(_size);
    return *this;
}

CString& CString::append(const CString& str) {
    this->reserve(str._size);
    for (int i = 0; i < str._size; i++) {
        _data[i + _size] = str._data[i];
    }
    _data[_size + str._size] = '\0';
    _size += str._size;
    return *this;
}

CString& CString::append(const CString& str, size_t subpos, size_t sublen) {
    this->reserve(sublen);
    for (int i = 0; i < sublen; i++) {
        _data[i + _size] = str._data[i +subpos];
    }
    _data[_size + sublen] = '\0';
    _size += sublen;
    return *this;
}

CString& CString::append(const char* s) {
    size_t s_size = 0;
    while (s[s_size] != '\0') {
        s_size++;
    }
    this->reserve(s_size);
    for (int i = 0; i < s_size; i++) {
        _data[i + _size] = s[i];
    }
    _data[_size + s_size] = '\0';
    _size += s_size;
    return *this;
}

CString& CString::append(const char* s, size_t n) {
    size_t s_size = 0;
    while (s[s_size] != '\0') {
        s_size++;
    }
    this->reserve(s_size);
    for (int i = 0; i < s_size; i++) {
        _data[i + _size] = s[i + n];
    }
    _data[_size + s_size] = '\0';
    _size += s_size;
    return *this;
}

CString& CString::append(size_t n, char c) {
    this->reserve(n);
    for (int i = 0; i < n; i++) {
        _data[i + _size] = c;
    }
    _data[_size + n] = '\0';
    _size += n;
    return *this;
}

CString& CString::insert(size_t pos, const CString& str)  {
    this->reserve(str._size);
    int counter = 0;
    char* new_data;
    new_data = new char[_capacity];
    for (int i = 0; i < _size-pos; i++) {
        new_data[i] = _data[i + pos];
        counter += 1;
    }
    for (int i = 0; i < str._size; i ++) {
        _data[i + pos] = str._data[i];
    }
    for (int i = 0; i < _size + str._size; i++) {
        _data[i + ((_size - counter) + str._size)] = new_data[i];
    }
    _data[_size + str._size] = '\0';
    _size += str._size;
    delete[] new_data;
    return *this;
}

CString& CString::insert
(size_t pos, const CString& str, size_t subpos, size_t sublen)  {
    this->reserve(sublen);
    int counter = 0;
    for (int i = _size-1; i >= pos; i--) {
        _data[i + sublen] = _data[i];
    }
    for (int i = pos, j = subpos; i < sublen + pos; i++, j++) {
        _data[i] = str._data[j];
    }
    _data[_size + sublen] = '\0';
    _size += sublen;
    return *this;
}

CString& CString::insert(size_t pos, const char* s)  {
    size_t new_size = 0;
    while (s[new_size] != '\0') {
        new_size++;
    }
    this->reserve(new_size);
    int counter = 0;
    char* new_data;
    new_data = new char[_capacity];
    for (int i = 0; i < _size - pos; i++) {
        new_data[i] = _data[i + pos];
        counter += 1;
    }
    for (int i = 0; i < new_size; i++) {
        _data[i + pos] = s[i];
    }
    for (int i = 0; i < _size + new_size; i++) {
        _data[i + ((_size - counter) + new_size)] = new_data[i];
    }
    _data[_size + new_size] = '\0';
    _size += new_size;
    delete[] new_data;
    return *this;
}

CString& CString::insert(size_t pos, const char* s, size_t n) {
    size_t new_size = 0;
    while (s[n + new_size] != '\0') {
        new_size++;
    }
    this->reserve(new_size);
    for (int i = _size - 1; i >= pos ; i--) {
        _data[i + new_size] = _data[i];
    }
    for (int i = pos, j = 0; i < new_size + 1; i++, j ++) {
        _data[i] = s[j];
    }
    _data[_size + new_size] = '\0';
    _size += new_size;
    return *this;
}

CString& CString::insert(size_t pos, size_t n, char c)  {
    this->reserve(n);

    for (int i = _size - 1; i >= pos; i--) {
        _data[i + n] = _data[i];
    }
    for (int i = pos; i < pos + n; i++) {
        _data[i] = c;
    }
    _data[_size + n] = '\0';
    _size += n;
    return *this;
}

CString& CString::replace(size_t pos, size_t len, const CString& str) {
    this->reserve(str._size);
    char* new_data;
    new_data = new char[_capacity];
    for (int i = pos + len; i < _size; i++) {
        new_data[i - pos - len] = _data[i];
    }
    _size -= len;
    for (int i = 0; i < _size + str._size; i++) {
        _data[i + pos] = str._data[i];
    }
    for (int i = 0; i < _size + str._size; i++) {
        _data[i + pos + str._size] = new_data[i];
    }
    _size += str._size;
    _data[_size] = '\0';
    delete[] new_data;
    return *this;
}

CString& CString::replace
(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) {
    this->reserve(sublen);
    char* new_data;
    new_data = new char[_capacity];
    for (int i = pos + len; i < _size; i++) {
        new_data[i - pos - len] = _data[i];
    }
    _size -= len;
    for (int i = 0; i < _size + sublen; i++) {
        _data[i + pos] = str._data[i + subpos];
    }
    for (int i = 0; i < _size + sublen; i++) {
        _data[i + pos + sublen] = new_data[i];
    }
    _size += sublen;
    _data[_size] = '\0';
    delete[] new_data;
    return *this;
}

CString& CString::replace(size_t pos, size_t len, const char* s, size_t n)  {
    int sublen = 0;
    while (s[sublen] != '\0') {
        sublen++;
    }
    sublen -= n;
    this->reserve(sublen);
    for (int i = _size -1; i >= pos; i--) {
        if (i >= pos && i < pos + len) {
            continue;
        } else {
            _data[i - len + sublen] = _data[i];
        }
    }
    for (int i = 0; i < sublen; i++) {
        _data[i + pos] = s[i + n];
    }
    _size -= len;
    _data[_size + sublen] = '\0';
    return *this;
}

CString& CString::replace(size_t pos, size_t len, size_t n, char c) {
    this->reserve(n);
    char* new_data;
    new_data = new char[_capacity];
    for (int i = pos + len; i < _size; i++) {
        new_data[i - pos - len] = _data[i];
    }
    _size -= len;
    for (int i = 0; i < _size + n; i++) {
        _data[i + pos] = c;
    }
    for (int i = 0; i < _size + n; i++) {
        _data[i + pos + n] = new_data[i];
    }
    _size += n;
    _data[_size] = '\0';
    delete[] new_data;
    return *this;
}

size_t CString::find(const CString& str) const {
    size_t pos = -1;
    int i = 0;
    while (i + str._size != _size + 1) {
        for (int c = 0; c < str._size; c++) {
            if (str._data[c] == _data[i + c]) {
                pos = i;
                if (c == str._size - 1) {
                    return pos + 1;
                }
                continue;
            } else {
                pos = -1;
                break;
            }
        }
        i++;
    }
    return pos;
}
size_t CString::find(const char* s) const {
    int sublen = 0;
    while (s[sublen] != '\0') {
        sublen++;
    }
    size_t pos = -1;
    int i = 0;
    while (i + sublen != _size + 1) {
        for (int c = 0; c < sublen; c++) {
            if (s[c] == _data[i + c]) {
                pos = i;
                if (c == sublen - 1) {
                    return pos + 1;
                }
                continue;
            } else {
                pos = -1;
                break;
            }
        }
        i++;
    }
    return pos;
}

size_t CString::find(const char* s, size_t pos, size_t n) const {
    int sublen = 0;
    while (s[sublen] != '\0') {
        sublen++;
    }
    size_t _pos = -1;
    int i = 0;
    while (i + n != _size + 1) {
        for (int c = 0; c < n; c++) {
            if (s[c + pos] == _data[i + c]) {
                _pos = i;
                if (c == n - 1) {
                    return _pos + 1;
                }
                continue;
            } else {
                _pos = -1;
                break;
            }
        }
        i++;
    }
    return pos;
}

size_t CString::find(char c) const {
    size_t res = -1;
    for (int i = 0; i < _size; i++) {
        if (_data[i] == c) {
            res = i;
            return res;
        }
    }
    return res;
}

size_t CString::find_first_of(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; j < str._size; j++) {
            if (_data[i] == str._data[j]) {
                return i;
            }
        }
    }
    return -1;
}

size_t CString::find_first_of(const char* s, size_t pos) const {
    int sublean = 0;
    while (s[sublean] != '\0') {
        sublean++;
    }
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; j < sublean; j++) {
            if (_data[i] == s[j]) {
                return i;
            }
        }
    }
    return -1;
}

size_t CString::find_first_of(const char* s, size_t pos, size_t n) const {
    int sublean = 0;
    while (s[sublean] != '\0') {
        sublean++;
    }
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = n; j < sublean; j++) {
            if (_data[i] == s[j]) {
                return i;
            }
        }
    }
    return -1;
}

size_t CString::find_first_of(char c, size_t pos) const {
    for (int i = 0; i < _size; i++) {
        if (_data[i] == c) {
            return i;
        }
    }
    return -1;
}

size_t CString::find_first_not_of(const CString& str, size_t pos) const {
    char* new_data;
    for (int i = 0; i < this->_size; i++) {
        bool found = false;
        for (int j = 0; j < str._size; j++) {
            if (this->_data[i] == str._data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return i;
        }
    }
}

size_t CString::find_first_not_of(const char* s, size_t pos) const {
    int sublean = 0;
    while (s[sublean] != '\0') {
        sublean++;
    }
    for (int i = 0; i < this->_size; i++) {
        bool found = false;
        for (int j = 0; j < sublean; j++) {
            if (this->_data[i] == s[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return i;
        }
    }
}

size_t CString::find_first_not_of(const char* s, size_t pos, size_t n) const {
    int sublean = 0;
    while (s[sublean] != '\0') {
        sublean++;
    }
    for (int i = pos; i < this->_size; i++) {
        bool found = false;
        for (int j = n; j < sublean; j++) {
            if (this->_data[i] == s[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return i;
        }
    }
}

size_t CString::find_first_not_of(char c, size_t pos) const {
    for (int i = 0; i < _size; i++) {
        if (_data[i] != c) {
            return i;
        }
    }
    return -1;
}
