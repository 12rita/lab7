// ConsoleApplication1.cpp: определяет точку входа для консольного приложения. 
// 

#include "stdafx.h" 

using namespace std; 

mutex g; 
mutex h; 

bool ready = false; 
mutex mtx; 
condition_variable cv; 

void po4(mutex& g) 
{ 
for (int i = 0;i < 5;i++) 
{ 
g.lock(); 
for (int j = 0;j < 5;j++) 
{ 
cout « 'a'; 
} 
g.unlock(); 
Sleep(2); 
} 
} 

void po4_2(mutex& g) 
{ 
for (int i = 0;i < 5;i++) 
{ 
g.lock(); 
for (int j = 0;j < 5;j++) 
{ 
cout « 'b'; 
} 
g.unlock(); 
Sleep(2); 
} 
} 

void timer(int a) 
{ 
Sleep(a*1000); 
cout « "timer" « endl; 
} 


void block(mutex& a, mutex& b) 
{ 
cout « '1'; 
lock_guard<mutex> l1(a); 
Sleep(10); 
lock_guard<mutex> l2(b); 
cout « '2'; 
} 

void block2(mutex& a, mutex& b) 
{ 
cout « '3'; 
lock_guard<mutex> l2(b); 
Sleep(10); 
lock_guard<mutex> l1(a); 
cout « '4'; 
} 

void block3() 
{ 
unique_lock<mutex> lk(mtx); 
cv.wait(lk, []() { return ready;}); 


for (int i = 0; i < 100; i++) 
{ 
Sleep(10); 
cout « "d"; 
} 

} 

void po50() 
{ 
unique_lock<mutex> lk(mtx); 

for (int i = 0; i < 50; i++) 
{ 
cout « "c"; 
} 
ready = true; 
lk.unlock(); 
cv.notify_one(); 

for (int i = 0; i < 50; i++) 
{ 
Sleep(10); 
cout « "c"; 
} 
} 

int main() 
{ 
{ 
int time; 
cin » time; 
thread a(timer, time); 
a.detach(); 

thread b(po4, ref(g)); 
thread c(po4_2, ref(g)); 
b.join(); 
c.join(); 
} 

system("pause"); 
{ 
thread d(block3); 
thread e(po50); 
d.join(); 
e.join(); 
} 

{ 
thread f(block, ref(g), ref(h)); 
thread j(block2, ref(g), ref(h)); 
f.join(); 
j.join(); 

} 

return 0; 
}
