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
|x \|\| y    | short-circuiting or           |                                        |
|~x        | bitwise not                   |                                        |
|x & y     | bitwise and                   |                                        |
|x \| y     | bitwise or                    |                                        |
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
- Julia では, PCRE (Perl Compatible Regular Expressions) という正規表現ライブラリを使える
- 文字列の前に `r` をつけることで, 正規表現を示す
    - `r"正規表現"`
- `math(正規表現型オブジェクト, "文字列")` 関数で, マッチさせる
- マッチした結果は, `RegexMatch` 型のオブジェクトが返り, 情報を持つ


```
julia> re = r"^\s*(?:#|$)"
r"^\s*(?:#|$)"

julia> typeof(re)
Regex

julia> occursin(r"^\s*(?:#|$)", "not a comment")
false

julia> occursin(r"^\s*(?:#|$)", "# a comment")
true

julia> regex = r"J.*g"
r"J.*g"

julia> typeof(regex)
Regex

julia> m = match(regex, "JuliaLang is the best.")
RegexMatch("JuliaLang")

julia> typeof(m)
RegexMatch

julia> n = match(regex, "JuliaLan is the best.")

julia> typeof(n)
Nothing

julia> m.match
"JuliaLang"

julia> m.offset
1

```


## 2.2 制御構文
### 2.2.1 条件評価
- `if, elseif, else, end` を用いて条件分岐させる


```
julia> x = 3; y = 2;

julia> if x < y
           println("x is less than y")
       elseif x > y
           println("x is greater than y")
       else
           println("x is equal to y")
       end
x is greater than y

```

- 三項演算子
    - 演算子の前にスペース必要


```
julia> x = 100;

julia> x > 100? true : false
ERROR: syntax: space required before "?" operator
Stacktrace:
 [1] top-level scope
   @ none:1

julia> x > 100 ? true : false
false
```

### 2.2.2 短絡評価
- `&&` や, `||` という演算子を用いた条件評価
    - if 文の代わりに使える
- `a && b` 
    - a ならば b という条件式
    - a と b どちらも `true` の場合のみ `true` を返す
    - a が `false` だった場合, b は評価されない
- `a || b`
    - a と b がどちらも `false` の場合のみ `false` を返す


```
# 整数 n が 0 以上のとき, エラーを返す
# a の式 n >= 0 が true のときのみ, b の式評価へ進む
julia> n = 1; n >= 0 && error("n must be negative.")
ERROR: n must be negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] top-level scope
   @ REPL[45]:1

# 整数 n が 0 より小さいときにエラーを返す
# a の式, n >= 0 が false のときのみ, b の式評価へ進む
julia> n = 1; n >= 0 && error("n must be non-negative.")
ERROR: n must be non-negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] top-level scope
   @ REPL[47]:1
```

#### && の評価

```
julia> true && true
true

julia> true && false
false

julia> false && true
false

julia> false && false
false

# 式評価
julia> returnTrue(x) = (println(x);  true)
returnTrue (generic function with 1 method)

julia> returnFalse(x) = (println(x); false)
returnFalse (generic function with 1 method)

julia> returnTrue(1) && returnTrue(2)
1
2
true

julia> returnTrue(1) && returnFalse(2)
1
2
false

# 最初の評価が false であれば, 最初の評価で止まる
julia> returnFalse(1) && returnTrue(2)
1
false

julia> returnFalse(1) && returnFalse(2)
1
false

```

#### || の評価

```
# a, b いずれかが true であれば true
julia> true || true
true

julia> true || false
true

julia> false || true
true

julia> false || false
false

# a が true であれば, 最初の式の評価で終わる
julia> returnTrue(1) || returnTrue(2)
1
true

julia> returnTrue(1) || returnFalse(2)
1
true

# a が false であれば b の式評価へ進む
julia> returnFalse(1) || returnTrue(2)
1
2
true

julia> returnFalse(1) || returnFalse(2)
1
2
false
```


#### 再帰的な階乗計算, Recursive Factorial Routine

```
julia> function factorial(n::Int)
           # n が 0 以上でないときのみ, 右の式評価へ進む
           n >= 0 || error("n must be non-negative.")
           # n が 0 であるときのみ, 右の式評価へ進む
           n == 0 && return 1
           n * factorial(n-1)
           end
factorial (generic function with 1 method)

julia> factorial(5)
120

julia> factorial(0)
1

julia> factorial(-1)
ERROR: n must be non-negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] factorial(n::Int64)
   @ Main ./REPL[82]:2
 [3] top-level scope
   @ REPL[85]:1

```

