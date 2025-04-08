#include "src/perfetto-bindings.h"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#if __cplusplus >= 201703L
#include <string_view>
#endif
#if __cplusplus >= 202002L
#include <ranges>
#endif

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_PANIC
#define CXXBRIDGE1_PANIC
template <typename Exception>
void panic [[noreturn]] (const char *msg);
#endif // CXXBRIDGE1_PANIC

struct unsafe_bitcopy_t;

namespace {
template <typename T>
class impl;
} // namespace

template <typename T>
::std::size_t size_of();
template <typename T>
::std::size_t align_of();

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final {
public:
  String() noexcept;
  String(const String &) noexcept;
  String(String &&) noexcept;
  ~String() noexcept;

  String(const std::string &);
  String(const char *);
  String(const char *, std::size_t);
  String(const char16_t *);
  String(const char16_t *, std::size_t);
#ifdef __cpp_char8_t
  String(const char8_t *s);
  String(const char8_t *s, std::size_t len);
#endif

  static String lossy(const std::string &) noexcept;
  static String lossy(const char *) noexcept;
  static String lossy(const char *, std::size_t) noexcept;
  static String lossy(const char16_t *) noexcept;
  static String lossy(const char16_t *, std::size_t) noexcept;

  String &operator=(const String &) & noexcept;
  String &operator=(String &&) & noexcept;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  const char *c_str() noexcept;

  std::size_t capacity() const noexcept;
  void reserve(size_t new_cap) noexcept;

  using iterator = char *;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const String &) const noexcept;
  bool operator!=(const String &) const noexcept;
  bool operator<(const String &) const noexcept;
  bool operator<=(const String &) const noexcept;
  bool operator>(const String &) const noexcept;
  bool operator>=(const String &) const noexcept;

  void swap(String &) noexcept;

  String(unsafe_bitcopy_t, const String &) noexcept;

private:
  struct lossy_t;
  String(lossy_t, const char *, std::size_t) noexcept;
  String(lossy_t, const char16_t *, std::size_t) noexcept;
  friend void swap(String &lhs, String &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const String &) noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, std::size_t);

  Str &operator=(const Str &) & noexcept = default;

  explicit operator std::string() const;
#if __cplusplus >= 201703L
  explicit operator std::string_view() const;
#endif

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const Str &) const noexcept;
  bool operator!=(const Str &) const noexcept;
  bool operator<(const Str &) const noexcept;
  bool operator<=(const Str &) const noexcept;
  bool operator>(const Str &) const noexcept;
  bool operator>=(const Str &) const noexcept;

  void swap(Str &) noexcept;

private:
  class uninit;
  Str(uninit) noexcept;
  friend impl<Str>;

  std::array<std::uintptr_t, 2> repr;
};
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_SLICE
#define CXXBRIDGE1_RUST_SLICE
namespace detail {
template <bool>
struct copy_assignable_if {};

template <>
struct copy_assignable_if<false> {
  copy_assignable_if() noexcept = default;
  copy_assignable_if(const copy_assignable_if &) noexcept = default;
  copy_assignable_if &operator=(const copy_assignable_if &) & noexcept = delete;
  copy_assignable_if &operator=(copy_assignable_if &&) & noexcept = default;
};
} // namespace detail

template <typename T>
class Slice final
    : private detail::copy_assignable_if<std::is_const<T>::value> {
public:
  using value_type = T;

  Slice() noexcept;
  Slice(T *, std::size_t count) noexcept;

  template <typename C>
  explicit Slice(C &c) : Slice(c.data(), c.size()) {}

  Slice &operator=(const Slice<T> &) & noexcept = default;
  Slice &operator=(Slice<T> &&) & noexcept = default;

  T *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  T &operator[](std::size_t n) const noexcept;
  T &at(std::size_t n) const;
  T &front() const noexcept;
  T &back() const noexcept;

  Slice(const Slice<T> &) noexcept = default;
  ~Slice() noexcept = default;

  class iterator;
  iterator begin() const noexcept;
  iterator end() const noexcept;

  void swap(Slice &) noexcept;

private:
  class uninit;
  Slice(uninit) noexcept;
  friend impl<Slice>;
  friend void sliceInit(void *, const void *, std::size_t) noexcept;
  friend void *slicePtr(const void *) noexcept;
  friend std::size_t sliceLen(const void *) noexcept;

  std::array<std::uintptr_t, 2> repr;
};

