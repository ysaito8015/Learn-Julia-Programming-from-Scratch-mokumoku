# 2 Julia の言語機能
## 2.1 Julia の基本
### 2.1.1 変数
- 宣言と代入
    - `x = 1`
- 変数の直前の数字がかけられる
    - `2x + 1 # 3`
- 変数名にユニコードが使える
    - `θ = pi /4 # 0.7853981633974483`
    - `sin(θ ) # 0.7071067811865475`

### 2.1.2 プリミティブ型
#### 型の調べ方
- `typeof(1) # Int32`

#### プリミティブ型
- Int{8,16,32,64,128}
- UInt{8,16,32,64,128}
- Bool
- Float{16,32,64}
- Int, UInt -> システムのディフォルトのビット長のエイリアス
    - `Sys.WORD_SIZE # 32`
    - `Int # Int32`

```
julia> for T in [Int8,Int16,Int32,Int64,Int128,UInt8,UInt16,UInt32,UInt64,UInt128]
           println("$(lpad(T,7)): [$(typemin(T)),$(typemax(T))]")
       end
   Int8: [-128,127]
  Int16: [-32768,32767]
  Int32: [-2147483648,2147483647]
  Int64: [-9223372036854775808,9223372036854775807]
 Int128: [-170141183460469231731687303715884105728,170141183460469231731687303715884105727]
  UInt8: [0,255]
 UInt16: [0,65535]
 UInt32: [0,4294967295]
 UInt64: [0,18446744073709551615]
UInt128: [0,340282366920938463463374607431768211455]
```

#### 16進数表現
- `0x1 # 0x01`
- `typeof(0x01) # 1, b000 0001 UInt8`
- `typeof(0x123) # 291, b000 0001 0010 0011 UInt16`
- `typeof(0x1234567) # 19088743, b0000 0001 0010 0011 0100 0101 0110 0111 UInt32`
- `typeof(0x123456789abcdef) # UInt64`

#### 浮動小数点
- `typeof(1.0) # Float64`
- Float32 型を指定するときは, `0.5f0` のようにサフィックスをつける
    - `typeof(0.5f0) # Float32`
- 予約語
    - 無限: Inf{16, 32, 64}
    - -無限: -Inf{16, 32, 64}
    - Nan系: NaN{16, 32, 64}

### 2.1.3 任意制度演算
- `BigInt` 型
- `BigFloat` 型

```
# 書籍の例のように BigInt 型にならないですね...
julia> x = 123567890123456789012345678901234567890
123567890123456789012345678901234567890

julia> x * x
16709914794736288363445475719704024132

julia> typeof(ans)
Int128
```

```
# https://doc.julialang.org から
julia> x = typemax(UInt128)
0xffffffffffffffffffffffffffffffff

julia> big(x)
340282366920938463463374607431768211455

julia> typeof(x)
UInt128

julia> typeof(big(x))
BigInt
```

- "BigInts can also be input as integer literals when they are too big for other built-in integer types. Note that as there is
no unsigned arbitrary-precision integer type in Base (BigInt is sufficient in most cases), hexadecimal, octal and binary literals can be used (in
addition to decimal literals)."

### 2.1.4 定数の宣言

```
julia> const y = 1.0
1.0

julia> y = 1
ERROR: invalid redefinition of constant y
```

#### 最初から定義済みの定数
```
julia> pi
π  = 3.1415926535897...

julia> VERSION
v"1.6.2"
```

```
# 定義されている定数を未使用前であれば好きに定義できる
julia> pi = 3
3

# However, if you try to redefine a built-in constant or function already in use, Julia will give you an error:

julia> pi
π = 3.1415926535897...

julia> pi = 3
ERROR: cannot assign a value to variable MathConstants.pi from module Main

julia> sqrt(100)
10.0

julia> sqrt = 4
ERROR: cannot assign a value to variable Base.sqrt from module Main
```

### 2.1.5 基本的な演算子
Expression      Name                    Description
+x         unary plus     the identity operation
-x         unary minus    maps values to their additive inverses
x + y      binary plus    performs addition
x - y      binary minus   performs subtraction
x * y      times          performs multiplication
x / y      divide         performs division
x ÷ y     integer divide x / y, truncated to an integer
x \ y      inverse divide equivalent to y / x
x ^ y      power          raises x to the yth power
x % y      remainder      equivalent to rem(x,y)
!x         negation
x && y     short-circuiting and
x || y     short-circuiting or
~x         bitwise not
x & y      bitwise and
x | y      bitwise or
x ⊻ y      bitwise xor (exclusive or)
x >>> y    logical shift right
x >> y     arithmetic shift right
x << y     logical/arithmetic shift left
==       equality
!=, ≠    inequality
<        less than
<=, ≤    less than or equal to
>        greater than
>=, ≥    greater than or equal to