#### 短絡評価 を使わない場合の Boolean 演算子
- boolean のビット演算で行われる
- `|`, `&` は両辺が必ず評価される


```
# & 演算子 -> bitwiase and
julia> returnTrue(1) & returnTrue(2)
1
2
true

julia> returnTrue(1) & returnFalse(2)
1
2
false

julia> returnFalse(1) & returnTrue(2)
1
2
false

julia> returnFalse(1) & returnFalse(2)
1
2
false

# | 演算子 -> bitwise or
julia> returnTrue(1) | returnTrue(2)
1
2
true

julia> returnTrue(1) | returnFalse(2)
1
2
true

julia> returnFalse(1) | returnTrue(2)
1
2
true

julia> returnFalse(1) | returnFalse(2)
1
2
false

```


#### non-boolean 値と, 短絡評価
- boolean 値以外を最後の評価式以外に置くとエラーになる


```
julia> false || 1 && false
ERROR: TypeError: non-boolean (Int64) used in boolean context
Stacktrace:
 [1] top-level scope
   @ REPL[101]:1

julia> false || false && 1
false
```

- 最後の式評価では, いかなる式評価でも置くことができる


```
julia> true && (x = (1, 2, 3))
(1, 2, 3)

julia> false && (x = (1, 2, 3))
false

```


### 2.2.3 ループ, Rpeated Evaluation: Loops

#### while 文
- `while ... end` のブロック区内の処理を繰り返し実行できる


```
# グローバル変数として宣言
julia> i = 1
1

julia> while i <= 5
           print(i)
           # グローバル変数の変更
           # global 修飾子をつける
           global i += 1
       end
12345
```


#### for 文

```
# 1:5 は Range 型のオブジェクト
# 1 2 3 4 5 を順番に渡す
julia> typeof(1:5)
UnitRange{Int64}

julia> for i = 1:5
           print(i)
       end
12345

# 配列を使った for 文
julia> for i in [1,4,0]
           print(i)
       end
140
```


#### break, continue


```
julia> for j = 1:1000
           println(j)
           # j が 5 以上ならルーブ終了
           if j >= 5
               break
           end
       end
1
2
3
4
5

# continue
julia> for i = 1:10
           # i を 3 でわってあまりが 0 以外はスキップする
           if i % 3 != 0
               continue
           end
           println(i)
       end
3
6
9
```


#### ネストされたループを簡略化できる


```
julia> for i = 1:2
           for j = 3:4
               println((i, j))
           end
       end
(1, 3)
(1, 4)
(2, 3)
(2, 4)

julia> for i = 1:2, j = 3:4
           println((i, j))
       end
(1, 3)
(1, 4)
(2, 3)
(2, 4)

```

### 2.2.4 rty/catch/finally
- 例外処理
    - テストしたいコードを `tyr` ブロックに書く
    - 例外が発生したときにに実行される処理を `catch` ブロックに書く
    - `catch` の処理が終わった後で `finally` ブロックが実行される


```
julia> str = "Julia"
"Julia"

julia> try
           i = parse(Int, str)
           println(i)
       catch
           # ...
       end

julia> println(parse(Int, str))
ERROR: ArgumentError: invalid base 10 digit 'J' in "Julia"
Stacktrace:
 [1] tryparse_internal(#unused#::Type{Int64}, s::String, startpos::Int64, endpos::Int64, base_::Int64, raise::Bool)
   @ Base ./parse.jl:137
 [2] parse(::Type{Int64}, s::String; base::Nothing)
   @ Base ./parse.jl:241
 [3] parse(::Type{Int64}, s::String)
   @ Base ./parse.jl:241
 [4] top-level scope
   @ REPL[123]:1

```


#### ファイルの入出力

