template<int... x>
void func() {
  static_assert(x < 5, @string(x, " is out of range"))...;
}

int main() {
  func<1, 2, 3, 7, 3>();
}