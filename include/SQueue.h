#if !defined(SIMPLE_QUEUE_H)
#define SIMPLE_QUEUE_H

#define Q_ERR 7 // A queue is overflow
#define Q_SIZE 64U

#include <inttypes.h>

template <typename T> class SQueue {
private:
  uint32_t front;
  uint32_t rear;
  uint32_t _mSize;
  uint32_t mCapacity;
  T **array;
  SQueue() {}

public:
  explicit SQueue(uint32_t capacity) {
    front = 0;
    _mSize = 0;
    mCapacity = capacity;
    rear = capacity - 1;
    array = new T *[capacity];
    Serial.println(F("Queue constructor ok"));
    stats();
  }

  ~SQueue() { delete[] array; }

  inline bool isFull() { return _mSize == mCapacity; }

  inline bool isEmpty() { return _mSize == 0; }

  inline uint32_t size() { return _mSize; }

  void clean() {
    if (!isEmpty()) {
      Serial.println(F("The queue is not empty"));
      return;
    }

    front = 0;
    _mSize = 0;
    rear = mCapacity - 1;
    stats();
  }

  bool enqueue(T *item) {
    if (isFull())
      return false;

    rear++;
    if (rear >= mCapacity)
      rear = 0;

    array[rear] = item;

    _mSize++;

#if defined(_Q_DEBUG_)

    stats();

#endif // _Q_DEBUG_

    return true;
  }

  T *dequeue() {
    if (isEmpty())
      return nullptr;

    T *tItem = array[front];

    front++;
    if (front >= mCapacity)
      front = 0;

    _mSize--;

#if defined(_Q_DEBUG_)

    stats();

#endif // _Q_DEBUG_

    return tItem;
  }

  void stats() {
    Serial.println(F("== Queue Stats =="));

    Serial.print("|Size ");
    Serial.println(_mSize);
    Serial.print("|Front ");
    Serial.println(front);
    Serial.print("|Rear ");
    Serial.println(rear);
    Serial.print("|isEmpty ");
    Serial.println(isEmpty());
    Serial.print("|isFull ");
    Serial.println(isFull());

    Serial.println(F("==="));
  }
};

#endif // SIMPLE_QUEUE_H