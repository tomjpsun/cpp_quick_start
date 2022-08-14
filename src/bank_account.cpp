#include <asio/execution.hpp>
#include <asio/static_thread_pool.hpp>
#include <asio/post.hpp>
#include <iostream>
#include <vector>
#include <atomic>

using asio::static_thread_pool;
namespace execution = asio::execution;

// Traditional active object pattern.
// Member functions do not block.
class pretty_print {

public:
	static std::atomic<int> count;
	pretty_print() { if (pretty_print::count++ % 10 == 0) std::cout << std::endl; }
};


std::atomic<int> pretty_print::count;

class bank_account
{
	int balance_ = 0;
	mutable static_thread_pool pool_{4};

public:
	mutable static_thread_pool record_{1};

	void deposit(int amount)  {
		execution::execute(
			asio::require(pool_.executor(), execution::blocking.always),
			[this, amount] {
				balance_ += amount;
				asio::post(this->record_.executor(),
					   [amount]{ std::cout << amount << "  ";
						   pretty_print p;
					   });
			});
	}

	void withdraw(int amount) {
		execution::execute(
			asio::require(pool_.executor(), execution::blocking.always),
			[this, amount] {
				if (balance_ >= amount) {
					balance_ -= amount;
					asio::post(this->record_.executor(),
						   [amount]{
							   std::cout << "-" << amount << "  ";
							   pretty_print p;
						   });
				}
			});
	}

	void print_balance() const {
		execution::execute(
			asio::require(pool_.executor(), execution::blocking.never),
			[this] {
				std::cout << "balance = " << balance_ << "\n";
			});
	}

	~bank_account() {
		pool_.wait();
	}
};

int main()
{
	bank_account acct;
	for (int i=0; i<1000; i++) {
		acct.deposit(20);
		acct.withdraw(10);
	}

	acct.print_balance();
}
