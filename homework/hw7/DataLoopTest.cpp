#include "DataLoop.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
#ifdef __APPLE__
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext->__ss.__rip);
#else
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
#endif
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;
#ifdef __APPLE__
  ((ucontext_t*)context)->uc_mcontext->__ss.__rip += 2;  // skip the seg fault
#else
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] += 2;  // skip the seg fault
#endif
}

#define ASSERT(cond) if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  }
#endif

/**
 * \struct DataLoopTest
 * \defgroup DataLoopTest
 * \brief Test cases for the DataLoop class
 */
struct DataLoopTest {
  /**
   * \brief A test function for default constructor
   */
  static void DefaultConstructorTest() {
    DataLoop *q = new DataLoop();
    // check if the structure is as expected
    ASSERT(q->start == nullptr);
    ASSERT(q->count == 0);
    delete q;
  }
   
  /**
   * \brief A test function for non-default constructor
   */
  static void NonDefaultConstructorTest() {
    DataLoop *q = new DataLoop(10);
    // check if the structure is as expected
    ASSERT(q->start != nullptr);
    ASSERT(q->start->next == q->start);
    ASSERT(q->start->prev == q->start);
    ASSERT(q->start->data == 10);
    ASSERT(q->count == 1);
    delete q;

    // Check zero case
    DataLoop *q1 = new DataLoop(0);
    ASSERT(q1->start == nullptr);
    ASSERT(q1->count == 0);
    delete q1;

    // Check negative case
    DataLoop *q2 = new DataLoop(-10);
    ASSERT(q2->start == nullptr);
    ASSERT(q2->count == 0);
    delete q2;

  }
  
