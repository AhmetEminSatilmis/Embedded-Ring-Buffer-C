#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define BUFFER_SIZE 5


typedef struct
{
  uint8_t buffer[BUFFER_SIZE];
  uint32_t head;
  uint32_t tail;
  bool is_full;
} RingBuffer_t;

void RingBuffer_Init(RingBuffer_t *rb)
{
  rb->head = 0;
  rb->tail = 0;
  rb->is_full = false;
  printf("Buffer is cleaned. Size: %d\n", BUFFER_SIZE);
}

bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data)
{
  if (rb->is_full)
  {
    return false;
  }
  rb->buffer[rb->head] = data;
  rb->head = (rb->head + 1) % BUFFER_SIZE;
  if (rb->head == rb->tail)
  {
    rb->is_full = true;
  }
  printf("Data: %d is written in the index: %d \n", data, (rb->head == 0 ? BUFFER_SIZE - 1 : rb->head -1));
  return true;
}

bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data)
{
  if ((rb->head == rb->tail) && !rb->is_full)
  {
    return false;
  }
  *data = rb->buffer[rb->tail];
  rb->tail = (rb->tail + 1) % BUFFER_SIZE;
  rb->is_full = false;
  printf("Data: %d is read. The next index to read is: %d\n", *data, rb->tail);
  return true;
}

int main()
{
  RingBuffer_t uart_query;
  uint8_t read_data;
  uint8_t written_data[] = {10, 20, 30, 40, 50, 60, 70};
  RingBuffer_Init(&uart_query);
  for (int i = 0; i < 6; i++)
  {
    if (!RingBuffer_Write(&uart_query, written_data[i]))
    {
      printf("Error, data: %d was not written because the buffer is full. Please read a data first.\n", written_data[i]);
    }
  }
  for (int i = 0; i < 2; i++)
  {
    if(!RingBuffer_Read(&uart_query, &read_data))
    {
      printf("Buffer is empty, there is no data to read\n");
    }
  }
  for (int i = 5; i < 7; i++)
  {
    if (!RingBuffer_Write(&uart_query, written_data[i]))
    {
      printf("Error, data: %d was not written because the buffer is full. Please read a data first.\n", written_data[i]);
    }
  }
  return 0;
}
  
  
  
  
  
    
  
  
    
  


  
