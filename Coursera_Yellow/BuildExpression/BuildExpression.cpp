#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <iterator>

using namespace std;

struct Operation {
	char op;
	int val;
};

class Expression {
public:
	explicit Expression(const size_t& siz) {
		expr = new Operation[siz];
		size = siz;
		cur_ind = -1;
	}

	void push(const int& val) {
		expr[++cur_ind].val = val;
		expr[cur_ind].op = '\0';
	}

	void push(const char& op, const int& val) {
		expr[++cur_ind].val = val;
		expr[cur_ind].op = op;
	}

	deque<string> str_with_brackets() {
		deque<string> d;
		d.push_back(to_string(expr[0].val));
		for (int i = 1; i <= cur_ind; ++i) {

			d.push_front("(");
			d.push_back(") ");
			d.push_back(string(1, expr[i].op));
			d.push_back(" ");
			d.push_back(to_string(expr[i].val));
		}
		return d;
	}

	deque<string> str() {
		deque<string> d;
		d.push_back(to_string(expr[0].val));
		bool priority;
		for (int i = 1; i <= cur_ind; ++i) {
			priority = (expr[i].op == '*' || expr[i].op == '/');
			priority &= (expr[i-1].op == '+' || expr[i-1].op == '-');
			if (priority) {
				d.push_front("(");
				d.push_back(") ");
			}
			else
				d.push_back(" ");
			d.push_back(string(1, expr[i].op));
			d.push_back(" ");
			d.push_back(to_string(expr[i].val));
		}
		return d;
	}

private:
	Operation* expr;
	size_t size;
	int cur_ind;
};


/*
template<typename RandIt>
string ExpressionStr(RandIt beg, RandIt end) {
	auto back_it = prev(end);
	auto [op, num] = *back_it;
	if (op == '\0')
		return to_string(num);

	bool priority = (op == '*' || op == '/');
	auto [pr_op, pr_num] = *prev(back_it);
	priority &= (pr_op == '+' || pr_op == '-');
	return (priority?"(":"") + ExpressionStr(beg, back_it) + (priority ? ") " : " ") + op + " " + to_string(num);
}
*/



int main()
{
	/*
	8
	81
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	* 3
	- 6
	/ 1
	*/
	char op;
	int num, q;
	cin >> num >> q;
	Expression expr(q+1);
	expr.push(num);

	for (size_t i = 0; i < q; ++i) {
		cin >> op >> num;
		expr.push(op, num);
	}

	for (const auto& s : expr.str()) {
		cout << s;
	}
	//std::cout << expr.str_with_brackets() << endl;
	//std::cout << expr.str() << endl;

	return 0;
}