#ifdef __cpp_deduction_guides
template <typename C>
explicit Slice(C &c)
    -> Slice<std::remove_reference_t<decltype(*std::declval<C>().data())>>;
#endif // __cpp_deduction_guides

template <typename T>
class Slice<T>::iterator final {
public:
#if __cplusplus >= 202002L
  using iterator_category = std::contiguous_iterator_tag;
#else
  using iterator_category = std::random_access_iterator_tag;
#endif
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::add_pointer<T>::type;
  using reference = typename std::add_lvalue_reference<T>::type;

  reference operator*() const noexcept;
  pointer operator->() const noexcept;
  reference operator[](difference_type) const noexcept;

  iterator &operator++() noexcept;
  iterator operator++(int) noexcept;
  iterator &operator--() noexcept;
  iterator operator--(int) noexcept;

  iterator &operator+=(difference_type) noexcept;
  iterator &operator-=(difference_type) noexcept;
  iterator operator+(difference_type) const noexcept;
  friend inline iterator operator+(difference_type lhs, iterator rhs) noexcept {
    return rhs + lhs;
  }
  iterator operator-(difference_type) const noexcept;
  difference_type operator-(const iterator &) const noexcept;

  bool operator==(const iterator &) const noexcept;
  bool operator!=(const iterator &) const noexcept;
  bool operator<(const iterator &) const noexcept;
  bool operator<=(const iterator &) const noexcept;
  bool operator>(const iterator &) const noexcept;
  bool operator>=(const iterator &) const noexcept;

private:
  friend class Slice;
  void *pos;
  std::size_t stride;
};

#if __cplusplus >= 202002L
static_assert(std::ranges::contiguous_range<rust::Slice<const uint8_t>>);
static_assert(std::contiguous_iterator<rust::Slice<const uint8_t>::iterator>);
#endif

template <typename T>
Slice<T>::Slice() noexcept {
  sliceInit(this, reinterpret_cast<void *>(align_of<T>()), 0);
}

template <typename T>
Slice<T>::Slice(T *s, std::size_t count) noexcept {
  assert(s != nullptr || count == 0);
  sliceInit(this,
            s == nullptr && count == 0
                ? reinterpret_cast<void *>(align_of<T>())
                : const_cast<typename std::remove_const<T>::type *>(s),
            count);
}

template <typename T>
T *Slice<T>::data() const noexcept {
  return reinterpret_cast<T *>(slicePtr(this));
}

template <typename T>
std::size_t Slice<T>::size() const noexcept {
  return sliceLen(this);
}

template <typename T>
std::size_t Slice<T>::length() const noexcept {
  return this->size();
}

template <typename T>
bool Slice<T>::empty() const noexcept {
  return this->size() == 0;
}

