#include <iostream>
#include <exception>
using namespace std;

template<typename T>
class List {

	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		
		Node()
		: next_(0),
		  prev_(0)
		{}
		
		Node(T val)
		: data_(val),
		  next_(0),
		  prev_(0)
		{}
		
	};

	Node* head_;
	
public:
	List()
	: head_(new Node)
	{
		head_->prev_=head_;
		head_->next_=head_;
	}
	
	~List() {
		while(!empty()) {
			pop_front();
		}
		delete head_;
	}

	

	
	bool empty() const {
		return head_->next_ == head_ -> prev_;
	}

	void push_front(T val) {
		Node* ptr = new Node(val);
		Node* front = head_->next_;
		
		head_->next_ = ptr;
		ptr->prev_ = head_;
		
		ptr->next_=front;
		front->prev_=ptr;	
	}

	void push_back(T val) {
		Node* ptr = new Node(val);
		Node* back = head_->prev_;
		
		back->next_ = ptr;
		ptr->prev_ = back;
		
		ptr->next_ = head_;
		head_->prev_ = ptr;
	}


	const T& front() const {
		if(empty()) {
			throw exception();
		}
		Node* front = head_ -> next_;
		return front->data_;
	}

	const T& back() const {
		if(empty()) {
			throw exception();
		}
		Node* back = head_ -> prev_;
		return back -> data_;
		
		
	}


	void pop_front() {
		if(empty()) {
			throw exception();
		}
		
		Node* front = head_->next_;
		Node* new_front = front->next_;
		
		head_->next_ = new_front;
		new_front->prev_=head_;
		
		delete front;
	}

	void pop_back() {
		if(empty()) {
			throw exception();
		}
		
		Node* back = head_->prev_;
		Node* new_back = back->prev_;
		
		new_back->next_= head_;
		head_->prev_ = new_back;
		
		delete back;
		
	}



	class iterator {
		friend class List;
	
		Node* current_;
		
		iterator(Node* current)
		: current_(current)
		{}
	public:
		iterator& operator++() {
			current_=current_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator res=*this;
			current_=current_->next_;
			
			return res;
		}
		
		int& operator*() {
			return current_->data_;
		}
		
		bool operator==(const iterator& other) const {
			return current_==other.current_;
		}
		
		bool operator!=(const iterator& other) const {
			return ! operator==(other);
		}
		
	};
	
	iterator begin() const {
		return iterator(head_->next_);
	}
	
	iterator end() const {
		return iterator(head_);
	}
	
	iterator insert(iterator pos, int val) {
		Node* node=new Node(val);
		Node* curr=pos.current_;
		
		Node* prev=curr->prev_;
		
		prev->next_=node;
		node->prev_=prev;
		
		node->next_=curr;
		curr->prev_=node;
		
		return iterator(node);
	}
	
	
	iterator erase(iterator pos) {
		Node* curr=pos.current_;
		
		Node* next=curr->next_;
		Node* prev=curr->prev_;
		
		prev->next_=next;
		next->prev_=prev;
		
		delete curr;
		
		return iterator(next);
	}
	


};


int main() {
	List<int> li;
	
	cout << li.empty() << endl;
	li.push_front(-1);
	li.push_front(1);
	li.push_front(2);
	li.push_front(3);
	
	cout << li.empty() << endl;

	cout << li.front() << endl;
	cout << li.back() << endl;

	li.pop_front();
	cout << li.front() << endl;
	li.pop_back();
	cout << li.back() << endl;

	li.push_back(44);
	cout << li.back() << endl;
	
	

	List<int>::iterator it=li.begin();

	it++;
	
	
	*it;
	*it=42;

	it!=li.end();
	
	
	li.insert(li.begin(),-6);
	li.insert(li.end(),8);
	
	for(List<int>::iterator i=li.begin();i!=li.end();++i) {
		cout << (*i) << ' ';
	}
	cout << endl;
	
	
	li.erase(li.begin());
	
	for(List<int>::iterator it=li.begin();it!=li.end();++it) {
		cout << (*it) << ' ';
	}
	cout << endl;
	
	return 0;
} 
