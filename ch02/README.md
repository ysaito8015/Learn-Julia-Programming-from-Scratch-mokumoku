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
|Expression|      Name                     | Description                            |
|----------|-------------------------------|----------------------------------------|
|+x        | unary plus                    | the identity operation                 |
|-x        | unary minus                   | maps values to their additive inverses |
|x + y     | binary plus                   | performs addition                      |
|x - y     | binary minus                  | performs subtraction                   |
|x * y     | times                         | performs multiplication                |
|x / y     | divide                        | performs division                      |
|x ÷ y    | integer divide                | x / y, truncated to an integer         |
|x \ y     | inverse divide                | equivalent to y / x                    |
|x ^ y     | power                         | raises x to the yth power              |
|x % y     | remainder                     | equivalent to rem(x,y)                 |
|!x        | negation                      |                                        |
|x && y    | short-circuiting and          |                                        |
|x || y    | short-circuiting or           |                                        |
|~x        | bitwise not                   |                                        |
|x & y     | bitwise and                   |                                        |
|x | y     | bitwise or                    |                                        |
|x ⊻ y     | bitwise xor (exclusive or)    |                                        |
|x >>> y   | logical shift right           |                                        |
|x >> y    | arithmetic shift right        |                                        |
|x << y    | logical/arithmetic shift left |                                        |
|==        | equality                      |                                        |
|!=, ≠    | inequality                    |                                        |
|<         | less than                     |                                        |
|<=, ≤    | less than or equal to         |                                        |
|>         | greater than                  |                                        |
|>=, ≥    | greater than or equal to      |                                        |

### 2.1.6 更新演算子
- `+=, -=, *=, /=, \=, ÷=, %=` など

```
julia> x = 1;

julia> x += 1
2
```

### 複素数
- `im` が虚数単位


```
julia> 1 + 2im
1 + 2im

julia> (1 + 2im) * (2 - 3im)
8 + 1im

julia> real(1 + 2im)
1

julia> imag(1 + 2im)
2

julia> conj(1 + 2im)
1 - 2im

julia> abs(1 + 2im)
2.23606797749979
```


### 2.1.8 文字列
- `String` 型
    - Unicode 文字列
    - UTF-8
- `string[idx]` で１始まり
    - `string[x以上:y以下]` という閉区間指定

```
julia> s = "Hello Julia"
"Hello Julia"

julia> s[1]
'H': ASCII/Unicode U+0048 (category Lu: Letter, uppercase)

julia> typeof(s[1])
Char

julia> s[end]
'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

julia> s[1:5]
"Hello"
```

#### 文字列の連結など

```
julia> h = "Hello";

julia> j = "Julia";

julia> string(h, " ", j)
"Hello Julia"

julia> h * " " * j
"Hello Julia"

julia> "$h #j"
"Hello #j"

julia> "$h $j"
"Hello Julia"
```

#### クォート
- ダブルクォートは `String` 型, 式展開可能
- バッククォートは `Cmd` 型, 式展開可能
- シングルクォートはエラー
- 生の文字列リテラルはどう出すのか

```
julia> "1 + 2 = $(1 + 2)"
"1 + 2 = 3"

julia> `1 + 2 = $(1 + 2)`
`1 + 2 = 3`

julia> '1 + 2 = $(1 + 2)'
ERROR: syntax: character literal contains multiple characters
Stacktrace:
 [1] top-level scope
   @ none:1

julia> typeof(`1 + 2 = $(1 + 2)`)
Cmd

julia> typeof("1 + 2 = $(1 + 2)")
String

julia> typeof('1 + 2 = $(1 + 2)')
ERROR: syntax: character literal contains multiple characters
Stacktrace:
 [1] top-level scope
   @ none:1

```

### 2.1.9 Unicode 文字列
- マルチバイト文字も操作できる
    - UTF-8 のような, 可変多バイト文字の扱いに注意
    - `nextiind()` 関数で次の文字のインデックスを取得できる
- 文字列などのインデックス指定に `end` キーワードが使える
    - `end-1` は, 1 byte 前を参照