template <typename T>
T &Slice<T>::operator[](std::size_t n) const noexcept {
  assert(n < this->size());
  auto ptr = static_cast<char *>(slicePtr(this)) + size_of<T>() * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
T &Slice<T>::at(std::size_t n) const {
  if (n >= this->size()) {
    panic<std::out_of_range>("rust::Slice index out of range");
  }
  return (*this)[n];
}

template <typename T>
T &Slice<T>::front() const noexcept {
  assert(!this->empty());
  return (*this)[0];
}

template <typename T>
T &Slice<T>::back() const noexcept {
  assert(!this->empty());
  return (*this)[this->size() - 1];
}

template <typename T>
typename Slice<T>::iterator::reference
Slice<T>::iterator::operator*() const noexcept {
  return *static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::pointer
Slice<T>::iterator::operator->() const noexcept {
  return static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator[](
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ptr = static_cast<char *>(this->pos) + this->stride * n;
  return *reinterpret_cast<T *>(ptr);
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator++() noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator++(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) + this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator--() noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator--(int) noexcept {
  auto ret = iterator(*this);
  this->pos = static_cast<char *>(this->pos) - this->stride;
  return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator+=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) + this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator-=(
    typename Slice<T>::iterator::difference_type n) noexcept {
  this->pos = static_cast<char *>(this->pos) - this->stride * n;
  return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator+(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) + this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator-(
    typename Slice<T>::iterator::difference_type n) const noexcept {
  auto ret = iterator(*this);
  ret.pos = static_cast<char *>(this->pos) - this->stride * n;
  return ret;
}

template <typename T>
typename Slice<T>::iterator::difference_type
Slice<T>::iterator::operator-(const iterator &other) const noexcept {
  auto diff = std::distance(static_cast<char *>(other.pos),
                            static_cast<char *>(this->pos));
  return diff / static_cast<typename Slice<T>::iterator::difference_type>(
                    this->stride);
}

template <typename T>
bool Slice<T>::iterator::operator==(const iterator &other) const noexcept {
  return this->pos == other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator!=(const iterator &other) const noexcept {
  return this->pos != other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<(const iterator &other) const noexcept {
  return this->pos < other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<=(const iterator &other) const noexcept {
  return this->pos <= other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>(const iterator &other) const noexcept {
  return this->pos > other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>=(const iterator &other) const noexcept {
  return this->pos >= other.pos;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::begin() const noexcept {
  iterator it;
  it.pos = slicePtr(this);
  it.stride = size_of<T>();
  return it;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::end() const noexcept {
  iterator it = this->begin();
  it.pos = static_cast<char *>(it.pos) + it.stride * this->size();
  return it;
}

template <typename T>
void Slice<T>::swap(Slice &rhs) noexcept {
  std::swap(*this, rhs);
}
#endif // CXXBRIDGE1_RUST_SLICE

#ifndef CXXBRIDGE1_RUST_BOX
#define CXXBRIDGE1_RUST_BOX
template <typename T>
class Box final {
public:
  using element_type = T;
  using const_pointer =
      typename std::add_pointer<typename std::add_const<T>::type>::type;
  using pointer = typename std::add_pointer<T>::type;

  Box() = delete;
  Box(Box &&) noexcept;
  ~Box() noexcept;

  explicit Box(const T &);
  explicit Box(T &&);

  Box &operator=(Box &&) & noexcept;

  const T *operator->() const noexcept;
  const T &operator*() const noexcept;
  T *operator->() noexcept;
  T &operator*() noexcept;

  template <typename... Fields>
  static Box in_place(Fields &&...);

  void swap(Box &) noexcept;

  static Box from_raw(T *) noexcept;

  T *into_raw() noexcept;

  /* Deprecated */ using value_type = element_type;

private:
  class uninit;
  class allocation;
  Box(uninit) noexcept;
  void drop() noexcept;

  friend void swap(Box &lhs, Box &rhs) noexcept { lhs.swap(rhs); }

  T *ptr;
};

template <typename T>
class Box<T>::uninit {};

template <typename T>
class Box<T>::allocation {
  static T *alloc() noexcept;
  static void dealloc(T *) noexcept;

public:
  allocation() noexcept : ptr(alloc()) {}
  ~allocation() noexcept {
    if (this->ptr) {
      dealloc(this->ptr);
    }
  }
  T *ptr;
};

template <typename T>
Box<T>::Box(Box &&other) noexcept : ptr(other.ptr) {
  other.ptr = nullptr;
}

template <typename T>
Box<T>::Box(const T &val) {
  allocation alloc;
  ::new (alloc.ptr) T(val);
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::Box(T &&val) {
  allocation alloc;
  ::new (alloc.ptr) T(std::move(val));
  this->ptr = alloc.ptr;
  alloc.ptr = nullptr;
}

template <typename T>
Box<T>::~Box() noexcept {
  if (this->ptr) {
    this->drop();
  }
}

template <typename T>
Box<T> &Box<T>::operator=(Box &&other) & noexcept {
  if (this->ptr) {
    this->drop();
  }
  this->ptr = other.ptr;
  other.ptr = nullptr;
  return *this;
}

template <typename T>
const T *Box<T>::operator->() const noexcept {
  return this->ptr;
}

template <typename T>
const T &Box<T>::operator*() const noexcept {
  return *this->ptr;
}

template <typename T>
T *Box<T>::operator->() noexcept {
  return this->ptr;
}

template <typename T>
T &Box<T>::operator*() noexcept {
  return *this->ptr;
}

template <typename T>
template <typename... Fields>
Box<T> Box<T>::in_place(Fields &&...fields) {
  allocation alloc;
  auto ptr = alloc.ptr;
  ::new (ptr) T{std::forward<Fields>(fields)...};
  alloc.ptr = nullptr;
  return from_raw(ptr);
}

template <typename T>
void Box<T>::swap(Box &rhs) noexcept {
  using std::swap;
  swap(this->ptr, rhs.ptr);
}

template <typename T>
Box<T> Box<T>::from_raw(T *raw) noexcept {
  Box box = uninit{};
  box.ptr = raw;
  return box;
}

template <typename T>
T *Box<T>::into_raw() noexcept {
  T *raw = this->ptr;
  this->ptr = nullptr;
  return raw;
}

template <typename T>
Box<T>::Box(uninit) noexcept {}
#endif // CXXBRIDGE1_RUST_BOX

#ifndef CXXBRIDGE1_RUST_FN
#define CXXBRIDGE1_RUST_FN
template <typename Signature>
class Fn;

template <typename Ret, typename... Args>
class Fn<Ret(Args...)> final {
public:
  Ret operator()(Args... args) const noexcept;
  Fn operator*() const noexcept;

private:
  Ret (*trampoline)(Args..., void *fn) noexcept;
  void *fn;
};

template <typename Ret, typename... Args>
Ret Fn<Ret(Args...)>::operator()(Args... args) const noexcept {
  return (*this->trampoline)(std::forward<Args>(args)..., this->fn);
}

template <typename Ret, typename... Args>
Fn<Ret(Args...)> Fn<Ret(Args...)>::operator*() const noexcept {
  return *this;
}
#endif // CXXBRIDGE1_RUST_FN

#ifndef CXXBRIDGE1_RUST_OPAQUE
#define CXXBRIDGE1_RUST_OPAQUE
class Opaque {
public:
  Opaque() = delete;
  Opaque(const Opaque &) = delete;
  ~Opaque() = delete;
};
#endif // CXXBRIDGE1_RUST_OPAQUE

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout {
  template <typename T>
  friend std::size_t size_of();
  template <typename T>
  friend std::size_t align_of();
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return T::layout::size();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return sizeof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      size_of() {
    return do_size_of<T>();
  }
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return T::layout::align();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return alignof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      align_of() {
    return do_align_of<T>();
  }
};

template <typename T>
std::size_t size_of() {
  return layout::size_of<T>();
}

template <typename T>
std::size_t align_of() {
  return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT

namespace repr {
struct PtrLen final {
  void *ptr;
  ::std::size_t len;
};
} // namespace repr

namespace detail {
class Fail final {
  ::rust::repr::PtrLen &throw$;
public:
  Fail(::rust::repr::PtrLen &throw$) noexcept : throw$(throw$) {}
  void operator()(char const *) noexcept;
  void operator()(std::string const &) noexcept;
};
} // namespace detail

namespace {
template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};

template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1

namespace behavior {
class missing {};
missing trycatch(...);

template <typename Try, typename Fail>
static typename ::std::enable_if<
    ::std::is_same<decltype(trycatch(::std::declval<Try>(), ::std::declval<Fail>())),
                 missing>::value>::type
trycatch(Try &&func, Fail &&fail) noexcept try {
  func();
} catch (::std::exception const &e) {
  fail(e.what());
}
} // namespace behavior
} // namespace rust

enum class LogLev : ::std::uint8_t;
struct DebugStringAnnotation;
struct DebugBoolAnnotation;
struct DebugIntAnnotation;
struct DebugDoubleAnnotation;
struct DebugAnnotations;
struct PollTracesCtx;
struct FlushCtx;
using PerfettoTracingSession = ::PerfettoTracingSession;

#ifndef CXXBRIDGE1_ENUM_LogLev
#define CXXBRIDGE1_ENUM_LogLev
enum class LogLev : ::std::uint8_t {
  Debug = 0,
  Info = 1,
  Important = 2,
  Error = 3,
};
#endif // CXXBRIDGE1_ENUM_LogLev

#ifndef CXXBRIDGE1_STRUCT_DebugStringAnnotation
#define CXXBRIDGE1_STRUCT_DebugStringAnnotation
struct DebugStringAnnotation final {
  ::rust::Str key;
  ::rust::String value;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_DebugStringAnnotation

#ifndef CXXBRIDGE1_STRUCT_DebugBoolAnnotation
#define CXXBRIDGE1_STRUCT_DebugBoolAnnotation
struct DebugBoolAnnotation final {
  ::rust::Str key;
  bool value;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_DebugBoolAnnotation

#ifndef CXXBRIDGE1_STRUCT_DebugIntAnnotation
#define CXXBRIDGE1_STRUCT_DebugIntAnnotation
struct DebugIntAnnotation final {
  ::rust::Str key;
  ::std::int64_t value;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_DebugIntAnnotation

#ifndef CXXBRIDGE1_STRUCT_DebugDoubleAnnotation
#define CXXBRIDGE1_STRUCT_DebugDoubleAnnotation
struct DebugDoubleAnnotation final {
  ::rust::Str key;
  double value;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_DebugDoubleAnnotation

#ifndef CXXBRIDGE1_STRUCT_DebugAnnotations
#define CXXBRIDGE1_STRUCT_DebugAnnotations
struct DebugAnnotations final {
  ::rust::Slice<::DebugStringAnnotation const> strings;
  ::rust::Slice<::DebugBoolAnnotation const> bools;
  ::rust::Slice<::DebugIntAnnotation const> ints;
  ::rust::Slice<::DebugDoubleAnnotation const> doubles;

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_DebugAnnotations

#ifndef CXXBRIDGE1_STRUCT_PollTracesCtx
#define CXXBRIDGE1_STRUCT_PollTracesCtx
struct PollTracesCtx final : public ::rust::Opaque {
  ~PollTracesCtx() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_PollTracesCtx

#ifndef CXXBRIDGE1_STRUCT_FlushCtx
#define CXXBRIDGE1_STRUCT_FlushCtx
struct FlushCtx final : public ::rust::Opaque {
  ~FlushCtx() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_FlushCtx

extern "C" {
::std::size_t cxxbridge1$PollTracesCtx$operator$sizeof() noexcept;
::std::size_t cxxbridge1$PollTracesCtx$operator$alignof() noexcept;
::std::size_t cxxbridge1$FlushCtx$operator$sizeof() noexcept;
::std::size_t cxxbridge1$FlushCtx$operator$alignof() noexcept;

void cxxbridge1$perfetto_global_init(::rust::Fn<void(::LogLev, ::std::int32_t, ::rust::Str, ::rust::Str)> log_callback, bool enable_in_process_backend, bool enable_system_backend) noexcept {
  void (*perfetto_global_init$)(::rust::Fn<void(::LogLev, ::std::int32_t, ::rust::Str, ::rust::Str)>, bool, bool) = ::perfetto_global_init;
  perfetto_global_init$(log_callback, enable_in_process_backend, enable_system_backend);
}

void cxxbridge1$perfetto_global_init$log_callback$1(::LogLev level, ::std::int32_t line, ::rust::Str filename, ::rust::Str message, void *) noexcept;

void cxxbridge1$perfetto_global_init$log_callback$0(::LogLev level, ::std::int32_t line, ::rust::Str filename, ::rust::Str message, void *extern$) noexcept {
  cxxbridge1$perfetto_global_init$log_callback$1(level, line, filename, message, extern$);
}

::rust::repr::PtrLen cxxbridge1$new_tracing_session(::rust::Slice<::std::uint8_t const> trace_config_bytes, ::std::int32_t output_fd, ::PerfettoTracingSession **return$) noexcept {
  ::std::unique_ptr<::PerfettoTracingSession> (*new_tracing_session$)(::rust::Slice<::std::uint8_t const>, ::std::int32_t) = ::new_tracing_session;
  ::rust::repr::PtrLen throw$;
  ::rust::behavior::trycatch(
      [&] {
        new (return$) ::PerfettoTracingSession *(new_tracing_session$(trace_config_bytes, output_fd).release());
        throw$.ptr = nullptr;
      },
      ::rust::detail::Fail(throw$));
  return throw$;
}

void cxxbridge1$trace_track_event_slice_begin(::std::uint64_t track_uuid, ::rust::Str name, ::rust::Str location_file, ::std::uint32_t location_line, ::DebugAnnotations const &debug_annotations) noexcept {
  void (*trace_track_event_slice_begin$)(::std::uint64_t, ::rust::Str, ::rust::Str, ::std::uint32_t, ::DebugAnnotations const &) = ::trace_track_event_slice_begin;
  trace_track_event_slice_begin$(track_uuid, name, location_file, location_line, debug_annotations);
}

void cxxbridge1$trace_track_event_slice_end(::std::uint64_t track_uuid, ::rust::Str name, ::rust::Str location_file, ::std::uint32_t location_line) noexcept {
  void (*trace_track_event_slice_end$)(::std::uint64_t, ::rust::Str, ::rust::Str, ::std::uint32_t) = ::trace_track_event_slice_end;
  trace_track_event_slice_end$(track_uuid, name, location_file, location_line);
}

void cxxbridge1$trace_track_event_instant(::std::uint64_t track_uuid, ::rust::Str name, ::rust::Str location_file, ::std::uint32_t location_line, ::DebugAnnotations const &debug_annotations) noexcept {
  void (*trace_track_event_instant$)(::std::uint64_t, ::rust::Str, ::rust::Str, ::std::uint32_t, ::DebugAnnotations const &) = ::trace_track_event_instant;
  trace_track_event_instant$(track_uuid, name, location_file, location_line, debug_annotations);
}

void cxxbridge1$trace_track_descriptor_process(::std::uint64_t parent_uuid, ::std::uint64_t track_uuid, ::rust::Str process_name, ::std::uint32_t process_pid) noexcept {
  void (*trace_track_descriptor_process$)(::std::uint64_t, ::std::uint64_t, ::rust::Str, ::std::uint32_t) = ::trace_track_descriptor_process;
  trace_track_descriptor_process$(parent_uuid, track_uuid, process_name, process_pid);
}

void cxxbridge1$trace_track_descriptor_thread(::std::uint64_t parent_uuid, ::std::uint64_t track_uuid, ::std::uint32_t process_pid, ::rust::Str thread_name, ::std::uint32_t thread_tid) noexcept {
  void (*trace_track_descriptor_thread$)(::std::uint64_t, ::std::uint64_t, ::std::uint32_t, ::rust::Str, ::std::uint32_t) = ::trace_track_descriptor_thread;
  trace_track_descriptor_thread$(parent_uuid, track_uuid, process_pid, thread_name, thread_tid);
}

::std::uint64_t cxxbridge1$trace_time_ns() noexcept {
  ::std::uint64_t (*trace_time_ns$)() = ::trace_time_ns;
  return trace_time_ns$();
}

::std::uint32_t cxxbridge1$trace_clock_id() noexcept {
  ::std::uint32_t (*trace_clock_id$)() = ::trace_clock_id;
  return trace_clock_id$();
}

void cxxbridge1$PerfettoTracingSession$start(::PerfettoTracingSession &self) noexcept {
  void (::PerfettoTracingSession::*start$)() = &::PerfettoTracingSession::start;
  (self.*start$)();
}

void cxxbridge1$PerfettoTracingSession$stop(::PerfettoTracingSession &self) noexcept {
  void (::PerfettoTracingSession::*stop$)() = &::PerfettoTracingSession::stop;
  (self.*stop$)();
}

void cxxbridge1$PerfettoTracingSession$flush(::PerfettoTracingSession &self, ::std::uint32_t timeout_ms, ::FlushCtx *ctx, ::rust::Fn<void(::rust::Box<::FlushCtx>, bool)> done) noexcept {
  void (::PerfettoTracingSession::*flush$)(::std::uint32_t, ::rust::Box<::FlushCtx>, ::rust::Fn<void(::rust::Box<::FlushCtx>, bool)>) = &::PerfettoTracingSession::flush;
  (self.*flush$)(timeout_ms, ::rust::Box<::FlushCtx>::from_raw(ctx), done);
}

void cxxbridge1$PerfettoTracingSession$flush$done$1(::FlushCtx *ctx, bool success, void *) noexcept;

void cxxbridge1$PerfettoTracingSession$flush$done$0(::rust::Box<::FlushCtx> ctx, bool success, void *extern$) noexcept {
  cxxbridge1$PerfettoTracingSession$flush$done$1(ctx.into_raw(), success, extern$);
}

void cxxbridge1$PerfettoTracingSession$poll_traces(::PerfettoTracingSession &self, ::PollTracesCtx *ctx, ::rust::Fn<void(::rust::Box<::PollTracesCtx>, ::rust::Slice<::std::uint8_t const>, bool)> done) noexcept {
  void (::PerfettoTracingSession::*poll_traces$)(::rust::Box<::PollTracesCtx>, ::rust::Fn<void(::rust::Box<::PollTracesCtx>, ::rust::Slice<::std::uint8_t const>, bool)>) = &::PerfettoTracingSession::poll_traces;
  (self.*poll_traces$)(::rust::Box<::PollTracesCtx>::from_raw(ctx), done);
}

void cxxbridge1$PerfettoTracingSession$poll_traces$done$1(::PollTracesCtx *ctx, ::rust::Slice<::std::uint8_t const> data, bool has_more, void *) noexcept;

void cxxbridge1$PerfettoTracingSession$poll_traces$done$0(::rust::Box<::PollTracesCtx> ctx, ::rust::Slice<::std::uint8_t const> data, bool has_more, void *extern$) noexcept {
  cxxbridge1$PerfettoTracingSession$poll_traces$done$1(ctx.into_raw(), data, has_more, extern$);
}
} // extern "C"

::std::size_t PollTracesCtx::layout::size() noexcept {
  return cxxbridge1$PollTracesCtx$operator$sizeof();
}

::std::size_t PollTracesCtx::layout::align() noexcept {
  return cxxbridge1$PollTracesCtx$operator$alignof();
}

::std::size_t FlushCtx::layout::size() noexcept {
  return cxxbridge1$FlushCtx$operator$sizeof();
}

::std::size_t FlushCtx::layout::align() noexcept {
  return cxxbridge1$FlushCtx$operator$alignof();
}

extern "C" {
static_assert(::rust::detail::is_complete<::PerfettoTracingSession>::value, "definition of PerfettoTracingSession is required");
static_assert(sizeof(::std::unique_ptr<::PerfettoTracingSession>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::PerfettoTracingSession>) == alignof(void *), "");
void cxxbridge1$unique_ptr$PerfettoTracingSession$null(::std::unique_ptr<::PerfettoTracingSession> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::PerfettoTracingSession>();
}
void cxxbridge1$unique_ptr$PerfettoTracingSession$raw(::std::unique_ptr<::PerfettoTracingSession> *ptr, ::PerfettoTracingSession *raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::PerfettoTracingSession>(raw);
}
::PerfettoTracingSession const *cxxbridge1$unique_ptr$PerfettoTracingSession$get(::std::unique_ptr<::PerfettoTracingSession> const &ptr) noexcept {
  return ptr.get();
}
::PerfettoTracingSession *cxxbridge1$unique_ptr$PerfettoTracingSession$release(::std::unique_ptr<::PerfettoTracingSession> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$PerfettoTracingSession$drop(::std::unique_ptr<::PerfettoTracingSession> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::PerfettoTracingSession>::value>{}(ptr);
}

::FlushCtx *cxxbridge1$box$FlushCtx$alloc() noexcept;
void cxxbridge1$box$FlushCtx$dealloc(::FlushCtx *) noexcept;
void cxxbridge1$box$FlushCtx$drop(::rust::Box<::FlushCtx> *ptr) noexcept;

::PollTracesCtx *cxxbridge1$box$PollTracesCtx$alloc() noexcept;
void cxxbridge1$box$PollTracesCtx$dealloc(::PollTracesCtx *) noexcept;
void cxxbridge1$box$PollTracesCtx$drop(::rust::Box<::PollTracesCtx> *ptr) noexcept;
} // extern "C"

namespace rust {
inline namespace cxxbridge1 {
template <>
::FlushCtx *Box<::FlushCtx>::allocation::alloc() noexcept {
  return cxxbridge1$box$FlushCtx$alloc();
}
template <>
void Box<::FlushCtx>::allocation::dealloc(::FlushCtx *ptr) noexcept {
  cxxbridge1$box$FlushCtx$dealloc(ptr);
}
template <>
void Box<::FlushCtx>::drop() noexcept {
  cxxbridge1$box$FlushCtx$drop(this);
}
template <>
::PollTracesCtx *Box<::PollTracesCtx>::allocation::alloc() noexcept {
  return cxxbridge1$box$PollTracesCtx$alloc();
}
template <>
void Box<::PollTracesCtx>::allocation::dealloc(::PollTracesCtx *ptr) noexcept {
  cxxbridge1$box$PollTracesCtx$dealloc(ptr);
}
template <>
void Box<::PollTracesCtx>::drop() noexcept {
  cxxbridge1$box$PollTracesCtx$drop(this);
}
} // namespace cxxbridge1
} // namespace rust