```
julia> f = open("nofile")
ERROR: SystemError: opening file "nofile": No such file or directory
Stacktrace:
 [1] systemerror(p::String, errno::Int32; extrainfo::Nothing)
   @ Base ./error.jl:168
 [2] #systemerror#62
   @ ./error.jl:167 [inlined]
 [3] systemerror
   @ ./error.jl:167 [inlined]
 [4] open(fname::String; lock::Bool, read::Nothing, write::Nothing, create::Nothing, truncate::Nothing, append::Nothing)
   @ Base ./iostream.jl:293
 [5] open(fname::String)
   @ Base ./iostream.jl:282
 [6] top-level scope
   @ REPL[124]:1

julia> try
           operate(f)
       finally
           close(f)
       end
ERROR: MethodError: no method matching close(::typeof(f))
Closest candidates are:
  close(::Union{Base.AsyncCondition, Timer}) at asyncevent.jl:136
  close(::Union{FileWatching.FileMonitor, FileWatching.FolderMonitor, FileWatching.PollingFileWatcher}) at /buildworker/worker/package_linux64/build/usr/share/julia/s
tdlib/v1.6/FileWatching/src/FileWatching.jl:304
  close(::Base.GenericIOBuffer{T}) where T at iobuffer.jl:337
  ...
Stacktrace:
 [1] top-level scope
   @ REPL[125]:4

caused by: UndefVarError: operate not defined
Stacktrace:
 [1] top-level scope
   @ REPL[125]:2

```

#### sqrt 関数を例外で場合分けする


```
julia> sqrt_second(x) = try
                  # x の２番めの要素の平方根を取る
                  sqrt(x[2])
              catch y
                  # y が DomainError であった場合
                  # DomainError, 適切なドメインの外の要素を引数にした場合
                  if isa(y, DomainError)
                      # 複素数として平方根を取る
                      sqrt(complex(x[2], 0))
                  # y が BoundsError であった場合
                  # BoundsError, 配列の長さ以外の要素にアクセスした場合
                  elseif isa(y, BoundsError)
                      sqrt(x)
                  end
              end
sqrt_second (generic function with 1 method)

julia> sqrt_second([1 4])
# 4 の平方根
2.0

julia> sqrt_second([1 -4])
# -4 の平方根
0.0 + 2.0im

julia> sqrt_second(9)
# 9 の平方根
3.0

julia> sqrt_second(-9)
ERROR: DomainError with -9.0:
sqrt will only return a complex result if called with a complex argument. Try sqrt(Complex(x)).
Stacktrace:
 [1] throw_complex_domainerror(f::Symbol, x::Float64)
   @ Base.Math ./math.jl:33
 [2] sqrt
   @ ./math.jl:582 [inlined]
 [3] sqrt
   @ ./math.jl:608 [inlined]
 [4] sqrt_second(x::Int64)
   @ Main ./REPL[137]:7
 [5] top-level scope
   @ REPL[141]:1

caused by: BoundsError
Stacktrace:
 [1] getindex
   @ ./number.jl:96 [inlined]
 [2] sqrt_second(x::Int64)
   @ Main ./REPL[137]:2
 [3] top-level scope
   @ REPL[141]:1

```


#### 独自の例外を定義する
- 構造体で宣言する

```
julia> struct MyCustomException <: Exception end

julia> struct MyUndefVarError <: Exception
           var::Symbol
       end

julia> Base.showerror(io::IO, e::MyUndefVarError) = println(io, e.var, " not defined")

```

#### 明示的なエラー文を加える
- 組み込みの例外に説明を加える
- `throw(組み込みの例外(x, "加える説明文"))` 


```
julia> f(x) = x>=0 ? exp(-x) : throw(DomainError(x, "argument must be non-negative"))
f (generic function with 1 method)

julia> f(1)
0.36787944117144233

julia> f(-1)
ERROR: DomainError with -1:
argument must be non-negative
Stacktrace:
 [1] f(x::Int64)
   @ Main ./REPL[132]:1
 [2] top-level scope
   @ REPL[134]:1

```


## 2.3 関数
- 関数とは, 引数を入力として受け取って, 何らかの結果を返すオブジェクト
- a function is an object that maps a tuple of argument values to a return value
- 最後に評価された値が自動的に戻り値となる
- pass-by-sharingと呼ばれる慣習に従ってます。
- 引数として関数に渡されるときにはその値をコピーしません。
- 引数は新しい変数として振る舞いますが、渡された値と同一のものが参照されます。
- 配列のようなミュータブルな値の変更は、呼び出し元に反映されます。

```
# function end で宣言
julia> function add(x, y)
           return x + y
       end
add (generic function with 1 method)

# 直接宣言 assignment form
julia> f(x, y) = x + y
f (generic function with 2 methods)

julia> add(2,3)
5

julia> f(2,3)
5

```

