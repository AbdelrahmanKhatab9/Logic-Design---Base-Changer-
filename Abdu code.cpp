#include <iostream>
#include <string>
#include <deque>
#include <vector>
using namespace std;
#define un unsigned
#define LL long long
#define allc(x) x.begin(), x.end()
#define all(x,i,j) x.begin() + i, x.begin() + j + 1
#define Test int TC; cin >> TC; while(TC--)
#define debug(x) cerr << '\t' << #x << " is " << x << '\n'
auto ConvToDec(string num, LL base)
{
int decPointPos = 0;
reverse(allc(num));
if (~num.find('.'))
num.erase((decPointPos = num.find('.')), 1);
long double ans = 0;
for (int i = 0; i < num.size(); i++)
if (num[i] >= 'A')
ans += (num[i] - 'A' + 10) * powl(base, i - decPointPos);
else
ans += (num[i] - '0') * powl(base, i - decPointPos);
return ans;
}
auto ConvFromDec(long double num, LL toBase)
{
LL intPart = num, prec = 15; num -= intPart;
deque<char> ans;
while (intPart)
(intPart % toBase >= 10 ? ans.push_front('A' + intPart % toBase - 10) : ans.push_front('0' + intPart % toBase)), intPart /= toBase;
ans.push_back('.');
while (min(num, (long double)prec--))
num *= toBase, (LL(num) >= 10 ? ans.push_back('A' + LL(num) - 10) : ans.push_back('0' + LL(num))), num -= LL(num);
return string(allc(ans));}

________________________
void FilterExpression(string& s)
{
int filter = 0;
while (~(filter = s.find(' ')))
s.erase(filter, 1);
while(~(filter = s.find("-+")))
s.replace(filter, 2, "-");
while (~(filter = s.find("+-")))
s.replace(filter, 2, "-");
while (~(filter = s.find("--")))
s.replace(filter, 2, "+");
while (~(filter = s.find("++")))
s.replace(filter, 2, "+");
}
long double EvaluateExpression(string s)
{
int bracPos, astPos, Ppos = s.find('+', 1), Npos = s.find('-', 1);
long double subans;
if (~(bracPos = s.find('(')))
{
string temp = "";
int balance = 1, i;
for (i = bracPos + 1; s[i] != ')' || balance != 1; i++)
temp += s[i], balance += (s[i] == '(' ? 1 : s[i] == ')' ? -1 : 0);
subans = EvaluateExpression(temp);
s.replace(bracPos, i - bracPos + 1, to_string(subans));
}
else if (~(astPos = s.find('*')))
{
long double first, second, i, j;
string temp = "";
for (i = astPos - 1; i >= 0 && s[i] >= '.'; i--)
temp += s[i];
reverse(allc(temp));
first = stold(temp);
for (j = astPos + 1, temp = ""; j < s.size() && (s[j] >= '.' || j == astPos + 1 && s[j] == '-'); j++)
temp += s[j];
second = stold(temp);
s.replace(i + 1, j - i - 1, to_string(first * second));
}
else if (Npos < (un LL)Ppos && ~Npos)
{
long double first = 0, second = 0, i, j;
string temp = "";
for (i = Npos - 1; i >= 0; i--)
temp += s[i];
reverse(allc(temp));
first = stold(temp);
for (j = Npos + 1, temp = ""; j < s.size() && s[j] >= '.'; j++)
temp += s[j];
second = stold(temp);
s.replace(0, j, to_string(first - second));
}
else if (Ppos < (un LL)Npos && ~Ppos)
{
long double first = 0, second = 0, i, j, ans;
string temp = "";
for (i = Ppos - 1; i >= 0; i--)
temp += s[i];
reverse(allc(temp));
first = stold(temp);
for (j = Ppos + 1, temp = ""; j < s.size() && s[j] >= '.'; j++)
temp += s[j];
second = stold(temp);
s.replace(0, j, to_string(first + second));
}
else
return stold(s);
FilterExpression(s);
return EvaluateExpression(s);
}

___________________________________________

void makeExpBase10(string& s, int FromBase)
{
string temp = "", ans = "";
for (int i = 0; i < s.size(); i++)
if (s[i] < '.' && temp.size())
ans += to_string(ConvToDec(temp, FromBase)) + s[i], temp = "";
else if (s[i] < '.')
ans += s[i];
else if (s[i] >= '.')
temp += s[i];
if (!temp.empty())
ans += to_string(ConvToDec(temp, FromBase));
s = ans;
}
void Solve()
{
string expression; LL base, toBase;
cout << "Kindly, Enter Your Expression using only this operators { *, +, -, () }.\nExpression: "; getline(cin, expression, '=');
FilterExpression(expression);
cout << "From Base: "; cin >> base;
if (base != 10)
makeExpBase10(expression, base);
auto ans = EvaluateExpression(expression);
cout << "To Base: "; cin >> toBase;
cout << "Answer: "; cout << (ans < 0 ? "-" : "") << ConvFromDec(abs(ans), toBase) << '\n';
}
int main()
{
ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
while (1) Solve(), cout << "----------------------------------------------------------------------------------------------------------------------\n";
return 0;
}



------------------------


