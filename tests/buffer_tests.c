#include <check.h>

#include "../mhttp.h"
#include <unistd.h>

START_TEST (buffer_tests)
{
  struct http_buffer_t buf;
  http_alloc_buffer(&buf, 20, true);

  ck_assert_uint_eq(buf.len, 20);
  ck_assert_uint_eq(buf.size, getpagesize());
  ck_assert_ptr_nonnull(buf.buf);

  http_free_buffer(&buf);

  ck_assert_uint_eq(buf.len, 0);
  ck_assert_uint_eq(buf.size, 0);
  ck_assert_ptr_null(buf.buf);

  http_alloc_buffer(&buf, getpagesize(), true); 
  ck_assert_uint_eq(buf.len, getpagesize());
  ck_assert_uint_eq(buf.size, getpagesize());

  http_free_buffer(&buf);

  http_alloc_buffer(&buf, getpagesize() + 1, true); 
  ck_assert_uint_eq(buf.len,  getpagesize() + 1);
  ck_assert_uint_eq(buf.size, 2 * getpagesize());

  http_free_buffer(&buf);

}
END_TEST

Suite *buffer_suite(void) {
  Suite *s;
  TCase *tc_buffer;

  s = suite_create("buffers");
  tc_buffer = tcase_create("allocation");
  tcase_add_test(tc_buffer, buffer_tests);
  suite_add_tcase(s, tc_buffer);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = buffer_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}