#### 引数や戻り値に型を指定
- 型はすべての引数に付与してもよいし, 一部の引数だけでも良い


```
julia> add_typed(x::Int, y::Int) = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> add_typed(x::Int8, y::Int8) = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> add_typed(x::Int8, y::Int8)::Int8 = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> function add_typed(x::Int8, y::Int8)::Int8
                  return x * y
              end;

julia> typeof(g(1,2))
Int8

```

#### 関数の戻り値を複数にする

```
julia> function sum_diff(x, y)
           x+y, x*y
       end;

julia> function sum_diff(x, y)
           x+y, x-y
       end;

julia> typeof(sum_diff(3, 4))
Tuple{Int64, Int64}

```

#### Tuple 型
- 組み込みのデータ構造
- 複数の値をまとめた型
    - 固定長のコンテナ
    - immutable であり変更できない
- `()` は空のタプル

```
julia> typeof((1, 1+1))
Tuple{Int64, Int64}

julia> typeof((1,))
Tuple{Int64}

julia> typeof((0.0, "hello", 6*7))
Tuple{Float64, String, Int64}

julia> x = (0.0, "hello", 6*7)
(0.0, "hello", 42)

julia> x[2]
"hello"

julia> typeof(())
Tuple{}

```


#### 名前付き Tuple 型
- Tuple の要素に名前をつけることができる


```
julia> x = (a=2, b=1+2)
(a = 2, b = 3)

julia> x[1]
2

julia> x.a
2

```


### 2.3.1 可変長引数, Varargs Functions
- `x...` のようにドットを３つつなげることで可変長であることを意味する
    - 引数の定義の最後の要素のみに使える
        - つまり, `bar(x..., y)` という定義はエラー
- 複数の引数をそれぞれ可変長にすることもできない
- 可変長引数に型注釈を与える
    - `g(x, y::Int...)`

```
julia> function f(x...)
           sum = 0
           println(length(x))
           # 引数の長さまでの range オブジェクト
           for i = 1:length(x)
               # 引数の Tuple にインデックスでアクセス
               sum += x[i]
           end
           sum
       end;

julia> f(3)
# 書籍の出力では 3
0.049787068367863944
# 同じセッションで, 同名の f(x) を定義していた
# julia> f(x) = x>=0 ? exp(-x) : throw(DomainError(x, "argument must be non-negative"))↲

julia> f(3)
1
3

julia> f(3,4)
7
```


#### 可変長引数と, Tuple

```
julia> bar(a, b, x...) = (a,b,x)
bar (generic function with 1 method)

# (1,2, (空のタプル))
julia> bar(1,2)
(1, 2, ())

# 3番目以降の引数は全て一つのタプルにまとめられる
julia> bar(1,2,3)
(1, 2, (3,))

julia> bar(1,2,3,4)
(1, 2, (3, 4))

julia> bar(1,2,3,4,5,7)
(1, 2, (3, 4, 5, 7))

# タプルを変数に格納
julia> x = (3,4)
(3, 4)

# タプルを格納した変数を ... を使わずに渡す
julia> bar(1,2,x)
(1, 2, ((3, 4),))

# 変数... で渡す
julia> bar(1,2,x...)
(1, 2, (3, 4))

# 要素を４つ持つタプル
julia> x = (1,2,3,4)
(1, 2, 3, 4)

julia> bar(1,2,x)
(1, 2, ((1, 2, 3, 4),))

julia> bar(x)
ERROR: MethodError: no method matching bar(::NTuple{4, Int64})
Closest candidates are:
  bar(::Any, ::Any, ::Any...) at REPL[179]:1
Stacktrace:
 [1] top-level scope
   @ REPL[189]:1

# 関数の引数で定義した, 第１, 第２引数をタプルから取り込み, 残りの要素を 可変長引数に格納する
julia> bar(x...)
(1, 2, (3, 4))

```


#### iterable オブジェクト
- いくつかの引数と可変長引数を持つ関数に, iterable オブジェクトを渡すとき 
    - 自動的にオブジェクトの先頭の要素から関数の各引数に割り当てられる


