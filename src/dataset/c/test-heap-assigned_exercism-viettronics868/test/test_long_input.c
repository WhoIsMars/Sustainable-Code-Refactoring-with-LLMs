/*
this file is modified from test_rna_transcription.c that was cloned from exercism website
. The modification for educational purpose only. Date 2024-12-25.
*/

#include "test-framework/unity.h"
#include "process_long_input.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



void setUp(void)
{
}

void tearDown(void)
{
}

static void check_transcription(int fd, const char *expected, char **real_text)
{

  
   size_t word = 16;
   
   parse_input(fd, word, real_text);
   TEST_ASSERT_EQUAL_STRING(expected, *real_text);
   
}

static void test_long_string(void) // my test case
{
   //TEST_IGNORE();
   int fd = open("for_test.txt", O_RDWR);
   char *real_text = NULL;
   check_transcription(fd, "Hello, this is a long string split into chunks. Enjoy testing!", &real_text);
   free(real_text);
   real_text = NULL;
   close(fd);

}

int main(void)
{
   UNITY_BEGIN();

   RUN_TEST(test_long_string);

   return UNITY_END();
}
