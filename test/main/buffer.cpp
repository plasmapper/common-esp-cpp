#include "buffer.h"
#include "unity.h"

//==============================================================================

const size_t bufferSize = 10;

#pragma pack(push, 1)
struct CustomBufferType {
  int x;
  int y;
  int z;
};
#pragma pack(pop)

const int dataToWrite[] = {1, 2, 3};

//==============================================================================

void TestBuffer() {
  uint8_t data[bufferSize];
  PL::Buffer buffer1 (data, bufferSize);
  TEST_ASSERT (buffer1.data == data);
  TEST_ASSERT (buffer1.size == bufferSize);
  TEST_ASSERT (buffer1.Lock() == ESP_OK);
  TEST_ASSERT (buffer1.Unlock() == ESP_OK);

  auto buffer2 = std::make_shared<PL::Buffer>(bufferSize);
  TEST_ASSERT (buffer2->data != NULL);
  TEST_ASSERT (buffer2->size == bufferSize);

  PL::Buffer buffer3 ((uint8_t*)buffer2->data + 1, bufferSize - 3, buffer2);
  TEST_ASSERT (buffer3.data == (uint8_t*)buffer2->data + 1);
  TEST_ASSERT (buffer3.size == bufferSize - 3);

  PL::TypedBuffer<CustomBufferType> buffer4;
  TEST_ASSERT_EQUAL (sizeof(CustomBufferType), buffer4.size);
  for (int i = 0; i < sizeof (dataToWrite) / sizeof (int); i++)
    ((int*)((PL::Buffer&)buffer4).data)[i] = dataToWrite[i];
  TEST_ASSERT_EQUAL (dataToWrite[0], buffer4.data->x);
  TEST_ASSERT_EQUAL (dataToWrite[1], buffer4.data->y);
  TEST_ASSERT_EQUAL (dataToWrite[2], buffer4.data->z);

  PL::TypedBuffer<CustomBufferType> buffer5 (10);
  TEST_ASSERT_EQUAL (sizeof(CustomBufferType) * 10, buffer5.size);
  for (int e = 0; e < (buffer5.size) / sizeof (CustomBufferType); e++) {
    for (int i = 0; i < sizeof (dataToWrite) / sizeof (int); i++)
      ((int*)((PL::Buffer&)buffer5).data)[e * sizeof (CustomBufferType) / sizeof (int) + i] = dataToWrite[i];
    TEST_ASSERT_EQUAL (dataToWrite[0], buffer5.data[e].x);
    TEST_ASSERT_EQUAL (dataToWrite[1], buffer5.data[e].y);
    TEST_ASSERT_EQUAL (dataToWrite[2], buffer5.data[e].z);
  }
}