```
julia> x = [3,4]
2-element Vector{Int64}:
 3
 4

julia> bar(1,2,x...)
(1, 2, (3, 4))

julia> bar(1,2,x)
(1, 2, ([3, 4],))

julia> x = [1,2,3,4]
4-element Vector{Int64}:
 1
 2
 3
 4

julia> bar(x...)
(1, 2, (3, 4))

julia> bar(x)
ERROR: MethodError: no method matching bar(::Vector{Int64})
Closest candidates are:
  bar(::Any, ::Any, ::Any...) at REPL[179]:1
Stacktrace:
 [1] top-level scope
   @ REPL[196]:1

```


#### 可変長引数の例 rand 関数
- doc
    - https://docs.julialang.org/en/v1/stdlib/Random/#Random-generation-functions
- 書式
    - `rand([rng=GLOBAL_RNG], [S], [dims...])`
        - `rng`
            - Random Number Generator
            - 乱数生成器を指定するオプション
            - `MersenneTwister` ライブラリを通して, `MersenneTwister` オブジェクトを乱数生成に使用する
            - ほかの RNG 型は, `AbstractRNG` を継承することで追加できる
                - `RandomDevide` という RNG 型
                    - OS が提供するエントロピープール
        - `S` が示す集合からランダムな要素を取って返す
        - `S` は
            - インデックス可能なオブジェクト
            - `AbstractDict` もしくは, `AbstractSet` オブジェクト
            - 文字列
            - 型, デフォルトは `Float64` 型
                - `[0, 1)`
- `GLOBAL_RNG`
    - https://github.com/JuliaLang/julia/search?q=GLOBAL_RNG
- `Base.GLOBAL_RNG`
    - deprecated
    - https://discourse.julialang.org/t/warning-base-global-rng-is-deprecated-it-has-been-moved-to-the-standard-library-package-random/19852/2

```
# rand([dims...]) の部分の可変長引数へ渡している
julia> rand(4)
4-element Vector{Float64}:
 0.8820544785627955
 0.5393306064191477
 0.5967269773734716
 0.14746272547042816

julia> rand(4, 3)
4×3 Matrix{Float64}:
 0.651322  0.476229  0.325794
 0.27001   0.400553  0.462608
 0.707405  0.463902  0.480943
 0.97128   0.466762  0.880856

julia> rand(4, 3, 2)
4×3×2 Array{Float64, 3}:
[:, :, 1] =
 0.729712   0.968799    0.588303
 0.695648   0.571302    0.86166
 0.0757485  0.00648672  0.627555
 0.76275    0.0663761   0.316861

[:, :, 2] =
 0.964524   0.383842  0.346668
 0.0692856  0.602752  0.275058
 0.684716   0.830487  0.975866
 0.157475   0.515344  0.374874

```

### 2.3.2 オプショナル引数
- 引数にデフォルト値を設定できる

#### Date 関数の例

```
function Date(y::Int64, m::Int64=1, d::Int64=1)
    err = validargs(Date, y, m, d)
    err === nothing || throw(err)
    return Date(UTD(totaldays(y, m, d)))
end
```


```
julia> f(x, y=1) = x + y;

julia> f(3)
4

julia> f(3,4)
7

julia> using Dates

julia> Date(2000, 12, 12)
2000-12-12

julia> Date(2000)
2000-01-01
```

#### オプショナル引数の設定位置
- 末尾の引数のみ


```
julia> f(x, y=1, z=1) = x + y +z;

julia> f(x=3, y, z) = x + y + z;
ERROR: syntax: optional positional arguments must occur at end around REPL[231]:1
Stacktrace:
 [1] top-level scope
   @ REPL[231]:1
```


### 2.3.3 キーワード引数
- `function f(;引数名::型指定=デフォルト値) end`
    - `;` の後に書く
- 名前を指定して呼び出せる引数
- オプショナル引数が多いときは, キーワード引数を用いるほうが可読性が高い


```
function plot(x, y; style="solid", width=1, color="black")
    ###
end

julia> plot(1.3, 5.2, color="red")

# 型を指定して, オプショナル引数を設定
function f(;x::Int=1)
    ###
end
```


### 2.3.4 匿名関数 Anonymous Functions
- 関数名をつけずに値や, 関数の組を割り当てる
- `x -> begin end` 構文

```
julia> square = x -> begin
           x * x
       end;

julia> square = x -> x * x;

julia> square(3)
9
```


#### 一時的な関数を作成


