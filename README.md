## Нагрузочные тесты

| Указатель | Создание, мс | Чтение, мс | Удаление, мс |
|---|---|---|---|
| `Raw`       | 18.488 | 0.797 | 14.523 |
| `UniquePtr` | 18.405 | 0.568 | 14.722 |
| `SharedPtr` | 38.12  | 1.998 | 29.934 |

## Санитайзеры 

```
[==========] Running 12 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from UniquePtrTest
[ RUN      ] UniquePtrTest.Constructor
[       OK ] UniquePtrTest.Constructor (0 ms)
[ RUN      ] UniquePtrTest.MoveTransfer
[       OK ] UniquePtrTest.MoveTransfer (0 ms)
[ RUN      ] UniquePtrTest.ArrayIndexAccess
[       OK ] UniquePtrTest.ArrayIndexAccess (0 ms)
[----------] 3 tests from UniquePtrTest (0 ms total)

[----------] 3 tests from SharedPtrTest
[ RUN      ] SharedPtrTest.Constructor
[       OK ] SharedPtrTest.Constructor (0 ms)
[ RUN      ] SharedPtrTest.UseCount
[       OK ] SharedPtrTest.UseCount (0 ms)
[ RUN      ] SharedPtrTest.Move
[       OK ] SharedPtrTest.Move (0 ms)
[----------] 3 tests from SharedPtrTest (0 ms total)

[----------] 6 tests from DynamicArrayTest
[ RUN      ] DynamicArrayTest.ConstructorSize
[       OK ] DynamicArrayTest.ConstructorSize (0 ms)
[ RUN      ] DynamicArrayTest.IndexOperator
[       OK ] DynamicArrayTest.IndexOperator (0 ms)
[ RUN      ] DynamicArrayTest.DeepCopy
[       OK ] DynamicArrayTest.DeepCopy (0 ms)
[ RUN      ] DynamicArrayTest.Move
[       OK ] DynamicArrayTest.Move (0 ms)
[ RUN      ] DynamicArrayTest.Resize
[       OK ] DynamicArrayTest.Resize (0 ms)
[ RUN      ] DynamicArrayTest.OutOfRangeThrows
[       OK ] DynamicArrayTest.OutOfRangeThrows (0 ms)
[----------] 6 tests from DynamicArrayTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 12 tests.
```