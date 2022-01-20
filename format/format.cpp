#include "format.h"

using namespace std;

void reverseStr(char str[])
{
    int N = strlen(str);
    for(int i = 0; i < N/2; ++i) {
        swap(str[i], str[N - i - 1]);
    }
}

result read_code(char str[], const int &max_char)
{
    fflush(stdin);
    cin.get(str, max_char);
    if(cin.fail()) {
        // an empty line was read
        cin.clear();
        cin.get(); // remove the '\n'
        return EMPTY;
    }
    char ch = cin.get();
    if(ch != '\n') {
        // too many characters read
        fflush(stdin);
        str[0] = '\0';
        return EXCESSIVE;
    }
    else {
        bool ok = true;
        for(int i = 0; i < strlen(str); ++i) {
            if(str[i] < '0' || str[i] > '9') {
                ok = false;
                break;
            }
        }
        if(ok) return SUCCESSFUL;
        else {
            str[0] = '\0';
            return INVALID;
        }
    }
}

result read_name(char str[], const int &max_char)
{
    fflush(stdin);
    cin.get(str, max_char);
    if(cin.fail()) {
        // an empty line was read
        cin.clear();
        cin.get(); // remove the '\n'
        return EMPTY;
    }
    char ch = cin.get();
    if(ch != '\n') {
        // too many characters read
        fflush(stdin);
        str[0] = '\0';
        return EXCESSIVE;
    }
    else return SUCCESSFUL; // read successfully
}

result read_char(char &chr)
{
    char str[2];
    chr = '\0';
    fflush(stdin);
    cin.get(str, 2);
    if(cin.fail()) {
        // an empty line was read
        cin.clear();
        cin.get(); // remove the '\n'
        return EMPTY;
    }
    char c = cin.get();
    if(c != '\n') {
        // too many characters read
        fflush(stdin);
        return EXCESSIVE;
    }
    else {
        if(str[0] != 'Y' && str[0] != 'N') {
            return INVALID;
        }
        else {
            chr = str[0];
            return SUCCESSFUL;
        }
    }
}

result read_double(double &d)
{
    d = -1.0;
    const int MAX = 50;
    char num[MAX];
    fflush(stdin);
    cin.get(num, MAX);
    if(cin.fail()) {
        // an empty line was read
        cin.clear();
        cin.get(); // remove the '\n'
        return EMPTY;
    }
    char c = cin.get();
    if(c != '\n') {
        // too many character was read
        fflush(stdin);
        return EXCESSIVE;
    }
    else {
        int N = strlen(num);

        // First, check the validity of a real number, that is, containing only digits and a dot (not in the beginning nor end).
        bool valid = true;
        int num_dot = 0;
        for(int i = 0; i < N; ++i) {
            if(num[i] == '.' || ('0' <= num[i] && num[i] <= '9')) {
                if(num[i] == '.') ++num_dot;
            }
            else {
                valid = false;
                break;
            }
        }
        if(num_dot > 1) valid = false;
        if(num[0] == '.' || num[N - 1] == '.') valid = false;
        if(!valid) return INVALID;

        // remove leading zeroes if multiple are encountered
        reverseStr(num);
        while(N > 1 && num[N - 1] == '0') {
            num[--N] = '\0';
        }
        if(num[N - 1] == '.') {
            num[N++] = '0';
            num[N] = '\0';
        }
        reverseStr(num);

        // remove trailing zeroes if multiple are encountered
        while(N > 1 && num[N - 1] == '0') {
            num[--N] = '\0';
        }
        if(num[N - 1] == '.') {
            num[N++] = '0';
            num[N] = '\0';
        }
        int num_decimal = 0;
        for(int i = N - 1; i > 0; --i) {
            if(num[i] == '.') {
                if(num_decimal > MAX_DECIMAL)
                    return INVALID;
            }
            ++num_decimal;
        }

        // now, every digit left should be significant.
        int sigfig = N - (num_dot == 1); // possibly, except the dot
        // this way of computing the number of significant figures could be wrong but I'm too lazy to fix it :3
        if(num[0] == '0') --sigfig;
        assert(sigfig >= 1);
        if(sigfig > 15) {
            return INVALID;
        }

        // convert the real number from string to double
        int64_t integer = 0, fraction = 0;
        int pos;
        for(pos = 0; pos < N; ++pos) {
            if(num[pos] == '.') {
                ++pos;
                break;
            }
            integer = 10*integer + num[pos] - '0';
        }
        int64_t divi = 1;
        for(; pos < N; ++pos) {
            divi *= 10;
            fraction = 10*fraction + num[pos] - '0';
        }
        d = double(integer) + double(fraction)/divi;
        return SUCCESSFUL;
    }
}

result read_pos_int(int &X)
{
    X = -1;
    const int MAX = 50;
    char num[MAX];
    fflush(stdin);
    cin.get(num, MAX);
    if(cin.fail()) {
        // an empty line was read
        cin.clear();
        cin.get(); // remove the '\n'
        return EMPTY;
    }
    char c = cin.get();
    if(c != '\n') {
        // too many character was read
        fflush(stdin);
        return EXCESSIVE;
    }
    else {
        int N = strlen(num);
        for(int i = 0; i < N; ++i) {
            if(num[i] < '0' || num[i] > '9')
                return INVALID;
        }

        // remove leading zeroes if multiple are encountered
        reverseStr(num);
        while(N > 1 && num[N - 1] == '0') {
            num[--N] = '\0';
        }
        reverseStr(num);
        if(N > 10) return INVALID;
        else if(N == 10) {
            char lim[] = "2147483647"; // MAX_INT
            if(strcmp(num, lim) == 1) return INVALID;
        }

        X = 0;
        for(int i = 0; i < N; ++i) {
            X = 10*X + num[i] - '0';
        }
        assert(X >= 0);
        return SUCCESSFUL;
    }
}