```
julia> array = [1, 2, 3, 4, 5]
5-element Vector{Int64}:
 1
 2
 3
 4
 5

# array の各要素に対する操作
julia> map(x -> x * x, array)
5-element Vector{Int64}:
  1
  4
  9
 16
 25

julia> map(x -> x % 2 == 1, array)
5-element Vector{Bool}:
 1
 0
 1
 0
 1

julia> filter(x -> x % 2 == 1, array)
3-element Vector{Int64}:
 1
 3
 5

```


## 2.4 型
- 動的型付けであるが, 型注釈をコードに付与できる
- 多重ディスパッチによって動的にメソッド呼び出しが行われる


#### 多重ディスパッチ
- 同一の名前で引数の数や方が異なる関数を行くか定義しておき, 実行時に型に応じた適切な関数が実行される仕組み
    - C++ のオーバーロードと似ている
- 多重ディスパッチは動的に引数の型に応じた関数が呼び出される
- 単一ディスパッチは1つの型を元にメソッドを選ぶということ、多重ディスパッチはそれが複数の型に基いて選ぶということ
    - https://qiita.com/dbym4820/items/dc640bbbf4303c1a4f26#%E5%A4%9A%E9%87%8D%E3%83%87%E3%82%A3%E3%82%B9%E3%83%91%E3%83%83%E3%83%81
- 多重ディスパッチ: 動的な型情報に基づいて, 実際に呼び出すメソッドを切り変える
    - C++ の場合: https://ufcpp.net/study/csharp/sp4_multipledispatch.html
- How Julia Perfected Multiple Dispatch
    - https://towardsdatascience.com/how-julia-perfected-multiple-dispatch-16675db772c2


#### 注意点
- オブジェクト指向プログラミング言語とは異なる
    - オブジェクトに関数を所属させることはできない
    - 型の継承はできない


#### 型注釈
- 基本的に動的型付け
- 必要に応じて, 型の注釈をつけることができる
- JIT コンパイル時に, コードが最適化されて実行速度を改善する場合がある
- 多重ディスパッチが利用できる
- 利用シーン
    - コードの可読性を向上させたい場合
    - 意図的なコードの最適化を行う場合
    - 多重ディスパッチを用いる場合


#### 実行時コンパイル
- JIT コンパイル
    - LLVM



### 2.4.1 型の宣言
- `::` 演算子を使う
    - e.g., `x::Int`
- 独自の型を定義できる
    - プリミティブ型の宣言
        - `julia/base/boot.jl`
            - https://github.com/JuliaLang/julia/blob/146de38b4004e3fbd4cacc1e502fd650473cb67f/base/boot.jl#L214
        - プリミティブ型は必ず 8 bit 単位で指定する必要がある
- 型の階層構造
    - 親: supertype
        - supertype が指定されなかった場合は, `Any` 型が supertype になる
    - 子: subtype


### 2.4.2 型の階層構造
- 型同士で親子関係を構築し, 全体で型をノードとするグラフを構成する

#### 型の種類
- 具体型
    - concrete type
        - e.g., Int64, Float64 などのプリミティブ型
        - 具体型を親とする方を定義することはできない
        - 型の継承もできない
- 抽象型
    - abstract type
        - プリミティブ型の親やさらにその親となる型
        - インスタンス化してオブジェクトを生成することはできない

