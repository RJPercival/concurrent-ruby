#ifndef rb_check_arity

// https://github.com/ruby/ruby/blob/ruby_2_0_0/include/ruby/intern.h
// rb_check_arity was added in Ruby 2.0

#define UNLIMITED_ARGUMENTS (-1)

static inline VALUE rb_error_arity(int argc, int min, int max)
{
  VALUE err_mess = 0;
  if (min == max) {
    err_mess = rb_sprintf("wrong number of arguments (%d for %d)", argc, min);
  }
  else if (max == UNLIMITED_ARGUMENTS) {
    err_mess = rb_sprintf("wrong number of arguments (%d for %d+)", argc, min);
  }
  else {
    err_mess = rb_sprintf("wrong number of arguments (%d for %d..%d)", argc, min, max);
  }
  return rb_ext_new3(rb_eTypeError, err_mess);
}

#define rb_check_arity(argc, min, max) do { \
  if (((argc) < (min)) || ((argc) > (max) && (max) != UNLIMITED_ARGUMENTS)) \
  rb_exc_raise(rb_error_arity(argc, min, max)); \
} while(0)

#endif