  /**
   * \brief A test function for operator+=
   */
  static void OperatorPlusGetsTest() {
    // create a dataloop ->10<->30<->20<-
    DataLoop *q = new DataLoop();

    *q += 10;        // test single use
    // check if the structure is as expected
    ASSERT(q->start != nullptr);
    ASSERT(q->start->next == q->start);
    ASSERT(q->start->prev == q->start);
    ASSERT(q->start->data == 10);
    ASSERT(q->count == 1);
   

    *q += 30;
    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == 10);  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == 30);
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == 30);

    *q += 20;  
    ASSERT(q->count == 3);

    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == 20);
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == 30);
    ASSERT(q->start->prev->prev->prev == q->start);

    DataLoop *r = new DataLoop();
    ((*r += 10) += 30) += 20;    // test chaining (function return)
    ASSERT(r->count == 3);
    ASSERT(r->start != nullptr);
    ASSERT(r->start->data == 10);
    ASSERT(r->start->next != nullptr);
    ASSERT(r->start->next->data == 30);
    ASSERT(r->start->prev != nullptr);
    ASSERT(r->start->prev->data == 20);
    ASSERT(r->start->next->next != nullptr);
    ASSERT(r->start->next->next->data == 20);
    ASSERT(r->start->next->next->next == r->start);
    ASSERT(r->start->prev->prev != nullptr);
    ASSERT(r->start->prev->prev->data == 30);
    ASSERT(r->start->prev->prev->prev == r->start);

    delete q;
    delete r;
  }
  

  /**
   * \brief A test function for copy constructor
   */
  static void CopyConstructorTest() {
    DataLoop *r = new DataLoop(10);
    *r += 30;
    *r += 20;
    DataLoop *q = new DataLoop(*r);
    // check if the structure is as expected
    ASSERT(q->count == 3);

    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == 10);  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == 30);
    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == 20);
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == 20);
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == 30);
    ASSERT(q->start->prev->prev->prev == q->start);

    // check that updating r doesn't affect q
    *r += 15;
    ASSERT(r->count == 4);
    ASSERT(q->count == 3);
    ASSERT(r->start->prev->data == 15);
    ASSERT(q->start->prev->data == 20);

    delete r;
    delete q;

    DataLoop *r1 = new DataLoop();
    DataLoop *q1 = new DataLoop(*r1);
    ASSERT(q1->count == 0);
    ASSERT(q1->start == nullptr);

    delete r1;
    delete q1;

  } 
  
  /**
   * \brief A test function for assignment operator
   */
  static void OperatorAssignmentTest() {
    DataLoop *r = new DataLoop(10);
    *r += 30; *r += 20;
    DataLoop *q = new DataLoop(15);
    *q = *r;
    // check if the structure is as expected
    ASSERT(q->count == 3);

    ASSERT(q->start != nullptr);
    ASSERT(q->start->data == 10);  // check not changed
    ASSERT(q->start->next != nullptr);
    ASSERT(q->start->next->data == 30);
    ASSERT(q->start->next->next != nullptr);
    ASSERT(q->start->next->next->data == 20);
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev != nullptr);
    ASSERT(q->start->prev->data == 20);
    ASSERT(q->start->prev->prev != nullptr);
    ASSERT(q->start->prev->prev->data == 30);
    ASSERT(q->start->prev->prev->prev == q->start);

    // check that updating r doesn't affect q
    // TODO: add your own tests here

    *r += 40;
    ASSERT(r->count == 4);
    ASSERT(q->count == 3);
    ASSERT(q->start->next->next->next == q->start);

    *r += 50;
    ASSERT(r->count == 5);
    ASSERT(q->count == 3);
    ASSERT(q->start->next->next->next == q->start);
    ASSERT(q->start->prev->data == 20);
    ASSERT(q->start->next->next->data == 20);

    delete r;
    delete q;

    // test with empty dataloop
    DataLoop *s = new DataLoop();
    DataLoop *t = new DataLoop(5);
    *t = *s;
    ASSERT(t->count == 0);
    ASSERT(t->start == nullptr);

    delete s;
    delete t;

    // Non-empty to empty dataloop assignment
    DataLoop *u = new DataLoop(10);
    DataLoop *v = new DataLoop();
    *v = *u;
    ASSERT(v->count == 1);
    ASSERT(v->start->data == 10);
    ASSERT(v->start->next == v->start);
    ASSERT(v->start->prev == v->start);

    delete u;
    delete v;

  }
  
  
  /**
   * \brief A test function for equality operator
   */
  static void OperatorEqualityTest() {
    DataLoop *q = new DataLoop();
    *q += 10; *q += 30; *q += 20;    
    DataLoop *r = new DataLoop();
    *r += 10; *r += 30; *r += 20;
    // check if they are the same
    ASSERT(*q == *r);

    q->start->data = 15;   // change node
    ASSERT(!(*q == *r));

    q->start->data = 10;   // reset to same
    q->start = q->start->next->next;   // move start
    ASSERT(!(*q == *r));

    q->start = q->start->prev->prev;  // reset to same
    *q += 15;               // add node
    ASSERT(!(*q == *r));
    
    delete r;
    delete q;

    // Empty comparison
    DataLoop *s = new DataLoop();
    DataLoop *t = new DataLoop();
    ASSERT(*s == *t);
    s->start = nullptr;
    t->start = nullptr;
    ASSERT(*s == *t);

    delete s;
    delete t;

    // Different size comparison
    DataLoop *u = new DataLoop();
    DataLoop *v = new DataLoop();

    *u += 10;
    *u += 20;
    *v += 10;
    *v += 20;
    *v += 30;

    ASSERT(u->count != v->count);

    delete u;
    delete v;

    DataLoop *a = new DataLoop();
    *a += 10; *a += 20; *a += 30;

    DataLoop *b = new DataLoop();
    *b += 20; *b += 30; *b += 10;

    ASSERT(!(*a == *b));

    delete a;
    delete b;

    // Same elements different size
    DataLoop *c = new DataLoop();
    *c += 10; *c += 20; *c += 30;

    DataLoop *d = new DataLoop();
    *d += 10; *d += 20; *d += 30; *d += 40;

    ASSERT(!(*c == *d));

    *c += 40;

    ASSERT(*c == *d);

    delete c;
    delete d;

    // Same element different start position
    DataLoop *e = new DataLoop();
    *e += 10; *e += 20; *e += 30;

    DataLoop *f = new DataLoop();
    *f += 20; *f += 30; *f += 10;

    e->start = e->start->next->next;

    ASSERT(!(*e == *f));

    delete e;
    delete f;
  }
  
  /**
   * \brief A test function for concatenate operator
   */
  static void OperatorConcatenateTest() {
    DataLoop *q = new DataLoop(10);
    *q += 30;
    DataLoop *r = new DataLoop(15);
    *r += 5;
    DataLoop *s = new DataLoop(100);
    *s = *q + *r;
    ASSERT(s->count == 4);

    // check if the structure is as expected
    ASSERT(s->start != nullptr);
    ASSERT(s->start->data == 10);
    ASSERT(s->start->next != nullptr);
    ASSERT(s->start->next->data == 30);
    ASSERT(s->start->next->next != nullptr);
    ASSERT(s->start->next->next->data == 15);
    ASSERT(s->start->next->next->next != nullptr);
    ASSERT(s->start->next->next->next->data == 5);
    ASSERT(s->start->next->next->next->next == s->start);

    // TODO: add prev tests
    ASSERT(s->start->prev != nullptr);
    ASSERT(s->start->prev->data == 5);
    ASSERT(s->start->next->next->prev != nullptr);
    ASSERT(s->start->next->next->prev->data == 30);

    // TODO: test that q and r have not changed
    ASSERT(q->count == 2);
    ASSERT(q->start->next->data == 30);
    ASSERT(r->count == 2);
    ASSERT(r->start->next->data == 5);

    delete s;
    delete r;
    delete q;

    // Test with empty dataloop
    DataLoop *a = new DataLoop();
    DataLoop *b = new DataLoop();
    DataLoop *c = new DataLoop();
    *c = *a + *b;
    ASSERT(c->count == 0);
    delete a;
    delete b;
    delete c;

    // Test with non-empty and empty dataloop
    DataLoop *d = new DataLoop(10);
    DataLoop *e = new DataLoop();
    DataLoop *f = new DataLoop();
    *f = *d + *e;
    ASSERT(f->count == 1);
    ASSERT(f->start->data == 10);
    delete d;
    delete e;
    delete f;

    // Test for not empty dataloops with different sizes
    DataLoop *g = new DataLoop(10);
    *g += 30;
    DataLoop *h = new DataLoop(15);
    *h += 5;
    DataLoop *i = new DataLoop();
    *i = *g + *h;
    ASSERT(i->count == 4);
    ASSERT(i->start->data == 10);
    ASSERT(i->start->next->data == 30);
    ASSERT(i->start->next->next->data == 15);
    ASSERT(i->start->next->next->next->data == 5);
    delete i;
    delete h;
    delete g;

    // Test for not empty dataloops with same sizes
    DataLoop *j = new DataLoop();
    *j += 10; *j += 20;
    DataLoop *k = new DataLoop();
    *k += 5; *k += 15;
    DataLoop *l = new DataLoop();
    *l = *j + *k;
    ASSERT(l->count == 4);
    ASSERT(l->start->data == 10);
    ASSERT(l->start->next->data == 20);
    ASSERT(l->start->next->next->data == 5);
    ASSERT(l->start->next->next->next->data == 15);
    delete l;
    delete k;
    delete j;

  }
  
  /**
   * \brief A test function for stream insertion operator
   */
  static void OperatorStreamInsertionTest() {
    DataLoop *q = new DataLoop();
    std::stringstream empty_ss;
    empty_ss << *q;
    ASSERT(empty_ss.str() == ">no values<");
    *q += 10; *q += 30; *q += 20;
    std::stringstream ss;
    ss << *q;
    ASSERT(ss.str() == "-> 10 <--> 30 <--> 20 <-");
    delete q;
  }

  /**
   * \brief A test function for shift operator
   */
  static void OperatorShiftTest() {
    DataLoop *q = new DataLoop();
    for (int i = 1; i <= 10; i++) {
      *q += i;
    }
    *q ^ 0;
    ASSERT(q->start->data == 1);
    *q ^ 1;
    ASSERT(q->start->data == 2);
    *q ^ 5;
    ASSERT(q->start->data == 7);
    *q ^ 20;
    ASSERT(q->start->data == 7);
    *q ^ -1;
    ASSERT(q->start->data == 6);
    *q ^ -8;
    ASSERT(q->start->data == 8);
    *q ^ -49;
    ASSERT(q->start->data == 9);
    
    delete q;
  }

  /**
   * \brief A test function for length function
   */
  static void FunctionLengthTest() {
    DataLoop *q = new DataLoop();
    ASSERT(q->length() == 0);
    *q += 10;
    ASSERT(q->length() == 1);
    *q += 30; *q += 20;
    ASSERT(q->length() == 3);
    delete q;
  }

  /**
   * \brief A test function for splice function, depends on operator<< and operator+=
   */
  static void FunctionSpliceTest() {
    DataLoop *q = new DataLoop();
    for (int i = 1; i <= 4; i++) {
      *q += i;
    }
    DataLoop *r = new DataLoop();
    for (int j = 10; j <= 12; j++) {
      *r += j;
    }

    q->splice(*r, 0);
    ASSERT(q->count == 7);
    ASSERT(r->count == 0);
    ASSERT(r->start == nullptr);

    std::stringstream ss1;
    ss1 << *q;
    ASSERT(ss1.str() == "-> 10 <--> 11 <--> 12 <--> 1 <--> 2 <--> 3 <--> 4 <-");

    std::stringstream ss2;
    ss2 << *r;
    ASSERT(ss2.str() == ">no values<");
    
    DataLoop *p = new DataLoop();
    *p += 20;
    *p += 25;
    q->splice(*p, 9);
    ASSERT(q->count == 9);
    std::stringstream ss3;
    ss3 << *q;
    ASSERT(ss3.str() == "-> 10 <--> 11 <--> 20 <--> 25 <--> 12 <--> 1 <--> 2 <--> 3 <--> 4 <-");

    delete p;   // empty list
    delete r;   // empty list
    delete q; 
  }

};

// call our test functions in the main
int main(int, char* argv[]) {
  cout << "Testing DataLoop" << endl;
  // register a seg fault handler
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);
  
  DataLoopTest::DefaultConstructorTest();
  DataLoopTest::NonDefaultConstructorTest();
  DataLoopTest::OperatorPlusGetsTest();    // needed for below tests

  DataLoopTest::CopyConstructorTest();
  DataLoopTest::OperatorAssignmentTest();
  DataLoopTest::OperatorEqualityTest();
  DataLoopTest::OperatorConcatenateTest();
  DataLoopTest::OperatorStreamInsertionTest();

  DataLoopTest::OperatorShiftTest();
  DataLoopTest::FunctionLengthTest();
  DataLoopTest::FunctionSpliceTest(); 

  cout << "Reached end of tests!" <<  endl;
  
  return 0;
}