#### 型の例
- Abstract Float 型 -> Float{16, 32, 64} など
- Signed 型 -> Int{8, 16, 32, 64}
- Unsigned 型 -> UInt{8, 16, 32, 64}
- ![](https://i.gyazo.com/52422227289b715af5054d3b41fcf5c2.png)


#### 抽象型, abstract type
- 宣言方法
    - `<:` 演算子は親子関係を示す

```
abstract type 型名 end
abstract type 型名 <: 親の型 end
```

##### 親子関係の追跡

```
julia> supertype(Float32)
AbstractFloat

julia> supertype(AbstractFloat)
Real

julia> supertype(Real)
Number

julia> supertype(Number)
Any

julia> subtypes(Real)
# 書籍の表示は, 4-element Array{Any,1}:
4-element Vector{Any}:
 AbstractFloat
 AbstractIrrational
 Integer
 Rational

julia> subtypes(AbstractFloat)
4-element Vector{Any}:
 BigFloat
 Float16
 Float32
 Float64

julia> subtypes(Float32)
# 書籍の表示は 0-element Array{Type,1}
Type[]

```


#### Any 型
- 型グラフの最上位に位置する型
- すべての型は Any 型の子孫
- 関数の引数に型を指定しない場合は, Any 型の引数であると解釈される


### 2.4.3 Nothing 型
- Nothing 型は何もないことを表す
    - nil, null 相等?
- `nothing` という唯一のオブジェクトを持つ


```
julia> x = nothing

julia> typeof(x)
Nothing

julia> isnothing(x)
true
```

#### 関数の戻り値
- 関数の戻り値がないときは, `return nothing` と同等
- e.g., findfirst 関数


```
julia> findfirst("a", "Hello Julia!")
11:11

julia> findfirst("b", "Hello Julia!")

julia> x = findfirst("b", "Hello Julia!")

julia> typeof(x)
Nothing

```


### 2.4.4 複合型, composite types
- 複数の名前付きフィールドをまとめて扱うことのできる型
- Julia では, 関数が複合型に所属するのではなく, 型の宣言とは独立している
    - 関数が常に第一級オブジェクトとして扱われる
        - 第一級オブジェクトとは
            - 関数の引数として渡すことができる
            - 複合データ型に格納できる

```
# 複合型としての構造体
# 具体型になる -> インスタンスが生成できる
# コンストラクタは自動的に生成される
julia> struct Point
           x::Int # 型注釈
           y::Int
       end

# 複合型を引数に取るという指定のみ
julia> function distance(p::Point)
           sqrt(p.x^2 + p.y^2)
       end;

# 構造体のインスタンスの宣言
julia> p = Point(2,3)
Point(2, 3)

julia> distance(p)
3.605551275463989

# 型の調査
julia> typeof(Point)
DataType

julia> supertype(Point)
Any

julia> typeof(DataType)
DataType

julia> supertype(DataType)
Type{T}
```


#### 構造体についてすこし
- フィールドに型注釈をつけることができる
- 構造体宣言時に, コンストラクタは自動的に生成される
    - カスタムしたコンストラクタも定義できる
- フィールドには `構造体名.フィールド名` でアクセスできる
- `struct` キーワードで宣言された構造体は, 変更不可, immutable
    - `struct` で宣言されていても, フィールドの型が, 配列など変更可能なオブジェクトの場合は変更可能
- `mutable struct` キーワードで宣言すると, 変更可能, mutable

```
julia> struct Point
           x::Int
           y::Int
       end

julia> p = Point(2,3)
Point(2, 3)

julia> p.x
2

julia> p.y
3

# y=0 で初期化するコンストラクタ
julia> Point(x) = Point(x, 0);

julia> p = Point(1)
Point(1, 0)

julia> p.x
1

julia> p.x =2
ERROR: setfield! immutable struct of type Point cannot be changed
Stacktrace:
 [1] setproperty!(x::Point, f::Symbol, v::Int64)
   @ Base ./Base.jl:34
 [2] top-level scope
   @ REPL[36]:1

```

##### mutable な構造体

```
julia> mutable struct Point
           x::Int
           y::Int
       end;

julia> p = Point(3, 4)
Point(3, 4)

julia> p.x
3

julia> p.x = 1
1

```


### 2.4.5 Union 型
- 複数の型の和集合を表す型
- `Union{型名, Nothing}` 型
    - 型名で指定した型, もしくは, nothing を表す
    - 値がない状態を許す型

```
# Int または, String を表す型
julia> IntOrString = Union{Int,String}
Union{Int64, String}

julia> union_type(x::IntOrString) = x
union_type (generic function with 1 method)

julia> union_type(1)
1

julia> union_type("Julia")
"Julia"

julia> union_type(1.2)
ERROR: MethodError: no method matching union_type(::Float64)
Closest candidates are:
  union_type(::Union{Int64, String}) at REPL[5]:1
Stacktrace:
 [1] top-level scope
   @ REPL[8]:1

```


### 2.4.6 パラメトリック型
- generics やテンプレートなどの機能と似ている
- 変数に型パラメータを定義できる
- すべての `DataType` 型のインスタンスはパラメータ化できる
- e.g., `Point{T}` -> 型 T をパラメータとする Point 型
    - `Point{T}` はあらゆる型 T のテンプレートとなる

```
julia> mutable struct Point{T}
           x::T # T 型パラメータ
           y::T
       end

# 型パラメータは, `Point{T}` をインスタンス化する際に,
# Int64 や, Float64 などの具体的な型として実行する
julia> p = Point(2,3)
Point{Int64}(2, 3)

# T の型を明示できる
julia> q = Point{Int}(2,3)
Point{Int64}(2, 3)

```


#### パラメトリック型とメソッド
- `where T` を宣言時に付加する

```
julia> mutable struct Point{T}
           x::T # T 型パラメータ
           y::T
       end

# function 行に where T を付加
julia> function distance(p::Point{T}) where T
           println(T) # 型情報の出力
           sqrt(p.x^2 + p.y^2)
       end;

julia> distance(Point(2,3))
Int64
3.605551275463989
```


#### 渡される型によって動作を分ける
- 多重ディスパッチを使う -> 型によってメソッドを分ける


```
julia> function distance(p::Point{Int})
        # Int 型のときの動作
       end
distance (generic function with 2 methods)

julia> function distance(p::Point{Float64})
           # Float64 型のときの動作
       end
distance (generic function with 2 methods)

julia> function distance(p::Point)
           # それ以外のときの操作
           throw("Error")
       end
distance (generic function with 2 methods)
```

#### 型パラメータを指定しない構造体とインスタンスの集合
- `Point` 型は, `Point{Float64}` や `Point{SbstractSting}` などのすべてのインスタンスを部分型として含む
- 多重ディスパッチでは, より具体型に近い型を優先する
- パラメトリック型の階層構造

```
julia> Point{Float64} <: Point
true

julia> Point{AbstractString} <: Point
true

```


#### 型パラメータが複数となる場合

```
julia> struct Point2{T,U}
           x::T
           y::U
       end;

julia> p = Point2(2, 3.1)
Point2{Int64, Float64}(2, 3.1)

# 関数の where キーワードにも型パラメータを記述する
julia> function distance(p::Point2{T,U}) where {T,U}
           sqrt(p.x^2 + p.y^2)
       end
distance (generic function with 3 methods)

```


### 2.4.7 パラメトリック型の階層構造
- プリミティブ型の階層構造
    - e.g., `Int < Signed < Integer < Real < Number`
- 包含関係は, `<:` もしくは `>:` で調べる


```
julia> Int <: Number
true

julia> Int >: Number
false

julia> Int <: Float64
false

```

- パラメトリック型の階層構造
    - Julia の型システムにおいて, パラメトリック型は不変
- Kotlin の場合
    - https://maku77.github.io/kotlin/generics/variant.html
    - A が B のサブタイプであったとしても、Point{A} は Point{B} のサブタイプにはならない
    - このような Generic クラスを 不変である (invariant) という
- Go の generics 関連
    - https://zenn.dev/syumai/articles/c42hdg1e0085btnen5hg

```
julia> typeof(Point)
UnionAll

julia> Point{Int} <: Point
true

# プリミティブ型では親子関係があったが
# Point 型では親子関係がない
julia> Point{Int} <: Point{Number}
false

julia> Point{Int} <: Point{Float64}
false

# もし, Point{Any} の値を, Pont{Int} が受け取ってしまったら
# 多重ディスパッチが成り立たなくなる
julia> Point{Int} <: Point{Any}
false

julia> Point{Any} <: Point{Int}
false

# Point{Int} 型は, Point{<:Any} 型に含まれる
julia> Point{Int} <: Point{<:Any}
true
```

#### 型パラメータに対する制約


```
# Point{Int} 型は, Point{<:Any} 型に含まれる
julia> Point{Int} <: Point{<:Any}
true

julia> function distance(p::Point{<:Number})
           # 処理
       end;

# 同じ意味
julia> function distance(p::Point{T<:Number})
           # 処理
       end;

```


### 2.4.8 抽象型のパラメトリック型
- 定義方法
    - `abstract type AbstractPoint{T} end;`
- `AbstractPoint{T}` を親とする型の定義


```
julia> struct Point2D{T} <: AbstractPoint{T}
           x::T
           y::T
       end;
```

#### 親子関係

```
julia> Point2D{Int} <: AbstractPoint
true

julia> Point2D{Int} <: AbstractPoint{Int}
true

julia> Point2D{Int} <: AbstractPoint{Number}
false

julia> Point2D{Int} <: AbstractPoint{<:Number}
true
```