```
julia> s = "こんにちは, Julia";

julia> s[1]
'こ': Unicode U+3053 (category Lo: Letter, other)

julia> s[2]
ERROR: StringIndexError: invalid index [2], valid nearby indices [1]=>'こ', [4]=>'ん'
Stacktrace:
 [1] string_index_err(s::String, i::Int32)
   @ Base ./strings/string.jl:12
 [2] getindex_continued(s::String, i::Int32, u::UInt32)
   @ Base ./strings/string.jl:233
 [3] getindex(s::String, i::Int32)
   @ Base ./strings/string.jl:226
 [4] top-level scope
   @ REPL[35]:1

julia> s[4]
'ん': Unicode U+3093 (category Lo: Letter, other)

julia> nextind(s, 1)
4

julia> nextind(s, 4)
7

# docs.julialang.org/en/v1/manual/strings
julia> str[1:4]
"こん"

julia> str[end]
'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

julia> str[end-1]
'i': ASCII/Unicode U+0069 (category Ll: Letter, lowercase)

julia> str[end-2]
'l': ASCII/Unicode U+006C (category Ll: Letter, lowercase)

julia> str[end-3]
'u': ASCII/Unicode U+0075 (category Ll: Letter, lowercase)

julia> str[end-4]
'J': ASCII/Unicode U+004A (category Lu: Letter, uppercase)

```

#### 文字列を文字の配列に変換する

```
julia> chars = Vector{Char}(s)
12-element Vector{Char}:
 'こ': Unicode U+3053 (category Lo: Letter, other)
 'ん': Unicode U+3093 (category Lo: Letter, other)
 'に': Unicode U+306B (category Lo: Letter, other)
 'ち': Unicode U+3061 (category Lo: Letter, other)
 'は': Unicode U+306F (category Lo: Letter, other)
 ',': ASCII/Unicode U+002C (category Po: Punctuation, other)
 ' ': ASCII/Unicode U+0020 (category Zs: Separator, space)
 'J': ASCII/Unicode U+004A (category Lu: Letter, uppercase)
 'u': ASCII/Unicode U+0075 (category Ll: Letter, lowercase)
 'l': ASCII/Unicode U+006C (category Ll: Letter, lowercase)
 'i': ASCII/Unicode U+0069 (category Ll: Letter, lowercase)
 'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

```

#### Characters
- `Char` 型は
    - 32 bit 長のプリミティブ型
    - `'x'` など, いち文字
- Unicode コードポイントへ変換可能
- Go の rune 型に近いイメージ？

```
# 'x' の Unicode コードポイント
julia> c = 'x'
'x': ASCII/Unicode U+0078 (category Ll: Letter, lowercase)

julia> typeof(c)
Char

# int 型への変換
julia> c = Int('x')
120

julia> typeof(c)
Int64

julia> Char(120)
'x': ASCII/Unicode U+0078 (category Ll: Letter, lowercase)
```

### 2.1.10 文字列の関数
- 文字列を捜査する標準の関数


```
# 文字列の長さ
julia> length("Julia")
5

# 文字列の繰り返し
julia> repeat("Julia", 2)
"JuliaJulia"

# 文字列の置き換え
julia> replace("Python is the best!", "Python" => "Julia")
"Julia is the best!"

# 指定の文字で, 文字列を区切る
# CSV など？
julia> split("Julia-Lang", "-")
2-element Vector{SubString{String}}:
 "Julia"
 "Lang"

 # 指定の文字で, 開始されているか
julia> startswith("JuliaLang", "Julia")
true

# 指定の文字で, 終わっているか
julia> endswith("JuliaLang", "Lang")
true

## 指定の文字で, 文字列を連結する
julia> join(["Julia", "Lang"], "-")
"Julia-Lang"

# 文字列の検索
# findfirst は見つかった場合, 文字インデックスを返す
# 見つからなかった場合は, nothing を返す
julia> findfirst("Julia", "JuliaLang")
1:5

```


### 2.1.11 正規表現
