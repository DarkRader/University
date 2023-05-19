/********************************************************************************
  - Producer/consumer problem synchronized by condition variables.
  - Each producer generates 10 items
  - The program ends when all the producers have finished and shared buffer is empty
*********************************************************************************/

#include <iostream>
#include <vector>
#include <chrono>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

#define BUFFER_SIZE 5

using namespace std;

// item of buffer
struct item_t
{
  int  tid;           // tid of the thread that created the item
  int  id;            // sequence number of the item creation
  int  value;         // value of item
  bool end;           // false => consumer should continue
                      // true  => consumer should finish
};

/*************************************/
class BufferClass
{
private:
  deque<item_t*>       buff;       // shared buffer
  mutex                mtx;        // controls access to share buffer (critical section)
  condition_variable   cv_full;    // protects from inserting items into a full buffer
  condition_variable   cv_empty;   // protects from removing items from an empty buffer

  /****************************/
  void PrintBuffer()
  {
    printf("Buffer: ");
    for (deque<item_t*>::iterator it = buff.begin(); it!=buff.end(); ++it)
      printf("[%d, %d, %d, %c] ",(*it)->tid, (*it)->id, (*it)->value, (*it)->end ? 'T' : 'F');
    printf("\n");
  }

public:
  /****************************/
  BufferClass() { }
 
  /****************************/
  virtual void insert(item_t *item)
  {
    unique_lock<mutex> ul (mtx);
    cv_full.wait(ul, [ this ] () { return ( buff.size() < BUFFER_SIZE ); } );
    buff.push_back(item);

    printf("Producer %d:  item [%d,%d,%d,%c] was inserted\n", item->tid, item->tid, item->id, item->value, item->end ? 'T' : 'F');
    PrintBuffer();
    
    cv_empty.notify_one();
  }

  /****************************/
  virtual item_t * remove(int tid)
  {
    item_t *item;

    unique_lock<mutex> ul (mtx);
    cv_empty.wait(ul, [ this ] () { return ( ! buff.empty() ); } );
    item = buff.front();
    buff.pop_front();
   
    printf("Consumer %d:  item [%d,%d,%d,%c] was removed\n", tid, item->tid, item->id, item->value, item->end ? 'T' : 'F');
    PrintBuffer();

    cv_full.notify_one();
    return item;
  }
  
  /****************************/
  virtual bool empty()
  {
    return buff.empty();
  }
};

/*************************************/
void producer(int tid, int delay, BufferClass &buff, mutex &mtx, int &runningProd, int &runningCons)
{
    int var;
  int count = 0;
  int delay_ms = 100 * delay;

  // Insert 10 items to the buffer
  for ( int i = 0; i < 10; i++ )
  {
    item_t *item  = new item_t { tid, count, rand() % 100, false };
    count++;
    
    buff.insert(item);

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
  }
    
  // Producer exit sequence
  unique_lock<mutex> ul (mtx);
    runningProd--;
    var = runningProd;
  ul.unlock();
    
  // The last producer inserts special termination items (one item per one running consumer)
  if(var == 0) {
    for(int i = 0; i < runningCons; i++) {
        item_t *item = new item_t { tid, count, 0, true };
        count++;
        buff.insert(item);
    }
  }
  printf("Producer %d: end\n", tid);
}

/*************************************/
void consumer(int tid, int delay, BufferClass &buff )
{
  int delay_ms = 100 * delay;

  // Remove items from the buffer
  while ( 1 )
  {
    item_t *item = buff.remove(tid);
      
    // End item -> -> the consumer ends
    if(item->end) {
        delete(item);
        break;
    }
     
    // Data item
    delete(item);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
  }
  printf("Consumer %d: end\n", tid);
}

/*************************************/
int main ( int argc, char * argv [] )
{
  int            prods;       // Number of producers
  int            prods_delay; // Producer delay
  int            cons;        // Number of consumers
  int            cons_delay;  // Consumer delay
  BufferClass    buffer;      // Shared buffer
  vector<thread> threads;
    
  mutex          mtx;         // Controls access to the following shared variables
  int            runningProds;// Number of running producers
  int            runningCons; // Number of running consumers

  // Check arguments
  if ( argc != 5 || sscanf ( argv[1], "%d", &prods )       != 1
                 || sscanf ( argv[2], "%d", &prods_delay ) != 1
                 || sscanf ( argv[3], "%d", &cons )        != 1
                 || sscanf ( argv[4], "%d", &cons_delay )  != 1
                 || prods < 1 || prods_delay < 0 || cons < 1 || cons_delay < 0 )
  {
    printf ( "Usage: %s <# of produsers> <producer delay> <# of consumers> <consumer delay>\n", argv[0] );
    return ( 1 );
  }
  
  // Create produsers
  for ( int i = 0; i < prods; i ++ )
    threads.push_back ( thread ( producer, i, prods_delay, ref(buffer), ref(mtx), ref(runningProds), ref(runningCons) ) );

  // Create consumers
  for ( int i = 0; i < cons; i ++ )
    threads.push_back ( thread ( consumer, i, cons_delay, ref(buffer) ) );

  // Wait for all threads
  for ( auto & t : threads )
    t.join ();

  return 0;
}
